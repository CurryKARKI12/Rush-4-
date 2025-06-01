#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#else
#include <sys/wait.h>
#include <unistd.h>
#endif

#define MAX_INPUT_SIZE 1024  // Taille maximale de l'entrée utilisateur
#define MAX_ARGS 64          // Nombre maximal d'arguments par commande

/* 
 * Lit l'entrée utilisateur depuis stdin
 * Retourne: chaîne allouée dynamiquement ou NULL si erreur/EOF
 */
char *read_input(void);

/*
 * Découpe la commande en arguments séparés
 * Param: input - la commande entrée par l'utilisateur
 * Retourne: tableau de chaînes alloué dynamiquement (NULL terminé)
 */
char **parse_input(char *input);

/*
 * Exécute la commande avec la méthode system()
 * Param: args - tableau d'arguments (args[0] = commande)
 * Retourne: 1 pour continuer, 0 pour quitter
 */
int execute_with_system(char **args);

/*
 * Exécute la commande avec la méthode exec()
 * Param: args - tableau d'arguments (args[0] = commande)
 * Retourne: 1 pour continuer, 0 pour quitter
 */
int execute_with_exec(char **args);

/*
 * Affiche l'invite de commande
 */
void print_prompt(void);

/*
 * Libère la mémoire allouée pour les arguments
 * Param: args - tableau d'arguments à libérer
 */
void free_args(char **args);

#endif