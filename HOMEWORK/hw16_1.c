#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 4) // if files_cnt != 3
        return 1;
    
    // char *input = argv[2];
    // char *output = argv[3];

    pid_t p = fork();
    if (!p) {
        int input = open(argv[2], O_RDONLY); // Файл FILE2 должен создаваться с помощью
        // системного вызова open с правами чтение-запись для всех категорий
        // пользователей (владелец, группа, прочие).
        dup2(input, STDIN_FILENO);
        int output = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(output, STDOUT_FILENO);
        close(output); // close f
        close(input); // close f
        execlp(argv[1], argv[1], NULL); // launch file
        exit(1); // end p
    }
    wait(NULL);
}