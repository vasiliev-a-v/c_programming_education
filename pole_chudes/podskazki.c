wchar_t word[];		/* тип wchar_t вместо char */
button = getwchar();	/* возвращает клавишу */
wcschr(word, char);	/* выясняет есть ли символ в строке */
wcslen(word);	/* вычисляет длину строки */
fgetws		/* читает файл */

	/* это необходимо для создания случайных чисел */
#include <time.h>
srand(time(NULL));
rand()%words+1;

	/* чтобы сделать паузу */
#include <unistd.h>		/* для функции sleep */

rewind(fp);	/* устанавливаем указатель на начало файла */

	/* локализация */
//~ заголовочные файлы необходимых библиотек
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

int main()
{
	setlocale(LC_ALL, "");	/* функция установки локализации */

	printf("%ls", L"Введи слово\n");	/* так выводится строка */
	return 0;
}
