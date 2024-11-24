#ifndef SERVEUR_H
#define SERVEUR_H

#include <stdbool.h>

// Fonction pour lancer le serveur HTTP
bool lancer_serveur(int port, const char *chemin_html);

#endif // SERVEUR_H
