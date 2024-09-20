
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_SIZE 128

void handle_sigint(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}



int main(void) {
    char *input;
    char **commands;

    signal(SIGINT, handle_sigint);

    while (1) {
        input = readline("bitwise # ");
        if (!input) break;
        if (strlen(input) > 0) add_history(input);

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        commands = malloc(64 * sizeof(char *));
        char *command = strtok(input, "|");
        int i = 0;
        while (command) {
            commands[i++] = command;
            command = strtok(NULL, "|");
        }
        commands[i] = NULL;

        execute_commands(commands);

        free(commands);
        free(input);
    }
    rl_clear_history();
    return 0;
}


