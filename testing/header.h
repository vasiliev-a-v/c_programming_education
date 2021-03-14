#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 40
#define MAX_INPUT 256
#define MAX_STRING 1024

FILE *open_file(char [], char []);

void print_line(void);

void read_config(char testing_file[]);

FILE *read_question(FILE *, int *);

int ask_user_question(int);
