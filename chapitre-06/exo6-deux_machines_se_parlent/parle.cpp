// chapitre-06/exo6-deux_machines_se_parlent/parle.cpp
// Un seul programme, deux roles : serveur ou client.
// Le reseau est gere par NKNetwork ; la console sert a voir l'echange.

#include "NKNetwork/NKNetwork.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace nkentseu;

namespace {

constexpr uint16 PORT = 7777;
constexpr uint32 NOMBRE_MAX_CLIENTS = 8;
constexpr auto DELAI_CONNEXION = std::chrono::seconds(15);

// Petite pause pour ne pas faire tourner les boucles a 100 % du processeur.
void petitePause() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int lancerServeur() {
    NkConnectionManager serveur;

    // Le callback est appele par le fil reseau quand un client est connecte.
    serveur.onPeerConnected = [](NkPeerId pair) {
        std::cout << "[Serveur] Pair connecte : " << pair.value << '\n';
    };

    // Le serveur ecoute sur le port 7777 et accepte jusqu'a huit clients.
    const NkNetResult resultat = serveur.StartServer(PORT, NOMBRE_MAX_CLIENTS);
    if (resultat != NkNetResult::NK_NET_OK) {
        std::cout << "[Serveur] Echec du demarrage : "
                  << net::NkNetResultStr(resultat) << '\n';
        return 1;
    }

    std::cout << "[Serveur] En ecoute sur le port " << PORT << ".\n";

    bool messageRecu = false;

    // DrainAll vide la file des messages a chaque tour de boucle.
    while (serveur.IsRunning() && !messageRecu) {
        NkVector<NkReceiveMsg> messages;
        serveur.DrainAll(messages);

        for (const NkReceiveMsg& message : messages) {
            std::cout << "[Serveur] Message de " << message.from.value << " : ";
            std::cout.write(
                reinterpret_cast<const char*>(message.data),
                static_cast<std::streamsize>(message.size));
            std::cout << '\n';
            messageRecu = true;
        }

        if (!messageRecu) {
            petitePause();
        }
    }

    // On ferme proprement le gestionnaire avant de quitter.
    serveur.Shutdown();
    return messageRecu ? 0 : 1;
}

int lancerClient(const char* adresseServeur) {
    NkConnectionManager client;

    // Le callback tourne dans le fil reseau. Ces deux indicateurs atomiques
    // permettent au fil principal de savoir quand la tentative d'envoi est finie.
    std::atomic<bool> tentativeTerminee{false};
    std::atomic<bool> envoiReussi{false};

    client.onPeerConnected = [&client, &tentativeTerminee, &envoiReussi](NkPeerId pair) {
        std::cout << "[Client] Pair connecte : " << pair.value << '\n';

        // SendTo recoit des octets. sizeof(message) - 1 exclut le caractere nul final.
        constexpr char message[] = "Bonjour serveur !";
        const NkNetResult resultat = client.SendTo(
            pair,
            reinterpret_cast<const uint8*>(message),
            static_cast<uint32>(sizeof(message) - 1));

        if (resultat == NkNetResult::NK_NET_OK) {
            std::cout << "[Client] Message envoye : " << message << '\n';
            envoiReussi.store(true);
        } else {
            std::cout << "[Client] Echec de l'envoi : "
                      << net::NkNetResultStr(resultat) << '\n';
        }

        tentativeTerminee.store(true);
    };

    // Connect lance la connexion ; le callback confirmera qu'elle est etablie.
    const NkNetResult resultat = client.Connect(NkAddress(adresseServeur, PORT));
    if (resultat != NkNetResult::NK_NET_OK) {
        std::cout << "[Client] Impossible de lancer la connexion : "
                  << net::NkNetResultStr(resultat) << '\n';
        return 1;
    }

    std::cout << "[Client] Connexion demandee a " << adresseServeur
              << ':' << PORT << ".\n";

    // La connexion est asynchrone : on laisse au fil reseau le temps de rappeler
    // onPeerConnected, sans envoyer le message trop tot.
    const auto debutAttente = std::chrono::steady_clock::now();
    while (!tentativeTerminee.load() &&
           std::chrono::steady_clock::now() - debutAttente < DELAI_CONNEXION) {
        petitePause();
    }

    if (!tentativeTerminee.load()) {
        std::cout << "[Client] Delai depasse : verifiez l'adresse, le serveur et le pare-feu.\n";
        client.Shutdown();
        return 1;
    }

    if (!envoiReussi.load()) {
        client.Shutdown();
        return 1;
    }

    // Laisser le programme ouvert permet de voir le resultat des deux consoles.
    std::cout << "[Client] Appuyez sur Entree pour fermer le client.\n";
    std::cin.get();

    client.Shutdown();
    return 0;
}

} // namespace

int main(int argc, char* argv[]) {
    // Cette initialisation est necessaire avant d'utiliser le reseau, quel que
    // soit le role choisi en ligne de commande.
    const NkNetResult initialisation = NkSocket::PlatformInit();
    if (initialisation != NkNetResult::NK_NET_OK) {
        std::cout << "Initialisation du reseau impossible : "
                  << net::NkNetResultStr(initialisation) << '\n';
        return 1;
    }

    if (argc < 2) {
        std::cout << "Utilisation : parle serveur\n"
                     "          ou : parle client [IP_DU_SERVEUR]\n"
                     "Sans IP indiquee, le client utilise 127.0.0.1.\n";
        return 1;
    }

    const std::string role = argv[1];

    if (role == "serveur") {
        return lancerServeur();
    }

    if (role == "client") {
        // Sur la meme machine, l'adresse locale suffit. Sur deux machines,
        // passez ici l'adresse IPv4 locale de la machine qui heberge le serveur.
        const char* adresseServeur = (argc >= 3) ? argv[2] : "127.0.0.1";
        return lancerClient(adresseServeur);
    }

    std::cout << "Role inconnu : utilisez 'serveur' ou 'client'.\n";
    return 1;
}
