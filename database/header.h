#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//~ код кнопки Esc
#define ESC 27
//~ условие выхода из программы
#define OUT_PROGRAMME ESC
//~ длина горизонтальной полосы
#define LINE_LEN 78
#define YES 1
#define NO 0
#define TRUE 1

FILE *open_file(char [], char []);

int get_button(void);

int read_file(char []);

void print_line(void);

void print_strike(void);

void print_string_in_line(char []);

void find_in_base(void);

char *find_word(char [], char []);

void read_database(void);

void write_database(void);
