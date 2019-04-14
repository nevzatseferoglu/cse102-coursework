#include <stdio.h>
/*--------------------------------------*/
/*--GTU-CSE-102-C-Programming (HW6)-----*/
/*--NEVZAT SEFEROGLU--------------------*/
/*--171044024---------------------------*/
/*--RECURSION---------------------------*/
/*--------------------------------------*/
#define clear() printf("\033[H\033[J") 	/* Cleaning The Terminal */
#define MAX 100	/* Max value int arrays Sıze  */

int great_common_divisor(int numberA,int numberB);
char first_capital_letter(char *str);
void mathFunction(int num); /* calculating math function which is  given recursively */
void merge_sort(int *arr,int right,int left); /**/ 
void merge(int numbers[], int temp[], int left, int mid, int right); /**/
void digits_check(int num,int sum,int checkNum,int digits,int tempDigits); /**/
void fill_multiplier(int num,int *arr,int primeCheck,int i); /**/
void string_cleaner(char *str); /* make  */
void array_cleaner(int *arr,int amount); /* filling int array with zero */
int isPrime(int num); /* Checking function */
int calculate_digits(int num,int temp); /* counting digits number */
int power_operation(int base,int digits); /* to make exponenetial operation */
void m_sort(int numbers[], int temp[], int left, int right); /* Merge Sort Subfunction */
void menu(); /* Menu void function all the function and variable in it */

int main(){ 	/* Main Function   */

	clear(); 	
	menu();  	/* Menu Function   */
	return 0;
}

