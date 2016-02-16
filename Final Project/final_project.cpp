//Author : Jaeseok Huh, CSE of Hanyang Univ.
//Date : Dec 10, 2015
//Final project using an one-way linked-list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MX 20
#pragma warning(disable:4996)

typedef struct record
{
	char id[20];
	char name[20];
	char major[20];
	char phone[20];
	char hobby[20];
	struct record * next;
} STUDENT;

void printInitMsg() {
	int i, j;
	for (i = 0; i<40; i++) printf("*"); printf("\n");

	const char* items[] = { "Student Management", "Jae-seok Huh", "2015005241" };
	for (i = 0; i<sizeof(items) / sizeof(char*); i++) {
		printf("*");
		for (j = 0; j<9; j++) printf(" ");
		printf("%-29s", items[i]);
		printf("*\n");
	}

	for (i = 0; i<40; i++) printf("*"); printf("\n");

}

void printRow(const STUDENT* st, bool isHead = false) {
	int width[] = { 15, 15, 10, 15, 10 };
	const char* items[] = { "ID", "NAME", "MAJOR", "PHONE", "HOBBY" };
	const char* ptr[] = { st->id, st->name, st->major, st->phone, st->hobby };

	assert(sizeof(width) / sizeof(int) == sizeof(items) / sizeof(char*)
		&& sizeof(width) / sizeof(int) == sizeof(ptr) / sizeof(char*));

	int i, j;

	if (isHead) {
		for (i = 0; i<sizeof(width) / sizeof(int); i++) {
			for (j = 0; j<width[i] - strlen(items[i]); j++) printf(" ");
			printf("%s", items[i]);
		}
		printf("\n");
		return;
	}
	else {
		for (i = 0; i<sizeof(width) / sizeof(int); i++) {
			for (j = 0; j<width[i] - strlen(ptr[i]); j++) {
				printf(" ");
			}
			printf("%s", ptr[i]);
		}
		printf("\n");
		return;
	}
}

//returns Menu code
int Menu(const char* items[], const int N) {

	int i;
	for (i = 0; i<N; i++) {
		printf("%d. %s\n", i + 1, items[i]);
	}
	printf("Please enter the number >> ");

	fflush(stdin);
	int ret; scanf("%d", &ret);
	assert(1 <= ret && ret <= N);

	return ret;
}
//return NOT-NULL if SUCEEDED
STUDENT* input_(STUDENT* head) {

	STUDENT* node = head;
	STUDENT* prv = NULL;
	//After loop, { head } is a new node of linked-list
	while (node != NULL) {
		prv = node;
		node = node->next;
	}

	node = (STUDENT*)malloc(sizeof(STUDENT));

	//if it has to allocate the pointer at head
	if (head == NULL) {
		head = node;
	}
	else {
		prv->next = node;
	}

	const char* items[] = { "id", "name", "major", "phone", "hobby" };
	char* ptrs[] = { node->id, node->name, node->major, node->phone, node->hobby };
	assert(sizeof(items) == sizeof(ptrs));

	int i;
	for (i = 1; i <= sizeof(items) / sizeof(char*); i++) {
		printf("%d) %s: ", i, items[i - 1]);
		scanf("%s", ptrs[i - 1]);
	}

	//Mark { head } as last node of linked-list
	node->next = NULL;

	return head;
}

int find_(STUDENT* head) {
	enum Sub_Menu_Code { FULL = 1, NAME, ID, MAJOR, HOBBY, UNDO };
	const char* sub_items[] = { "Full list",
		"Search by name",
		"Search by id",
		"Search by major",
		"Search by hobby",
		"Undo"
	};

	int cnt = 0;

	char compare_str[20];
	switch (Menu(sub_items, sizeof(sub_items) / sizeof(char*))) {
	case FULL:
		//print head row
		printRow(NULL, true);
		while (head != NULL) {
			printRow(head);
			head = head->next;
			cnt++;
		}
		break;

	case NAME:
		printf("Name >> ");
		scanf("%s", compare_str);

		//print head row
		printRow(NULL, true);

		while (head != NULL) {
			if (strncmp(head->name, compare_str, MX) == 0) {
				printRow(head);
				cnt++;
			}
			head = head->next;
		}

		break;

	case ID:
		//print head row
		printf("ID >> ");
		scanf("%s", compare_str);

		//print head row
		printRow(NULL, true);

		while (head != NULL) {
			if (strncmp(head->id, compare_str, MX) == 0) {
				printRow(head);
				cnt++;
			}
			head = head->next;
		}
		break;

	case MAJOR:

		printf("MAJOR >> ");
		scanf("%s", compare_str);

		//print head row
		printRow(NULL, true);

		while (head != NULL) {
			if (strncmp(head->major, compare_str, MX) == 0) {
				printRow(head);
				cnt++;
			}
			head = head->next;
		}
		break;

	case HOBBY:
		printf("HOBBY >> ");
		scanf("%s", compare_str);

		//print head row
		printRow(NULL, true);

		while (head != NULL) {
			if (strncmp(head->hobby, compare_str, MX) == 0) {
				printRow(head);
				cnt++;
			}
			head = head->next;
		}
		break;

	case UNDO:

		return 0;
		break;

	default:

		break;

	}
	printf("\n%d student founded\n", cnt);
	return 1;
}

