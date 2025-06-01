#include "minishell.h"

/*
 * Découpe la commande en arguments séparés
 * Param: input - la commande entrée par l'utilisateur
 * Retourne: tableau de chaînes alloué dynamiquement (NULL terminé)
 */
char **parse_input(char *input) {
    // Allocation du tableau d'arguments
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (args == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    char *token;  // Pointeur vers le token courant
    int i = 0;    // Index dans le tableau d'arguments

    // Découpage de la chaîne en utilisant les espaces comme séparateurs
    token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        // Copie du token dans le tableau
        args[i] = strdup(token);
        if (args[i] == NULL) {
            perror("Erreur de duplication de chaîne");
            exit(EXIT_FAILURE);
        }
        i++;
        // Passage au token suivant
        token = strtok(NULL, " ");
    }
    
    // Marquage de la fin du tableau
    args[i] = NULL;

    return args;
}