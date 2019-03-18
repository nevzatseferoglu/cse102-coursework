/*** Definition *** */
#include <stdio.h>
#define MAX 5
#define MAXIMUM 30 /* I used for sscanf() function to divide my string in proportional type  */
#define SIZE 10 
#define EXAM 2
#define clear() printf("\033[H\033[J")  	 	/* It is using for clean the terminal screen */
int add(int number1,int number2);				/* Function for Calculation */
int sub(int number1,int number2);
int mult(int number1,int number2);
int divs(int number1,int number2);
int mod(int number1,int number2);
int toPow(int number1,int number2);
int doit (int cal(),int first_number,int second_number);	/* Doit functiona , callign function as a parameter */
int take_grades(int[] );
int take_exam_grades(int[]);
double calculate_homework(int[]);		/* Calculation of Lab Grades */
double calculate_lab(int[]);			/* Calculation of Lab Grades */
double calculate_all(int,int[],int);    /* Calculation of All Grade Value */
void shape();							/* Printing Shape */			
void calculator();						/* Void Calculator Function  */
void grade_average();					/* Void  Grade_average Functionas */
int main()
{
	clear();
	int choice,situation=1;
	while(situation)
	{
				printf("**** Welcome to the Program ****\n");				/* Munu */
				printf("Press  (1) to Calculator \n");
				printf("Press  (2) to Calculate Average Grade \n");
				printf("Press  (3) to Printing the Shape \n");
				printf("Press  (4) to Quit\n");
				printf("Choice : ");
				scanf("%d",&choice);										/* Getting value of choice */				
				clear();
		switch(choice)
		{
			case 1:	
				clear();
				calculator();									
				break;
			case 2:
				clear();
				grade_average();
				break;				
			case 3:
				clear();
				shape();
				break;
			case 4:
			if(choice==4){	
				printf("Exiting ... \n");		
				situation=0;				 	/*Controlling While loop with Logic operation  */
			}	
				break;
			default:
			getchar();
				break;	
		}
	}
		return 0;
}
int add(int number1,int number2){ 	/* Addition */
	return number1+number2;
}
int sub(int number1,int number2){ 	/* Substraction */
	return number1-number2;
}
int mult(int number1,int number2){	/* Multification */

	return number1*number2;
}
int divs(int number1,int number2){ 	/* Division */
	return number1/number2;
}
int mod(int number1,int number2){  	/* Modula Operation */

	return number1%number2;
}
int toPow(int number1,int number2){ 	/* to Make Power Operation */
	int i=0,temp=number1;
	if(number2==0)
		return 1;
	else if(number2<-1)
		return 0;
	for(i=0 ; i<number2-1 ; ++i){
		number1=temp*number1;
	} 
	return number1;
}
int doit (int cal(),int first_number,int second_number){ 	/* Passing Function  as a Parameter to Another Function */
	
	int value;  					
	value=cal(first_number,second_number);
	return value;
}
int take_grades(int grade[] ){
	
	for(int i=0 ; i<SIZE ; ++i){
		printf("%d . Grade : ",i+1);
		scanf("%d",&grade[i]);
	}
	return 0;
}
int take_exam_grades(int grade[]){
	for(int i=0 ; i<EXAM ; ++i){
		if(i==0) 			 printf("Midterm Grade :");
		else if(i==EXAM-1) 	 printf("Final Grade :");
		scanf("%d",&grade[i]);
	}
	return 0;
}
double calculate_homework(int homework[]){
	double average;
	int i=0;
	for(i=0 ; i<SIZE-1 ;++i){
		homework[i+1]=homework[i+1]+homework[i];
	}
	average=homework[SIZE-1]/SIZE;
	return average;
}
double calculate_lab(int lab[]){
	double average=0;
	int i;
	for(i=0 ; i<SIZE-1 ;++i){
		lab[i+1]=lab[i+1]+lab[i];
	}
	average=lab[SIZE-1]/SIZE;
	return average;
}
double calculate_all(int lab,int exam[],int hw){

	double average;
	average=(double)(hw*1+lab*2+(exam[0]*3)+(exam[1]*4))/10;
	return average;
}
void shape(){
	int i=0,j=0,counterA=0,counterB=2,height=0;
	printf("Height : ");
	scanf("%d",&height);
	
	for(i=0 ; i<height ; ++i)			/* Printing the upper side of the shape */
	{
		for(j=0 ; j<height-1-i ; ++j)
			printf(" ");
		if(i==0)
			counterB=0;
		printf("/");
		for(j=0 ; j<counterA+counterB ; ++j)
			printf("*");
		printf("\\\n");
		counterA+=2;
	}
	counterB=2;
	counterA=(height-2)*2;
	for(i=height ; i>0 ; --i)			/* Printing the lower side of computer  */
	{
		for(j=height-i ; j>0 ; --j)
			printf(" ");
		if(i==0)
			counterB=0;
		printf("\\");
		for(j=counterA+counterB  ; j>0 ; --j)
			printf("*");
		printf("/\n");
		counterA-=2;
	}
}
void calculator(){
	int initial_Number=0,counterA=0,counterB=0,i=0,k=0;  		/*First Value of My Calculator */
	int firstComponent=0,secondComponent=0,quit=1,exit=1;
	char signComponent[2]={0},collectorInput[MAXIMUM]={0},controlChar;

	 printf("\t\t\t****_Calculator_****\n");	/* Description of the using of Calculator */
	 printf("Usage Example :\n It must be exactly the as same as this example! \n+ 5 6\n11\n+ 5\n16\n- 2\n14\nLets Start !\n\n");
	 printf("(+)  Addition       Operation\n");
	 printf("(-)  Substraction   Operation\n");
	 printf("(*)  Multiplication Operation\n");
	 printf("(/)  Division       Operation\n");
	 printf("(**) Exponential    Operation\n");
	 printf("(%%)  Modula         Operation\n");
	 printf("(Q)  Quit  \n");

	 printf("\n");
	 while(exit)
	 {
	 		scanf(" %[^\n]s",collectorInput);	/* Getting string from user untill he/she press enter key */
	 		while(collectorInput[k]!='\0')
	 		{
				if(collectorInput[k]==' ')		/* Calculating hwo many white space there is in the string */
					++counterA;
				++k;
			}
			k=0;
			if(collectorInput[0]=='Q'||collectorInput[0]=='q') break;
			if(counterA==1) 		sscanf(collectorInput," %s %d",signComponent,&firstComponent); 	/* Checking with if statement */
			else if(counterA==2)    sscanf(collectorInput," %s %d %d ",signComponent,&firstComponent,&secondComponent);
			else if(counterA>2) 	printf("Invalid Input! Try Again \n");

			while(signComponent[k]!='\0'){  /* Checking with if statement */	  
				++counterB;
				++k;
			}
			k=0;
			if(counterB==1&&counterA==1) 		/* CounterA == Amount of line in the string */
			{									/* CounterB == Amount of character in signComponent String */
				if(signComponent[0]=='+'){   	/* Addition */
					initial_Number=doit(add,firstComponent,initial_Number);
					printf("%d\n",initial_Number);
				}
				else if(signComponent[0]=='-'){	/* Substraction */
					initial_Number=doit(sub,initial_Number,firstComponent);
					printf("%d\n",initial_Number);
				}
				else if(signComponent[0]=='/'){ /* Division */
					if(firstComponent==0) printf("Division by zero is undefined! Try Again. \n");
					else{
					initial_Number=doit(divs,initial_Number,firstComponent); 
						printf("%d\n",initial_Number);
					}
				}
				else if(signComponent[0]=='%'){ /* Modula Operation */
					if(firstComponent==0) printf("Malformed Expression! Try Again.\n");
						else{
						initial_Number=doit(mod,initial_Number,firstComponent);
						printf("%d\n",initial_Number);
					}
				}
				else if(signComponent[0]=='*'){/* Multification */
					initial_Number=doit(mult,firstComponent,initial_Number);
					printf("%d\n",initial_Number);
				}
				else printf("Invalid Input! Try Again \n");
			}
			else if(counterB==1&&counterA!=1)
			{
				if(signComponent[0]=='+'){
					initial_Number=doit(add,firstComponent,secondComponent);
					printf("%d\n",initial_Number);
				}
				else if(signComponent[0]=='-'){
					initial_Number=doit(sub,firstComponent,secondComponent);
					printf("%d\n",initial_Number);
				}
				else if(signComponent[0]=='/'){
					if(secondComponent==0) printf("Division by zero is undefined! Try Again. \n"); /* Checking whether It is divided by zero or not */
					else{
					initial_Number=doit(divs,firstComponent,secondComponent); 
						printf("%d\n",initial_Number);
					}
				}
				else if(signComponent[0]=='%'){
						if(secondComponent==0) printf("Malformed Expression! Try Again.\n"); /* Checking whether there is modula operation with zero or not */
						else{
						initial_Number=doit(mod,firstComponent,secondComponent);
						printf("%d\n",initial_Number);
					}
				}
				else if(signComponent[0]=='*'){
					initial_Number=doit(mult,firstComponent,secondComponent);
					printf("%d\n",initial_Number);
				}
				else printf("Invalid Input! Try Again \n");

			}
			else if(counterB>1&&counterA==1){
					initial_Number=doit(toPow,initial_Number,firstComponent);
					printf("%d\n",initial_Number);
			}
			else if(counterB>1&&counterA!=1){
				if(counterA==0) printf("Invalid Input! Try Again \n");
				else{
					initial_Number=doit(toPow,firstComponent,secondComponent);
					printf("%d\n",initial_Number);
				}	
			}
			else printf("Invalid Input! Try Again \n");
			counterA=0;
			counterB=0;
		}
		exit=0;
}
void grade_average(){
	int i;
	double lab_Average,hw_Average;
	int homework_Grade[SIZE]={0};
	int lab_Grade[SIZE]={0};
	int exam_Grade[EXAM]={0};
	printf("Enter homework grade respectively : \n");
	take_grades(homework_Grade);
	printf("Enter lab grade respectively :\n");
	take_grades(lab_Grade);
	take_exam_grades(exam_Grade);
	lab_Average=calculate_lab(lab_Grade);
	hw_Average=calculate_homework(homework_Grade);
	printf("Total Grade Average : %.1lf   \n",calculate_all(lab_Average,exam_Grade,hw_Average));
}