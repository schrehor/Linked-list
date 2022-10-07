#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct list {
	char category[52];
	char place[52];
	char street[102];
	int area;
	int price;
	char description[202];
	int index;
	struct list* prev;
	struct list* next;
}LIST;

void deleteList(LIST** first) {
	LIST* holder1, * holder2;
	holder1 = *first;
	while (holder1 != NULL) {
		holder2 = holder1;
		holder1 = holder1->next;
		free(holder2);
	}
	*first = NULL;
}

LIST* executeN() {
	FILE* fr;
	int i = 1;
	char s[3];
	char s2[] = "&\n";

	LIST* frst = (LIST*)malloc(sizeof(LIST));
	LIST* first = frst;
	LIST* second = (LIST*)malloc(sizeof(LIST));

	if ((fr = fopen("reality.txt", "r")) == NULL)
	{
		printf("Zaznamy neboli nacitane\n");
	}
	else
	{
		while (fgets(s, 3, fr) != NULL)
		{
			char hold[51];
			if (i != 1)
			{
				first = first->next;
				second = second->next;
				second = (LIST*)malloc(sizeof(LIST));
			}
			for (int i = 1; i < 7; i++)
			{
				switch (i)
				{
				case 1:
					fgets(first->category, 52, fr);
					break;
				case 2:
					fgets(first->place, 52, fr);
					break;
				case 3:
					fgets(first->street, 102, fr);
					break;
				case 4:
					fgets(hold, 51, fr);
					first->area = atoi(hold);
					break;
				case 5:
					fgets(hold, 51, fr);
					first->price = atoi(hold);
					break;
				case 6:
					fgets(first->description, 202, fr);
					break;
				}
			}
			first->index = i;
			i++;
			first->next = second;
			second->prev = first;
			second->next = NULL;
		}

		first->next = NULL;

		if (fclose(fr) == EOF)
			printf("Subor sa nepodarilo zatvorit.\n");
		printf("Nacitalo sa %d zaznamov\n", i - 1);

		return frst;
	}


}

void executeV(LIST** first) {
	LIST* now = *first;
	int count = 1;
	int go = 1;

	while (go == 1)
	{
		printf("%d.\n", count);
		printf("kategoria ponuky: %s", now->category);
		printf("miesto ponuky: %s", now->place);
		printf("ulica: %s", now->street);
		printf("rozloha v m2: %d\n", now->area);
		printf("cena: %d\n", now->price);
		printf("popis: %s", now->description);
		//printf("INDEX (VYMAZAT): %d\n", now->index);
		count++;
		if (now->next == NULL)
		{
			go = 0;
		}
		else
		{
			now = now->next;
		}
	}
}

void executeP(LIST** first, int exist) {
	LIST* newFile = (LIST*)malloc(sizeof(LIST));
	LIST* now = *first;
	LIST* before = NULL;
	int placement, flag = 0, go = 1;
	char hold[51];

	scanf("%d", &placement);

	fgets(hold, 2, stdin);												//Napln zaznamu

	fgets(newFile->category, 52, stdin);

	fgets(newFile->place, 52, stdin);

	fgets(newFile->street, 102, stdin);

	fgets(hold, 51, stdin);
	newFile->area = atoi(hold);

	fgets(hold, 51, stdin);
	newFile->price = atoi(hold);

	fgets(newFile->description, 202, stdin);

	newFile->index = placement;

	if (exist == 0)
	{
		while (go == 1)										  //Dava zaznam na vybranu poziciu
		{
			if (newFile->index == 1 && flag == 0)
			{
				newFile->next = now;
				now->prev = newFile;
				*first = newFile;
				flag = 1;
			}
			else if (now->index == newFile->index)
			{
				before = now->prev;
				newFile->next = now;
				before->next = newFile;
				newFile->prev = before;
				now->prev = newFile;
				flag = 1;
			}
			else {
			}
			if (flag == 1) {
				now->index++;
			}
			if (now->next == NULL)
			{
				break;
			}
			else
			{
				now = now->next;
			}
		}

		if (flag == 0)							   //Prida zaznam na koniec ak je placement vacsi ako cely zoznam
		{
			now->next = newFile;
			newFile->prev = now;
			newFile->index = now->index + 1;
			newFile->next = NULL;
		}
	}
	else
	{
		*first = newFile;
		newFile->next = NULL;
		newFile->index = 1;
	}
}

