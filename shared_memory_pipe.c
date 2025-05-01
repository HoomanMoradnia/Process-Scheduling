#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    int shmid;
    key_t key;
    char *shm;
    int pipefd[2];
    pid_t pid;
    char input_string[SHM_SIZE];

    // Generate a unique key for shared memory
    if ((key = ftok("Moradnia.txt", 2004)) == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment to the process
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Create one pipe
    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        exit(1);
    }

    // Fork to create child process
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    // ================== PARENT PROCESS ==================
    if (pid > 0) {
        printf("Parent Process (PID: %d)\n", getpid());
        printf("Enter a string: \n");
        fgets(input_string, SHM_SIZE, stdin);
        input_string[strcspn(input_string, "\n")] = '\0';  // Remove newline

        // Write string to shared memory
        strcpy(shm, input_string);
        printf("Parent: Wrote to shared memory: '%s'\n", shm);

        // Send sync signal to child
        close(pipefd[0]);  // Close read end of pipe
        write(pipefd[1], "OK", 2);
        close(pipefd[1]);  // Done writing

        wait(NULL);  // Wait for child

        // Cleanup
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Parent: Shared memory detached and removed.\n");
    }

    // ================== CHILD PROCESS ==================
    else {
        printf("Child Process (PID: %d)\n", getpid());

        // Wait for sync signal from parent
        close(pipefd[1]);  // Close write end of pipe
        char sync_signal[2];
        read(pipefd[0], sync_signal, 2);  // Block until parent writes
        close(pipefd[0]);

        // Read string from shared memory
        printf("Child: Reading shared memory: '%s'\n", shm);
        int char_count = strlen(shm);
        printf("Child: Character count: %d\n", char_count);

        // Detach from shared memory
        shmdt(shm);
        printf("Child: Shared memory detached.\n");
        exit(0);
    }

    return 0;
}
