#include <iostream>

#include "NKWindow/NKMain.h"
#include "NKNetwork/NKNetwork.h"
#include "NKCore/NkAtomic.h"
#include "NKTime/NkChrono.h"
#include "NKFileSystem/NkFile.h"

using namespace nkentseu;

// Le même exécutable joue les deux rôles :
//   allerretour serveur
//   allerretour client 127.0.0.1
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData app{};
    app.appName = "Mesure du temps aller-retour";
    app.appVersion = "1.0.0";
    return app;
})());

namespace {
    constexpr uint16 PORT_RESEAU = 7777;
    constexpr uint32 NOMBRE_MESURES = 100;
    constexpr float64 DELAI_MAX_CONNEXION_MS = 10000.0;
    constexpr float64 DELAI_MAX_REPONSE_MS = 5000.0;
    constexpr float64 ALPHA = 0.125;

    // Le callback de connexion est exécuté par le fil réseau.
    // Les valeurs partagées avec le fil principal sont donc atomiques.
    NkAtomic<bool> gConnecte{false};
    NkAtomic<uint64> gIdentifiantPair{0};

    // Le numéro est encodé sur quatre octets, dans un ordre connu.
    // Ainsi, le serveur peut renvoyer exactement le même message sans le modifier.
    void EncoderNumero(uint32 numero, uint8 donnees[4]) {
        donnees[0] = static_cast<uint8>(numero & 0xFFu);
        donnees[1] = static_cast<uint8>((numero >> 8) & 0xFFu);
        donnees[2] = static_cast<uint8>((numero >> 16) & 0xFFu);
        donnees[3] = static_cast<uint8>((numero >> 24) & 0xFFu);
    }

    uint32 LireNumero(const uint8 donnees[4]) {
        return static_cast<uint32>(donnees[0])
             | (static_cast<uint32>(donnees[1]) << 8)
             | (static_cast<uint32>(donnees[2]) << 16)
             | (static_cast<uint32>(donnees[3]) << 24);
    }

    int LancerServeur() {
        if (NkSocket::PlatformInit() != NkNetResult::NK_NET_OK) {
            std::cout << "Erreur : initialisation du reseau impossible.\n";
            return 1;
        }

        NkConnectionManager serveur;
        serveur.onPeerConnected = [](NkPeerId pair) {
            std::cout << "Pair connecte : " << pair.value << '\n';
        };

        if (serveur.StartServer(PORT_RESEAU, 1) != NkNetResult::NK_NET_OK) {
            std::cout << "Erreur : impossible de demarrer le serveur.\n";
            serveur.Shutdown();
            NkSocket::PlatformShutdown();
            return 1;
        }

        std::cout << "Serveur pret sur le port " << PORT_RESEAU << ".\n";
        std::cout << "Il renverra les 100 messages du client, puis s'arretera.\n";

        uint32 messagesRenvoyes = 0;
        NkChrono attenteMaximale;

        // Le fil réseau reçoit les paquets. Cette boucle applicative les vide,
        // puis renvoie chaque message, sans changer son contenu.
        while (serveur.IsRunning()
               && messagesRenvoyes < NOMBRE_MESURES
               && attenteMaximale.Elapsed().milliseconds < 180000.0) {
            NkVector<NkReceiveMsg> messages;
            serveur.DrainAll(messages);

            for (usize i = 0; i < messages.Size(); ++i) {
                const NkReceiveMsg& message = messages[i];

                if (serveur.SendTo(message.from, message.data, message.size)
                    == NkNetResult::NK_NET_OK) {
                    ++messagesRenvoyes;
                    std::cout << "Echo " << messagesRenvoyes
                              << "/" << NOMBRE_MESURES
                              << " envoye au pair " << message.from.value << '\n';
                }
            }

            // Une petite pause évite de faire tourner cette boucle à plein régime.
            NkChrono::SleepMilliseconds(1);
        }

        serveur.Shutdown();
        NkSocket::PlatformShutdown();
        std::cout << "Serveur termine : " << messagesRenvoyes
                  << " messages renvoyes.\n";
        return (messagesRenvoyes == NOMBRE_MESURES) ? 0 : 1;
    }