void executeZ(LIST** first) {
	LIST* now = *first;
	LIST* before = NULL;
	LIST* iter = NULL;
	int count = 0, go = 1, flag = 0;
	char str[51], hold[5], strComp[51];

	fgets(hold, 3, stdin); //holder

	fgets(str, 50, stdin);

	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
	str[strlen(str) - 1] = '\0';

	while (go == 1)
	{
		if (flag == 1)
		{
			now->index = before->index + 1;
		}
		strcpy(strComp, now->place);
		for (int i = 0; strComp[i]; i++) {
			strComp[i] = tolower(strComp[i]);
		}
		strComp[strlen(strComp) - 1] = '\0';

		if (strstr(strComp, str) != NULL)
		{
			if (now->index == 1)
			{
				*first = now->next;
				now = now->next;
				now->index = 1;
				free(now->prev);
				count++;
				flag = 1;
				continue;
			}
			else
			{
				LIST* del = now;
				before = now->prev;
				now = now->next;
				now->prev = before;
				before->next = now;
				free(del);
				count++;
				flag = 1;
				continue;
			}
		}
		else
		{
			if (now->next == NULL)
			{
				printf("Vymazalo sa %d zaznamov\n", count);
				break;
			}
			else
			{
				before = now;
				now = now->next;
			}
		}
	}

}

void executeH(LIST** first) {
	LIST* now = *first;
	int priceLimit, count = 0, go = 1;

	scanf("%d", &priceLimit);

	while (go == 1)
	{
		if (priceLimit >= now->price)
		{
			count++;
			printf("%d.\n", count);
			printf("kategoria ponuky: %s", now->category);
			printf("miesto ponuky: %s", now->place);
			printf("ulica: %s", now->street);
			printf("rozloha v m2: %d\n", now->area);
			printf("cena: %d\n", now->price);
			printf("popis: %s", now->description);
			//printf("INDEX (VYMAZAT): %d\n", now->index);
			if (now->next == NULL)
			{
				break;
			}
			else
			{
				now = now->next;
			}
		}
		else if (now->next == NULL)
		{
			break;
		}
		else
		{
			now = now->next;
		}
	}
	if (count == 0)
	{
		printf("V ponuke su len reality s vyssou cenou\n");
	}
}


void executeA(LIST** first) {
	LIST* now = *first;
	LIST* replace = (LIST*)malloc(sizeof(LIST));
	char hold[51], newPlace[52], testPlace[52];
	int go = 1, indexHold, count = 0;

	fgets(hold, 3, stdin);	  //holder
	fgets(newPlace, 51, stdin);
	for (int i = 0; newPlace[i]; i++) {
		newPlace[i] = tolower(newPlace[i]);
	}
	newPlace[strlen(newPlace) - 1] = '\0';

	fgets(replace->category, 52, stdin);
	fgets(replace->place, 52, stdin);
	fgets(replace->street, 102, stdin);
	fgets(hold, 51, stdin);
	replace->area = atoi(hold);
	fgets(hold, 51, stdin);
	replace->price = atoi(hold);
	fgets(replace->description, 202, stdin);

	while (go == 1)
	{
		strcpy(testPlace, now->place);
		for (int i = 0; testPlace[i]; i++) {
			testPlace[i] = tolower(testPlace[i]);
		}
		testPlace[strlen(testPlace) - 1] = '\0';

		if (strstr(testPlace, newPlace) != NULL)
		{
			strcpy(now->category, replace->category);
			strcpy(now->place, replace->place);
			strcpy(now->street, replace->street);
			strcpy(now->description, replace->description);
			now->area = replace->area;
			now->price = replace->price;
			count++;
		}
		if (now->next == NULL)
		{
			break;
		}
		else
		{
			now = now->next;
		}
	}
	printf("Aktualizovalo sa %d zaznamov\n", count);
}

int main() {
	char c;
	LIST* first = NULL;
	int flag = 0;

	while ((c = getchar()) != 'k')
	{
		switch (c)
		{
		case 'n':
			if (first == NULL) {
				first = executeN();
			}
			else
			{
				deleteList(&first);
				first = executeN();
			}
			break;
		case 'v':
			if (first != NULL) {
				executeV(&first);
			}
			break;
		case 'p':
			if (first == NULL) {
				flag = 1;
			}
			executeP(&first, flag);
			flag = 0;
			break;
		case 'z':
			if (first != NULL) {
				executeZ(&first);
			}
			break;
		case 'h':
			if (first != NULL) {
				executeH(&first);
			}
			break;
		case 'a':
			if (first != NULL) {
				executeA(&first);
			}
			break;
		}
	}
	return 0;
}
