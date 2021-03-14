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

int main()
{
	FILE *fp;
	int cities = 0;
	wchar_t user_city[MAX_WORD];
	//~ wchar_t comp_city[MAX_WORD];
	char filename[] = "goroda.txt";

	setlocale(LC_ALL, "");
	printf("%ls", L"Введи город\n");
	scanf("%ls", user_city);
	fp = open_file(filename, "r");
	while (!feof(fp)) {
		read_city(fp);
		cities++;
	}
	printf("%i\n", cities);

	return 0;
}
