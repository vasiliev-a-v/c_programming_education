//~ программа тестирования пользователя
//~ с выдачей оценки
#include "header.h"

int main()
{
	FILE *fp;			// указатель на файл теста
	int right_answer = 0;		// количество правильных ответов
	int user_score = 0;		// количество правильных ответов пользователя
	int questions = 0;		// количество вопросов в тесте
	double rating = 0;		// оценка пользователя
	char testing_file[MAX_INPUT];	// имя тестового файла

	//~ читаем файл конфигурации и открываем файл с вопросами теста
	read_config(testing_file);
	fp = open_file(testing_file, "r");

	//~ читаем вопросы и подсчитываем количество правильных ответов
	while (!feof(fp)) {
		fp = read_question(fp, &right_answer);
		if (right_answer != -1) {
			user_score += ask_user_question(right_answer);
			print_line();
			questions++;
		} else {
			break;
		}
	}

	//~ подсчет оценки пользователя
	rating = (double) user_score / (double) questions * 100;
	if (rating > 90)
		rating = 5;
	else if (rating > 80)
		rating = 4;
	else if (rating > 70)
		rating = 3;
	else if (rating > 60)
		rating = 2;
	else if (rating > 50)
		rating = 1;

	//~ выводит результат пользователя
	printf("\nПравильных ответов: %i\n", user_score);
	printf("Всего вопросов: %i\n", questions);
	printf("Ваша оценка: %.0f\n", rating);
	return 0;
}

//~ читает очередной вопрос,
//~ возвращает правильный ответ и указатель на следующий вопрос
FILE *read_question(FILE *fp, int *answer) {
	char str[MAX_STRING] = "";
	while (strstr(str, "Ответ: ") == NULL) {
		printf(str);
		fgets(str, sizeof(str), fp);
		if(feof(fp)) {
			*answer = -1;
			return fp;
		}
	}
	sscanf(str, "Ответ: %ud", answer);
	return fp;
}

//~ простит пользователя ввести ответ и сравнивает с правильным
//~ если правильно - возвращает 1, неправильно - 0
int ask_user_question(int right_answer) {
	int user_answer;
	printf("Ваш ответ: ");
	scanf("%ud", &user_answer);
	if (right_answer == user_answer) {
		printf("Ответ правильный\n");
		return 1;
	} else {
		printf("Ответ неправильный\n");
		return 0;
	}
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

//~ читает конфигурационный файл программы
//~ ищет название файла с тестами
void read_config(char testing_file[]) {
	FILE *fp;
	char config_file[MAX_STRING] = "testing_config.conf";
	char parameter[MAX_STRING];
	char value[MAX_INPUT];
	fp = open_file(config_file, "r");
	do {
		fscanf(fp, "%s %s\n", parameter, value);
		if (strcmp(parameter, "testing_file") == 0) {
			strcpy(testing_file, value);
		}
		printf("%s\n", testing_file);
	} while (!feof(fp));
	fclose(fp);
}

//~ рисует горизонтальную полоску из символов =
void print_line() {
	int i;
	printf("+");
	for (i = 0; i < LINE_LEN; i++) {
		printf("=");
	}
	printf("+\n");
}

