#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int durum;

    pid = fork();

    if (pid < 0) { 
        perror("Fork basarisiz");
        exit(1);
    } else if (pid == 0) {
        printf("Child process calisiyor.\n");

        FILE *dosya = fopen("text.txt", "r");
        if (dosya == NULL) {
            perror("Dosya acilamadi. Hata: ");
            printf("Child process abort() cagiriyor\n");
            abort(); 
        }

        printf("Dosya acildi\n");
        fclose(dosya);
        exit(0); 
    } else {
        printf("Parent process, child process'in bitmesini bekliyor\n");
        wait(&durum);

        if (WIFEXITED(durum)) {
            printf("Child process normal bir sekilde sonlandi. Cikis durumu: %d\n", WEXITSTATUS(durum));
        } else if (WIFSIGNALED(durum)) {
            printf("Child process bir sinyal ile sonlandi. Sinyal numarasi: %d\n", WTERMSIG(durum));
            if (WTERMSIG(durum) == SIGABRT) {
                printf("Sinyal turu: SIGABRT (abort cagrildi)\n");
            }
        } else {
            printf("Child process beklenmeyen bir sekilde sonlandi.\n");
        }
    }

    return 0;
}
