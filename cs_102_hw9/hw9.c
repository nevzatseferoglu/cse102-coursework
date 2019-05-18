/*--------------------------------*/
/*---CSE-102--HW-9----------------*/
/*---NEVZAT-SEFEROGLU-171044024---*/
/*---GEBZE TECHNICAL UNIVERSTIY---*/
/*---STACK-OPERATION--------------*/
/*--------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J") 	/* Cleaning The Terminal */
#define SIZE 30

struct person{    	/* Initialization a struct for persons */
	char name[SIZE];/* To take the name of person */
	char surname[SIZE];/* To take the surname of person */
	char musical_Work[SIZE];/* To take the creation of person */
	int age;/* To take the age of person */
	struct person* next;
}*top=NULL;

/* Function Introduction */
void addNode(char name[], char surname[], char creation[], int age);
void push(struct person*** temp_pop,struct person* current);
void SortAlphabetically(struct person** tempMain,struct person** tempStack);
void sort_Increasingly(struct person** tempMain,struct person** tempStack);
struct person* pop(struct person*** temp_pop);
int isEmpty(struct person* temp_check);
void deleteNode();
void print_stack();
void allFree();
void menu();
/* -------------------------End-------------------------------*/
int main()
{
	clear(); /* Cleaning the terminal */
	menu();  /* User Menu */
	allFree(); /* I deallocate all memory which is allocated by the 'top' pointer variable */
	return 0;
}
void menu()
{
	int exit=1,choice=-1,age=-1;
	char name[SIZE],surname[SIZE],creation[SIZE];
	struct person* tempMain=NULL,*tempStack=NULL;

	while(exit)
	{
		/* Menu itself */
		printf("****MENU****\n");
		printf("1- Add a Person to the Stack \n");
		printf("2- Pop a Person from the Stack\n");
		printf("3- Sort Alphabetical Order\n");
		printf("4- Sort Age in Increasing Order \n");
		printf("5- Exit Menu\n");
		printf("************\n");
		/* -------------------------End-------------------------------*/
		/* Taking the Choice From the User */
		while(choice<1||choice>6)
		{
			printf("Select your choice : ");
			scanf("%d",&choice);
		}
		clear();
		switch(choice)
		{
			case 1:
			printf("-> Creating New Person !\n");
			/* Taking the Properties of the Person From User */
			printf("Name : ");
			scanf(" %[^\n]s",name);
			printf("Surname : ");
			scanf(" %[^\n]s",surname);
			printf("Creation : ");
			scanf(" %[^\n]s",creation);
			while(age<0)
			{
				printf("Age : ");
				scanf(" %d",&age);
				if(age<=0)
					printf("Invalid Age !\n");
			}
			/* -------------------------End-------------------------------*/
			printf("\n\n");
			/* Adding a new person via function which is named addNode */
			addNode(name,surname,creation,age);
			print_stack();
			break;

			case 2:
			/* Deletion */
			deleteNode();
			print_stack();
			break;

			case 3:
			/* Sorting Alphabetically */
			SortAlphabetically(&tempMain,&tempStack);
			break;

			case 4:
			/* Sorting Increasingly based on persons their ages */
			sort_Increasingly(&tempMain,&tempStack);
			break;

			case 5:
			/* While Exit Control */
			exit=0;
			break;
		}
		choice=-1,age=-1;
		tempMain=top,tempStack=NULL;;
		/* After all operation , I need to change tempMain struct pointer variable so that I can use in print_stack function */
		/* And also for the forward operation , I need to assign a NULL to tempStack */
	}
}
void addNode(char name[], char surname[], char creation[], int age)
{
	struct person* tempNode;
	if(top==NULL)
	{
		/* Allocate a memory for the new person  */
		top=(struct person*)malloc(sizeof(struct person));
		/* Assigning a Value in it with via strcpy function */
		strcpy(top->name,name);
		strcpy(top->surname,surname);
		strcpy(top->musical_Work,creation);
		top->age=age;
		top->next=NULL;
		/* I assign a NULL character to the next of the 'top' */
	}
	else
	{
		/* Allocate a memory for the new person  */
		tempNode=(struct person*)malloc(sizeof(struct person));
		/* Assigning a Value in it with via strcpy function */
		strcpy(tempNode->name,name);
		strcpy(tempNode->surname,surname);
		strcpy(tempNode->musical_Work,creation);
		tempNode->age=age;
		tempNode->next=top;
		top=tempNode;
		/* Creating a new Node is done */
	}
}
void deleteNode()
{
	/* Deletion Operation */
	struct person* temp;
	temp=top;
	/* Controlling variable whether it is NULL or not */
	if(temp==NULL)
		printf("\n--> There is no element to delete ! \n\n");
	/* If not */
	else if(top!=NULL)
	{
		/* Deletion of the with using temp and free() operation */
		top=top->next;
		free(temp);
		printf("\n--> Deletion is  completed ! \n\n");
	}
	/*---------------------------End--------------------------*/
}
void SortAlphabetically(struct person** tempMain,struct person** tempStack)
{
	/* My sorting algorithm is just based on stack operation , I obey the rule of LIFO (Last in First Out)*/
	struct person* current;
	while(!isEmpty(*tempMain))
	{
		current=pop(&tempMain);
		/* Popping the real element to the temporary variable  */
		if((*tempStack)==NULL)
			push(&tempStack,current);
		/* Pushing the current element to the temporary stack */
		else if(strcmp((*tempStack)->name,current->name)>0)
			/* Also Pushing the proper element to the tempStack */
			push(&tempStack,current);
		else
		{
			/* If current element does not obey the rule filling the main stack again */
			while((*tempStack)!=NULL&&strcmp((*tempStack)->name,current->name)<0)
				push(&tempMain,pop(&tempStack));
			/* After that pushing the current element to the tempStack */
			push(&tempStack,current);
		}
	}
	/* After all operation , assigning tempStack to the main stack */
	top=(*tempStack);
	printf("\t* Alphabetically Sorted Stack *\n");
	print_stack();
}
void sort_Increasingly(struct person** tempMain,struct person** tempStack)
{
	/* My sorting algorithm is just based on stack operation , I obey the rule of LIFO (Last in First Out)*/
	struct person* current;
	while(!isEmpty(*tempMain))
	{
		current=pop(&tempMain);
		/* Popping the real element to the temporary variable  */
		if((*tempStack)==NULL)
			push(&tempStack,current);
			/* Pushing the current element to the temporary stack */
		else if((*tempStack)->age>current->age)
			/* Also Pushing the proper element to the tempStack */
			push(&tempStack,current);
		else
		{
			/* If current element does not obey the rule filling the main stack again */
			while((*tempStack)!=NULL&&(*tempStack)->age<current->age)
				push(&tempMain,pop(&tempStack));
			/* After that pushing the current element to the tempStack */
			push(&tempStack,current);
		}
	}
	/* After all operation , assigning tempStack to the main stack */
	top=(*tempStack);
	printf("\t* Increasingly Sorted Stack *\n");
	print_stack();
}
struct person* pop(struct person*** temp_pop)
{
	struct person* temp;
	/* Creating temporary struct to keep adress safe */
	temp=(**temp_pop);
	/* Going to the next */
	(**temp_pop)=(**temp_pop)->next;
	/* Assining a NULL to the next , to sepera from the main struct */
	temp->next=NULL;
	return temp;
}
void push(struct person*** temp_push,struct person* current)
{
	struct person* temp;
	/* Creating temporary struct to keep adress safe */
	temp=(**temp_push);
	/* Adding the new element to the head of the stack*/
	current->next=temp;
	/* Adding the new element to the head of the stack*/
	(**temp_push)=current;
	/* Sliding a stack cursor */
}
int isEmpty(struct person* temp_check)
{
	/* Checking whether struct is empy or not */
	if(temp_check==NULL) return 1;
	else				 return 0;
}
void print_stack()
{
	/* Printing the stack */
	int counter=1 ; 
	struct person* temp_top;
	temp_top=top;
	/* Checking the whether it stack is empy or not */
	if(temp_top==NULL)
	{
		printf("\n --> There is no person to show !\n");
		return;
	}
	else
	{
		while(temp_top!=NULL)
		{
			/* Printing the stack with going till the NULL */
			printf("%d)\n",counter);
			printf("Name : %s\n",temp_top->name);
			printf("Surname : %s\n",temp_top->surname);
			printf("Creation : %s \n",temp_top->musical_Work);
			printf("Age : %d\n",temp_top->age);
			printf("---------------------------\n");
			temp_top=temp_top->next;
			++counter;
		}
	}
}
void allFree()
{
	/*I make deallocation opearation in this this function*/
	struct person* temp;
	while(top)
	{
		temp=top;
		top=top->next;
		free(temp);
	}
}
/*---------------------End--the--Program------------------------*/