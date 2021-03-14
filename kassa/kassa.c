#include <stdio.h>
#include <stdlib.h>

//~ объявление функций
void read_kassa(int *, int *);
void write_kassa(int, int);


int main(int argc, char **argv)
{
	int kassa_money = 0; // деньги из кассы
	int user_money = 0;  // деньги, которые введет кассир (пользователь)

	//~ если через командную строку переданы аргументы
	if (argc > 1) {
		sscanf(argv[1], "%i", &user_money);
	}

	//~ читаем и пишем в бесконечном цикле - условие выхода - 0 денег
	while(1) {
		read_kassa(&kassa_money, &user_money);
		write_kassa(kassa_money, user_money);
	}
	return 0;
}

//~ читаем сколько в кассе денег
void read_kassa(int *kassa_money, int *user_money) {
	FILE *fp;
	if ((fp = fopen("kassa.txt", "r")) == NULL) {
		printf("Не могу открыть файл");
		exit(0);
	}
	fscanf(fp, "%i", kassa_money);

	printf("В кассе %i денег\n", *kassa_money);

	do {
		printf("Сколько положить денег в кассу?");
		scanf("%i", user_money);
		if (*user_money == 0) {
			printf("Деньги не положены - выходим\n");
			fclose(fp);
			exit(0);
		}
	} while (*user_money == 0 || (*kassa_money + *user_money) < 0);
	fclose(fp);
}


void write_kassa(int kassa_money, int user_money) {
	FILE *fp;
	//~ записываем новое значение в кассу
	if ((fp = fopen("kassa.txt", "w")) == NULL) {
		printf("Не могу создать файл\n");
		exit(0);
	}
	kassa_money += user_money;
	fprintf(fp, "%i", kassa_money);
	fclose(fp);
}
