	/* программа "Поле чудес" */

#include <stdio.h>		/* стандартный ввод-вывод */
#include <locale.h>		/* для русской локализации */
#include <string.h>		/* для работы со строками */
#include <stdlib.h>		/* для exit(0); */
#include <wchar.h>		/* для русских символов в кодировке UTF-8 */
#include <time.h>		/* надо для случайных чисел */
getwchar
#include <unistd.h>		/* для функции sleep - пауза */

#define MAX_WORD 256		/* максимальная длина слова */
#define TRUE 1			/* для бесконечного цикла */

	/* объявляем наши функции */
FILE *open_file(char filename[], char method[]);
int read_words(FILE *fp);
void check_word(wchar_t play_word[], wchar_t word[], wchar_t user_char);
int get_random(FILE *fp, int words);
void get_word(FILE *fp, int number, wchar_t word[]);
int get_play_word(wchar_t word[], wchar_t play_word[]);


int main(int argc, char **argv)
{
	FILE *fp;			// указатель на файл со словами
	int rnd_word;			// порядковый номер случайного слова
	int words;			// количество слов в файле
	int word_len = 0;		// длина слова
	wchar_t word[MAX_WORD];		// случайное слово, которое надо отгадать
	wchar_t play_word[MAX_WORD];	// строка в виде точек
	wchar_t user_char;		// букву, которую выбирает пользователь

	setlocale(LC_ALL, "");			/* устанавливаем локаль */
	fp = open_file("words.txt", "r");	/* отрываем файл */
	words = read_words(fp);			/* читаем количество слов в файле */
	rnd_word = get_random(fp, words);	/* получаем порядковый номер случайного слова */
	get_word(fp, rnd_word, word);		/* получаем случайное слово */
	word_len = get_play_word(word, play_word);	/* создаем слово с точками на основе "случайного слова" */

	while (TRUE) {				/* бесконечный цикл */
		system("tput reset");		/* очищаем экран */
		system("stty -icanon");		/* включаем неканоничный ввод */
		printf("%ls\n", play_word);	/* выводим слово в виде точек */
		printf("Введите вашу букву: ");
		user_char = getwchar();		/* запоминаем клавишу пользователя */
		if (user_char == 27) {		/* клавиша выхода из игры */
			exit(0);
		}
		printf("\nБыла введена буква: %lc\n", user_char);
		check_word(play_word, word, user_char);	/* проверяем, есть ли буквы в слове */
		if (wcschr(play_word, L'.') == NULL) {
			printf("Слово \"%ls\" угадано!\n", play_word);
			break;
		}
	}

	fclose(fp);	/* закрываем файл со словами */
	return 0;	/* завершаем программу */
}

void check_word(wchar_t play_word[], wchar_t word[], wchar_t user_char) {
	int i;					/* объявляем счетчик */
	int word_len = wcslen(word);		/* вычисляем длину слова */

	for (i = 0; i < word_len; i++) {	/* проверяем букву в слове */
		if (word[i] == user_char) {	/* если буква угадана */
			play_word[i] = user_char;
			printf("Буква \"%lc\" угадана!\n", user_char);
			sleep(1);
		}
	}

}

//~ открываем файл со словами
FILE *open_file(char filename[], char method[]) {
	FILE *fp;			/* объявляем указатель на файл */

	if ((fp = fopen(filename, method)) == NULL) {	/* открываем файл */
		printf("Не могу открыть файл\n");
		return NULL;
	} else {
		return fp;		/* возвращаем указатель  */
	 }
}


/* читаем количество строк (слов) в файле */
int read_words(FILE *fp) {
	int words = 0;				/* количество слов */
	wchar_t str[MAX_WORD];			/* массив для чтения файла */

	while (!feof(fp)) {			/* пока не конец файла */
		fgetws(str, sizeof(str), fp);	/* читаем строку из файла */
		words++;			/* считаем количество строк */
	}

	return words -= 1;	/* возвращаем количество слов (строк) */
}


/* порядковый номер случайного слова */
int get_random(FILE *fp, int words) {
	srand(time(NULL));	/* создаем псевдослучайную последовательность */
	return rand()%words+1;	/* возвращаем порядковый номер случайного слова */
}


/* берет случайное слово из файла */
void get_word(FILE *fp, int number, wchar_t word[]) {
	rewind(fp);	/* устанавливаем указатель на начало файла */

	//~ выбираем соответствующее случайное слово из файла
	while (number--) { 
		fgetws(word, sizeof(wchar_t) * MAX_WORD, fp);
	}
}


/* создает строку с точками. возвращает длину слова */
int get_play_word(wchar_t word[], wchar_t play_word[]) {
	int i;				/* объявляем переменную счетчика */
	int word_len = wcslen(word);	/* вычисляем длину строки */

	play_word[0] = L'\0';	/* обнуляем строку для игры */

	/* заполняем строку для игры точками */
	for (i = 0; i < word_len - 1; i++) {
		play_word[i] = L'.';
	}
	play_word[i] = L'\0';	/* завершающий символ строки */
	return word_len;	/* возращает длину строки */
}
