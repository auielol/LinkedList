#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	int x;
	struct node *n;
	struct node *p;
}NODE;

typedef struct list
{
	int count;
	struct node *head;
	struct node *tail;
}LIST;

int menu();
void createList(LIST *L, int data);
void insertFront(LIST *L, int data);
void insertEnd(LIST *L, int data);
void insertAt(LIST *L, int data, int pos);
void deleteFront(LIST *L);
void deleteAt(LIST *L, int pos);
void deleteEnd(LIST *L);
void deleteAll(LIST *L);
void displayAll(NODE *h);

int main()
{
	int ch, data, pos;
	bool f =1;
	
	LIST *L = (LIST*)malloc(sizeof(LIST));
	L->head = NULL;
	L->tail = NULL;
	L->count = 0;
	
	for(;f;)
	{
		do
		{
			menu();
			ch = getche();
		}while(ch<'1'&&ch>'4');
		
		switch(ch)
		{
			case '1':
				printf("\n\nEnter a number: ");
				scanf("%d", &data);
				createList(L, data);
				break;
			case '2':
				displayAll(L->head);
		}
	}
	
	return 0;
}

void createList(LIST *L, int data)
{
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	
	newNode->x = data;
	newNode->n = NULL;
	newNode->p = NULL;
	L->head = newNode;
	L->tail = newNode;
}

int menu()
{
	printf("[1] - CREATE LIST");
	printf("\n[2] - INSERT FRONT");
	printf("\n[3] - INSERT AT POSITION");
	printf("\n[4] - ");
}

void insertFront(LIST *L, int data)
{
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	
	if (L->count == 0)
	{
		createList(L, data);
	}
	else
	{
		newNode->x = data;
		newNode->n = NULL;
		newNode->n = L->head;
		L->head->p = newNode;
		L->head = newNode;
	}
	L->count++;
}

void insertAt(LIST *L, int data, int pos)
{
	int i;
	
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	
	if (L->count == 0)
	{
		createList(L, data);
		
		L->count++;
	}
	else if (pos == 1)
	{
		insertFront(L, data);
	}
	else if (pos == L->count + 1)
	{
		insertEnd(L, data);
	}
	else
	{
		newNode->x = data;
		
		NODE *tempNode = L->head;
		
		pos--;
		while (pos != 1)
		{
			tempNode = tempNode->n;
			pos--;
		}
		
		newNode->n = tempNode->n;
		tempNode->n = newNode;
		
		L->count++;
	}
}

void insertEnd(LIST *L, int data)
{
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	
	if(L->count == 0)
	{
		createList(L, data);
	}
	else
	{
		newNode->x = data;
		newNode->n = NULL;
		L->tail->n = newNode;
		L->tail = newNode;
	}
	
	L->count++;
}

void deleteFront(LIST *L)
{
	NODE *nextNode = (NODE*)malloc(sizeof(NODE));
	
	if (L->head == L->tail) //1 node left
	{
		free(L->head);
		free(L->tail);
		L->head = NULL;
		L->tail = NULL;
		L->count = 0;
	}
	else
	{
		nextNode = L->head->n;
		free(L->head);
		L->head = nextNode;
		
		L->count--;
	}
}

void deleteAt(LIST *L, int pos)
{
	int i;
	
	NODE *prevNode = L->head;
	NODE *tempNode = L->head;
	
	if (L->head == L->tail) //1 node left
	{
		free(L->head);
		free(L->tail);
		L->head = NULL;
		L->tail = NULL;
		L->count = 0;
	}
	else if (pos == 1)
	{
		deleteFront(L);
	}
	else if (pos == L->count + 1)
	{
		deleteEnd(L);
	}
	else
	{
		while (pos != 1)
		{
			prevNode = tempNode;
			tempNode = tempNode->n;
			pos--;
		}
		prevNode->n = tempNode->n;
		free(tempNode);
		tempNode = NULL;
		
		L->count--;
	}
}

void deleteEnd(LIST *L)
{
	NODE *prevNode = (NODE*)malloc(sizeof(NODE));
	
	if (L->head == L->tail) // 1 node left
	{
		free(L->head);
		free(L->tail);
		L->head = NULL;
		L->tail = NULL;
		L->count = 0;
	}
	else
	{
		prevNode->n = L->head;
		while (prevNode->n != L->tail)
		{
			prevNode = prevNode->n;	
		}
		free(L->tail);
		prevNode->n = NULL;
		L->tail = prevNode;
		
		L->count--;
	}
}

void deleteAll(LIST *L)
{
	NODE *temp = L->head;
	
	while (temp != NULL)
	{
		temp = temp->n;
		free(L->head);
		L->head = temp;
	}
	
	L->count = 0;
}

void displayAll(NODE *h)
{
	if (h == NULL)
	{
		printf("List is Empty\n");
	}
	else
	{
		while (h != NULL)
		{
			printf("%d ", h->x);
			h = h->n;
		}
		printf("\n");
	}
}

