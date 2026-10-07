#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    int fd = open("secret.txt", O_RDONLY);
    
    // Вывод идентификаторов
    printf("Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
    
    if (fd == -1) {
        printf("Ошибка доступа к файлу!\n");
    } else {
        char buffer[100];
        int n = read(fd, buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';
        printf("Содержимое: %s", buffer);
        close(fd);
    }
    return 0;


}


