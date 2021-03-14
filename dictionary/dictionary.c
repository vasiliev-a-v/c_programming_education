/* dictionary - словарь английских и русских слов */

#include <stdio.h>	/* заголовочный файл для ввода-вывода */
#include <string.h>	/* заголовочный файл для работы со строками */
#define MAX_WORD 256	/* объявляем длину максимального слова */

/* открываем файл со словами */
FILE *open_file(char filename[], char method[]) {
	FILE *fp;			/* объявляем указатель на файл */

	if ((fp = fopen(filename, method)) == NULL) {	/* открываем файл */
		printf("Не могу открыть файл\n");	/* выводим на экран надпись */
		return NULL;				/* если файл не открывается */
	} else {
		return fp;		/* возвращаем указатель на файл */
	}
}

/* ищем слово в словаре и выводим на экран */
int search_word(FILE *fp, char word[], char type) {
	char eng[MAX_WORD];	/* символьный массив с английским словом */
	char rus[MAX_WORD];	/* символьный массив с русским словом */

	while (!feof(fp)) {			/* пока не конец файла */
		fscanf(fp, "%s %s", eng, rus);	/* читаем очередную строку из файла */
		if (type == 'e') {		/* если задан англо-русский */
			if (strcasecmp(word, eng) == 0) {	/* если совпадение найдено */
				printf("%s\n", rus);		/* выводим на экран */
				return 0;			/* выходим из функции */
			}
		} else {
			if (strcasecmp(word, rus) == 0) {
				printf("%s\n", eng);
				return 0;
			}
		}
	}
	printf("Слово не найдено\n");
	return 0;
}

int main(int argc, char **argv) {
	FILE *fp;		/* указатель на файл, который мы откроем */
	char type;		/* тип словаря анг-рус ("e") или рус-анг ("r") */
	char word[MAX_WORD];	/* искомое слово */

	if (argc > 3) {		/* если при вызове программы были переданы аргументы */
		if (strcasecmp(argv[1], "r") == 0) {	/* если аргумент был "r" */
			type = 'r';			/* то тип словаря рус-англ */
		} else {				/* иначе */
			type = 'e';			/* тип словаря англ-рус */
		}
		strcpy(word, argv[2]);	/* копируем слово из командной строки */
	} else {			/* если аргументов передано не было */
		printf("Введите r, если русско-английский, e, если англо-русский\n");
		scanf("%c", &type);
		printf("Введите слово\n");
		scanf("%s", word);
	}

	fp = open_file("dictionary.txt", "r");	/* открываем словарь */
	search_word(fp, word, type);		/* ищем совпадение в слове */

	return 0;		/* завершение программы */
}

