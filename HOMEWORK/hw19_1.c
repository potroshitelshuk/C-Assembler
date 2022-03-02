#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

enum {SIZE = 1000};

int main(int argc, char const *argv[]) {
    struct addrinfo *data, *it;//, *lst_it;
    struct addrinfo unsued;
    char host[SIZE], service[SIZE];
    struct sockaddr_in * min_addr = NULL;

    memset(&unsued, 0, sizeof unsued);
    unsued.ai_family = AF_INET;
    unsued.ai_socktype = SOCK_STREAM;

    while (scanf("%1000s %1000s", host, service) != EOF) {
        int fl = getaddrinfo(host, service, &unsued, &data);
        if (fl != 0) {
            printf("%s\n", gai_strerror(fl));
            continue;
        }
        it = data;
        // lst_it = it;
        while (it) {
            if (!min_addr) {
                min_addr = (struct sockaddr_in *)it->ai_addr;
                continue;
            }

            if (ntohl(((struct sockaddr_in *)it->ai_addr)->sin_addr.s_addr) < ntohl(min_addr->sin_addr.s_addr)) {
                // lst_it = it;
                min_addr = ((struct sockaddr_in *)it->ai_addr);
            }
            it = it->ai_next;
        }
        printf("%s:", inet_ntoa(min_addr->sin_addr));
        printf("%d\n", ntohs(min_addr->sin_port));
        freeaddrinfo(data);
        min_addr = NULL;
        *host = '\0';
        *service = '\0';
        
    }
    return 0;
}