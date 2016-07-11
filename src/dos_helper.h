#ifndef DOS_HELPER_H
#define DOS_HELPER_H

/* To work easily with boolean calls */
#define false 0
#define true !false

/* Parse arguments from command line */
void parse_args(int argc, char *argv[], int *port, char **target_host, int *connections, _Bool *verbose);

#endif