void menu()
{
	int choice=-1,numberA=0,numberB=0,arrA[MAX],arrB[MAX],num=0,sum=0,i=0,exit=1,digits,length=0;
	char str[MAX]={'\0'};
	while(exit)
	{
		while(choice<1||choice>6)
		{
			printf("\t\t***---Welcome to the Calculator Program---***\n\n");
			printf("(1) Great Common Divisor        (Part1)\n");/* For Part1 */
			printf("(2) Merge Sort Recursively      (Part2)\n");/* For Part2 */
			printf("(3) Math  Function              (Part3)\n"); /* For Part3 */
			printf("(4) Digits Function             (Part4)\n"); /* For Part4 */
			printf("(5) Finding Uppercase Letter    (Part5)\n");/* For Part5 */
			printf("(6) Exit\n"); /* Exit for Quitting the Program */
			printf("Choice:");	/* Choice which is taken by user */
			scanf(" %d",&choice); /* Choice which is taken by user */
		}
		clear();
		switch(choice)
		{
		/*-----------------------------------------------------------------------------------*/
		/* I take two number from user and with using helper function that I wrote on my own  */
		/* I also calculate the multipler of each function */
		/* My arrays size is already defined at the beginning of the function*/
			case 1:
				array_cleaner(arrA,MAX),array_cleaner(arrB,MAX);
				numberA=-1;
				numberB=-1;
				while(numberA<0){
					printf("First Number : ");
					scanf(" %d",&numberA);  /* First  Number */
				}

				while(numberB<0){
					printf("Second Number : ");
					scanf(" %d",&numberB);	/* Second Number */
				}
				fill_multiplier(numberA,arrA,2,i),fill_multiplier(numberB,arrB,2,i);
				printf("\nMultipliers of  %3d : {",numberA);
				for(i=0 ; arrA[i]!=0 ; ++i)
				printf(" %d ",arrA[i]);
				printf("}\n");
				printf("Multipliers of  %3d : {",numberB);
				for(i=0 ; arrB[i]!=0 ; ++i)
				printf(" %d ",arrB[i]);
				printf("}\n\n");
				i=0;
				if(numberA>numberB) printf("Greate Common Divisor : %d\n\n",great_common_divisor(numberA,numberB));/*Great Common Divisor Function*/
				else 				printf("Greate Common Divisor : %d\n\n",great_common_divisor(numberB,numberA));/*Great Common Divisor Function*/
			break;

			/*---------------------------------------------------------------------------------*/
			
			case 2:
			length=-1;
			printf("Enter the length of the list (under the MAX<=%d): ",MAX);
			while(length<1)
			scanf(" %d",&length);	/* Lenght of the array which is taken by user */
			
			for(i=0 ; i<length ; ++i)
			scanf("%d",&arrA[i]);
		
			m_sort(arrA,arrB,0,length-1); /* Merge Sorting ALgorithm */
			printf("Sorted array is : ");
			
			for(i=0 ; i<length ; ++i)
			printf("%d ",arrB[i]);
			printf("\n\n");

			break;
			/*-----------------------------------------------------------------------------------*/
			case 3:
				printf("Enter the Number : ");
				scanf(" %d",&num); /* number for math function */
				mathFunction(num);
				printf("\n\n");
			break;
			/*-------------------------------------------------------------------------------------*/
			case 4:
				printf("Enter the Number : ");
				scanf(" %d",&num); /* number for digits function */
				digits=calculate_digits(num,0);
				digits_check(num,sum,num,digits,digits);
			break;
			/*------------------------------------------------------------------------------*/
			case 5:
				printf("Enter the String :"); /* getting string from user */
				scanf(" %[^\n]s",str);
				printf("First Capital Letter : %c\n\n",first_capital_letter(str));
				string_cleaner(str);
			break;
			/*------------------------------------------------------------------------------*/
			case 6:
				exit=0;
			break;
			/*------------------------------------------------------------------------------*/
		}
		choice=-1;
	}
}
int great_common_divisor(int numberA,int numberB){

	if(numberB == 0) return numberA;
  	else 			 return great_common_divisor(numberB, numberA%numberB);
}
char first_capital_letter(char *str){
	if(*str>='A'&&*str<='Z') /* Checking Character with ASCII Character under the if control*/
		return *str;
	else if(*str)
		return first_capital_letter(++str); /* incrementing of array index */
}
void mathFunction(int num){
	printf("%d ",num);  /* printing number on the screen */
	if(num>1){
		if(num%2==0&&num>0){ 	/*if checking */
			num=num/2;
			mathFunction(num);
		}
		else if(num%2==1&&num>0){ /*if checking */
			num=3*num+1;
			mathFunction(num);
		}
	}
}
void digits_check(int checkNum,int sum,int num,int digits,int tempDigits){
	if(tempDigits>0){
		sum=sum+power_operation(checkNum%10,digits);/* with making exponential operation , Sum has already initialized in main */
		digits_check(checkNum/10,sum,num,digits,--tempDigits); /* Recursion */
	}
	else{
		if(sum==num) printf("Result : Equal\n\n");
		else         printf("Result : Not Equal\n\n");
	}
}
void string_cleaner(char *str){ /* Cleaning String Function */
	if
		(*str) *str='\0';
	else 
		string_cleaner(++str);
}
void fill_multiplier(int num,int *arr,int primeCheck,int i){ /* Determination of Multiplier of Function */
	if(num>=2){
		if(isPrime(primeCheck)==1&&num%primeCheck==0){  
			arr[i]=primeCheck;  	/* Assignment in fucntion */
			fill_multiplier(num/primeCheck,arr,primeCheck,++i);
		}
		else if(isPrime(primeCheck)==1&&num%primeCheck!=0||isPrime(primeCheck)==-1){
			fill_multiplier(num,arr,++primeCheck,i);
		}
	}
}
int isPrime(int num){  /* Checking function whether it is prime or not */
	int i=2,j=0;
	if(num<=1)
		return -1;
	while(i<=num/2){
		if(num%i==0)
			return -1;
		++i;
	}
	return 1;
}
void array_cleaner(int *arr,int amount){  /* Integer array cleaner function  */
	if(amount>=0){
		arr[amount]=0;
		array_cleaner(arr,--amount);
	}
}
int calculate_digits(int num,int temp){   /* Calculation of amounts of digits */
	if(num>0)
		return calculate_digits(num/10,++temp);
	return temp;
}
int power_operation(int base,int digits){ /* Exponential Operation */
	if(digits==0)  return 1;
	if(digits==1)  return base;
	if(digits-1>0) return base*power_operation(base,--digits);
}
void m_sort(int numbers[], int temp[], int left, int right)
{
    int mid;
    if (right > left){ 			/* ındex contolling */
        mid=(right + left)/2;
        m_sort(numbers,temp,left,mid); /* sending m_sort function */
        m_sort(numbers,temp,mid+1,right);
        merge(numbers,temp,left,mid+1,right);
    }
}
void merge(int numbers[], int temp[], int left, int mid, int right)
{
    int i=0,left_end=0,num_elements=0,tmp_pos=0;
    left_end=mid-1;
    tmp_pos=left;
    num_elements = right-left+1;

	while ((left <= left_end) && (mid <= right)){
            if (numbers[left]<=numbers[mid]){
                temp[tmp_pos]=numbers[left];
                tmp_pos=tmp_pos+1;
                left=left+1;
            }
    		else{
			    temp[tmp_pos]=numbers[mid];
			    tmp_pos=tmp_pos+1;
			    mid=mid+1;
            }
    }
    while (left <= left_end){
            temp[tmp_pos]=numbers[left];
            left=left + 1;
            tmp_pos = tmp_pos + 1;
    }
    while (mid <= right){	
        temp[tmp_pos]=numbers[mid];
        mid=mid+1;
        tmp_pos=tmp_pos+1;
    }
    for (i = 0; i <= num_elements; i++){
        numbers[right]=temp[right];
        right=right-1;
    }
}