#include "minishell.h"

int main(void) {
    char *input;        // Stocke l'entrée utilisateur
    char **args;        // Tableau d'arguments
    int status = 1;     // 1 = continuer, 0 = quitter
    int use_system = 1; // 1 = utiliser system(), 0 = utiliser exec()

    printf("Bienvenue dans le Mini Shell!\n");
    printf("Mode d'execution: %s\n", use_system ? "system()" : "exec()");
    printf("Tapez 'exit' pour quitter ou 'switch' pour changer de mode.\n\n");

    while (status) {
        print_prompt(); //Affiche quelque chose comme minishell> dans ce cas
        input = read_input(); //lis l'entrée de l'utilisateur depuis l'entrée standard
        
        // Gestion de Ctrl+D (EOF)
        if (input == NULL) {
            printf("\n");
            break;
        }
        
        // Parser l'entrée en arguments en utilisant généralement strtok()
        args = parse_input(input); 
        
        // Si la commande n'est pas vide et si elle l'est alors on n'execute rien !
        if (args[0] != NULL) {
            // Commande spéciale pour changer de mode / strcmp permet de comparer deux chaines de caractéres si egal on retourne 0
            if (strcmp(args[0], "switch") == 0) {  //si switch alors on inverse le mode d'execution 
                use_system = !use_system;
                printf("Changement de mode: utilisation de %s\n", 
                      use_system ? "system()" : "exec()");
            } 
            // Exécution normale donc si ce n'est pas switch cest une commande normale
            else {
                if (use_system) {
                    status = execute_with_system(args);
                } else {
                    status = execute_with_exec(args);
                }
            }
        }
        
        // Nettoyage mémoire
        free(input);
        free_args(args);
    }

    printf("Au revoir!\n");
    return 0;
}