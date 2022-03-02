#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct FileContent read_file(int fd) {
    struct FileContent file;
    file.size = 0;
    file.data = NULL;
    char buf[4 * 1024];
    int input;
    while ((input = read(fd, buf, sizeof(buf)))) {
        
        if (input < 0) {
            free(file.data);
            file.data = NULL;
            file.size = -1;
            return file;
        }
        char *p = realloc(file.data, file.size + input);
        if (!p) {
            free(file.data);
            file.data = NULL;
            file.size = -1;
            return file;
        }
        file.data = p;
        memcpy(file.data + file.size, buf, input);
        file.size += input;
    }
    char *p = realloc(file.data, file.size + 1);
    if (!p) {
        free(file.data);
        file.data = NULL;
        file.size = -1;
        return file;
    }
    file.data = p;
    file.data[file.size] = '\0';
    return file;
}