// yoyo_daemon.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>  // Include for file system operations

#define LOG_DIR "logs"    // Define log directory
#define LOG_FILE "yoyo.log"

void createLogDirIfNotExists() {
    struct stat st = { 0 };
    if (stat(LOG_DIR, &st) == -1) {
        mkdir(LOG_DIR, 0700);
    }
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Create log directory if not exists
    createLogDirIfNotExists();

    // Open the log file
    FILE* log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

    // Print startup message to the log
    fprintf(log_file, "Yoyo daemon started\n");

    // Determine random sleep duration (between 1 and 10 seconds)
    int sleep_duration = rand() % 10 + 1;

    // Sleep for the determined duration
    sleep(sleep_duration);

    // Randomly decide whether to exit or crash
    int decision = rand() % 2;
    if (decision == 0) {
        // Exit gracefully
        fprintf(log_file, "Yoyo daemon exiting gracefully\n");
        fclose(log_file);
        exit(EXIT_SUCCESS);
    }
    else {
        // Simulate crash (divide by zero)
        int crash_trigger = 1 / decision;
    }

    // We'll never reach this point, but closing the log file is good practice
    fclose(log_file);

    return 0;
}
