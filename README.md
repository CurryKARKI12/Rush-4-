# Rush-4-
Mini Shell
Ce projet est une implémentation simple d’un shell minimal en C. Il permet à l'utilisateur d'exécuter des commandes en ligne de commande à l'aide de deux méthodes différentes : system() et exec().

📌 Fonctionnalités
Lecture interactive de commandes depuis l'utilisateur.

Exécution de commandes via :

system() — simple appel système.

exec() — création d'un processus enfant via fork() puis exécution via execvp().

Support de la commande exit pour quitter le shell.

Support de la commande switch pour basculer dynamiquement entre les modes system() et exec().

🗂️ Structure des fichiers

Fichier	Description:

main.c	Point d’entrée du programme. Gère la boucle principale, lit les commandes et exécute selon le mode actif.
exec.c	Implémente l’exécution des commandes en utilisant exec() (et CreateProcess() sous Windows).
system.c	Implémente l’exécution via system().
input.c	Gère la lecture de l’entrée utilisateur, le parsing en arguments, et la libération mémoire.
prompt.c	Affiche l’invite minishell>.
minishell.h	Fichier d’en-tête pour les fonctions et constantes partagées.

⚙️ Compilation
Utilisez gcc pour compiler les fichiers. Voici une commande type (à adapter selon vos fichiers) :

make
Remarque : Ce shell est principalement destiné à Unix/Linux. Pour une compatibilité Windows, des portions spécifiques du code utilisent #ifdef _WIN32.

▶️ Utilisation
Lancez simplement le programme :

bash
./minishell
Commandes intégrées :
exit : quitte le shell.

switch : change la méthode d'exécution (system() ↔ exec()).

Exemple de session :
bash

Bienvenue dans le Mini Shell!
Tapez 'exit' pour quitter ou 'switch' pour changer de mode.

minishell> ls -l
Exécution avec system(): ls -l

minishell> switch
Changement de mode: utilisation de exec()

minishell> ls
Exécution avec exec(): ls

🧼 Gestion mémoire

L’entrée utilisateur est allouée dynamiquement via getline() et doit être libérée.

Chaque argument est dupliqué dynamiquement via strdup() et libéré après exécution.

Une fonction free_args() est utilisée pour nettoyer correctement le tableau d’arguments.

🧪 Limites et améliorations possibles

Ne gère pas la redirection (>, <) ni les pipes (|).

Ne supporte pas encore les variables d’environnement ou l’historique.

La séparation des arguments est très simple (basée sur les espaces seulement).

Une gestion des erreurs plus robuste et un affichage couleur pour l'invite pourraient être ajoutés.

Auteurs:

excute_exec.c                                                   Nana Fourera_ZY
execute_system.c                                                Nana Fourera_ZY
main.c                                                          Housseini_KM
parse.c                                                         Yacouba Assoumane_S
utils.c                                                         Ibrahim_B
Makefile                                                        Housseini_KM
minishell.h                                                     Ibrahim_B
