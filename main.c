#include <stdio.h>
#include "serveur.h"
#include <stdlib.h>
void ouvrir_navigateur(int port) {
#ifdef _WIN32
    // Commande pour Windows
    char commande[256];
    sprintf(commande, "start http://localhost:%d", port);
    system(commande);
#elif __APPLE__
    // Commande pour macOS
    char commande[256];
    sprintf(commande, "open http://localhost:%d", port);
    system(commande);
#elif __linux__
    // Commande pour Linux
    char commande[256];
    sprintf(commande, "xdg-open http://localhost:%d", port);
    system(commande);
#else
    fprintf(stderr, "Système non supporté pour ouvrir le navigateur.\n");
#endif
}


int main() {
    int port = 8080;

    printf("Démarrage de l'application...\n");

    // Lancer le serveur
    if (!lancer_serveur(port, "ui/index.html")) {
        fprintf(stderr, "Erreur : Impossible de démarrer le serveur.\n");
        return 1;
    }

    // Ouvrir le navigateur
    ouvrir_navigateur(port);

    printf("Serveur lancé sur http://localhost:%d\n", port);


    return 0;
}


