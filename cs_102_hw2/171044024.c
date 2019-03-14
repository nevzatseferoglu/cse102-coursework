#include <stdio.h>		/*Nevzat Seferoglu ~ 171044024 ~ GTU  CSE-102 ~ HW2 */
#include <time.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_NUM 1024  /* alterable max amount of border for lucky game */
#define MIN_NUM 1	  /* alterable min amount of border for lucky game */
#define TRIAL 10	  /* alterable amount of trial */
#define clear() printf("\033[H\033[J") 	/* I made terminal more neat with clean() */

void menu();
void draw_mountain_road (int,int);	/*Declaration of Functions*/
int make_a_guess (int,int,int);		
void show_scores(int,int);			
void draw_hourglass (int);				
int distanceCalculator(int,int); /*Distance Calculator for Lucky Number Game */	
int toPow(int);	/* for exponentiating with two */

int main(){
	srand(time(NULL));			/* srand for getting pseudo number */
	menu();
	return 0;
}
void menu(){
	int choice,check=TRUE;	/*check is for managing the loops inside of the main function */
	int height,i=0,j=0,length=0,max_radius=0,scoreHuman=0,scoreComputer=0;
	int trial=TRIAL,counter=0,userNum=0,randomNum=0,situation=1; /*variable which I use inside of the function*/
    int minDefault=MIN_NUM,maxDefault=MAX_NUM;
	clear();
	while(check==TRUE){      			/* I used one variable to check my all loops , it was more efficient */       
		check=TRUE;
		while(check==TRUE){
		printf("***** MENU *****\n");			/* Menu for User */
		printf("1. Play Lucky Number \n");
		printf("2. Draw Hourglass \n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("Choice: ");
				scanf("%d",&choice);
				if(choice<=0||choice>4)		
					printf("This is an invalid choice.Try Again!\n\n");
				else
				check=FALSE;
		}
		check=TRUE;	
		printf("\n");
		switch(choice)
		{
			case 1:
				clear();
				randomNum=((rand()%MAX_NUM)+MIN_NUM);		/*Random Creator*/
			    printf("T:%d  LN: %d \n\n",TRIAL,randomNum); 
			    counter=0;    					 	/*I used counter for replicate the amount of trials */
			    while(counter!=trial&&situation){  /*Checking with logic opeartion*/ 
			    	userNum=make_a_guess(counter+1,minDefault,maxDefault); 	/* assignment of make_a_guess function */
			    
			        if(userNum>randomNum&&userNum<=maxDefault)	
			            maxDefault=userNum; 					/* Arranging upper band */
			        else if(userNum<randomNum&&userNum>=minDefault)
			            minDefault=userNum; 					/* Arranging lower band */
			        if(userNum<minDefault||userNum>maxDefault){
			           	printf("Invalid Interval !\n");
			        }  				        
			        if(userNum==randomNum){					 /*Sending Distance Function*/
			            printf("Distance :%d You win! \n",distanceCalculator(userNum,randomNum));
			            situation=0;
			            ++scoreHuman;					/*Counter for keep user skor in program */
			            show_scores(scoreHuman, scoreComputer);
			        }
			        else
			        printf("Distance : %d \n",distanceCalculator(userNum,randomNum));
			        ++counter;	
			    }
		    	if(situation==1){
		        printf("You lost , Computer won !\n");
		        ++scoreComputer;			/*Counter for keep computer skor in program */
		        show_scores(scoreHuman, scoreComputer);
		    	}
		    	situation=1;
		        minDefault=MIN_NUM;
		        maxDefault=MAX_NUM;
			break;

			case 2:
				clear();
				printf("Enter Positive and Odd Number for Height: ");	
				check=TRUE;
				while(check==TRUE)
				{
					scanf(" %d",&height);
					if(height<=0||((height%2)==0)){ /* Checking whether it is even or negative */
						printf("Invalid Height ! \n");
						printf("Enter Positive and Odd Number for Height: ");
					}
					else
						check=FALSE;
				}
				draw_hourglass(height);
				printf("\n");
				check=TRUE;
			break;

			case 3:
			clear();		/* clean() is for */
				check=TRUE;
				printf("Length: ");	/*Mountain Length */
				while(check==TRUE)		/* TRUE / FALSE control with check */
				{
					scanf(" %d",&length);
					if(length<=0){
						printf("Invalid Length ! \n");	/* Invalid length indicator */
						printf("Length: ");
					}
					else
					check=FALSE;	
				}
				check=TRUE;
				printf("Max Radius: ");			/* Mountain Radius */
				while(check==TRUE)
				{
					scanf("%d",&max_radius);
					if(max_radius<0){
						printf("Invalid Radius ! \n");	/* Invalid length indicator */
						printf("Max Radius: ");
					}
					else
					check=FALSE;
				}
				draw_mountain_road(length,max_radius);
				check=TRUE;
				break;
			case 4:
			clear();
				printf("Exiting ... \n");
				check=FALSE;	/*Controlled terminating initial while loop */
				break;
		}
	}	
}
int make_a_guess (int trial, int min, int max){
	int userNum;
    if(trial==1)
    printf("(Trial: %d) Make a guess between %d and %d: ",trial,MIN_NUM,MAX_NUM);
    else
    printf("(Trial: %d) Make a guess between %d and %d: ",trial,min,max);
    scanf(" %d",&userNum);
    return userNum;  
}
int distanceCalculator(int userNum , int randomNum){
    int n=TRIAL,i=0,counter=0,situation=1;					/*I used an algorithm related with exponential type*/
    userNum=userNum-randomNum; 								/*I already made a function which name is toPow to make exponential operation with 2 */
    if(userNum==0)				
    	return counter;									
    if(userNum<0)
        userNum=(-1)*userNum;
    for(i=0 ; i<n&&situation ; ++i)						/*With for loop I can measure the distance between userNum and randomNum*/
    {												/*Instead of if else statement , loop was more efficient*/
        ++counter;
        if(userNum>=toPow(i)&&userNum<toPow(i+1))		/*Checking logic variable that is inside the for loop*/
        {
            situation=0;
            return counter;								/*Counter=distance*/
        }
    }   
}
void show_scores(int score_human, int score_program){
	printf("Your Score: %d  Program Score: %d\n\n\n",score_human,score_program);		/* printing the scores */
}
int toPow(int exponent){					/* Function which can handle with */
    int i=0,base=2,temp=2;
    if(exponent==0)				
        return 1;
    for(i=0 ; i<exponent-1 ; ++i)
        base=base*temp;
    return base;
}
void draw_hourglass (int height){ 		/*Drawing Hourglass*/
	int i=0,j=0;
	for(i=0 ; i<height ; ++i)		/* It is counting the amount of line */	
	{
		if(i==0||i==height-1){				/* Ligic operation with variable named 'i' */	
			for(j=0 ; j<height ; ++j)
				printf("*");
			printf("\n");						/* for passing the new line on the terminal */	
		}	
		else{
			if(i<=(height-1)/2){	
			for(j=0 ; j<i ; ++j)
				printf(" ");					/* whitespace character */
			for(j=0 ; j<height-2*i ; ++j)
				printf("*");
			printf("\n");
			}
			else{
				for(j=0 ; j<(height-i-1) ; ++j)
					printf(" ");					/* whitespace character */
				for(j=0 ; j<(2*i-height+2) ; ++j)
					printf("*");
				printf("\n");
			}
		}
	}
}
void draw_mountain_road (int length, int max_radius){
	int i=0,j=0,k=0,halfCircular=0,test=0,situation=1;
    while(k<length)
    {
    	if(max_radius==0)
    		printf(" | ---------> Radius : 	 %d \n",max_radius);
    	else{
	        halfCircular=(rand()%(max_radius+1));		/* Getting Random Number */
	        if(test%2==0)
	        {
	        	if(halfCircular==0)			
	        		situation=0;
	            for(i=0 ; i<(halfCircular+1); ++i)
	            {
	                for(j=0 ; j<max_radius+1-i ; ++j)
	                    printf(" ");				    /* whitespace character */
	            	if(situation==0)
	            		printf("| ---------> Radius :  %d",halfCircular); /* I put the radius indicators for illustrate the radius */

	                if(i==halfCircular&&situation==1)
	                printf("|	---------> Radius :  %d",halfCircular);	
	                else if(i!=halfCircular&&situation==1)
	                printf("/");

	                printf("\n");
	            }
	            for(i=halfCircular ; i>0 && situation==1 ; --i)	/*For loop with logic operation control */
	            {
	                for(j=max_radius+2-i ; j>0 ; --j)
	                    printf(" ");
	                printf("\\\n");
	            }
	            situation=1;
	        }
	        else{
	            for(i=0 ; i<halfCircular+1 ; ++i){
	            	if(halfCircular==0){  						/*Control for come up to  over and over for zero */
	            		for(j=0 ; j<max_radius+1-i ; ++j)
	                    printf(" ");
	                	printf("| ---------> Radius :  %d",halfCircular);
	                	--test;
	                    }
	                else{	
	                for(j=max_radius+2+i ; j>0 ; --j)
	                    printf(" ");
	                if(i==halfCircular)
	                printf("|	---------> Radius :  %d",halfCircular);
	                else
	                printf("\\");
	        		}
	                printf("\n");
	            }
	            for(i=0 ; i<halfCircular ; ++i){
	                for(j=0 ; j<max_radius+1+halfCircular-i ; ++j)
	                    printf(" ");
	                printf("/\n");
	            }
	        }
    }
        ++test;	/* This are the variable that I use in the loops */
        ++k;
    }
    situation=1;	/* That variable is for logic operation for controlling the while  loop */
}