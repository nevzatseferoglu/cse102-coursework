/* --------------------------------------------------------- */
/* NEVZAT SEFEROGLU  171044024 								 */
/* MONOPOLY GAME    										 */
/* GEBZE TECHNICAL UNIVERSITY 								 */
/* HW7														 */
/* --------------------------------------------------------- */

#include <stdio.h> 			/* standart input library  */
#include <stdlib.h> 		/* for creating random number  */
#include <time.h>   		/* for creating random number  */
#define clear() printf("\033[H\033[J") 	/* Cleaning The Terminal */
#define blockNumber 20
enum player_type{noone,cap,car};
enum block_type{start, property, tax, punish};

struct player{
	enum player_type type;	/*Holds type of the player*/
	int current_block_id; 	/*Holds player location as block id*/
	int owned_block_ids[12];/*Holds property block ids that are owned by the user*/
	int account;			/*Holds amount of the current money of the player*/
	int turn_to_wait;		/*Holds number of turns to wait if the player got a punishment*/
	char * name;			/*Holds the name of the player*/
};
struct block{
	int block_id;			/*Holds id of the block*/
	char * name;			/*Holds text of the block that is shown on the top of the block*/
	int price;				/*If the block is property, holds the price of property. If the block is a taxblock than holds the tax fee and if the block is punishment block, then holds the number ofturns to wait*/
	int rent;				/*Holds the default rent of a property (no house)*/
	int rent_1;				/*Holds the rent of a property with one house*/
	int rent_2;				/*Holds the rent of a property with two houses*/
	int rent_3;				/*Holds the rent of a property with three houses*/
	int house_price;		/*Holds price of building a house on the block*/
	int house_count;		/*Holds the number of the houses on the block that are already built*/
	struct player owner;	/*Holds the owner of the block*/
	enum block_type type;	/*Holds type of the block*/
};
void gameplay (struct block board[blockNumber],struct player player_one,struct player player_two);
void init_the_board(struct block board[blockNumber]);
void show_board(struct block board[blockNumber],struct player player_one, struct player player_two);
void show_properties(struct block board[blockNumber]);
void moveGamer(struct player* player_one, struct player* player_two,int dice,int *turnPlayer);
void analysis_block(struct block board[blockNumber],struct player* player_one, struct player* player_two,int *dice,int *turnPlayer,int *choice);
void buy_property(struct block* current_block, struct player* current_player);
void passTurn(int *turnPlayer);
void payment(struct block* current_block, struct player* current_player,struct block board[blockNumber]);
void sell_property(struct block board[blockNumber],struct player* current_player);
void show_my_properties(struct player* current_player,struct block board[blockNumber]);
void buyHouse(struct player* current_player,struct block board[blockNumber]);
void round_allowance(struct block* current_block,struct player* current_player,int dice);
int main()
{
	srand(time(NULL));	/* For Pseudo Number */
	clear();
	
	struct block board[blockNumber];
	/* Initialization of Players Structures */
	struct player player_one={cap,0,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},100000,0,"cap"};	/*Initialization of player_one*/
	struct player player_two={car,0,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},100000,0,"car"};	/*Initialization of player_two*/
	/* ---------------------------------------------------------------------------------*/
	init_the_board(board);
	gameplay(board,player_one,player_two);
	
	return 0;
}
void gameplay (struct block board[blockNumber],struct player player_one,struct player player_two)
{
	clear();
	int i=0,j=0,choice=-1,turnPlayer=noone,dice=-1,initialValue=0;
	char pass;
	turnPlayer=rand()%2+1;			/*It keeps the order of the player for starting*/
	initialValue=-1;
	show_board(board,player_one,player_two);

	/* This is the main functions included main starter function */
	while(player_one.account>=0&&player_two.account>=0)
	{
		if(turnPlayer==cap)	printf("Current Player : *%s* !\n\n",player_one.name);
		else				printf("Current Player : *%s* !\n\n",player_two.name);
		
		/* Munü for Player */
		printf("--> 1 - Roll the Dice\n");
		printf("--> 2 - Show My Account\n");
		printf("--> 3 - Show My Properties\n");
		printf("--> 4 - Show Property Deeds\n");
		printf("--> 5 - Buy Property\n");
		printf("--> 6 - Buy House\n");
		printf("--> 7 - Sell Property\n\n");
		while(choice>7||choice<1){
			printf("Please select an option to continue : ");
			scanf("%d",&choice);
			printf("\n");
		}
		clear();
		switch (choice)
		{
			case 1:
			/*Dice Throwing*/
					if(initialValue!=-1)
					passTurn(&turnPlayer);

					dice=rand()%6+1;

					if(turnPlayer==cap)	round_allowance(&board[player_one.current_block_id],&player_one,dice);
					else				round_allowance(&board[player_two.current_block_id],&player_two,dice);

					moveGamer(&player_one,&player_two,dice,&turnPlayer);
			break;

			case 2:
			/* Checking Account Balance */
				if(turnPlayer==cap)	printf("--> Account Balance of Player (* %s *) : %d$\n\n",player_one.name,player_one.account);
				else				printf("--> Account Balance of Player (* %s *) : %d$\n\n",player_two.name,player_two.account);
			break;

			case 3:
			/* Checking Properties */
				if(turnPlayer==cap)	show_my_properties(&player_one,board);
				else				show_my_properties(&player_two,board);
			break;

			case 4:
			/* Checking Properties Deeds */ 
				show_properties(board);
			break;

			case 5:
			/* Buying Property */ 
				if(turnPlayer==cap)	buy_property(&board[player_one.current_block_id],&player_one);
				else				buy_property(&board[player_two.current_block_id],&player_two);
			break;

			case 6:
			/* Buying House */
				if(turnPlayer==cap)	buyHouse(&player_one,board);
				else				buyHouse(&player_two,board);
			break;

			case 7:
			/* Selling Property */
				if(turnPlayer==cap)	sell_property(board,&player_one);
				else				sell_property(board,&player_two);
			break;
		}
		/* ---------------------------------------------------------------------------------*/
		analysis_block(board,&player_one,&player_two,&dice,&turnPlayer,&choice);
		show_board(board,player_one,player_two),initialValue=-2;

		/* Game Wait Turn Determination */
		if(turnPlayer==cap&&player_two.turn_to_wait!=1&&player_two.turn_to_wait!=0)
		{
				--player_two.turn_to_wait;
				passTurn(&turnPlayer);
		}
		else if(turnPlayer==cap&&turnPlayer==cap&&player_two.turn_to_wait==1)
			player_two.turn_to_wait=0;
		else if(turnPlayer==car&&player_one.turn_to_wait!=1&&player_one.turn_to_wait!=0)
		{
				--player_one.turn_to_wait;
				passTurn(&turnPlayer);
		}
		else if(turnPlayer==car&&player_one.turn_to_wait==1)
			player_one.turn_to_wait=0;
				
		choice=-1;
	}
	if(player_one.account<0&&player_two.account>0)		printf("--> The winner is %s , Congratulations ! \n\n",player_two.name);
	else if(player_two.account<0&&player_one.account>0)	printf("--> The winner is %s , Congratulations ! \n\n",player_one.name);
	printf("***___The Game is Over___***\n\n");
}
void analysis_block(struct block board[blockNumber],struct player* player_one, struct player* player_two,int *dice,int *turnPlayer,int *choice)
{
		/* This function is for determinating and checking the block of player */
	int i=0,exit=1;
	if(*turnPlayer==cap) /*it is for cap */
	{
		/* Property */
		if(board[player_one->current_block_id].type==property)	payment(&board[player_one->current_block_id],player_one,board),player_one->turn_to_wait=0;
		else if(board[player_one->current_block_id].type==tax&&(*choice==1))
		{
			player_one->account=player_one->account-board[player_one->current_block_id].rent;
			printf("%s is in trouble , %s have to pay the tax ! (It is paid automatically by the system from the bank account)\n\n",player_one->name,player_one->name);
			player_one->turn_to_wait=0;
			/* Tax */
		}
		else if(board[player_one->current_block_id].type==punish)
		{
			if(player_one->current_block_id==5) 		/* Waiting two Turn */
			{
				if(player_one->turn_to_wait==0)
					player_one->turn_to_wait=3;
			}
			else if(player_one->current_block_id==15) 	/* Waiting one Turn */
			{
				if(player_one->turn_to_wait==0)
					player_one->turn_to_wait=2;
			}
		}
		/* Punish */
	}
	else if(*turnPlayer==car)	/*it is for Cap */
	{
		/* Property */
		if(board[player_two->current_block_id].type==property)	payment(&board[player_two->current_block_id],player_two,board),player_two->turn_to_wait=0;
		else if(board[player_two->current_block_id].type==tax&&(*choice==1)){
			player_two->account=player_two->account-board[player_two->current_block_id].rent;
			printf("%s is in trouble , %s have to pay the tax ! (It is paid automatically by the system from the bank account)\n\n",player_two->name,player_two->name);
			player_two->turn_to_wait=0;
			/* Tax */
		}
		else if(board[player_two->current_block_id].type==punish)
		{
			/* Punish */
			if(player_two->current_block_id==5)
			{
				if(player_two->current_block_id==5) 		/* Waiting two Turn */
				{
					if(player_two->turn_to_wait==0)
						player_two->turn_to_wait=3;
				}
			}
			else if(player_two->current_block_id==15) 	/* Waiting one Turn */
			{
				if(player_two->turn_to_wait==0)
					player_two->turn_to_wait=2;
			}
		}	
	}
}
void round_allowance(struct block* current_block,struct player* current_player,int dice)
{
	if((current_player->current_block_id+dice)>19) /* It is adding the money to the bank account */
	{
		current_player->account=current_player->account+10000;
		printf("--> %s has earned 10000$ because of completing the tour !\n\n",current_player->name);
	}
}
void payment(struct block* current_block, struct player* current_player,struct block board[blockNumber])
{
	/*This function for payment system , ıf the use do not enough money to pay his payment , you have to sell his own porperty*/
	/* I added every single situation thanks to if statement */
	/* I also check the current according the parameter */
	int exit=1,i=0,finish=1;
	if(current_block->owner.type==noone&&current_player->account>current_block->price)					printf("--> You can buy this property , Noone has it !\n");
	else if(current_block->owner.type==car&&current_player->type==car&&current_block->house_count<3)	printf("--> It is your property , You can build an house !\n");
	else if(current_block->owner.type==car&&current_player->type==cap)
	{
		if(current_player->account>=((current_block->house_count)*(current_block->house_price)))
		{
			printf("--> You are in private property , your rent fee is automatically paid by the system from your bank account !\n");
			if(current_block->house_count==0)
			{
				current_player->account=current_player->account-(current_block->rent);
				current_block->owner.account=current_block->owner.account+current_block->rent;
			}
			else if(current_block->house_count==1)
			{
				current_player->account=current_player->account-(current_block->rent_1);
				current_block->owner.account=current_block->owner.account+current_block->rent_1;
			}
			else if(current_block->house_count==2)
			{
				current_player->account=current_player->account-(current_block->rent_2);
				current_block->owner.account=current_block->owner.account+current_block->rent_2;
			}
			else if(current_block->house_count==3)
			{
				current_player->account=current_player->account-(current_block->rent_3);
				current_block->owner.account=current_block->owner.account+current_block->rent_3;
			}
		}
		else
		{
			printf("--> You do not enought money to pay this rent.You must sell some properties !\n");
			sell_property(board,current_player);
		}
	}
	else if(current_block->owner.type==cap&&current_player->type==car)
	{
		if(current_player->account>=((current_block->house_count)*(current_block->house_price)))
		{
			printf("--> You are in private property , your rent fee is automatically paid by the system from your bank account !\n");
			if(current_block->house_count==0)
			{
				current_player->account=current_player->account-(current_block->rent);
				current_block->owner.account=current_block->owner.account+current_block->rent;
			}
			else if(current_block->house_count==1)
			{
				current_player->account=current_player->account-(current_block->rent_1);
				current_block->owner.account=current_block->owner.account+current_block->rent_1;
			}
			else if(current_block->house_count==2)
			{
				current_player->account=current_player->account-(current_block->rent_2);
				current_block->owner.account=current_block->owner.account+current_block->rent_2;
			}
			else if(current_block->house_count==3)
			{
				current_player->account=current_player->account-(current_block->rent_3);
				current_block->owner.account=current_block->owner.account+current_block->rent_3;
			}
		}
		else
		{
			printf("--> You do not enought money to pay this rent.You must sell some properties !\n");
			if(current_block->house_count==0)
			{
				current_player->account=current_player->account-(current_block->rent);
				current_block->owner.account=current_block->owner.account+current_block->rent;
			}
			else if(current_block->house_count==1)
			{
				current_player->account=current_player->account-(current_block->rent_1);
				current_block->owner.account=current_block->owner.account+current_block->rent_1;
			}
			else if(current_block->house_count==2)
			{
				current_player->account=current_player->account-(current_block->rent_2);
				current_block->owner.account=current_block->owner.account+current_block->rent_2;
			}
			else if(current_block->house_count==3)
			{
				current_player->account=current_player->account-(current_block->rent_3);
				current_block->owner.account=current_block->owner.account+current_block->rent_3;
			}
			while(current_player->account<0&&finish)
			{
				for(i=0 ; i<12 && exit; ++i)
				{
					if((current_player->owned_block_ids[i])!=-1)
						exit=0;
				}
				if(exit==0)	sell_property(board,current_player);
				else		finish=0;
			}
		}
	}
	exit=1,finish=1;
}
/*--------------------------------------------------------------------------------------------------------------*/
void buy_property(struct block* current_block, struct player* current_player)
{
	/* This function is  for buying property for the player */
	int i=0,exit=1,house=-1;
	char option='o';
	if((current_block->owner.type==noone)&&(current_block->type==property)&&((current_player->account)>=(current_block->price)))
	{
		current_block->owner.type=current_player->type;
		current_player->account=(current_player->account)-(current_block->price);
		/* Checking with for loop and 'i' variable */
		for(i=0 ; i<12 && exit; ++i)
		{
			if((current_player->owned_block_ids[i])==-1)
			{
				current_player->owned_block_ids[i]=current_block->block_id;
				exit=0;
			}
		}
		exit=1;
		printf("--> %s has bought the property (%s) successfully !\n\n",current_player->name,current_block->name);
		printf("\n--> Current Account Balance = %d$\n\n",current_player->account);
		/* Asking for house building */
			printf("--> Do you want to build an house on your property :\n");
			printf("--> YES : press -> Y <-\n");
			printf("--> NO  : press -> N <-\n");
			while(option!='y'&&option!='Y'&&option!='n'&&option!='N')
			{
				printf("--> Option : ");
				scanf(" %c",&option);
			}
			printf("\n\n");
			if(option=='y'||option=='Y')
			{
				if(((current_player->account)>(current_block->house_price))||((current_player->account)>2*(current_block->house_price))||((current_player->account)>3*(current_block->house_price)))
				{
					while((((current_player->account)>(current_block->house_price))||((current_player->account)>2*(current_block->house_price))||((current_player->account)>3*(current_block->house_price)))&&exit)
					{
						/*Subsecuently if statement and its own condition */
						/*-------------------------------------------------*/
						clear();
						printf("\n--> Current Account Balance : %d$\n\n",current_player->account);
						printf("--> Price of per house in %s : %d$\n\n",current_block->name,current_block->house_price);
						printf("--> How many house do you want to build ?\n");
						printf("--> For building 1 House Press '1' Price : %d$\n",current_block->house_price);
						printf("--> For building 2 House Press '2' Price : %d$\n",current_block->house_price*2);
						printf("--> For building 3 House Press '3' Price : %d$\n",current_block->house_price*3);
						while(house<1||house>3)
						{
							printf("--> Option : ");
							scanf(" %d",&house);
						}
						/* Housing Number Checking */
						if(house==1&&((current_player->account)>=(current_block->house_price)))
						{
							current_player->account=current_player->account-current_block->house_price;
							++(current_block->house_count),exit=0,printf("--> %s has built one  house in (%s) successfully !\n\n",current_player->name,current_block->name);

						}
						/*----------------------------------------------------------------------------*/
						else if(house==2&&((current_player->account)>=2*(current_block->house_price)))
						{
							current_player->account=current_player->account-2*current_block->house_price;
							(current_block->house_count)=(current_block->house_count)+2;
							exit=0,printf("--> %s has built two houses in (%s) successfully !\n\n",current_player->name,current_block->name);
						}
						/*-----------------------------------------------------------------------------*/
						else if(house==3&&((current_player->account)>=3*(current_block->house_price)))
						{
							current_player->account=current_player->account-3*current_block->house_price;
							(current_block->house_count)=(current_block->house_count)+3;
							exit=0,printf("--> %s has built three houses in (%s) successfully !\n\n",current_player->name,current_block->name);
						}
						/*-----------------------------------------------------------------------------*/
						/*And so on*/
						else if(house==1&&((current_player->account)<(current_block->house_price))) 	printf("--> Your money is not enought for building one house !\n");
						else if(house==2&&((current_player->account)<(current_block->house_price))) 	printf("--> Your money is not enought for building two house !\n");
						else if(house==3&&((current_player->account)<(current_block->house_price))) 	printf("--> Your money is not enought for building three house !\n");
						house=-1;
					}
				}
				else
					printf("--> Your account balance is  not enought for building houses !\n\n");
				exit=1;
			}
	}
	else if((current_block->owner.type==noone)&&(current_block->block_id==current_player->current_block_id)&&((current_player->account)<(current_block->price)))
		printf("--> Your account balance is not enought to this property !\n");
	/*-------------------------End--------------------------------------------------*/
}
void buyHouse(struct player* current_player,struct block board[blockNumber])
{
	/* This function is for buying house if it is possible */
	int i=0,exit=1,house=4;
	for(i=0 ; i<12 &&exit ; ++i)
	{
		/* Checking owned ids number  */
		if((current_player->owned_block_ids[i])==current_player->current_block_id)
			exit=0;
	}
	/* Thanks to if condition */
	if(exit==0&&board[current_player->current_block_id].house_count<3)
	{
		printf("\n--> Current House Amount : %d\n",board[current_player->current_block_id].house_count);
		printf("--> Buildable House Amount : %d\n",3-board[current_player->current_block_id].house_count);
		while(house>(3-board[current_player->current_block_id].house_count)||house<=0)
		{
			printf("\n-->How many house do you want to build : ");
			scanf("%d",&house);
		}
		current_player->account=current_player->account-(house*board[current_player->current_block_id].house_price);
		board[current_player->current_block_id].house_count=board[current_player->current_block_id].house_count+house;
		printf("\n--> %d more house has been built !\n\n",house);
	}
	else if(exit==0&&board[current_player->current_block_id].house_count>=3)
		printf("\n--> There are already 3 houses on this property , You cannot build more !\n\n");
	else if(exit==1)
		printf("--> It is not your private property , You cannot build an house !\n\n");
	exit=1;
	house=4;
	/*--------------------------------------------------------------------------------------*/
}
void show_properties(struct block board[blockNumber])
{
	/*List of the property in the monopoly , included their rent and house Price */
	int i=0,propertyTemp=-1,exit_out=1,exit_in=1;
	while(exit_out){
		printf("Please select a property to see details: \n");
		for(i=0 ; i<blockNumber ; ++i){
			if(board[i].type==property)
				printf("%2d - %-10s\n",board[i].block_id,board[i].name);
		}
		printf("%2d - %-10s\n",0,"Exit");
			while(exit_in){
				scanf("%d",&propertyTemp);
				if(propertyTemp==0)
					exit_in=0;
				for(i=0 ; i<blockNumber ; ++i){
					if(board[propertyTemp].type==property)
						exit_in=0;
				}
			}
			if(propertyTemp==0)
				exit_out=0;
			else{
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				printf("|%11s%-20s|\n","",board[propertyTemp].name);
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				/*-------------------------------------------------------------------------------------- */
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent"," ",board[propertyTemp].rent,"$","|");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent 1 H"," ",board[propertyTemp].rent_1,"$","|");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent 2 H"," ",board[propertyTemp].rent_2,"$","|");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent 3 H"," ",board[propertyTemp].rent_3,"$","|");
				/*-------------------------------------------------------------------------------------- */
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","House Price"," ",board[propertyTemp].house_price,"$","|");
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
			}
			propertyTemp=-1,exit_in=1;
	}
	/*--------------------------------------------End---------------------------------------- */
}
void moveGamer(struct player* player_one, struct player* player_two,int dice,int *turnPlayer)
{
	/*Moving the Gamer */
	if(*turnPlayer==cap)			player_one->current_block_id=(player_one->current_block_id+dice)%blockNumber;
	else if(*turnPlayer==car)		player_two->current_block_id=(player_two->current_block_id+dice)%blockNumber;
	/*--------------------------------------------End---------------------------------------- */
}
void passTurn(int *turnPlayer)
{
	/* Passing the turn of the Gamer */
	if(*turnPlayer==cap) 		*turnPlayer=car;
	else if(*turnPlayer==car)	*turnPlayer=cap;
	/*--------------------------------------------End---------------------------------------- */
}
void show_my_properties(struct player* current_player,struct block board[blockNumber])
{
	int i=0,t=0;
	/*	List of the Current Owned Property  */
	printf("\t\t*** Properties ***\n\n");
	for(i=0 ; i<12 ; ++i)
	{
		if((current_player->owned_block_ids[i])!=-1)
		{
			printf("--> Propertiy Name : %s (Id:%d) \n",board[current_player->owned_block_ids[i]].name,current_player->owned_block_ids[i]);
			printf("--> House Amount   : %d in %s\n\n",board[current_player->owned_block_ids[i]].house_count,board[current_player->owned_block_ids[i]].name);
		}
		else ++t;
	}
	if(t==12)
		printf("--> You do not have any property\n\n");
	/*--------------------------------------------End---------------------------------------- */
}
void sell_property(struct block board[blockNumber],struct player* current_player)
{
	/*When player cannot afford the buy some house or porperty , he/she can use that function */
	int i=0,option=-500,exit=1,quit=1,finish=1;
	char answer='a';
		for(i=0 ; i<12 &&finish ; ++i)
		{
			if((current_player->owned_block_ids[i])!=-1)
				finish=0;
		}
		if(finish)
		printf("--> You do not have any property to sell ! \n\n");
		else
		{
			show_my_properties(current_player,board);
			/* List of the Current Owned Property on the Block*/
			printf("--> Do not forget , You will get just half of their prices included houses!\n");
			printf("--> Which properties do you want to sell with its houses ?\n\n");
			while(quit&&option!=-2)
			{
				printf("Please enter the Id of the property : ");
				scanf(" %d",&option);
				for(i=0 ; i<12&&quit; ++i)
				{
					/* Condition with if statement */
					if(current_player->owned_block_ids[i]==option)
					{
						if(board[current_player->owned_block_ids[i]].house_count==0)
						{
							current_player->account = current_player->account + (board[current_player->owned_block_ids[i]].price)/2;
							printf("\n--> %s has been sold successfully \n\n",board[current_player->owned_block_ids[i]].name);
						}
						else if(board[current_player->owned_block_ids[i]].house_count>0)
						{
							current_player->account=current_player->account+(board[current_player->owned_block_ids[i]].price+board[current_player->owned_block_ids[i]].house_price*board[current_player->owned_block_ids[i]].house_count)/2;
							printf("\n--> %s has been sold successfully !\n\n",board[current_player->owned_block_ids[i]].name);
						}
						quit=0;
						board[current_player->owned_block_ids[i]].owner.type=noone;
						current_player->owned_block_ids[i]=-1;
					}
				}
			}
			quit=1;
		}
	answer='a';
	/*--------------------------------------------End---------------------------------------- */
}
void init_the_board(struct block board[blockNumber])
{
	/* Initialization of structure with given as an input */

	int i=0;
	struct block tempBoard[blockNumber]={
		/*    {id,"name            ,price    		rent    ,	rent1    ,rent2    ,rent3    ,house_price,	house_count, owner    ,type"}    */
		{	0	,"Start"		,		0	,		   0	,	    0	,		0	,		0	,		0	,	0	,	{noone},	start 		},
		{	1	,"Esenyurt"		,	16000	,		 800	,	 4000	,	 9000	,	25000	,	10000	,	0	,	{noone},	property	},
		{	2	,"Car Park"		,		0	,		1500	,	    0	,		0	,		0	,		0	,	0	,	{noone},	tax   		},
		{	3	,"Tuzla"		,	16500	,		 850	,	 4250	,	 9500	,	26000	,	12000	,	0	,	{noone},	property 	},
		{	4	,"Arnavutkoy"	,	17000	,		 875	,	 4500	,	10000	,	28000	,	12000	,	0	,	{noone},	property 	},
		{	5	,"Wait 2 Turn"	,		0	,		   2	,	    0	,		0	,		0	,		0	,	0	,	{noone},	punish 		},
		{	6	,"Catalca"		,	20000	,		1000	,	 5000	,	12000	,	30000	,	13000	,	0	,	{noone},	property 	},
		{	7	,"Beykoz"		,	23000	,		1100	,	 5500	,	12500	,	33000	,	13000	,	0	,	{noone},	property 	},
		{	8	,"Car Fix"		,		0	,		1750	,	    0	,		0	,		0	,		0	,	0	,	{noone},	tax 		},
		{	9	,"Maltepe"		,	30000	,		1350	,	 7000	,	15000	,	40000	,	15000	,	0	,	{noone},	property 	},
		{	10	,"Bills"		,		0	,		2000	,	    0	,		0	,		0	,		0	,	0	,	{noone},	tax 		},
		{	11	,"Sisli"		,	33000	,		1500	,	 8000	,	16000	,	42000	,	16000	,	0	,	{noone},	property 	},
		{	12	,"Oil"			,		0	,		2250	,	    0	,		0	,		0	,		0	,	0	,	{noone},	tax   		},
		{	13	,"Atasehir"		,	35000	,		1600	,	 8500	,	17000	,	45000	,	17000	,	0	,	{noone},	property 	},
		{	14	,"Sariyer"		,	40000	,		1750	,	 9500	,	19000	,	48000	,	19000	,	0	,	{noone},	property 	},
		{	15	,"Wait 1 Turn"	,		0	,		   1	,	    0	,		0	,		0	,		0	,	0	,	{noone},	punish 		},
		{	16	,"Kadikoy"		,	43000	,		1900	,	11000	,	21500	,	55000	,	23000	,	0	,	{noone},	property 	},
		{	17	,"Besiktas"		,	60000	,		2500	,	15000	,	28000	,	60000	,	30000	,	0	,	{noone},	property 	},
		{	18	,"Vacation"		,		0	,		5000	,	    0	,		0	,		0	,		0	,	0	,	{noone},	tax 		},
		{	19	,"Bebek"		,	70000	,		3500	,	20000	,	35500	,	65000	,	35000	,	0	,	{noone},	property	}
	};
	/* Copying the structure to the main sturucture array */
	for(i=0 ; i<blockNumber ; ++i)
		board[i]=tempBoard[i];
}
void show_board(struct block board[blockNumber],struct player player_one,struct player player_two)
{
	int i=0,j=0,t=0,k=0;

	/*Printing the board with using three diffrent variable  */
	/*i is keepign the amount of vertical rectanfular block  */
	/*t is keepign the amount of horizonal rectanfular block */
	/*k is keepign three different variable on the block 	 */

	printf("\t\t\t\t\t\t\t***Welcome to  the Monopoly Game***\n\n");
	while(t<6)
	{
		if(t==0||t==1||t==5){
			for(i=0 ; i<24*6+1 ; ++i)
			printf("-");
		}
		else{
			for(i=0 ; i<24*6+1  ; ++i){
				if(i<25||i>=120)	printf("-");
				else				printf(" ");
			}	
		}
		printf("\n");
		while(k<3){
			for(j=0 ; j<6 ; ++j){
				if(t!=0&&t!=5){
					if(j==5){
						if(k==0)	printf("|%7s%-16s","",board[j+t].name);
						if(k==1){
							if(board[j+t].type==tax)											printf("|%7s%-5d$%-10s","",board[j+t].rent,"");
							else if(board[j+t].type==property)									printf("|%7s%-5d$%-10s","",board[j+t].price,"");
							else if((board[j+t].type==punish||board[j].type==start))  			printf("|%7s%-5s %-10s","","","");
						}
						if(k==2){
							if(board[j+t].block_id==player_one.current_block_id&&board[j+t].block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
							else if(board[j+t].block_id!=player_one.current_block_id&&board[j+t].block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
							else if(board[j+t].block_id==player_one.current_block_id&&board[j+t].block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
							else if(board[j+t].block_id!=player_one.current_block_id&&board[j+t].block_id!=player_two.current_block_id)	printf("|%7s%-16s","","");
						}
					}
					else if(j==0){	
						if(k==0)	printf("|%7s%-16s","",board[blockNumber-t].name);
						if(k==1){
							if(board[blockNumber-t-j].type==tax)										printf("|%7s%-5d$%-10s","",board[blockNumber-t].rent,"");
							else if(board[blockNumber-t].type==property)								printf("|%7s%-5d$%-10s","",board[blockNumber-t].price,"");
							else if(board[blockNumber-t].type==punish||board[j].type==start)  			printf("|%7s%-5s %-10s","","","");
						}
						if(k==2){
							if(board[blockNumber-t].block_id==player_one.current_block_id&&board[blockNumber-t].block_id==player_two.current_block_id)	printf("|%7s    %-12s",player_one.name,player_two.name);
							else if(board[blockNumber-t].block_id!=player_one.current_block_id&&board[blockNumber-t].block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
							else if(board[blockNumber-t].block_id==player_one.current_block_id&&board[blockNumber-t].block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
							else if(board[blockNumber-t].block_id!=player_one.current_block_id&&board[blockNumber-t].block_id!=player_two.current_block_id)	printf("|%7s%-16s","","");
						}
						
					}
					else if(j==1)	printf("|%7s%-16s","","");
					else			printf("%8s%-16s","","");
				}
				else if(t==0){
					if(k==0)		printf("|%7s%-16s","",board[j].name);
					if(k==1){
						if(board[j].type==tax)													printf("|%7s%-5d$%-10s","",board[j].rent,"");
						else if(board[j].type==property)										printf("|%7s%-5d$%-10s","",board[j].price,"");
						else if(board[j].type==punish||board[j].type==start)  					printf("|%7s%-5s %-10s","","","");
					}
					if(k==2){
						if(board[j].block_id==player_one.current_block_id&&board[j].block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
						else if(board[j].block_id!=player_one.current_block_id&&board[j].block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
						else if(board[j].block_id==player_one.current_block_id&&board[j].block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
						else if(board[j].block_id!=player_one.current_block_id&&board[j].block_id!=player_two.current_block_id)	printf("|%7s%-16s","","");
					}
				}
				else if(t==5){
					if(k==0)		printf("|%7s%-16s","",board[blockNumber-t-j].name);
					if(k==1){
						if(board[blockNumber-t-j].type==tax)										printf("|%7s%-5d$%-10s","",board[blockNumber-t-j].rent,"");
						else if(board[blockNumber-t-j].type==property)								printf("|%7s%-5d$%-10s","",board[blockNumber-t-j].price,"");
						else if(board[blockNumber-t-j].type==punish||board[j].type==start)  		printf("|%7s%-5s %-10s","","","");
					}
					if(k==2){
						if(board[blockNumber-t-j].block_id==player_one.current_block_id&&board[blockNumber-t-j].block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
						else if(board[blockNumber-t-j].block_id!=player_one.current_block_id&&board[blockNumber-t-j].block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
						else if(board[blockNumber-t-j].block_id==player_one.current_block_id&&board[blockNumber-t-j].block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
						else if(board[blockNumber-t-j].block_id!=player_one.current_block_id&&board[blockNumber-t-j].block_id!=player_two.current_block_id)	printf("|%7s%-16s", "","");
					}
				}	
			}
			printf("|\n");
			++k;
		}
		k=0,++t;
	}
	for(i=0 ; i<24*6+1 ; ++i)
	printf("-");
	printf("\n");
	/*--------------------------------------------End---------------------------------------- */
}