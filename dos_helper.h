#ifndef DOS_HELPER_H
#define DOS_HELPER_H

/* To work easily with boolean calls */
#define false 0
#define true !false

/* Checks if a given string is a valid IP */
_Bool is_valid_ip(char *ip);

/* Display a help message and ends the program with or without error */
void display_help(char *msg, _Bool with_error);

/* Parse arguments from command line */
void parse_args(int argc, char *argv[], int *port, char **target_host, int *connections, _Bool *verbose);

#endif
