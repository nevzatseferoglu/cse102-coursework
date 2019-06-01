/* Gebze Technical University */
/* Nevzat Seferoglu - 171044024  */
/* HW10-Data Structures */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20 /* Inıtial Size */

typedef struct bst{
	struct bst* leftChild;
	int data;
	struct bst* rightChild;
}bst;

typedef struct queue{
	int data;
	struct queue* next;
}queue;

typedef struct stack{
	int data;
	struct stack* next;
}stack;

void fill_structures(stack** stack_, queue** queue_, bst** bst_, int data[SIZE]);
void ordered_print(stack * stack_, queue * queue_, bst * bst_);
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search);
void special_traverse(stack * stack_, queue* queue_, bst * bst_);
stack* stack_filling(int data[SIZE]);
queue* queue_filling(int data[SIZE]);
bst* bst_filling(int data[SIZE]);
bst* newTree(int data);
bst* create_tree(bst* bstHead,int data);
double descending_stack(stack* stack_);
double descending_queue(queue* queue_);
void descending_BST(bst* bst_);
void push(stack** head,int data);
void enqueue(queue** head,int data);
void copyStack(stack* stack_,stack** copyStack);
void copyQueue(queue* queue_,queue** tempQueue);
int pop(stack** head);
int emptyCheckStack(stack** head);
void insert_Stack(stack** head,int temp);
void sortStack(stack** head);
int dequeue(queue** head);
int take_length_queue(queue* tempQueue);
int findMax(queue** tempQueue,int k,int n);
void reorder(queue** tempQueue,int max,int n,int* count);
void search_Stack(stack* stack_,int val_to_search);
void search_Queue(queue* queue_,int val_to_search);
void search_BST(bst* bst_,int val_to_search);
void helperSearchBST(bst* bst_,int steps[SIZE],int val_to_search,int i);
void traverse_Stack(stack* stack_);
void traverse_Queue(queue* queue_);
void traverse_BST(bst* bst_);
int findMax_Stack(stack* tempStack);
int findMin_Stack(stack* tempStack);
int findMax_Queue(queue* tempQueue);
int findMin_Queue(queue* tempQueue);
void deleteNodeStack(stack** head_ref, int key);
void deleteNodeQueue(queue** head_ref, int key);

