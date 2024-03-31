#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 32

// Function prototypes
void printHelp();
void registerDaemon(char* name, char* command, char** arguments);

int main() {
    char input[MAX_COMMAND_LENGTH];
    char* command;
    char* arguments[MAX_ARGUMENTS];
    int numArguments;

    while (1) {
        printf("legion> ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Tokenize input command and arguments
        command = strtok(input, " ");
        if (command == NULL) continue;  // Ignore empty input or only whitespace

        // Tokenize remaining arguments
        numArguments = 0;
        while ((arguments[numArguments] = strtok(NULL, " ")) != NULL) {
            numArguments++;
        }

        // Process the command
        if (strcmp(command, "help") == 0) {
            printHelp();
        }
        else if (strcmp(command, "register") == 0 && numArguments >= 2) {
            registerDaemon(arguments[0], arguments[1], arguments + 2);
        }
        else if (strcmp(command, "quit") == 0 && numArguments == 0) {
            // Add code to terminate daemons and exit
            break;
        }
        else {
            printf("Error: Unknown command or incorrect arguments.\n");
        }
    }

    return 0;
}

void printHelp() {
    printf("Available commands:\n");
    printf("help (0 args) Print this help message\n");
    printf("quit (0 args) Quit the program\n");
    printf("register (2+ args) Register a daemon\n");
}

void registerDaemon(char* name, char* command, char** arguments) {
    // Here we would typically store the daemon information in some data structure
    // For simplicity, let's print the information for now

    printf("Registering daemon:\n");
    printf("Name: %s\n", name);
    printf("Command: %s\n", command);

    // Print any additional arguments
    printf("Arguments:\n");
    for (int i = 0; arguments[i] != NULL; i++) {
        printf("- %s\n", arguments[i]);
    }

    // Fork a child process to execute the daemon
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    }
    else if (pid == 0) {
        // Child process: execute the daemon
        execl("./daemons/yoyo/yoyo_daemon", "./daemons/yoyo/yoyo_daemon", NULL);
        // If execl fails, perror will be printed and then exit
        perror("Execl failed");
        exit(EXIT_FAILURE);
    }
    else {
        // Parent process: print registration message
        printf("Daemon %s registered with PID %d\n", name, pid);
    }
}
