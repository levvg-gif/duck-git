
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

// ANSI
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

void print_help() {
    printf("Использование: duck [опции] [сообщение]\n");
    printf("Опции:\n");
    printf("  -m, --message TEXT  Что скажет утка\n");
    printf("  -s, --sleeping      Утка спит (-_-)\n");
    printf("  -a, --angry         Утка злится (ò_ó)\n");
    printf("  -d, --dead          Утка... всё (x_x)\n");
    printf("  -r, --rainbow       Радужная утка\n");
    printf("  -b, --blue          Синяя утка\n");
    printf("  -v, --version       Версия и лицензия\n");
    printf("  -h, --help          Справка\n");
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    char message[256] = "Кря!";
    char *eye = "o";
    char *color = YELLOW;
    int rainbow = 0;

    static struct option long_options[] = {
        {"message",  required_argument, 0, 'm'},
        {"sleeping", no_argument,       0, 's'},
        {"angry",    no_argument,       0, 'a'},
        {"dead",     no_argument,       0, 'd'},
        {"rainbow",  no_argument,       0, 'r'},
        {"blue",     no_argument,       0, 'b'},
        {"version",  no_argument,       0, 'v'},
        {"help",     no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "m:sadbrvh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'm': strncpy(message, optarg, 255); break;
            case 's': eye = "-"; break;
            case 'a': eye = "ò"; break;
            case 'd': eye = "x"; break;
            case 'r': rainbow = 1; break;
            case 'b': color = BLUE; break;
            case 'v': 
                printf("duck version 1.1\nLicense: MIT\nCreated by a legend (Sw0ReX).\n"); 
                return 0;
            case 'h': print_help(); return 0;
            default: return 1;
        }
    }

    if (geteuid() == 0) {
        const char *user_home;
        if (getenv("SUDO_USER")) {
            struct passwd *pw = getpwnam(getenv("SUDO_USER"));
            user_home = pw->pw_dir;
        } else {
            user_home = getenv("HOME");
        }

        if (user_home) {
            char path[512], file_path[1024];
            snprintf(path, sizeof(path), "%s/quack", user_home);
            mkdir(path, 0755);

            snprintf(file_path, sizeof(file_path), "%s/what.lz4.tar.gz.md5.zip.7z", path);
            FILE *f = fopen(file_path, "w");
            if (f) {
                fprintf(f, "Зачем тебе привилегии для утки? Кря!\n");
                fclose(f);
            }

            snprintf(file_path, sizeof(file_path), "%s/decrypt.py", path);
            f = fopen(file_path, "w");
            if (f) {
                fprintf(f, "print('Анализ цепочки архивов...')\n");
                fprintf(f, "print('Распаковка... [####################] 100%%')\n");
                fprintf(f, "print('Результат из decrypt.txt: hello')\n");
                fclose(f);
            }

            if (getenv("SUDO_UID") && getenv("SUDO_GID")) {
                uid_t u = atoi(getenv("SUDO_UID"));
                gid_t g = atoi(getenv("SUDO_GID"));
                chown(path, u, g);
                chown(file_path, u, g);
            }
        }
    }

    if (!isatty(STDIN_FILENO)) {
        if (fgets(message, 255, stdin) != NULL) {
            size_t len = strlen(message);
            if (len > 0 && message[len-1] == '\n') message[len-1] = '\0';
        }
    } else if (optind < argc) {
        strncpy(message, argv[optind], 255);
    }

    if (rainbow) {
        printf("\n%s      __\n", RED);
        printf("%s     <( %s_ )___\n", YELLOW, eye);
        printf("%s      (  /    |>\n", GREEN);
        printf("%s       `--'--'  %s\n", BLUE, RESET);
    } else {
        printf("\n%s      __\n", color);
        printf("     <( %s_ )___\n", eye);
        printf("      (  /    |>\n");
        printf("       `--'--'  %s\n", RESET);
    }

    printf("  [ %s ]\n\n", message);

    return 0;
}