    int LancerClient(const char* adresseServeur) {
        if (NkSocket::PlatformInit() != NkNetResult::NK_NET_OK) {
            std::cout << "Erreur : initialisation du reseau impossible.\n";
            return 1;
        }

        // Le callback ne fait que publier le pair et signaler la connexion.
        // Les mesures et les fichiers restent gérés par le fil principal.
        NkConnectionManager client;
        client.onPeerConnected = [](NkPeerId pair) {
            gIdentifiantPair.Store(pair.value, NkMemoryOrder::NK_RELAXED);
            gConnecte.Store(true, NkMemoryOrder::NK_RELEASE);
        };

        const NkAddress adresse(adresseServeur, PORT_RESEAU);
        if (client.Connect(adresse) != NkNetResult::NK_NET_OK) {
            std::cout << "Erreur : impossible de lancer la connexion vers "
                      << adresseServeur << ".\n";
            client.Shutdown();
            NkSocket::PlatformShutdown();
            return 1;
        }

        std::cout << "Connexion en cours vers " << adresseServeur
                  << ':' << PORT_RESEAU << "...\n";

        NkChrono delaiConnexion;
        while (!gConnecte.Load(NkMemoryOrder::NK_ACQUIRE)
               && delaiConnexion.Elapsed().milliseconds < DELAI_MAX_CONNEXION_MS) {
            NkChrono::SleepMilliseconds(1);
        }

        if (!gConnecte.Load(NkMemoryOrder::NK_ACQUIRE)) {
            std::cout << "Erreur : delai de connexion depasse.\n";
            client.Shutdown();
            NkSocket::PlatformShutdown();
            return 1;
        }

        const NkPeerId pair{gIdentifiantPair.Load(NkMemoryOrder::NK_RELAXED)};
        std::cout << "Connecte au pair " << pair.value << ".\n";
        std::cout << "Debut des 100 mesures RTT...\n";

        float64 mesures[NOMBRE_MESURES] = {};

        for (uint32 i = 0; i < NOMBRE_MESURES; ++i) {
            const uint32 numeroAttendu = i + 1;
            uint8 donnees[4] = {};
            EncoderNumero(numeroAttendu, donnees);

            // Le chronometre démarre juste avant l'envoi.
            // On n'envoie rien d'autre avant d'avoir reçu cet écho.
            NkChrono chronoRTT;
            if (client.SendTo(pair, donnees, 4) != NkNetResult::NK_NET_OK) {
                std::cout << "Erreur d'envoi pour le message " << numeroAttendu << ".\n";
                client.Shutdown();
                NkSocket::PlatformShutdown();
                return 1;
            }

            bool reponseRecue = false;
            NkChrono delaiReponse;

            while (!reponseRecue
                   && delaiReponse.Elapsed().milliseconds < DELAI_MAX_REPONSE_MS) {
                NkVector<NkReceiveMsg> messages;
                client.DrainAll(messages);

                for (usize j = 0; j < messages.Size(); ++j) {
                    const NkReceiveMsg& message = messages[j];

                    // La réponse doit venir du serveur et porter le numéro demandé.
                    if (message.from.value == pair.value
                        && message.size == 4
                        && LireNumero(message.data) == numeroAttendu) {
                        mesures[i] = chronoRTT.Elapsed().milliseconds;
                        reponseRecue = true;
                        break;
                    }
                }

                if (!reponseRecue) {
                    NkChrono::SleepMilliseconds(1);
                }
            }

            if (!reponseRecue) {
                std::cout << "Delai depasse pour le message " << numeroAttendu
                          << ". Les fichiers de mesures ne seront pas presentes comme complets.\n";
                client.Shutdown();
                NkSocket::PlatformShutdown();
                return 1;
            }

            std::cout << "Mesure " << numeroAttendu << ": "
                      << NkString::Format("%.3f ms", mesures[i]).CStr() << '\n';
        }

        // On demande les statistiques après les 100 échanges : le champ rttMs
        // est l'estimation propre au moteur, et non notre chronométrage applicatif.
        net::NkConnectionStats statistiques{};
        bool statsDisponibles = false;
        NkChrono attenteStats;
        while (!statsDisponibles && attenteStats.Elapsed().milliseconds < 2000.0) {
            statsDisponibles = client.GetConnectionStats(pair, statistiques);
            if (!statsDisponibles) {
                NkChrono::SleepMilliseconds(10);
            }
        }

        if (!statsDisponibles) {
            std::cout << "Erreur : les statistiques du moteur ne sont pas disponibles.\n";
            client.Shutdown();
            NkSocket::PlatformShutdown();
            return 1;
        }

        // Calcul des statistiques à partir des 100 valeurs réellement mesurées.
        float64 somme = 0.0;
        float64 minimum = mesures[0];
        float64 maximum = mesures[0];
        float64 srtt = 100.0; // Valeur initiale imposée par l'énoncé.

        for (uint32 i = 0; i < NOMBRE_MESURES; ++i) {
            const float64 rtt = mesures[i];
            somme += rtt;
            if (rtt < minimum) minimum = rtt;
            if (rtt > maximum) maximum = rtt;

            // Lissage exponentiel : une mise à jour après chaque mesure.
            srtt = (1.0 - ALPHA) * srtt + ALPHA * rtt;
        }

        const float64 moyenne = somme / static_cast<float64>(NOMBRE_MESURES);
        const float64 rttMoteur = statistiques.rttMs;
        const float64 ecart = (rttMoteur >= srtt) ? (rttMoteur - srtt) : (srtt - rttMoteur);

        // Le rapport précise le contexte : une mesure loopback n'est pas une mesure LAN.
        const bool essaiSurUneMachine = NkString(adresseServeur) == "127.0.0.1"
                                     || NkString(adresseServeur) == "localhost";
        const char* contexteMachines = essaiSurUneMachine
            ? "Essai sur une seule machine via loopback : le trajet ne traverse pas le LAN."
            : "Client configure pour joindre l'adresse serveur indiquee sur le reseau local.";

        // Le fichier ne contient que les cent valeurs, une par ligne.
        NkFile fichierMesures("chapitre-06/exo9-l_aller_retour/mesures-rtt.txt", NkFileMode::NK_WRITE);
        if (!fichierMesures.IsOpen()) {
            std::cout << "Erreur : impossible de creer mesures-rtt.txt.\n";
            client.Shutdown();
            NkSocket::PlatformShutdown();
            return 1;
        }

        for (uint32 i = 0; i < NOMBRE_MESURES; ++i) {
            const NkString ligne = NkString::Format("%.3f", mesures[i]);
            if (!fichierMesures.WriteLine(ligne.CStr())) {
                std::cout << "Erreur pendant l'ecriture de mesures-rtt.txt.\n";
                client.Shutdown();
                NkSocket::PlatformShutdown();
                return 1;
            }
        }
        fichierMesures.Flush();

        NkFile rapport("chapitre-06/exo9-l_aller_retour/rtt.txt", NkFileMode::NK_WRITE);
        if (!rapport.IsOpen()) {
            std::cout << "Erreur : impossible de creer rtt.txt.\n";
            client.Shutdown();
            NkSocket::PlatformShutdown();
            return 1;
        }

        rapport.WriteLine(NkString::Format("Moyenne : %.3f ms", moyenne).CStr());
        rapport.WriteLine(NkString::Format("Minimum : %.3f ms", minimum).CStr());
        rapport.WriteLine(NkString::Format("Maximum : %.3f ms", maximum).CStr());
        rapport.WriteLine(NkString::Format("Lissée : %.3f ms", srtt).CStr());
        rapport.WriteLine(NkString::Format("Moteur : %.3f ms", rttMoteur).CStr());
        rapport.WriteLine(NkString::Format(
            "Écart : %.3f ms entre le lissage applicatif et l'estimation du moteur. "
            "Notre chrono mesure l'envoi d'un message jusqu'a son echo. Le fil reseau "
            "du moteur, dans NetThreadLoop, sonde les sockets et met a jour les connexions; "
            "l'estimation rttMs suit les mesures du protocole et son propre lissage. "
            "La cadence de traitement et le lissage expliquent qu'elles ne soient pas identiques. %s",
            ecart, contexteMachines).CStr());
        rapport.Flush();

        std::cout << "\n=== RESULTAT ===\n";
        std::cout << NkString::Format("Moyenne : %.3f ms\n", moyenne).CStr();
        std::cout << NkString::Format("Minimum : %.3f ms\n", minimum).CStr();
        std::cout << NkString::Format("Maximum : %.3f ms\n", maximum).CStr();
        std::cout << NkString::Format("Lissée : %.3f ms\n", srtt).CStr();
        std::cout << NkString::Format("Moteur : %.3f ms\n", rttMoteur).CStr();
        std::cout << NkString::Format("Écart : %.3f ms\n", ecart).CStr();
        std::cout << "Les fichiers chapitre-06/exo9-l_aller_retour/mesures-rtt.txt et rtt.txt ont ete actualises.\n";

        client.Shutdown();
        NkSocket::PlatformShutdown();
        return 0;
    }
}

int nkmain(const NkEntryState& state) {
    if (state.args.Size() < 2) {
        std::cout << "Utilisation :\n"
                  << "  allerretour serveur\n"
                  << "  allerretour client 127.0.0.1\n";
        return 1;
    }

    if (state.args[1] == "serveur") {
        return LancerServeur();
    }

    if (state.args[1] == "client") {
        const char* adresse = "127.0.0.1";
        if (state.args.Size() >= 3) {
            adresse = state.args[2].CStr();
        }
        return LancerClient(adresse);
    }

    std::cout << "Role inconnu : utilisez serveur ou client.\n";
    return 1;
}
