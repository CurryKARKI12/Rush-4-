#include "minishell.h"

/*
 * Exécute la commande avec la méthode exec()
 * Param: args - tableau d'arguments (args[0] = commande)
 * Retourne: 1 pour continuer, 0 pour quitter
 */
int execute_with_exec(char **args) {
    // Commande interne "exit"
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    printf("Execution avec exec(): ");
    for (int i = 0; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

#ifdef _WIN32
    /* Version Windows */
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmd_line[MAX_INPUT_SIZE] = {0};

    // Construction de la ligne de commande
    for (int i = 0; args[i] != NULL; i++) {
        strcat(cmd_line, args[i]);
        strcat(cmd_line, " ");
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Création du processus
    if (!CreateProcess(
        NULL,           // Nom de l'application
        cmd_line,       // Ligne de commande
        NULL,           // Attributs de sécurité processus
        NULL,           // Attributs de sécurité thread
        FALSE,          // Héritage des handles
        0,              // Flags de création
        NULL,           // Environnement
        NULL,           // Répertoire courant
        &si,            // STARTUPINFO
        &pi             // PROCESS_INFORMATION
    )) {
        fprintf(stderr, "Erreur CreateProcess (%lu)\n", (unsigned long)GetLastError());
        return 1;
    }

    // Attente de la fin du processus
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Récupération du code de sortie
    DWORD exit_code;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    printf("Commande terminee avec le code: %lu\n", (unsigned long)exit_code);

    // Fermeture des handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

#else
    /* Version Unix/Linux */
    pid_t pid = fork();
    
    if (pid == 0) {
        // Processus enfant
        execvp(args[0], args);
        
        // Si on arrive ici, execvp a échoué
        perror("Erreur dans execvp");
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0) {
        // Erreur lors du fork
        perror("Erreur dans fork");
    } 
    else {
        // Processus parent - attend la fin de l'enfant
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Commande terminee avec le code: %d\n", WEXITSTATUS(status));
        }
    }
#endif

    return 1;
}