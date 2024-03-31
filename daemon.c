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
void registerDaemon(char *name, char *command, char **arguments);
void unregisterDaemon(char *name);
void printDaemonStatus(char *name);
void startDaemon(char *name);
void stopDaemon(char *name);
void rotateLogs(char *name);

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *command;
    char *arguments[MAX_ARGUMENTS];
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
        } else if (strcmp(command, "register") == 0 && numArguments >= 2) {
            registerDaemon(arguments[0], arguments[1], arguments + 2);
        } else if (strcmp(command, "unregister") == 0 && numArguments == 1) {
            unregisterDaemon(arguments[0]);
        } else if (strcmp(command, "status") == 0 && numArguments == 1) {
            printDaemonStatus(arguments[0]);
        } else if (strcmp(command, "start") == 0 && numArguments == 1) {
            startDaemon(arguments[0]);
        } else if (strcmp(command, "stop") == 0 && numArguments == 1) {
            stopDaemon(arguments[0]);
        } else if (strcmp(command, "logrotate") == 0 && numArguments == 1) {
            rotateLogs(arguments[0]);
        } else if (strcmp(command, "quit") == 0 && numArguments == 0) {
            // Add code to terminate daemons and exit
            break;
        } else {
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
    printf("unregister (1 args) Unregister a daemon\n");
    printf("status (1 args) Show the status of a daemon\n");
    printf("start (1 args) Start a daemon\n");
    printf("stop (1 args) Stop a daemon\n");
    printf("logrotate (1 args) Rotate log files for a daemon\n");
}

void registerDaemon(char *name, char *command, char **arguments) {
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
    } else if (pid == 0) {
        // Child process: execute the daemon
        execvp(command, arguments);
        // If execvp fails, perror will be printed and then exit
        perror("Execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process: print registration message
        printf("Daemon %s registered with PID %d\n", name, pid);
    }
}

void unregisterDaemon(char *name) {
    // Add code to unregister a daemon
}

void printDaemonStatus(char *name) {
    // Add code to print daemon status
}

void startDaemon(char *name) {
    // Add code to start a daemon
}

void stopDaemon(char *name) {
    // Add code to stop a daemon
}

void rotateLogs(char *name) {
    // Add code to rotate logs for a daemon
}

