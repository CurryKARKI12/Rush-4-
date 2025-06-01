#include "minishell.h"

/*
 * Affiche l'invite de commande
 */
void print_prompt(void) {
    printf("minishell> ");
    fflush(stdout); // Force l'affichage immédiat
}

/*
 * Lit une ligne d'entrée depuis stdin
 * Retourne: chaîne allouée dynamiquement ou NULL si erreur/EOF
 */
char *read_input(void) {
    char *input = NULL;    // Pointeur qui sera alloué par getline
    size_t size = 0;       // Taille du buffer (gérée par getline)
    ssize_t nread;         // Nombre de caractères lus

    // getline alloue automatiquement la mémoire nécessaire
    nread = getline(&input, &size, stdin);
    
    // Gestion de l'erreur/EOF
    if (nread == -1) {
        free(input);       // Libération même en cas d'erreur
        return NULL;
    }
    
    // Suppression du saut de ligne final
    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
    }
    
    return input;
}

/*
 * Libère la mémoire allouée pour les arguments
 * Param: args - tableau d'arguments à libérer
 */
void free_args(char **args) {
    if (args == NULL) return;
    
    // Libération de chaque argument
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    // Libération du tableau lui-même
    free(args);
}