int main()
{
	int data[SIZE]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
	bst* bst_;
	queue* queue_;
	stack* stack_;
	fill_structures(&stack_,&queue_,&bst_,data);
	ordered_print(stack_,queue_,bst_);
	search(stack_,queue_,bst_,5);
	special_traverse(stack_,queue_,bst_);

	return 0;
}
void fill_structures(stack** stack_, queue** queue_, bst** bst_,int data[SIZE])
{
	double stack_cpu_time_used=0,queue_cpu_time_used=0,bst_cpu_time_used=0,start,end;

	printf("\n------------Start_Filling_Process----------------------\n\n");
	start=clock();
	(*stack_)=stack_filling(data);
	end=clock();
	stack_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	end=0,start=0;
	
	start=clock();
	(*queue_)=queue_filling(data);
	end=clock();
	queue_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	end=0,start=0;
	
	start=clock();
	(*bst_)=bst_filling(data);
	end=clock();
	bst_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	stack_cpu_time_used=stack_cpu_time_used*1000;
	queue_cpu_time_used=queue_cpu_time_used*1000;
	bst_cpu_time_used=bst_cpu_time_used*1000;
	
	printf("-> Filling Report : \n");
	printf("-------------------\n");
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_cpu_time_used,queue_cpu_time_used,bst_cpu_time_used);
	printf("\n-------End_of_the_Filling_Process----------------------\n\n");
}
void ordered_print(stack* stack_, queue* queue_, bst* bst_)
{
	double stack_cpu_time_used=0,queue_cpu_time_used=0,bst_cpu_time_used=0,start=0,end=0;
	printf("\n------------Start_Sorting_Process----------------------\n\n");
	printf("-> Sorted Stack : \n");
	printf("-----------------\n");
	stack_cpu_time_used=descending_stack(stack_);

	printf("\n-> Sorted Queue : \n");
	printf("-----------------\n");
	queue_cpu_time_used=descending_queue(queue_);

	printf("\n-> Sorted BST:\n");
	printf("--------------\n");
	start=clock();
	descending_BST(bst_);
	end=clock();
	bst_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	start=0,end=0;
	printf("\n");

	stack_cpu_time_used=stack_cpu_time_used*1000;
	queue_cpu_time_used=queue_cpu_time_used*1000;
	bst_cpu_time_used=bst_cpu_time_used*1000;

	printf("\n-> Sorting Report : \n");
	printf("-------------------\n");
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_cpu_time_used,queue_cpu_time_used,bst_cpu_time_used);
	printf("\n-------End_of_the_Sorting_Process----------------------\n\n");
}
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search)
{
	double stack_cpu_time_used=0,queue_cpu_time_used=0,bst_cpu_time_used=0,start=0,end=0;
	printf("\n------------Start_Searching_Process--------------------\n\n");

	start=clock();
	search_Stack(stack_,val_to_search);
	end=clock();
	stack_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	start=0,end=0;
	start=clock();
	search_Queue(queue_,val_to_search);
	end=clock();
	queue_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	start=0,end=0;
	start=clock();
	search_BST(bst_,val_to_search);
	end=clock();
	bst_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	stack_cpu_time_used=stack_cpu_time_used*1000;
	queue_cpu_time_used=queue_cpu_time_used*1000;
	bst_cpu_time_used=bst_cpu_time_used*1000;

	printf("\n-> Searching Report : \n");
	printf("-------------------\n");
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_cpu_time_used,queue_cpu_time_used,bst_cpu_time_used);
	printf("\n-------End_of_the_Searching_Process----------------------\n\n");
}
void search_Stack(stack* stack_,int val_to_search)
{
	int steps[SIZE],i=0,target=0;
	stack* tempStack=NULL;
	copyStack(stack_,&tempStack);

	printf("Stack based result : (Searching)\n");
	printf("--------------------\n");
	printf("-> Searching Data: %d \n",val_to_search);
	for(i=0 ; i<SIZE ; ++i)
		steps[i]=-1;
	i=0;
	while(tempStack)
	{
		if(tempStack->data==val_to_search)
		{
			steps[i]=i+1,++target;
		}
		++i;
		tempStack=tempStack->next;	
	}
	if(target!=0)
	{
		printf("-> %d results founded on ",target);
		for(i=0 ; i<SIZE ; ++i)
		{
			if(steps[i]!=-1)
			printf("%d. step ",steps[i]);
		}
	}
	else
		printf("-> There is no result by this data ");
	printf("!\n\n");
}	
void search_Queue(queue* queue_,int val_to_search)
{
	int steps[SIZE],i=0,target=0;
	queue* tempQueue=NULL;
	copyQueue(queue_,&tempQueue);
	
	printf("Queue based result : (Searching)\n");
	printf("--------------------\n");
	printf("-> Searching Data: %d \n",val_to_search);
	for(i=0 ; i<SIZE ; ++i)
		steps[i]=-1;
	i=0;
	while(tempQueue)
	{
		if(tempQueue->data==val_to_search)
		{
			steps[i]=i+1,++target;
		}
		++i;
		tempQueue=tempQueue->next;	
	}
	if(target!=0)
	{
		printf("-> %d results founded on ",target);
		for(i=0 ; i<SIZE ; ++i)
		{
			if(steps[i]!=-1)
			printf("%d. step ",steps[i]);
		}
	}
	else
		printf("-> There is no result by this data ");
	printf("!\n\n");
}
void search_BST(bst* bst_,int val_to_search)
{
	int steps[SIZE],target=0,i=0;

	printf("BST based result : (Searching)\n");
	printf("--------------------\n");
	printf("-> Searching Data: %d \n",val_to_search);

	for(i=0 ; i<SIZE ; ++i)
		steps[i]=-1;
	helperSearchBST(bst_,steps,val_to_search,0);
	for(i=0 ; i<SIZE ; ++i)
	{
		if(steps[i]!=-1)
			++target;
	}
	if(target!=0)
	{
		printf("-> %d results founded on ",target);
		for(i=0 ; i<SIZE ; ++i)
		{
			if(steps[i]!=-1)
			printf("%d. step ",steps[i]);
		}
	}
	else
		printf("-> There is no result by this data ");
	printf("!\n\n");

}
void helperSearchBST(bst* bst_,int steps[SIZE],int val_to_search,int i)
{
	if(bst_)
	{
		if(bst_->data==val_to_search)
		{
			steps[i]=i+1;
		}
		++i;
		if(bst_->rightChild)
			helperSearchBST(bst_->rightChild,steps,val_to_search,i);
		
		if(bst_->leftChild)
			helperSearchBST(bst_->leftChild,steps,val_to_search,i);
	}
}
void special_traverse(stack* stack_, queue* queue_, bst* bst_)
{
	double stack_cpu_time_used=0,queue_cpu_time_used=0,bst_cpu_time_used=0,start=0,end=0;
	printf("\n------------Start_Traversing_Process--------------------\n\n");

	start=clock();
	traverse_Stack(stack_);(stack_);
	end=clock();
	stack_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	start=0,end=0;
	start=clock();
	traverse_Queue(queue_);
	end=clock();
	queue_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	start=0,end=0;
	start=clock();
	traverse_BST(bst_);(bst_);
	end=clock();
	bst_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	stack_cpu_time_used=stack_cpu_time_used*1000;
	queue_cpu_time_used=queue_cpu_time_used*1000;
	bst_cpu_time_used=bst_cpu_time_used*1000;

	printf("\n-> Traversa Report : \n");
	printf("-------------------\n");
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_cpu_time_used,queue_cpu_time_used,bst_cpu_time_used);
	printf("\n-------End_of_the_Traversing_Process----------------------\n\n");
}
void traverse_Stack(stack* tempStack)
{
	printf("Stack based result : (Traversa)\n");
	printf("--------------------\n");
	while(tempStack)
	{
		printf("%d ",findMax_Stack(tempStack));
		deleteNodeStack(&tempStack,findMax_Stack(tempStack));
		printf("%d ",findMin_Stack(tempStack));
		deleteNodeStack(&tempStack,findMin_Stack(tempStack));
	}
	printf("\n\n");
}
void deleteNodeStack(stack** head_ref, int key) 
{ 
    stack* temp = *head_ref,*prev;
    if (temp != NULL && temp->data == key) 
    { 
        *head_ref = temp->next;   
        free(temp);               
        return; 
    } 
    while (temp != NULL && temp->data != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
    if (temp == NULL) return; 
    prev->next = temp->next; 
    free(temp);
}
void traverse_Queue(queue* tempQueue)
{
	printf("Queue based result : (Traverse)\n");
	printf("--------------------\n");
	while(tempQueue)
	{
		printf("%d ",findMax_Queue(tempQueue));
		deleteNodeQueue(&tempQueue,findMax_Queue(tempQueue));
		printf("%d ",findMin_Queue(tempQueue));
		deleteNodeQueue(&tempQueue,findMin_Queue(tempQueue));
	}
	printf("\n\n");
}
void deleteNodeQueue(queue** head_ref, int key) 
{ 
   queue* temp = *head_ref,*prev;
    if (temp != NULL && temp->data == key) 
    { 
        *head_ref = temp->next;   
        free(temp);               
        return; 
    } 
    while (temp != NULL && temp->data != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
    if (temp == NULL) return; 
    prev->next = temp->next; 
    free(temp);
}
void traverse_BST(bst* bst_)
{
	printf("BST based result : (Traverse)\n");
	printf("--------------------\n");
	printf("In process ... :( \n");
}
int findMaxTree(bst* root) 
{ 
    if( !root)
        return 0;
    if( root->rightChild )
        return findMaxTree(root->rightChild);
    return root->data;
}
double descending_queue(queue* queue_)
{
	double start=0,end=0,queue_cpu_time_used=0;
	int i=0,length=0,max=0,count=0,countTotal=0;

	queue* tempQueue=NULL;
	copyQueue(queue_,&tempQueue);

	start=clock();
	length=take_length_queue(tempQueue);
	for(i=0 ; i<=length-1 && length-(i+countTotal)!=0 ; ++i)
	{
		if(count>1)
		{
			countTotal=countTotal+(count-1);
		}
		max = findMax(&tempQueue,length-(i+countTotal),length);
		count=0;
		reorder(&tempQueue,max,length,&count);
	}
	while(tempQueue)
	{
		printf("%d ",tempQueue->data);
		tempQueue=tempQueue->next;
	}
	end=clock();
	queue_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n");
	return queue_cpu_time_used;
}
int findMax(queue** tempQueue,int k,int n)
{
	int i=0,curr=0,max=0,count;
		for(i=1 ; i<=n ; ++i)
		{
			curr=dequeue(tempQueue);
			if(i==1) max=curr-1;
			if(curr>max && i<=k)
			{
				max=curr;
			}
			enqueue(tempQueue,curr);
		}
	return max;
}
int findMax_Stack(stack* tempStack)
{
	int max=0;
	if(tempStack)
		max=tempStack->data-1;
	while(tempStack)
	{
		if(tempStack->data>max)
			max=tempStack->data;
		tempStack=tempStack->next;
	}
	return max;
}
int findMin_Stack(stack* tempStack)
{
	int min=0;
	if(tempStack)
		min=tempStack->data+1;
	while(tempStack)
	{
		if(tempStack->data<min)
			min=tempStack->data;
		tempStack=tempStack->next;
	}
	return min;
}
int findMax_Queue(queue* tempQueue)
{
	int max=0;
	if(tempQueue)
		max=tempQueue->data-1;
	while(tempQueue)
	{
		if(tempQueue->data>max)
			max=tempQueue->data;
		tempQueue=tempQueue->next;
	}
	return max;
}
int findMin_Queue(queue* tempQueue)
{
	int min=0;
	if(tempQueue)
		min=tempQueue->data+1;
	while(tempQueue)
	{
		if(tempQueue->data<min)
			min=tempQueue->data;
		tempQueue=tempQueue->next;
	}
	return min;
}
void reorder(queue** tempQueue,int max,int n,int *count)
{
	int i=0,curr=0;
	for(i=1 ; i<=n ; ++i)
	{
		curr = dequeue(tempQueue);
		if(curr==max)
		{
			++(*count);
		}
		if (curr != max)
		{
			enqueue(tempQueue,curr);
		}
	}
	for(i=0 ; i<(*count) ; ++i)
	enqueue(tempQueue,max);
}
int take_length_queue(queue* tempQueue)
{
	int length=0;
	while(tempQueue)
	{
		++length;
		tempQueue=tempQueue->next;
	}
	return length;
}
double descending_stack(stack* stack_)
{
	double start=0,end=0,stack_cpu_time_used=0;
	stack* tempStack=NULL;
	copyStack(stack_,&tempStack);

	start=clock();
	sortStack(&tempStack);
	while(tempStack)
	{
		printf("%d ",tempStack->data);
		tempStack=tempStack->next;
	}
	end=clock();
	printf("\n");
	stack_cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	return stack_cpu_time_used;
}
void sortStack(stack** head)
{
	int temp;
	
	if(emptyCheckStack(head))
	{
		temp=pop(head);
		sortStack(head);
		insert_Stack(head,temp);
	}
}
void insert_Stack(stack** head,int temp)
{
	int temp_second;
	if((*head)==NULL||((*head)->data)<temp)
	{
		push(head,temp);
		return;
	}
	temp_second=pop(head);
	insert_Stack(head,temp);
	push(head,temp_second);
}
int pop(stack** head)
{
	int tempData=0;
	stack* temp;
	temp=(*head);
	tempData=(*head)->data;
	(*head)=(*head)->next;
	free(temp);
	return tempData;
}
void push(stack** head,int data)
{
	stack* newNode=NULL;
	if((*head)==NULL)
	{
		(*head)=(stack*)malloc(sizeof(stack));
		(*head)->data=data;
		(*head)->next=NULL;
	}
	else
	{
		newNode=(stack*)malloc(sizeof(stack));
		newNode->data=data;
		newNode->next=(*head);
		*head=newNode;
	}
}
void copyStack(stack* stack_,stack** tempStack)
{
	if(stack_)
	{
		copyStack(stack_->next,tempStack);
		push(tempStack,stack_->data);
	}
}
void copyQueue(queue* queue_,queue** tempQueue)
{
	if(queue_)
	{
		enqueue(tempQueue,queue_->data);
		copyQueue(queue_->next,tempQueue);
	}
}
/* Thanks to recursion method  */
void descending_BST(bst* bst_)
{
	if(bst_!=NULL)
	{
		descending_BST(bst_->rightChild);
		printf("%d ",bst_->data);
		descending_BST(bst_->leftChild);
	}
}
/* Queue Filling */
queue* queue_filling(int data[SIZE])
{
	int i=0;
	queue* queueHead=NULL;

	for(i=0 ; i<SIZE ; ++i)
	{
		enqueue(&queueHead,data[i]);
	}
	return queueHead;
}
/* Stack Filling */
stack* stack_filling(int data[SIZE])
{
	int i=0;
	stack* stackHead=NULL;
	for(i=0 ; i<SIZE ; ++i)
	{
		push(&stackHead,data[i]);
	}
	return stackHead;
}
int emptyCheckStack(stack** head)
{
	if(*head) return 1;
	return 0;
}
/* Denqueue operation for queue data structure */
int dequeue(queue** head)
{
	int tempData=0;
	queue* temp;
	if(head)
	{
		temp=(*head);
		tempData=(*head)->data;
		(*head)=(*head)->next;
		free(temp);
		return tempData;
	}
}
/* Enqueue operation for queue data structure */
void enqueue(queue** head,int data)
{
	queue* temp=NULL;
	queue* newNode=NULL;

	if(*head==NULL)
	{
		(*head)=(queue*)malloc(sizeof(queue));
		(*head)->data=data;
		(*head)->next=NULL;
	}
	else
	{
		temp=(*head);
		while(temp->next!=NULL){
			temp=temp->next;
		}
		newNode=(queue*)malloc(sizeof(queue));
		newNode->data=data;
		newNode->next=NULL;
		temp->next=newNode;
	}
}
/* Constracting new Tree  */
bst* create_tree(bst* bstHead,int data)
{
	if(bstHead==NULL)
	{
		return newTree(data);
	}
	else if(data>bstHead->data)	bstHead->rightChild=create_tree(bstHead->rightChild,data);
	else	bstHead->leftChild=create_tree(bstHead->leftChild,data);
}
/* Binary Tree Filling  */
bst* bst_filling(int data[SIZE])
{
	int i=0;
	bst* bstHead=NULL;
	bst* tempHead=NULL;

	bstHead=create_tree(bstHead,data[0]);
	tempHead=bstHead;
	for(i=1 ; i<=SIZE-1 ; ++i)
	{
		tempHead=create_tree(tempHead,data[i]);
	}
	return bstHead;
}
/* Creating new tree */
bst* newTree(int data)
{
	bst* newTree=(bst*)malloc(sizeof(bst));
	newTree->data=data;
	newTree->leftChild=NULL;
	newTree->rightChild=NULL;
	return newTree;
}