//returns head that might be changed in this procedure

STUDENT* delete_(STUDENT* head) {
	STUDENT *ret = head;
	enum Sub_Menu_Code { FULL = 1, NAME, ID, MAJOR, HOBBY, UNDO };
	const char* sub_items[] = { "Delete All",
		"Delete by name",
		"Delete by id",
		"Delete by major",
		"Delete by hobby",
		"Undo"
	};

	char compare_str[20];
	switch (Menu(sub_items, sizeof(sub_items) / sizeof(char*))) {
	case FULL:
		while (head != NULL) {
			STUDENT* nxt = head->next;
			free(head);
			head = nxt;
		}
		return NULL; //no more nodes
		break;

	case NAME:
	{
		printf("NAME >> "); scanf("%s", compare_str);

		//store the previous node to memorize its next node
		STUDENT *prv = NULL;

		while (head != NULL) {

			STUDENT* nxt = head->next;
			if (strncmp(head->name, compare_str, MX) == 0) {

				//if the node to be deleted is the first of linked-list
				if (head == ret) {
					//temporarily set the head as { nxt }
					ret = nxt;
				}
				free(head);

			}
			else {
				prv = head;
			}
			head = nxt;
			if (prv != NULL) prv->next = head;
		}
		break;
	}
	case ID:
	{
		printf("ID >> "); scanf("%s", compare_str);

		//store the previous node to memorize its next node
		STUDENT *prv = NULL;

		while (head != NULL) {

			STUDENT* nxt = head->next;
			if (strncmp(head->id, compare_str, MX) == 0) {

				//if the node to be deleted is the first of linked-list
				if (head == ret) {
					//temporarily set the head as { nxt }
					ret = nxt;
				}
				free(head);

			}
			else {
				prv = head;
			}
			head = nxt;
			if (prv != NULL) prv->next = head;
		}
		break;
	}
	case MAJOR:
	{
		printf("MAJOR >> "); scanf("%s", compare_str);

		//store the previous node to memorize its next node
		STUDENT *prv = NULL;

		while (head != NULL) {

			STUDENT* nxt = head->next;
			if (strncmp(head->major, compare_str, MX) == 0) {

				//if the node to be deleted is the first of linked-list
				if (head == ret) {
					//temporarily set the head as { nxt }
					ret = nxt;
				}
				free(head);

			}
			else {
				prv = head;
			}
			head = nxt;
			if (prv != NULL) prv->next = head;
		}
		break;
	}

	case HOBBY:
	{
		printf("HOBBY >> "); scanf("%s", compare_str);

		//store the previous node to memorize its next node
		STUDENT *prv = NULL;

		while (head != NULL) {

			STUDENT* nxt = head->next;
			if (strncmp(head->hobby, compare_str, MX) == 0) {

				//if the node to be deleted is the first of linked-list
				if (head == ret) {
					//temporarily set the head as { nxt }
					ret = nxt;
				}
				free(head);

			}
			else {
				prv = head;
			}
			head = nxt;
			if (prv != NULL) prv->next = head;
		}
		break;
	}

	case UNDO:
		return head;
		break;

	default:

		break;

	}

	return ret;

}
int main(void) {

	STUDENT* head = NULL;
	const char* main_items[] = { "Input a new student information",
		"Find a student using condition",
		"Delete a student using condition",
		"Quit"
	};
	enum main_menu_code { INPUT = 1, FIND, DELETE, QUIT };

	printInitMsg();
	bool routine_flag = true;
	while (routine_flag) {
		switch (Menu(main_items, sizeof(main_items) / sizeof(char*))) {
		case INPUT:
			head = input_(head);
			printf("> succeeded\n");
			break;

		case FIND:
			find_(head);
			break;

		case DELETE:
			head = delete_(head);
			break;

		case QUIT:
			routine_flag = false;
			break;
		}

	}
	return 0;
}
