#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <limits.h>

#define BUF_SIZE 4096

void reverse_string(const char *src, char *dest) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0';
}

void reverse_file_content(const char *src_path, const char *dest_path) {
    int fd_in = open(src_path, O_RDONLY);
    if (fd_in < 0) {
        perror("Ошибка открытия исходного файла");
        return;
    }

    struct stat st;
    if (fstat(fd_in, &st) < 0) {
        perror("Ошибка fstat");
        close(fd_in);
        return;
    }

    int fd_out = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode & 0777);
    if (fd_out < 0) {
        perror("Ошибка создания целевого файла");
        close(fd_in);
        return;
    }

    off_t file_size = lseek(fd_in, 0, SEEK_END);
    if (file_size > 0) {
        char buf[BUF_SIZE];
        off_t pos = file_size;

        while (pos > 0) {
            size_t to_read = (pos >= BUF_SIZE) ? BUF_SIZE : pos;
            pos -= to_read;

            lseek(fd_in, pos, SEEK_SET);
            ssize_t bytes_read = read(fd_in, buf, to_read);

            if (bytes_read > 0) {
                for (ssize_t i = 0; i < bytes_read / 2; i++) {
                    char tmp = buf[i];
                    buf[i] = buf[bytes_read - 1 - i];
                    buf[bytes_read - 1 - i] = tmp;
                }
                write(fd_out, buf, bytes_read);
            }
        }
    }

    close(fd_in);
    close(fd_out);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <путь_к_каталогу>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char src_dir_path[PATH_MAX];
    strncpy(src_dir_path, argv[1], PATH_MAX - 1);
    src_dir_path[PATH_MAX - 1] = '\0';
    
    size_t len = strlen(src_dir_path);
    if (len > 1 && src_dir_path[len - 1] == '/') {
        src_dir_path[len - 1] = '\0';
    }

    char *dir_name_ptr = basename(src_dir_path);
    char reversed_dir_name[PATH_MAX];
    reverse_string(dir_name_ptr, reversed_dir_name);

    if (mkdir(reversed_dir_name, 0755) < 0) {
    }
    printf("111111111111111111111111111111111111111111111111111111111111111\n");
    DIR *dir = opendir(src_dir_path);
        printf("222222222222222222222222222222222222222222222222222222222222222\n");

    if (!dir) {
        perror("Не удалось открыть каталог");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    struct stat file_stat;


    char src_file_path[PATH_MAX * 2];
    char dest_file_path[PATH_MAX * 2];
    char rev_name[PATH_MAX];

            printf("333333333333333333333333333333333333333333333333333333333333\n");

    while ((entry = readdir(dir)) != NULL) {
        printf("44444444444444444444444444444444444444444444444444444444444444444\n");
        snprintf(src_file_path, sizeof(src_file_path), "%s/%s", src_dir_path, entry->d_name);

        if (lstat(src_file_path, &file_stat) < 0) {
            continue;
        }

        if (!S_ISREG(file_stat.st_mode)) {
            continue;
        }
            reverse_string(entry->d_name, rev_name);
            snprintf(dest_file_path, sizeof(dest_file_path), "%s/%s", reversed_dir_name, rev_name);

            printf("Копирование: %s -> %s\n", entry->d_name, rev_name);
            reverse_file_content(src_file_path, dest_file_path);

    }

    closedir(dir);
    printf("Готово! Результат в директории: %s\n", reversed_dir_name);

    return EXIT_SUCCESS;
}
