#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int K;
    uint64_t x;
    if (argc < 3) {
        fprintf(stderr, "%s\n", "Not enough args");
    }
    char *addr = argv[1];
    char *server = argv[2];
    char *key = argv[3];
    FILE *f_in;
    FILE *f_out;
    struct addrinfo *data;

    struct addrinfo unused;
    memset(&unused, 0, sizeof unused);
    unused.ai_family = PF_INET;
    unused.ai_socktype = SOCK_STREAM;
    int fl = getaddrinfo(addr, server, &unused, &data);
    if (fl != 0)
        _exit(0);
    
    int fd1 = socket(data->ai_family, data->ai_socktype, 0);

    if (fd1 < 0) {
        freeaddrinfo(data);
        _exit(0);
    }
    if (connect(fd1, data->ai_addr, data->ai_addrlen) < 0) {
        freeaddrinfo(data);
        _exit(0);
    }
    int fd2 = dup(fd1);

    f_in = fdopen(fd1, "r");
    f_out = fdopen(fd2, "w");

    fprintf(f_out, "%s\n", key);
    fflush(f_out);

    
    if (fscanf(f_in, "%d", &K) < 0) {
        freeaddrinfo(data);
        _exit(0);
    }

    for (int n = 0; n <= K; ++n) {
        fprintf(f_out, "%d\n", n);
        fflush(f_out);
    }
    if (fscanf(f_in, "%" SCNu64, &x) < 0) {
        freeaddrinfo(data);
        _exit(0);
    }
    printf("%" PRIu64 "\n", x);
    fflush(stdout);

    fclose(f_in);
    fclose(f_out);
    freeaddrinfo(data);
}