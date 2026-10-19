// chapitre-06/exo7-la_decouverte/decouverte.cpp
// Découverte de serveurs sur le réseau local avec NKNetwork.
// Lancement : decouverte serveur [nom]  ou  decouverte client

#include "NKWindow/NKMain.h"
#include "NKNetwork/NKNetwork.h"
#include "NKTime/NkChrono.h"

#include <cstring>   // std::strncpy : ServerInfo::name est un tableau de caractères.
#include <iostream>  // Affichage dans la console.

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData donnees{};
    donnees.appName = "Découverte LAN";
    donnees.appVersion = "1.0.0";
    return donnees;
})());

namespace {

constexpr uint16 PORT_SERVEUR = 7777;
constexpr uint32 JOUEURS_MAX = 8;

// Le serveur annonce sa présence périodiquement jusqu'à l'arrêt du programme.
int diffuserServeur(const char* nom) {
    NkDiscovery::ServerInfo info{};

    // Any(7777) représente l'adresse d'écoute du jeu sur toutes les interfaces.
    // Le broadcast lui-même utilise le port de découverte par défaut de NkDiscovery.
    info.addr = NkAddress::Any(PORT_SERVEUR);
    std::strncpy(info.name, nom, sizeof(info.name) - 1);
    info.name[sizeof(info.name) - 1] = '\0'; // Garantit une chaîne terminée.
    info.maxPlayers = 8;

    std::cout << "[Serveur] Nom : " << info.name << '\n'
              << "[Serveur] Places disponibles : " << info.maxPlayers << '\n'
              << "[Serveur] Diffusion toutes les 2 secondes. Ctrl+C pour arrêter.\n";

    while (true) {
        const NkNetResult resultat = NkDiscovery::Broadcast(info);

        if (resultat == NkNetResult::NK_NET_OK) {
            std::cout << "[Serveur] Présence diffusée : " << info.name << '\n';
        } else {
            // On garde le serveur vivant : le prochain essai aura lieu après la pause.
            std::cout << "[Serveur] Échec de diffusion : "
                      << net::NkNetResultStr(resultat) << '\n';
        }

        // Pas de NkAtomic ici : cette boucle est séquentielle, sans état partagé entre fils.
        // NkChrono appartient à NKTime et fournit la pause sans std::chrono.
        NkChrono::SleepMilliseconds(2000);
    }
}

// Le client écoute six secondes, puis affiche les résultats fournis par NkDiscovery.
int rechercherServeurs() {
    NkVector<NkDiscovery::ServerInfo> trouves;

    std::cout << "[Client] Recherche des serveurs pendant 6 secondes...\n";
    const NkNetResult resultat = NkDiscovery::Listen(6000, trouves);

    if (resultat != NkNetResult::NK_NET_OK) {
        std::cout << "[Client] Échec de la recherche : "
                  << net::NkNetResultStr(resultat) << '\n';
        return 1;
    }

    if (trouves.IsEmpty()) {
        std::cout << "[Client] Aucun serveur trouvé. Vérifie le réseau local et le pare-feu.\n";
        return 0;
    }

    std::cout << "[Client] Serveurs trouvés : " << trouves.Size() << '\n';

    for (usize i = 0; i < trouves.Size(); ++i) {
        const NkDiscovery::ServerInfo& serveur = trouves[i];
        const NkString adresse = serveur.addr.ToString();

        std::cout << "  " << (i + 1) << ". " << adresse.CStr()
                  << " — " << serveur.name
                  << " (maximum : " << serveur.maxPlayers << " joueurs)\n";
    }

    return 0;
}

} // namespace

int nkmain(const NkEntryState& state) {
    // L'initialisation plateforme doit précéder tout usage du réseau.
    const NkNetResult initialisation = NkSocket::PlatformInit();
    if (initialisation != NkNetResult::NK_NET_OK) {
        std::cout << "[Réseau] Initialisation impossible : "
                  << net::NkNetResultStr(initialisation) << '\n';
        return 1;
    }

    // Les arguments sont fournis par NkMain dans un NkVector<NkString>.
    // Le premier argument utilisateur choisit le rôle : serveur ou client.
    if (state.args.Size() < 2) {
        std::cout << "Utilisation :\n"
                  << "  decouverte serveur [nom_du_serveur]\n"
                  << "  decouverte client\n";
        NkSocket::PlatformShutdown();
        return 1;
    }

    int codeRetour = 0;

    if (state.args[1] == "serveur") {
        const char* nom = "Salle Nkentseu";
        if (state.args.Size() >= 3) {
            nom = state.args[2].CStr();
        }
        // Cette boucle tourne tant que l'utilisateur n'arrête pas le serveur.
        return diffuserServeur(nom);
    }

    if (state.args[1] == "client") {
        codeRetour = rechercherServeurs();
    } else {
        std::cout << "Rôle inconnu. Utilise 'serveur' ou 'client'.\n";
        codeRetour = 1;
    }

    NkSocket::PlatformShutdown();
    return codeRetour;
}
