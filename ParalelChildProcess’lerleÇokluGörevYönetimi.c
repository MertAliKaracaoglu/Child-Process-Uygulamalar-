#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void create_file() {
    const char *dosya_adi = "test.txt";
    FILE *dosya = fopen(dosya_adi, "w");
    if (dosya == NULL) {
        perror("Dosya olusturulamadi");
        exit(1);
    }
    printf("Dosya olusturuldu: %s\n", dosya_adi);
    fclose(dosya);
}

void write_file() {
    const char *dosya_adi = "test.txt";
    FILE *dosya = fopen(dosya_adi, "a");
    if (dosya == NULL) {
        perror("Dosyaya yazilamadi");
        exit(1);
    }
    fprintf(dosya, "Test yazisi.\n");
    printf("Dosyaya veri eklendi.\n");
    fclose(dosya);
}

void read_file() {
    const char *dosya_adi = "test.txt";
    FILE *dosya = fopen(dosya_adi, "r");
    if (dosya == NULL) {
        perror("Dosya okunamadi");
        exit(1);
    }

    printf("Dosya içerigi:\n");
    char satir[256];
    while (fgets(satir, sizeof(satir), dosya)) {
        printf("%s", satir);
    }
    fclose(dosya);
}

int main() {
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        create_file();
        exit(0);
    } else if (pid1 < 0) {
        perror("Child process olusturulamadi (1)");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        sleep(1);
        write_file();
        exit(0);
    } else if (pid2 < 0) {
        perror("Child process olusturulamadi (2)");
        exit(1);
    }

    pid3 = fork();
    if (pid3 == 0) {
        sleep(2);
        read_file();
        exit(0);
    } else if (pid3 < 0) {
        perror("Child process olusturulamadi (3)");
        exit(1);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Tüm child process'ler tamamlandi.\n");
    return 0;
}
