#include "minishell.h"

/*
 * Exécute la commande avec la méthode system()
 * Param: args - tableau d'arguments (args[0] = commande)
 * Retourne: 1 pour continuer, 0 pour quitter
 */
int execute_with_system(char **args) {
    // Commande interne "exit"
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    // Construction de la commande complète
    char command[MAX_INPUT_SIZE] = {0};
    for (int i = 0; args[i] != NULL && i < MAX_ARGS; i++) {
        strcat(command, args[i]);
        if (args[i+1] != NULL) {
            strcat(command, " ");
        }
    }

    printf("Execution avec system(): %s\n", command);
    
    // Exécution avec system()
    int status = system(command);
    
    // Vérification du statut de retour
    if (status == -1) {
        perror("Erreur dans system()");
    } else {
        printf("Commande terminee avec le code: %d\n", status);
    }

    return 1;
}