//~ программа "база данных"
//~ производит чтение, запись и поиск по базе данных
//~ объявляем необходимые заголовочные файлы библиотек
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//~ объявляем константы 
//~ код кнопки Esc
#define ESC 27
//~ условие выхода из программы
#define OUT_PROGRAMME ESC
//~ длина горизонтальной полосы
#define LINE_LEN 78
//~ значение для "найдено слово" или нет
#define YES 1
#define NO 0
//~ значение для истины
#define TRUE 1

//~ объявляем функции
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
void main_menu(void);

//~ главная функция, с нее начинает работать программа
int main(int argc, char **argv)
{
	main_menu();
	get_button();
	return 0;
}

//~ выводит начальное меню
void main_menu() {
	print_string_in_line("База данных пользователей");
}

//~ принимает клавишу пользователя
//~ вызывает функцию в соответствии с нажатой клавишей
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

//~ открывает файл
FILE *open_file(char filename[], char method[]) {
	FILE *fp;
	if ((fp = fopen(filename, method)) == NULL) {
		printf("Не могу открыть файл\n");
		return NULL;
	} else {
		return fp;
	}
}

//~ читает файл построчно, выводит на экран
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

//~ рисует полоску знаком =
void print_line() {
	int i;
	printf("+");
	for (i = 0; i < LINE_LEN; i++) {
		printf("=");
	}
	printf("+\n");
}

//~ рисует черточки знаками -
void print_strike() {
	int i;
	for (i = 0; i < LINE_LEN / 2; i++) {
		printf("-");
	}
	printf("\n");
}

//~ выводит строку обрамленную полосками и меню снизу
void print_string_in_line(char str[]) {
	system("tput reset");
	system("stty icanon echo");
	print_line();
	printf("%s\n", str);
	print_line();
	read_file("control.txt");
}

//~ ищет по базе данных
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

//~ ищет слово в строке
char *find_word(char text[], char word[]) {
	char *substr;
	substr = strstr(text, word);
	return substr;
}

//~ пишет в базу данных
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

//~ читает базу данных
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
//~ ---
//~ файл control.txt
//~ 0 - главное меню
//~ 1 - читать базу данных
//~ 2 - записать в базу данных
//~ 3 - поиск по базе
//~ ESC - выход из программы
//~ ---
//~ файл database.txt
//~ Иванов Иван Иванович 15 5
//~ Сидоров Сидор Сидорович 15 4
//~ Петров Петр Петрович 14 3
//~ Денисов Денис Денисович 16 5
//~ Попов Павел Валентинович 20 3
//~ Пелевин Виктор Олегович 40 5
