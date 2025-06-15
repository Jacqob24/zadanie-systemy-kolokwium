#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "client.h"

static char client_name[100];

void handle_sigterm(int sig) {
    printf("%s: Terminating...\n", client_name);
    _exit(0);
}

void handle_sigusr2(int sig) {
    printf("%s: Acknowledged\n", client_name);
}

void handle_sigint(int sig) {
    printf("%s: Shutting down\n", client_name);
    _exit(0);
}

void init_client(const char* name, int pipefd[]) {
    strcpy(client_name, name);
    printf("%s: Client initialized\n", name);

    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR2, handle_sigusr2);
    signal(SIGINT, handle_sigint);

    char buffer[100];
    close(pipefd[1]);

    while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "Hello clients! Who are you?") == 0) {
            printf("I am %s\n", client_name);
        } else if (strcmp(buffer, "Hello clients! Your PID?") == 0) {
            printf("%s: PID is %d\n", client_name, getpid());
        }
    }
}
