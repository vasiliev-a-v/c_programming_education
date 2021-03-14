#include "header.h"

void main_menu() {
	print_string_in_line("База данных пользователей");
}

int get_button() {
	int c = 0;

	while (TRUE) {
		system("stty -icanon -echo");
		c = getchar();
		switch (c) {
			//~ выход из программы
		case OUT_PROGRAMME:
			return 0;
			break;
			//~ возврат в главное меню
		case '0':
			main_menu();
			break;
			//~ читать базу данных
		case '1':
			print_string_in_line("Читать базу данных");
			read_database();
			break;
		//~ записать в базу данных
		case '2':
			print_string_in_line("Записать в базу данных");
			write_database();
			break;
		//~ поиск по базе данных
		case '3':
			print_string_in_line("Поиск по базе данных");
			find_in_base();
			break;
		default:
			break;
		}
	}
	return 0;
}

FILE *open_file(char filename[], char method[]) {
	FILE *fp;
	if ((fp = fopen(filename, method)) == NULL) {
		printf("Не могу открыть файл\n");
		return NULL;
	} else {
		return fp;
	}
}

int read_file(char filename[]) {
	FILE *fp;
	char str[1024];
	fp = open_file(filename, "r");
	print_line();
	while (fgets(str, sizeof(str), fp) != NULL) {
		printf("%s", str);
	}
	fclose(fp);
	print_line();
	return 0;
}

void print_line() {
	int i;
	printf("+");
	for (i = 0; i < LINE_LEN; i++) {
		printf("=");
	}
	printf("+\n");
}

//~ рисуем полоску
void print_strike() {
	int i;
	for (i = 0; i < LINE_LEN / 2; i++) {
		printf("-");
	}
	printf("\n");
}

void print_string_in_line(char str[]) {
	system("tput reset");
	system("stty icanon echo");
	print_line();
	printf("%s\n", str);
	print_line();
	read_file("control.txt");
}

void find_in_base() {
	char str[1024];
	char word[256];
	char *p;
	int string_number = 1;
	FILE *fp;
	int found = NO;

	printf("Введите слово для поиска:");
	scanf("%s", word);
	print_strike();
	fp = open_file("database.txt", "r");
	while (fgets(str, sizeof(str), fp) != NULL) {
		p = find_word(str, word);
		if (p != NULL) {
			found = YES;
			printf("Найдено в строке %i:\n%s", string_number, str);
			print_strike();
		}
		string_number++;
	}
	if (found == NO) {
		printf("Ничего не найдено\n");
	}
	fclose(fp);
	print_line();
}

char *find_word(char text[], char word[]) {
	char *substr;
	substr = strstr(text, word);
	return substr;
}

void write_database() {
	FILE *fp;
	char c;
	char surname[256];	// фамилия
	char name[256];		// имя
	char patronymic[256];	// отчество
	int  age;		// возраст
	int  assessment;	// оценка
	fp = open_file("database.txt", "a+");

	printf("Введите данные в таком порядке:\n");
	printf("фамилия\tимя\tотчество\tвозраст\tоценка\n");

	scanf("%s %s %s %i %i",
	surname, name, patronymic, &age, &assessment);

	while((c = getchar()) != '\n')
		;

	fprintf(fp, "%s %s %s %i %i\n",
	surname, name, patronymic, age, assessment);

	fclose(fp);
	print_line();
}

void read_database() {
	FILE *fp;
	char surname[256];	// фамилия
	char name[256];		// имя
	char patronymic[256];	// отчество
	int  age;		// возраст
	int  assessment;	// оценка
	int  string_number = 1;	// номер строки в базе данных
	fp = open_file("database.txt", "r");

	printf("| №  | фамилия\tимя\tотчество\tвозраст\tоценка\n");
	print_line();
	while (!feof(fp)) {
		fscanf(fp, "%s %s %s %i %i\n",
		surname, name, patronymic, &age, &assessment);

		printf("| %2i | %s\t%s\t%s\t%i\t%i\n",
		string_number++, surname, name, patronymic, age, assessment);
	}
	print_line();
	fclose(fp);
}


