#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10

void execute_command(char *command) {
    char *args[MAX_ARGS];

    // Tokenize the command into arguments
    char *token = strtok(command, " ");
    int arg_count = 0;

    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count] = token;
        token = strtok(NULL, " ");
        arg_count++;
    }

    args[arg_count] = NULL; // Set the last element to NULL for execvp

    // Fork a new process
    pid_t pid = fork();

    if (pid == -1) {
        // Handle fork error
        perror("fork");
    } else if (pid == 0) {
        // Child process
        // Execute the command using execvp
        execvp(args[0], args);

        // If execvp fails, print an error message and exit
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Wait for the child to finish
        wait(NULL);
    }
}

int main(void) {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        // Display the prompt
        printf("simple_shell$ ");

        // Read the command from the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end-of-file condition (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize the input into commands separated by semicolons
        char *command = strtok(input, ";");

        while (command != NULL) {
            // Execute each command
            if (command[0] != '\0') {
                // Check if the command exists
                if (access(command, X_OK) == 0) {
                    execute_command(command);
                } else {
                    fprintf(stderr, "simple_shell: command not found: %s\n", command);
                }
            }
            command = strtok(NULL, ";");
        }
    }

    return 0;
}

