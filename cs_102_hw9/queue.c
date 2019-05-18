#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};
struct node* createNode();
void enqeue(struct node** head);
void denqeue(struct node** head);
void print_list(struct node* head);

int amountNode;

int main()
{
	int choice;
	struct node* head;
	head=createNode();
	while(1)
	{
		printf("\n1) Enqeue \n");
		printf("2) Denqeue \n");
		printf("3) Print Queue \n");
		printf("Choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			enqeue(&head);
			break;

			case 2:
			denqeue(&head);
			break;

			case 3:
			print_list(head);
			break;
		}
	}

	return 0;
}
struct node* createNode()
{
	int data=0,i=0;
	struct node* head;
	struct node* temp;
	struct node* newNode;

	while(amountNode<=0)
	{
		printf("How many nodes do you need ?\n");
		printf("Number : ");
		scanf("%d",&amountNode);
		if(amountNode<=0)
			printf("Invalid Input !\n");
	}
	head=(struct node*)malloc(sizeof(struct node));
	printf("Node Data : ");
	scanf("%d",&data);
	head->data=data;
	head->next=NULL;

	temp=head;
	
	for(i=1 ; i<amountNode ; ++i)
	{
		newNode=(struct node*)malloc(sizeof(struct node));
		printf("Node Data : ");
		scanf(" %d",&data);
		newNode->data=data;
		temp->next=newNode;
		temp=temp->next;
	}
	return head;
}
void enqeue(struct node** head)
{
	int data=0;
	struct node* temp;
	struct node* newNode;

	temp=(*head);

	while(temp->next!=NULL){
		temp=temp->next;
	}

	newNode=(struct node*)malloc(sizeof(struct node));
	printf("Node Data : ");
	scanf("%d",&data);
	newNode->data=data;
	newNode->next=NULL;

	temp->next=newNode;

	print_list(*head);
}
void denqeue(struct node** head)
{
	struct node* temp;
	temp=*head;
	if(!temp)
		printf("There is no element in the list ");
	else
	{
		(*head)=(*head)->next;
		free(temp);
	}
	print_list(*head);
}
void print_list(struct node* head)
{
	while(head)
	{
		if(head->next)	printf(" %d -> ",head->data);
		else			printf(" %d ",head->data);
		head=head->next;
	}
}