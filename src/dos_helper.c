#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>

#include"dos_helper.h"

#define LAST_PORT 65535

_Bool is_valid_ip(char *ip)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip, &(sa.sin_addr));

    return result != 0;
}

void display_help(char *msg, _Bool with_error)
{
    if (msg != NULL) {
        printf(":: Error: %s\n\n", msg);
    }

    printf("Usage: dos [OPTION...] DOMAIN/IP\n");
    printf("  -p, --port\t\tSet port for attack. Default is port 21\n");
    printf("  -v, --verbose\t\tSet operation mode to verbose\n");
    printf("  -c, --connections\tSet how many connections the program will attempt in target\n");
    printf("  -V, --version\t\tDisplay the version and useful information\n");

    exit(with_error);
}

void display_version()
{
    printf(":: Simple DoS Attack\n");
    printf("Author: Giovani Ferreira\n");
    printf("Source: https://github.com/giovanifss/Denial-of-Service\n");
    printf("License: GPLv3\n");
    printf("Version: 0.2\n");

    exit(0);
}

void parse_args(int argc, char *argv[], int *port, char **target_host, int *connections, _Bool *verbose)
{
    if (argc < 2) {
        display_help("You must pass the domain/ip for DoS", true);
    }
    
    for (short i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            if (atoi(argv[i + 1]) != 0) {
                *port = atoi(argv[i + 1]); 

                if (*port < 1 || *port > LAST_PORT) {
                    display_help("Port must be in a range from 1 to 65535", true); 
                }

                i++;
                continue;
            } else {
                display_help("Port must be a number", true); 
            } 
        }

        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            *verbose = true; 
            continue;
        }

        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--connections") == 0) {
            if (atoi(argv[i + 1]) != 0) {
                *connections = atoi(argv[i + 1]); 
                i++;
                continue;
            } else {
                display_help("Number of connections must be a number", true); 
            }
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            display_help(NULL, false); 
        }

        if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0) {
            display_version(); 
        }

        if (*target_host == NULL) {
            *target_host = argv[i];

            if (!is_valid_ip(*target_host)) {
                struct hostent *host;
                host = gethostbyname(*target_host);

                if (host != NULL) {
                    *target_host = inet_ntoa(*((struct in_addr *)host->h_addr));
                } else {
                    display_help("Invalid domain", true); 
                }
            }

            continue;
        } 

        display_help("Unknow argument", true);
    }
}
