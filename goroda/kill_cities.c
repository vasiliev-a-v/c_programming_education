#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

#define MAX_WORD 256

FILE *open_file(char filename[], char method[]) {
	FILE *fp;
	if ((fp = fopen(filename, method)) == NULL) {
		printf("Не могу открыть файл\n");
		return NULL;
	} else {
		return fp;
	}
}

void read_city(wchar_t *city) {
	int i = 0;
	while (city[i+1] != '(') {
		i++;
	}
	city[i] = '\0';
}

int main(int argc, char **argv)
{
	FILE *from;
	FILE *to;
	wchar_t str[MAX_WORD];

	setlocale(LC_ALL, "");
	from = open_file("goroda.txt", "r");
	to   = open_file("goroda_copy.txt", "w");
	
	while(!feof(from)) {
		fgetws(str, sizeof(str), from);
		read_city(str);
		fprintf(to, "%ls\n", str);
		printf("%ls", str);
	}

	fclose(from);
	fclose(to);

	return 0;
}



