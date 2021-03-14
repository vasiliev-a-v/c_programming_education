#include <stdio.h>

int main(int argc, char **argv)
{
	char *cities[20] = {
		{"Москва"},
		{"Санкт-Петербург"},
		{"Самара"},
		{"Воронеж"},
		{"Астрахань"},
		{"Краснодар"},
		{"Ухта"},
		{"Сыктывкар"}
		};

	printf("%c", cities[0]);
	return 0;
}
