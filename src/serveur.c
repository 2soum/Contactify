#include "serveur.h"
#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

// Fonction pour lire un fichier
static char *lire_fichier(const char *chemin, long *taille) {
    FILE *fichier = fopen(chemin, "r");
    if (!fichier) {
        perror("Erreur d'ouverture de fichier");
        return NULL;
    }

    fseek(fichier, 0, SEEK_END);
    *taille = ftell(fichier);
    rewind(fichier);

    char *contenu = malloc(*taille + 1);
    if (!contenu) {
        perror("Erreur allocation mémoire");
        fclose(fichier);
        return NULL;
    }

    fread(contenu, 1, *taille, fichier);
    contenu[*taille] = '\0';
    fclose(fichier);
    return contenu;
}

// Déterminer le type MIME en fonction de l'extension
const char *determiner_content_type(const char *chemin) {
    if (strstr(chemin, ".css")) return "text/css";
    if (strstr(chemin, ".js")) return "application/javascript";
    if (strstr(chemin, ".html")) return "text/html";
    if (strstr(chemin, ".png")) return "image/png";
    if (strstr(chemin, ".jpg") || strstr(chemin, ".jpeg")) return "image/jpeg";
    if (strstr(chemin, ".gif")) return "image/gif";
    return "text/plain";
}

// Fonction pour gérer les requêtes
static int gerer_requete(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **ptr) {
    char chemin[BUFFER_SIZE];
    snprintf(chemin, BUFFER_SIZE, "./ui%s", url);

    // Si aucun fichier n'est spécifié, servir index.html
    if (strcmp(url, "/") == 0) {
        strcpy(chemin, "./ui/index.html");
    }

    long taille = 0;
    char *contenu = lire_fichier(chemin, &taille);
    if (!contenu) {
        const char *message = "404 Not Found";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(message),
                                                                        (void *)message, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    }

    // Déterminer le Content-Type
    const char *content_type = determiner_content_type(chemin);

    struct MHD_Response *response = MHD_create_response_from_buffer(taille,
                                                                    contenu, MHD_RESPMEM_MUST_FREE);
    MHD_add_response_header(response, "Content-Type", content_type);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

// Fonction pour lancer le serveur
bool lancer_serveur(int port, const char *chemin_html) {
    struct MHD_Daemon *serveur;

    serveur = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL,
                               &gerer_requete, (void *)chemin_html, MHD_OPTION_END);
    if (!serveur) {
        fprintf(stderr, "Erreur : Impossible de démarrer le serveur HTTP.\n");
        return false;
    }

    printf("Serveur lancé sur http://localhost:%d\n", port);
    printf("Appuyez sur Entrée pour arrêter le serveur...\n");
    getchar(); // Attend une entrée utilisateur pour arrêter le serveur

    MHD_stop_daemon(serveur);
    return true;
}


