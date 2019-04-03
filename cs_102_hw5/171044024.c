/*************************************************/
/*	  CSE-102 Computer Programming - Hw-5 		 */
/*    NEVZAT SEFEROGLU							 */
/*	  171044024					 				 */
/*    The Word Hunter Game  					 */
/*************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define DICT_SIZE 15  /* amount of word in the dictionary */
#define WORD_LEN 10   /* max length of the word which is in dictionary*/
#define LINE_LEN 18   /*max lenght size of the line */
#define clear() printf("\033[H\033[J") /* Cleaning The Terminal */

void reverseF(char* str);
void make_uppercase(char area[DICT_SIZE][DICT_SIZE],int x,int y,char *pre_user,int k,int score);
int str_cmp(char *strA,char *strB);
void showPuzzle(char area[DICT_SIZE][DICT_SIZE]);
void filling_area(char area[DICT_SIZE][DICT_SIZE] , int coord[DICT_SIZE][4],char *dict[DICT_SIZE]);
int check_user_coord(int x,int y,char area[DICT_SIZE][DICT_SIZE],char *pre_user,int i);
int check_user_string(char *pre_user,char *dict[DICT_SIZE]);
char random_character_creator();

int get_line_size(char *line){
    char *ch_iter = line; // so as not to lose beginning of line
    int counter = 0;
    // go until you see new line or null char
    while(*ch_iter != '\n' && *ch_iter != '\0'){
        ch_iter++; // next char
        counter++; // increment counter
    }
    return counter;
}
void copy_string(char *source, char *destination){
    // get iterators over original pointers
    char *src_iter = source;
    char *dst_iter = destination;
    // until null char
    while (*src_iter != '\0'){
        // copy pointers
        *dst_iter = *src_iter;
        // advance to next char
        src_iter++;
        dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}
void remove_newline(char *line){
    char *ch_iter = line;
    // go until you see new line
    while(*ch_iter != '\n'){
        ch_iter++; // next char
    }
    *ch_iter = '\0'; // overwrite new line
}
void print_dictionary(char *dict[]){
    int i;
    for(i = 0 ; i < DICT_SIZE ; i++){
        printf("%s\n", dict[i]);
    }
}
void print_coord(int coord[DICT_SIZE][4]){
    int i, j;
    for(i = 0 ; i < DICT_SIZE ; i++){
        for(j = 0 ; j < 4 ; j++){
            printf("%d ", coord[i][j]);
        }
        printf("\n");
    }
}
int main()
{
	clear();
	srand(time(NULL));    			/* to get random  number in real time */
    char *dict[DICT_SIZE];			/* decleartion of pointer array */
    int  coord[DICT_SIZE][4],i=0,j=0,x=-1,y=-1,score=0,exit=1,iter=0,k=0;
    char line[LINE_LEN];			
    char pre_user[WORD_LEN]={'\0'}; /* initialization of char array for keeping the string which is typed by the user */
    char area[15][15]={'\0'};       /* area for display */
    int  coord_Control_A=0,coord_Control_B=0;  


    FILE *fp = fopen("word_hunter.dat", "r");
    if(fp == NULL)
      printf("Error!"); /* Controlling the .dat file whether it is empy or not */

    int line_counter = 0;
    int dict_counter = 0;
    while(fgets(line, LINE_LEN, fp) != NULL){
        if(line_counter%5 == 0){
            dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
            remove_newline(line);
            copy_string(line, dict[dict_counter]);
        }
        else if (line_counter%5 == 1){
            coord[dict_counter][0] = atoi(line);
        }
        else if (line_counter%5 == 2){            
            coord[dict_counter][1] = atoi(line);        
        }
        else if (line_counter%5 == 3){
            coord[dict_counter][2] = atoi(line);
        } 
        else if (line_counter%5 == 4){
            coord[dict_counter][3] = atoi(line);
            dict_counter++;
        }
        line_counter++;
    }
    filling_area(area,coord,dict);
    while(score!=DICT_SIZE&&exit){
    	clear();
        showPuzzle(area);
        printf("Word : ");   							/* Getting string from the user */
        scanf(" %[^\n]s",pre_user);						/* With Using Scanset Method , I get the string untill the user press enter key */
        if(str_cmp(pre_user,"exit game")==0)			/* Checking with exit statement */
            exit=0;
        if(check_user_string(pre_user,dict)==1){
            printf("---> Word is correct !\n");			/* Row Code */
            while(x>DICT_SIZE-1||x<0){
            printf("---> Row Code of the Word: ");		/* Column Code */
            scanf(" %d",&x);
            }
            while(y>DICT_SIZE-1||y<0){
            printf("---> Column Code of the Word: ");
            scanf(" %d",&y);
            }
            if(check_user_coord(x,y,area,pre_user,iter)==1){
                make_uppercase(area,x,y,pre_user,k,++score);
            }
        }
        x=-1,y=-1,i=0;
    }
    if(exit==0)
    printf("Exiting ...\n");
    else
    printf("***You found all the world in the puzzle , Congratulations! ***\n");
    fclose(fp);
    return 0;
}
char random_character_creator(){ /* Rondom Creator Function */
    int c=rand()%123;
    while(c<97||c>122)
    c=rand()%123;
    return c;
}
void filling_area(char area[DICT_SIZE][DICT_SIZE],int coord[DICT_SIZE][4],char *dict[DICT_SIZE]){
	/* This function get the three different parameter to fill the area in the puzzle */
	/* There are eight(8) different situation to fill and I checked the situation seperately  */
    int coord_Control_A=0,coord_Control_B=0,k=0,i=0,t=0;
    /* Rows are constant columns are different , their magnitudes are different */
    for(i=0 ; i<DICT_SIZE; ++i)
    {
        if(coord[i][0]==coord[i][2]&&coord[i][3]<coord[i][1]) 
        {
            coord_Control_A=coord[i][3];
            while(*(dict[i]+k)!=13){
                area[coord[i][0]][coord_Control_A]=*(dict[i]+k);
                ++k;
                ++coord_Control_A;
            }
            k=0;
            coord_Control_A=0;
        }
/* --------------------------------------------------------------------------- ----------------*/
        /* Rows are constant columns are different , their magnitudes are different */
        else if(coord[i][0]==coord[i][2]&&coord[i][1]<coord[i][3])
        {
            coord_Control_A=coord[i][1];
            while(*(dict[i]+k)!=13){
                area[coord[i][0]][coord_Control_A]=*(dict[i]+k);
                ++k;
                ++coord_Control_A;
            }
            k=0;
            coord_Control_A=0;  
        }
/* --------------------------------------------------------------------------- ----------------*/
        /* Column are constant Rows are different , their magnitudes are different */
        else if(coord[i][1]==coord[i][3]&&coord[i][2]>coord[i][0])
        {
            coord_Control_A=coord[i][0];
            while(*(dict[i]+k)!=13){
                area[coord_Control_A][coord[i][1]]=*(dict[i]+k);
                ++k;
                ++coord_Control_A;
            }
            k=0;
            coord_Control_A=0;
        }
/* --------------------------------------------------------------------------- ----------------*/        
        /* Both Colums and Rows are different , their magnitudes are different */
        else if(coord[i][1]==coord[i][3]&&coord[i][0]>coord[i][2])
        {
            coord_Control_A=coord[i][0];
            while(*(dict[i]+k)!=13){
                area[coord_Control_A][coord[i][1]]=*(dict[i]+k);
                ++k;
                --coord_Control_A;
            }
            k=0;
            coord_Control_A=0;
        }
/* --------------------------------------------------------------------------- ----------------*/        
        /* Both Colums and Rows are different , their magnitudes are different */
        else if(coord[i][2]>coord[i][0]&&coord[i][3]>coord[i][1])
        {
            while(*(dict[i]+t)!=13)
                ++t;
            coord_Control_A=coord[i][0];
            coord_Control_B=coord[i][1];
            for(k=0 ; k<t ; ++k){
                area[coord_Control_A][coord_Control_B]=*(dict[i]+k);
                ++coord_Control_A;
                ++coord_Control_B;
            }
            t=0,k=0,coord_Control_B=0,coord_Control_A=0;
        }
/* --------------------------------------------------------------------------- ----------------*/        
        /* Both Colums and Rows are different , their magnitudes are different */
        else if(coord[i][2]>coord[i][0]&&coord[i][1]>coord[i][3]){
            while(*(dict[i]+t)!=13)
                ++t;
            coord_Control_A=coord[i][0];
            coord_Control_B=coord[i][1];
            for(k=0 ; k<t ; ++k)
            {
                area[coord_Control_A][coord_Control_B]=*(dict[i]+k);
                ++coord_Control_A;
                --coord_Control_B;
            }
            t=0,k=0,coord_Control_B=0,coord_Control_A=0;
        }
/* --------------------------------------------------------------------------- ----------------*/        
        /* Both Colums and Rows are different , their magnitudes are different */
        else if(coord[i][0]>coord[i][2]&&coord[i][3]>coord[i][1]){
            while(*(dict[i]+t)!=13)
                ++t;
            coord_Control_A=coord[i][0];
            coord_Control_B=coord[i][1];
            for(k=0 ; k<t ; ++k){
                area[coord_Control_A][coord_Control_B]=*(dict[i]+k);
                --coord_Control_A;
                ++coord_Control_B;
            }
            t=0,k=0,coord_Control_B=0,coord_Control_A=0;
        }
/* --------------------------------------------------------------------------- ----------------*/        
        /* Both Colums and Rows are different , their magnitudes are different */
        else if(coord[i][0]>coord[i][2]&&coord[i][1]>coord[i][3])
        {
            while(*(dict[i]+t)!=13)
                ++t;
            coord_Control_A=coord[i][0];
            coord_Control_B=coord[i][1];
            for(k=0 ; k<t ; ++k)
            {
                area[coord_Control_A][coord_Control_B]=*(dict[i]+k);
                --coord_Control_A;
                --coord_Control_B;
            }
            t=0,k=0,coord_Control_B=0,coord_Control_A=0;
        }
    }
}
int check_user_coord(int x,int y,char area[DICT_SIZE][DICT_SIZE],char *pre_user,int i){
	/* This function get the coordinate from the main and check the coordinate is true or not */
	/* There are eight(8) different situation to fill and I checked the situation seperately  */
	/* I also used recursion with reversing the string , normally I got 16 different situation but with using reverse operation*/
	/* Thanks to recursion and reverse operation ,  I could check both last and first coordinate of the string */
	/* I equalized the variables with zero at the end of the each way of operation */
    int j=0,counter=0,size=0,exit=1;
    /* Measuring the size of string */
    while(pre_user[size]!='\0')
        ++size;
    /* --------------------------------------------------------------------------- ----------------*/
    /* Direction : North  Checking */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        --x;
    }
    if(counter==size)
        return 1;
    x=x+size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
    /* Direction : South  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        ++x;
    }
    if(counter==size)
        return 1;
    x=x-size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
    /* Direction : East  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        ++y;
    }
    if(counter==size)
        return 1;
    y=y-size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
/* Direction : West  Checking  */    
    for(j=0 ; j<size ; ++j){

        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        --y;
    }
    if(counter==size)
        return 1;
    y=y+size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
    /* Direction : Noth and East  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        ++y,--x;
    }
    if(counter==size)
        return 1;
    x=x+size,y=y-size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
	/* Direction : South and West Checking  */    
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        --y,++x;
    }
    if(counter==size)
        return 1;
    y=y+size,x=x-size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
    /* Direction : Noth and West  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        --y,--x;
    }
    if(counter==size)
        return 1;
    y=y+size,x=x+size,counter=0;
/* --------------------------------------------------------------------------- ----------------*/
    /* Direction : South and East Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||area[x][y]==(*(pre_user+j)-32))
            ++counter;
        ++y,++x;
    }
    if(counter==size)
        return 1;
    y=y-size,x=x-size,counter=0;
    if(i==0){
        reverseF(pre_user); 	/* Recursive Operation to control the whether input coordinate is last or not */
        check_user_coord(x,y,area,pre_user,++i);
    }
    else
    return -1;
}
int check_user_string(char *pre_user,char *dict[DICT_SIZE]){
    int i=0;
    for(i=0 ; i<DICT_SIZE ; ++i){
        if(str_cmp(dict[i],pre_user)==13)
        return 1;
    }
        return -1;
}
void make_uppercase(char area[DICT_SIZE][DICT_SIZE],int x,int y,char *pre_user,int k,int score){
	/* This function get area and coordinate from  the main and make uppercase */
	/* There are eight(8) different situation to make uppercase and I checked the situation seperately */
	/* I also used recursion with reversing the string , normally I got 16 different situation but with using reverse operation*/
	/* Thanks to recursion and reverse operation ,  I could check both last and first coordinate of the string */
	/* I equalized the variables with zero at the end of the each way of operation */
    int i=0,j=0,size=0,counter=0;
    while(pre_user[size]!='\0')
        ++size;
    /* --------------------------------------------------------------------------- ----------------*/
    /* Direction : North  Checking */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        --x;
    }
    x=x+size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
            area[x][y]=area[x][y]-32;
            --x;
        }
    }
    counter=0;
    /* --------------------------------------------------------------------------- ----------------*/
    /* Direction : South  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        ++x;
    }
    x=x-size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
            area[x][y]=area[x][y]-32;
            ++x;
        }
    }
    counter=0;
    /* --------------------------------------------------------------------------- ----------------*/
    /* Direction : East  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        ++y;
    }
    y=y-size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
            area[x][y]=area[x][y]-32;
            ++y;
        }
    }
    counter=0;
/* --------------------------------------------------------------------------- ----------------*/
	/* Direction : West  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        --y;
    }
    y=y+size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
            area[x][y]=area[x][y]-32;
            --y;
        }
    }
    counter=0;
/* --------------------------------------------------------------------------------------------*/
    /* Direction : Noth and East  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        ++y,--x;
    }
    x=x+size,y=y-size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
            area[x][y]=area[x][y]-32;
            ++y,--x;
        }
    }
    counter=0;
/* --------------------------------------------------------------------------------------------*/
	/* Direction : South and West Checking  */ 
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        --y,++x;
    }
    y=y+size,x=x-size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
            area[x][y]=area[x][y]-32;
            --y,++x;
        }
    }
    counter=0;
