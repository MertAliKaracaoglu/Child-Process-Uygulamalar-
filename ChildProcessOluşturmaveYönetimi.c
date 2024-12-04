#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int durum;

    pid = fork();

    if (pid < 0) { 
        perror("Fork basarisizz");
        exit(1);
    } else if (pid == 0) {
        printf("Child process calisiyor\n");
        execlp("cat", "cat", "text.txt", (char *)NULL);
        perror("execlp basarisiz");
        exit(1);
    } else {
        printf("Parent process, child process'in bitmesini bekliyor\n");
        wait(&durum);

        if (WIFEXITED(durum)) {
            printf("\nChild process başarili. Cikis durumu: %d\n", WEXITSTATUS(durum));
        } else {
            printf("Child process normal şekilde sonlanmadi.\n");
        }
    }

    return 0;
}