/* --------------------------------------------------------------------------------------------*/
    /* Direction : Noth and West  Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        --y,--x;
    }
    y=y+size,x=x+size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
        area[x][y]=area[x][y]-32;
        --y,--x;
        }
    }
    counter=0;
/* --------------------------------------------------------------------------------------------*/
    /* Direction : South and East Checking  */
    for(j=0 ; j<size ; ++j){
        if(area[x][y]==*(pre_user+j)||((area[x][y])>=65&&(area[x][y])<=90))
            ++counter;
        ++y,++x;
    }
    y=y-size,x=x-size;
    if(counter==size){
    	++score;
        for(j=0 ; j<size ; ++j){
        	if(!((area[x][y])>=65&&(area[x][y])<=90))
        	area[x][y]=area[x][y]-32;
        ++y,++x;
        }
    }
    counter=0;
    if(k==0){
        reverseF(pre_user);  /* Recursive Operation to control the whether input coordinate is last or not */
        make_uppercase(area,x,y,pre_user,++k,score);
    }
}
int str_cmp(char *strA,char *strB){
    while(*strA==*strB&&*strB!='\0'&&*strA!='\0'){
        ++strA;
        ++strB;
    }
    return *strA-*strB;
}
void reverseF(char* str){  		/* Reverse Function */
    char temp,t=0,size=0,i=0;
    while(str[i]!='\0')
        ++i;
    size=i/2;
    while(size>0){
    temp=str[t];
    str[t]=str[i-1];
    str[i-1]=temp;
    ++t,--i,--size;
    }
}
void showPuzzle(char area[DICT_SIZE][DICT_SIZE]){ 			/* Filling the area Randomly */
    int i=0,j=0;
    printf("\t\t\t\t*** Welcome to the Word Puzzle Game ***\n");
    printf("**Rules : \n");
    printf("--> You can validate your detection with typing the beginning or the last coordinate of the word and  with typing the word itself.\n");
    printf("--> If both coordinate and word are correct , all letters of the word will be uppercase.\n");
    printf("--> There are %d word  in the puzzle!\n",DICT_SIZE);
    printf("*** Lets Start ! ***\n\n");
    printf("\n");
    printf("    ");
    for(i=0 ; i<15 ; ++i)
    	printf("%2d ",i);
    printf("\n");
    for(i=0 ; i<DICT_SIZE ; ++i){
        printf(" %2d ",i);
        for(j=0 ; j<DICT_SIZE ; ++j){ 				
            if(area[i][j]=='\0')
                area[i][j]=random_character_creator(); /* Filling the area Randomly */
                printf("%2c ",area[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}