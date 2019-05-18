/*-----------------------------------------------------------*/
/* GEBZE TECHNICAL UNIVERSITY-CSE-102 (Computer Programming) */
/* NEVZAT SEFEROGLU - 171044024------------------------------*/
/* MONOPOLY 2 (Linked List Implementation)-------------------*/
/* ----------------------------------------------------------*/
#include <stdio.h> 			/* standart input library  */
#include <stdlib.h> 		/* for creating random number  */
#include <time.h>   		/* for creating random number  */
#define clear() printf("\033[H\033[J") 	/* Cleaning The Terminal */
#define blockNumber 24	/* Board Amount Defination */

enum player_type{noone,cap,car};
enum block_type{start, property, tax, punish,fortune};

struct fortune_card{
	int card_no_1,card_no_2,card_no_3,card_no_4,card_no_5;
	char *card_name_1,*card_name_2,*card_name_3,*card_name_4,*card_name_5;
};
struct player{
	enum player_type type;	/*Holds type of the player*/
	int current_block_id; 	/*Holds player location as block id*/
	int owned_block_ids[12];/*Holds property block ids that are owned by the user*/
	int account;			/*Holds amount of the current money of the player*/
	int turn_to_wait;		/*Holds number of turns to wait if the player got a punishment*/
	char* name;				/*Holds the name of the player*/
};
struct block{
	int block_id;			/*Holds id of the block*/
	char* name;				/*Holds text of the block that is shown on the top of the block*/
	int price;				/*If the block is property, holds the price of property. If the block is a taxblock than holds the tax fee and if the block is punishment block, then holds the number ofturns to wait*/
	int rent;				/*Holds the default rent of a property (no house)*/
	int rent_1;				/*Holds the rent of a property with one house*/
	int rent_2;				/*Holds the rent of a property with two houses*/
	int rent_3;				/*Holds the rent of a property with three houses*/
	int house_price;		/*Holds price of building a house on the block*/
	int house_count;		/*Holds the number of the houses on the block that are already built*/
	struct player owner;	/*Holds the owner of the block*/
	enum block_type type;	/*Holds type of the block*/
	struct block* next;
};

void init_the_board(struct block** board);
void creatingList(struct block** board,int block_id,char * name,int price,int rent,int rent_1,int rent_2,int rent_3,int house_price,int house_count,enum block_type type);
void go_target_link(struct block** head,int target_block_id);
void show_board(struct block* board,struct player player_one,struct player player_two);
void gameplay (struct block* board,struct player player_one,struct player player_two);
void analysis_block(struct block* board,struct player* player_one, struct player* player_two,int *dice,int *turnPlayer,int *choice,struct fortune_card card);
void passTurn(int *turnPlayer);
void moveGamer(struct player* player_one, struct player* player_two,int dice,int *turnPlayer);
void payment(struct block* current_block, struct player* current_player,struct block *board);
void sell_property(struct block* board,struct player* current_player);
void show_my_properties(struct player* current_player,struct block *board);
void show_properties(struct block *board);
void round_allowance(struct block* current_block,struct player* current_player,int dice);
void buy_property(struct block* current_block, struct player* current_player);
void buyHouse(struct player* current_player,struct block *board);

int main()
{
	int i=0;
	srand(time(NULL));
	struct player player_one={cap,0,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},100000,0,"cap"};	/* Computer initialization */
	struct player player_two={car,0,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},100000,0,"car"};	/* Player initialization */

	struct block *head=malloc(sizeof(struct block));
	struct block *head_temp=malloc(sizeof(struct block));
	
	head=head_temp;
	init_the_board(&(head_temp)); 
	gameplay (head,player_one,player_two);

	free(head);			/* Free operation*/
	free(head_temp);	

	return 0;
}
void gameplay (struct block* board,struct player player_one,struct player player_two)
{
	int i=0,j=0,choice=-1,turnPlayer=noone,dice=-1,option=-1,pastDice=-1;

	struct block* head=malloc(sizeof(struct block));
	struct fortune_card* card=malloc(sizeof(struct block));
	/* Fortune Card Declearation */
	card->card_name_1="Free House";
	card->card_name_2="Time Travel";
	card->card_name_3="Garnishment";
	card->card_name_4="Genorosity";
	card->card_name_5="Treasure Hunter";
	card->card_no_1=1;
	card->card_no_2=2;
	card->card_no_3=3;
	card->card_no_4=4;
	card->card_no_5=5;
	/*---------------------------------------------------------------*/

	head=board;
	turnPlayer=(rand()%2)+1;
	show_board(board,player_one,player_two);
	while(player_one.account>=0&&player_two.account>=0)
	{
		if(turnPlayer==car)
		{
			/*-----------------------------Menu for Player--------------------------------*/
			printf("--> Car(Player)   Account: %d$\n",player_two.account);
			printf("--> Cap(Computer) Account: %d$\n\n",player_one.account);
			printf("--> 1 - Roll the Dice\n");
			printf("--> 2 - Show My Account\n");
			printf("--> 3 - Show My Properties\n");
			printf("--> 4 - Show Property Deeds\n");
			printf("--> 5 - Buy Property\n");
			printf("--> 6 - Buy House\n");
			printf("--> 7 - Sell Property\n\n");
			/*----------------------------------------------------------------------------*/
			while(choice>7||choice<1){
				printf("Please select an option to continue : ");
				scanf("%d",&choice);
				printf("\n");
			}
		}
		else if(turnPlayer==cap) choice=1;
		clear();
		switch (choice)
		{
			case 1:
			/*In this case  , I do a lot of operations according to game design */
			/*For Example : If player in wait turn or computer wait turn block , all those operation controls i this case */
			/*-----------------------Player-Operations------------------------------*/
				if(turnPlayer==car&&pastDice==1&&player_one.turn_to_wait==0){
					if(!(player_one.current_block_id==6||player_one.current_block_id==18||player_two.current_block_id==6||player_two.current_block_id==18))
					{
						printf("--> (1) To give the turn(dice) !\n");
						printf("--> (2) To go back to menu !\n");
						while(option!=1&&option!=2){
							printf("Option : ");
							scanf("%d",&option);
						}
					}
					else option=1;
					if(option==1)	passTurn(&turnPlayer); /* Changing the main player (computer - player) */
				}
			/*-----------------------Player-Operations------------------------------*/
				if((turnPlayer==car&&pastDice==-1)||player_one.turn_to_wait!=0){
					dice=rand()%6+1;
					go_target_link(&head,player_two.current_block_id);
					round_allowance(head,&player_two,dice);
					head=board;
					moveGamer(&player_one,&player_two,dice,&turnPlayer);
					pastDice=1;
				}
			/*----------------------------------------------------------------------*/
			/*-----------------------Computer-Operations------------------------------*/
				else if(turnPlayer==cap||player_two.turn_to_wait!=0){
					dice=rand()%6+1; /* Throwing Dice */
					go_target_link(&head,player_one.current_block_id);
					round_allowance(head,&player_one,dice);
					head=board;
					printf("--> Computer rolled the dice : %d\n\n",dice);
					moveGamer(&player_one,&player_two,dice,&turnPlayer);
					pastDice=-1;
				}
			/*------------------------------------------------------------*/
			break;

			case 2:
				if(turnPlayer==car)	printf("--> Account Balance of Player (* %s *) : %d$\n\n",player_two.name,player_two.account);
			break;

			case 3:
				if(turnPlayer==car)	show_my_properties(&player_two,board);
			break;

			case 4:
				show_properties(board);
			break;

			case 5:
				if(turnPlayer==car)
				{
					go_target_link(&head,player_two.current_block_id);
					buy_property(head,&player_two);
					head=board;
				}
			break;
			
			case 6:
				if(turnPlayer==car)	buyHouse(&player_two,board);
			break;

			case 7:
				if(turnPlayer==car)	sell_property(board,&player_two);
			break;
		}
		analysis_block(board,&player_one,&player_two,&dice,&turnPlayer,&choice,*card);
		show_board(board,player_one,player_two);
		if(turnPlayer==cap&&player_two.turn_to_wait==0)	passTurn(&turnPlayer);
		choice=-1,option=-1;
	}
	if(player_one.account<0&&player_two.account>0)		printf("--> The winner is %s , Congratulations ! \n\n",player_two.name);
	else if(player_two.account<0&&player_one.account>0)	printf("--> The winner is %s , Congratulations ! \n\n",player_one.name);
	printf("***___The Game is Over___***\n\n");
}
void analysis_block(struct block* board,struct player* player_one, struct player* player_two,int *dice,int *turnPlayer,int *choice,struct fortune_card card)
{
	/*With this function implementation , My purpose is analyzing a block and entrance an action according to it*/
	/*I also made linked list implementation for all those case */
	int i=0,exit=1,finish=1,tempDice=0,id=-1,checkId=1;
	struct block* head=malloc(sizeof(struct block));
	struct block* head_opponent=malloc(sizeof(struct block));
	/* Getting the first node */
	head=board;
	head_opponent=board;
	/*I am going to use initial node before for all operation and after for all operation */
	/*I divided the function  as two main situation */
	/*In case of that User is cap(computer) */
	if(*turnPlayer==cap) 
	{
		go_target_link(&head,player_one->current_block_id); 
		go_target_link(&head_opponent,player_two->current_block_id);
		/*-----------------------------------------------------------------------------------------*/
		if(head_opponent->type==punish)
		{
			if(player_two->current_block_id==6)
			{	
				if(player_two->turn_to_wait!=1)			--player_two->turn_to_wait;
				else if(player_two->turn_to_wait==1)	player_two->turn_to_wait=0;
			}
			else if(player_two->current_block_id==18)
			{
				if(player_two->turn_to_wait!=1)			--player_two->turn_to_wait;
				else if(player_two->turn_to_wait==1)	player_two->turn_to_wait=0;
			}
		}
		/*-----------------------------------------------------------------------------------------*/
		if(head->type==property)	payment(head,player_one,board),player_one->turn_to_wait=0;
		else if(head->type==punish)
		{
			if(head->block_id==6) /* wait 2 turn */
			{
				if(player_one->turn_to_wait==0)
					player_one->turn_to_wait=3;
				
			}
			else if(head->block_id==18) /* wait 1 turn */
			{
				if(player_one->turn_to_wait==0)
					player_one->turn_to_wait=2;
			}
		}
		/*-----------------------------------------------------------------------------------------*/
		else if(head->type==fortune)
		{
			player_one->turn_to_wait=0;
			tempDice=rand()%5+1;
			if(tempDice==1)		 printf("--> Computer's fortune card is ** %s ** !\n\n",card.card_name_1);
			else if(tempDice==2) printf("--> Computer's fortune card is ** %s ** !\n\n",card.card_name_2);
			else if(tempDice==3) printf("--> Computer's fortune card is ** %s ** !\n\n",card.card_name_3);
			else if(tempDice==4) printf("--> Computer's fortune card is ** %s ** !\n\n",card.card_name_4);
			else if(tempDice==5) printf("--> Computer's fortune card is ** %s ** !\n\n",card.card_name_5);
			head=board;
			if( tempDice==card.card_no_1)
			{
				for(i=11 ; i>=0 &&exit; ++i)
				{	
					go_target_link(&head,player_one->owned_block_ids[i]);
					if(player_one->owned_block_ids[i]!=-1&&head->house_count<3)
						exit=0;
				}
				if(exit==0)
				{
					head->house_count=head->house_count+1;
					printf("--> Computer a has built a free house on %s \n\n",head->name);
				}
				else	printf("--> Computer has no property to build a free house ! \n\n");
				exit=1;
				head=board;
			}
			else if(tempDice==card.card_no_2)
			{
				tempDice=rand()%6+1;
				if(1>=tempDice&&tempDice<=3){
					player_one->current_block_id=(player_one->current_block_id+2)%blockNumber;
					printf("--> Computer has been moved forward by two(2) block !\n\n");
				}
				else{		
						player_one->current_block_id=(player_one->current_block_id-2)%blockNumber;
						printf("--> Computer has been moved backward by two(2) block !\n\n");
				}
				return analysis_block(board,player_one,player_two,dice,turnPlayer,choice,card);
			}
			else if(tempDice==card.card_no_3)
			{
				player_one->account=player_one->account-5000;
				if(player_one->account>=5000)	printf("--> computer has paid 5000$ to bank ! \n\n");
				else
				{
					printf("--> Computer has to sell some properties to pay your bank charge ! \n\n");
					while(player_one->account<0&&finish)
					{
						for(i=0 ; i<12 && exit; ++i)
						{
							if((player_one->owned_block_ids[i])!=-1)
								exit=0;
						}
						if(exit==0)	sell_property(board,player_one);
						else		finish=0;
					}
					if(player_one->account>=0) printf("--> %s has paid 5000$ to bank ! \n\n",player_one->name);
					finish=1,exit=1;
				}
			}
			else if(tempDice==card.card_no_4)
			{
				printf("--> Computer has to give 10000$ to the opponent ! \n\n");
				player_one->account=player_one->account-10000;
				player_two->account=player_two->account+10000;

				if(player_one->account>=10000)	printf("--> %s has gotten 10000$ from the opponent ! \n\n",player_two->name);
				else
				{
					printf("--> Computer have to sell some properties to pay the money to the opponent! \n\n");
					while(player_one->account<0&&finish)
					{
						for(i=0 ; i<12 && exit; ++i)
						{
							if((player_one->owned_block_ids[i])!=-1)
								exit=0;
						}
						if(exit==0)	sell_property(board,player_one);
						else		finish=0;
					}
					if(player_one->account>=0) printf("--> %s has gotten 10000$ from the computer ! \n",player_two->name);
					finish=1,exit=1;
				}
			}
			else if(tempDice==card.card_no_5)
			{
				player_one->account=player_one->account+20000;
				printf("--> Computer is a treasure hunter , Computer has gotten 20000$ from the bank !\n\n");
			}
		}
		/*----------------------------------END-----------------------------------------------------*/
		else if(head->type==tax)
		{
			player_one->turn_to_wait=0;
			if(player_one->account>=head->rent)
			{
				player_one->account=player_one->account-head->rent;
				printf("--> %s is in trouble , %s have to pay the tax ! (It is paid automatically by the system from the bank account)\n\n",player_one->name,player_one->name);
			}
			else
			{
				player_one->account=player_one->account-head->rent;
				printf("--> Computer has to sell some properties !\n");
				while(player_one->account<0&&finish)
				{
					for(i=0 ; i<12 && exit; ++i)
					{
						if((player_one->owned_block_ids[i])!=-1)
							exit=0;
					}
					if(exit==0)	sell_property(board,player_one);
					else 		finish=0;
				}
			}
		}
	}
	/*----------------------------------END-----------------------------------------------------*/
	/*In case of that User is car(computer) */
	else if(*turnPlayer==car)	
	{
		go_target_link(&head,player_two->current_block_id);
		go_target_link(&head_opponent,player_one->current_block_id);

		if(head_opponent->type==punish)
		{
			if(player_one->current_block_id==6)
			{	
				if(player_one->turn_to_wait!=1)			--player_one->turn_to_wait;
				else if(player_one->turn_to_wait==1)	player_one->turn_to_wait=0;
			}
			else if(player_one->current_block_id==18)
			{
				if(player_one->turn_to_wait!=1)			--player_one->turn_to_wait;
				else if(player_one->turn_to_wait==1)	player_one->turn_to_wait=0;
			}
		}

		if(head->type==property)	payment(head,player_two,board),player_two->turn_to_wait=0;
		else if(head->type==punish)
		{
			if(head->block_id==6) /* wait 2 turn */
			{
				if(player_two->turn_to_wait==0)
					player_two->turn_to_wait=3;
			}
			else if(head->block_id==18) /* wait 1 turn */
			{
				if(player_two->turn_to_wait==0)
					player_two->turn_to_wait=2;
			}	
		}
		else if(head->type==fortune&&(*choice==1))
		{
			player_two->turn_to_wait=0;
			tempDice=rand()%5+1;
			if(tempDice==1)		 printf("--> %s's fortune card is ** %s ** !\n\n",player_two->name,card.card_name_1);
			else if(tempDice==2) printf("--> %s's fortune card is ** %s ** !\n\n",player_two->name,card.card_name_2);
			else if(tempDice==3) printf("--> %s's fortune card is ** %s ** !\n\n",player_two->name,card.card_name_3);
			else if(tempDice==4) printf("--> %s's fortune card is ** %s ** !\n\n",player_two->name,card.card_name_4);
			else if(tempDice==5) printf("--> %s's fortune card is ** %s ** !\n\n",player_two->name,card.card_name_5);

			if(tempDice==card.card_no_1)
			{
				for(i=0 ; i<12 &&exit; ++i)
				{	
					if(player_two->owned_block_ids[i]!=-1)
						exit=0;
				}
				if(exit==0)
				{
					show_my_properties(player_two,board);
					printf("--> Which property do you want to build an house ?\n");
					printf("--> Please enter the ID number of the property\n");
					while(checkId!=0)
					{
						printf("--> Id :  ");
						scanf("%d",&id);
						for(i=0 ; i<12 &&checkId ; ++i)
						{
							if(player_two->owned_block_ids[i]==id)
								checkId=0;
						}
					}
					checkId=1;
					head=board;
					go_target_link(&head,id);
					head->house_count=head->house_count+1;
					printf("--> A house has been built on %s successfully thanks to Fortune Card ! \n\n",head->name);
					head=board;
				}
				else printf("--> Unfortunately , You have no property to build a free house ! \n\n");
				exit=1;
			}
			else if(tempDice==card.card_no_2)
			{
				tempDice=rand()%6+1;
				if(1>=tempDice&&tempDice<=3){
					player_two->current_block_id=(player_two->current_block_id+2)%blockNumber;
					printf("--> Player has been moved forward by two(2) block !\n\n");
				}
				else{		
						player_two->current_block_id=(player_two->current_block_id-2)%blockNumber;
						printf("--> Player has been moved backward by two(2) block !\n\n");
				}
				return analysis_block(board,player_one,player_two,dice,turnPlayer,choice,card);
			}
			else if(tempDice==card.card_no_3)
			{
				player_two->account=player_two->account-5000;
				if(player_two->account>=5000)	printf("--> %s has paid 5000$ to bank ! \n\n",player_two->name);
				else
				{
					printf("--> %s have to sell some properties to pay your bank charge ! \n\n",player_two->name);
					while(player_two->account<0&&finish)
					{
						for(i=11 ; i>=0 && exit; --i)
						{
							if((player_two->owned_block_ids[i])!=-1)
								exit=0;
						}
						if(exit==0)	sell_property(board,player_two);
						else		finish=0;
					}
					if(player_two->account>=0) printf("--> %s has paid 5000$ to bank ! \n\n",player_two->name);
					finish=1,exit=1;
				}
			}
			else if(tempDice==card.card_no_4)
			{
				printf("--> %s has to give 10000$ to the opponent ! \n\n",player_two->name);
				player_two->account=player_two->account-10000;
				player_one->account=player_one->account+10000;

				if(player_two->account>=10000)	printf("--> Computer has gotten 10000$ from the opponent ! \n");
				else
				{
					printf("--> %s have to sell some properties to pay the money to the opponent! \n\n",player_two->name);
					while(player_two->account<0&&finish)
					{
						for(i=11 ; i>=0 && exit; --i)
						{
							if((player_two->owned_block_ids[i])!=-1)
								exit=0;
						}
						if(exit==0)	sell_property(board,player_two);
						else		finish=0;
					}
					if(player_two->account>=0) printf("--> Computer has gotten 10000$ from the opponent ! \n");
					finish=1,exit=1;
				}
			}
			else if(tempDice==card.card_no_5)
			{
				player_two->account=player_two->account+20000;
				printf("--> %s is a treasure hunter , %s has gotten 20000$ from the bank !\n\n",player_two->name,player_two->name);
			}
		}
		else if(head->type==tax&&(*choice==1))
		{
			player_two->turn_to_wait=0;
			if(player_two->account>=head->rent)
			{
				player_two->account=player_two->account-head->rent;
				printf("--> %s is in trouble , %s have to pay the tax ! (It is paid automatically by the system from the bank account)\n\n",player_two->name,player_two->name);
			}
			else
			{
				player_two->account=player_two->account-head->rent;
				printf("--> %s has to sell some properties !\n",player_two->name);
				while(player_two->account<0&&finish)
				{
					for(i=11 ; i>=11 && exit; ++i)
					{
						if((player_two->owned_block_ids[i])!=-1)
							exit=0;
					}
					if(exit==0)	sell_property(board,player_two);
					else 		finish=0;
				}
			}
		}
	}
	/*----------------------------------END-----------------------------------------------------*/
	exit=1,finish=1;
}
void buy_property(struct block* current_block, struct player* current_player)
{
	/* This function implementation is for car(player) , I use a lot of if implementation because of that there are many condition */
	/* Buy function check the properties whether ıt is owned by car(player) */
	/* -----------------------------------------------------------------------------------------------*/
	int i=0,exit=1,house=-1;
	char option='o';

	if((current_block->owner.type==noone)&&(current_block->type==property)&&((current_player->account)>=(current_block->price)))
	{
		current_block->owner.type=current_player->type;
		current_player->account=(current_player->account)-(current_block->price);
		for(i=11 ; i>=0 && exit; --i)
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
					if(house==1&&((current_player->account)>=(current_block->house_price)))
					{
						current_player->account=current_player->account-current_block->house_price;
						++(current_block->house_count),exit=0,printf("--> %s has built one  house in (%s) successfully !\n\n",current_player->name,current_block->name);

					}
					else if(house==2&&((current_player->account)>=2*(current_block->house_price)))
					{
						current_player->account=current_player->account-2*current_block->house_price;
						(current_block->house_count)=(current_block->house_count)+2;
						exit=0,printf("--> %s has built two houses in (%s) successfully !\n\n",current_player->name,current_block->name);
					}
					else if(house==3&&((current_player->account)>=3*(current_block->house_price)))
					{
						current_player->account=current_player->account-3*current_block->house_price;
						(current_block->house_count)=(current_block->house_count)+3;
						exit=0,printf("--> %s has built three houses in (%s) successfully !\n\n",current_player->name,current_block->name);
					}
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
			/* -----------------------------------------------------------------------------------------------*/
	}
	else if((current_block->owner.type==noone)&&(current_block->block_id==current_player->current_block_id)&&((current_player->account)<(current_block->price)))
		printf("--> Your account balance is not enought to this property !\n");
	/* -----------------------------------------------------------------------------------------------*/
}
void buyHouse(struct player* current_player,struct block *board)
{
	int i=0,exit=1,house=4;
	struct block* head=malloc(sizeof(struct block));
	head=board;

	for(i=11 ; i>=0 &&exit ; --i)
	{
		if((current_player->owned_block_ids[i])==current_player->current_block_id)
			exit=0;
	}
	go_target_link(&head,current_player->current_block_id);
	if(exit==0&&head->house_count<3)
	{
		printf("\n--> Current House Amount : %d\n",head->house_count);
		printf("--> Buildable House Amount : %d\n",3-head->house_count);
		while(house>(3-head->house_count)||house<=0)
		{
			printf("\n-->How many house do you want to build : ");
			scanf("%d",&house);
		}
		if(current_player->account>=house*head->house_price)
		{
			current_player->account=current_player->account-(house*head->house_price);
			head->house_count=head->house_count+house;
			printf("\n--> %d more house has been built !\n\n",house);
		}
		else printf("--> You do not have enought money to build house !\n");
	}
	else if(exit==0&&head->house_count>=3)	printf("\n--> There are already 3 houses on this property , You cannot build more !\n\n");
	else if(exit==1)						printf("--> It is not your private property , You cannot build an house !\n\n");
	exit=1,house=4;
}
void payment(struct block* current_block, struct player* current_player,struct block *board)
{
	/*This function for payment system , ıf the use do not enough money to pay his payment , you have to sell his own porperty*/
	/* I added every single situation thanks to if statement */
	/* I also check the current according the parameter */
	/*I also made an computer action in this function  */
	int exit=1,i=0,finish=1,averageCost=0,propertyAmount=0,tempDice=-1,house_check_temp=0;
	struct block* head=malloc(sizeof(struct block));
	head=board;
	for(i=0 ; i<24 ; ++i)
	{
		if(head->type==property)	averageCost=averageCost+head->price,++propertyAmount;
		head=head->next;
	}
	head=board;
	averageCost=averageCost/propertyAmount;


	if(current_block->owner.type==noone&&current_player->type==car&&current_player->account>=current_block->price)					printf("--> You can buy this property , Noone has it !\n");
	else if(current_block->owner.type==noone&&current_player->type==cap&&current_player->account>=current_block->price)
	{
		if(current_block->price<averageCost)
		{
			for(i=11 ; i>=0 && exit; --i)
			{
				if((current_player->owned_block_ids[i])==-1)
				{
					current_player->account=current_player->account-current_block->price;
					current_block->owner.type=cap;
					current_player->owned_block_ids[i]=current_block->block_id;
					printf("--> Computer has bought the %s successfully !\n\n",current_block->name);
					exit=0;
				}
			}
			exit=1;
		}
		else
		{
			tempDice=rand()%6+1;
			if(1<=tempDice&&tempDice>=3)
			{
				for(i=propertyAmount-1 ; i>=0 && exit; --i)
				{
					if((current_player->owned_block_ids[i])==-1)
					{
						current_player->account=current_player->account-current_block->price;
						current_block->owner.type=cap;
						current_player->owned_block_ids[i]=current_block->block_id;
						printf("--> Computer has bought the %s successfully !\n\n",current_block->name);
						exit=0;
					}
				}
				exit=1;
			}
			tempDice=-1;
		}
	}
	else if(current_block->owner.type==cap&&current_player->type==cap)
	{
		if(current_block->house_count<3&&(current_player->account>current_block->house_price))
		{
			for(i=propertyAmount-1 ; i>=0 ; --i)
			{
				if(current_player->owned_block_ids[i]!=-1)	++house_check_temp;
			}
			if(house_check_temp>=propertyAmount/3)
			{
				tempDice=rand()%6+1;
				if(1<=tempDice&&tempDice>=3)
				{
					current_player->account=current_player->account-current_block->house_price;
					current_block->house_count=current_block->house_count+1;
					printf("\n--> Computer has built an house its own property !\n\n");
				}
			}
		}
		else printf("--> Computer cannot build a house due to algorithm !\n\n");
	}
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
void sell_property(struct block* board,struct player* current_player)
{
	int i=0,option=-500,exit=1,quit=1,finish=1,tempSell=0,temp_i=0;
	char answer='a';
	struct block* head=malloc(sizeof(struct block));
	head=board;
	if(current_player->type==car)
	{
		for(i=11 ; i>=0 &&finish ; --i)
		{
			if((current_player->owned_block_ids[i])!=-1)
			{
				go_target_link(&head,current_player->owned_block_ids[i]);
				finish=0;
			}
		}
		if(finish)
		printf("--> You do not have any property to sell ! \n\n");
		else
		{
			show_my_properties(current_player,board);
			printf("--> Do not forget , You will get just half of their prices included houses!\n");
			printf("--> Which properties do you want to sell with its houses ?\n\n");
			while(quit&&option!=-2)
			{
				printf("Please enter the Id of the property : ");
				scanf(" %d",&option);
				for(i=11 ; i>=0&&quit; --i)
				{
					if(current_player->owned_block_ids[i]==option)
					{
						if(head->house_count==0)
						{
							current_player->account = current_player->account + (head->price)/2;
							printf("\n--> %s has been sold successfully \n\n",head->name);
						}
						else if(head->house_count>0)
						{
							current_player->account=current_player->account+(head->price+head->house_price*head->house_count)/2;
							printf("\n--> %s has been sold successfully !\n\n",head->name);
						}
						quit=0;
						head->owner.type=noone;
						current_player->owned_block_ids[i]=-1;
					}
				}
			}
			quit=1;
		}
		head=board;
	}
	else if(current_player->type==cap)
	{
		for(i=11 ; i>=0 ; --i)
		{
			if(current_player->owned_block_ids[i]!=-1)
			{
				go_target_link(&head,current_player->owned_block_ids[i]);
				if(((head->price)+(head->house_count)*(head->house_price))>tempSell)
				{
					tempSell=((head->price)+(head->house_count)*(head->house_price))/2;
					head=board;
					quit=0;
					temp_i=i;
				}
				head=board;
			}
		}
		if(quit==0)
		{
			go_target_link(&head,current_player->owned_block_ids[temp_i]);
			current_player->account=current_player->account+tempSell;
			current_player->owned_block_ids[temp_i]=-1;
			head->owner.type=noone;
			printf("Computer has sold %s which is its own property ! \n\n",head->name);
			head=board;
		}
	}
	quit=1;
	answer='a';
}
void show_my_properties(struct player* current_player,struct block *board)
{
	/*	List of the Current Owned Property  */
	int i=0,t=0;
	struct block* head=malloc(sizeof(struct block));
	head=board;
	printf("\t\t*** Properties ***\n\n");
	for(i=0 ; i<12 ; ++i)
	{
		if((current_player->owned_block_ids[i])!=-1)
		{
			go_target_link(&head,current_player->owned_block_ids[i]);
			printf("--> Propertiy Name : %s (Id:%d) \n",head->name,current_player->owned_block_ids[i]);
			printf("--> House Amount   : %d in %s\n\n",head->house_count,head->name);
			head=board;
		}
		else ++t;
	}
	if(t==12)
		printf("--> You do not have any property\n\n");
	/*--------------------------------------------End---------------------------------------- */
}
void show_properties(struct block *board)
{
	int i=0,propertyTemp=-1,exit_out=1,exit_in=1;
	struct block* head=malloc(sizeof(struct block));

	head=board;

	while(exit_out)
	{
		printf("Please select a property to see details: \n");
		for(i=0 ; i<blockNumber ; ++i)
		{
			go_target_link(&head,i);
			if(head->type==property)
				printf("%2d - %-10s\n",head->block_id,head->name);
			head=board;
		}
		printf("%2d - %-10s\n",0,"Exit");
			while(exit_in)
			{
				scanf("%d",&propertyTemp);
				if(propertyTemp==0)
					exit_in=0;
				for(i=0 ; i<blockNumber ; ++i)
				{
					go_target_link(&head,propertyTemp);
					if(head->type==property)
						exit_in=0;
					head=board;
				}
			}
			if(propertyTemp==0)
				exit_out=0;
			else{
				go_target_link(&head,propertyTemp);
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				printf("|%11s%-20s|\n","",head->name);
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent"," ",head->rent,"$","|");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent 1 H"," ",head->rent_1,"$","|");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent 2 H"," ",head->rent_2,"$","|");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","Rent 3 H"," ",head->rent_3,"$","|");
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				printf("%-8s%-11s%-5s%5d%-1s%3s\n","|","House Price"," ",head->house_price,"$","|");
				for(i=0 ; i<33 ; ++i)
					printf("-");
				printf("\n");
				head=board;
			}
			propertyTemp=-1,exit_in=1;
	}
}
void init_the_board(struct block** board)
{

	/* Initialization of linked list with given as an input */
	/* I am using function to declare linked list in structure */

	struct block *header=malloc(sizeof(struct block));
	header=*board;
	creatingList(board 	,0	,"Start"		,		0,	  	   0,		0,		0,		0,		0,	0,	start 		);
	creatingList(board 	,1	,"Esenyurt"		,	16000,		 800,	 4000,	 9000,	25000,	10000,	0,	property	);
	creatingList(board 	,2	,"Car Park"		,		0,		1500,	    0,		0,		0,		0,	0,	tax   		);
	creatingList(board 	,3	,"Fortune Card"	,		0,		   0,	    0,		0,		0,		0,	0,	fortune 	);
	creatingList(board 	,4	,"Tuzla"		,	16500,		 850,	 4250,	 9500,	26000,	12000,	0,	property	);
	creatingList(board 	,5	,"Arnavutkoy"	,	17000,		 875,	 4500,	10000,	28000,	12000,	0,	property	);
	creatingList(board 	,6	,"Wait 2 Turn"	,		0,		   2,	    0,		0,		0,		0,	0,	punish 		);
	creatingList(board 	,7	,"Catalca"		,	20000,		1000,	 5000,	12000,	30000,	13000,	0,	property	);
	creatingList(board 	,8	,"Beykoz"		,	23000,		1100,	 5500,	12500,	33000,	13000,	0,	property	);
	creatingList(board 	,9	,"Fortune Card"	,		0,		   0,	    0,		0,		0,		0,	0,	fortune 	);
	creatingList(board 	,10	,"Car Fix"		,		0,		1750,	    0,		0,		0,		0,	0,	tax 		);
	creatingList(board 	,11	,"Maltepe"		,	30000,		1350,	 7000,	15000,	40000,	15000,	0,	property	);
	creatingList(board 	,12	,"Bills"		,		0,		2000,	    0,		0,		0,		0,	0,	tax 		);
	creatingList(board 	,13	,"Sisli"		,	33000,		1500,	 8000,	16000,	42000,	16000,	0,	property	);
	creatingList(board 	,14	,"Oil"			,		0,		2250,	    0,		0,		0,		0,	0,	tax   		);
	creatingList(board 	,15	,"Fortune Card"	,		0,		   0,	    0,		0,		0,		0,	0,	fortune 	);
	creatingList(board 	,16	,"Atasehir"		,	35000,		1600,	 8500,	17000,	45000,	17000,	0,	property	);
	creatingList(board 	,17	,"Sariyer"		,	40000,		1750,	 9500,	19000,	48000,	19000,	0,	property	);
	creatingList(board 	,18	,"Wait 1 Turn"	,		0,		   1,	    0,		0,		0,		0,	0,	punish 		);
	creatingList(board 	,19	,"Kadikoy"		,	43000,		1900,	11000,	21500,	55000,	23000,	0,	property	);
	creatingList(board 	,20	,"Besiktas"		,	60000,		2500,	15000,	28000,	60000,	30000,	0,	property	);
	creatingList(board 	,21	,"Fortune Card"	,		0,		   0,	    0,		0,		0,		0,	0,	fortune 	);
	creatingList(board 	,22	,"Vacation"		,		0,		5000,	    0,		0,		0,		0,	0,	tax 		);
	creatingList(board 	,23	,"Bebek"		,	70000,		3500,	20000,	35500,	65000,	35000,	0,	property	);
	(*board)->next=header;
}
void creatingList(struct block** board,int block_id,char * name,int price,int rent,int rent_1,int rent_2,int rent_3,int house_price,int house_count,enum block_type type)
{
	/*  made one banch of opearation for all block  */

	(**board).block_id=block_id;
	(**board).name=name;
	(**board).price=price;
	(**board).rent=rent;
	(**board).rent_1=rent_1;
	(**board).rent_2=rent_2;
	(**board).rent_3=rent_3;
	(**board).house_price=house_price;
	(**board).house_count=house_count;
	(**board).owner.type=noone;
	(**board).type=type;
	(*board)->next=malloc(sizeof(struct block));
	(*board)=(*board)->next;
}
void show_board(struct block* board,struct player player_one,struct player player_two)
{

	/*Printing the board with using three diffrent variable  */
	/*i is keepign the amount of vertical rectanfular block  */
	/*t is keepign the amount of horizonal rectanfular block */
	/*k is keepign three different variable on the block 	 */

	int i=0,j=0,t=0,k=0;
	struct block* head=malloc(sizeof(struct block));
	head=board;
	printf("\t\t\t\t\t\t\t***Welcome to  the Monopoly Game***\n\n");
	while(t<7){
		if(t==0||t==1||t==6){
			for(i=0 ; i<24*7+1 ; ++i)
			printf("-");
		}
		else{
			for(i=0 ; i<24*7+1  ; ++i){
				if(i<25||i>=144)	printf("-");
				else				printf(" ");
			}	
		}
		printf("\n");
		while(k<3){
			for(j=0 ; j<7 ; ++j){
				if(t!=0&&t!=6){
					if(j==6){
						go_target_link(&head,j+t);
						if(k==0)	printf("|%7s%-16s","",head->name);
						if(k==1){
							if(head->type==tax)																	printf("|%7s%-5d$%-10s","",head->rent,"");
							else if(head->type==property)														printf("|%7s%-5d$%-10s","",head->price,"");
							else if((head->type==punish||head->type==start||head->type==fortune))				printf("|%7s%-5s %-10s","","","");
						}
						if(k==2){
							if(head->block_id==player_one.current_block_id&&head->block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
							else if(head->block_id!=player_one.current_block_id&&head->block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
							else if(head->block_id==player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
							else if(head->block_id!=player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s","","");
						}
					}
					else if(j==0){
						go_target_link(&head,blockNumber-t);
						if(k==0)	printf("|%7s%-16s","",head->name);
						if(k==1){
							if(head->type==tax)																			printf("|%7s%-5d$%-10s","",head->rent,"");
							else if(head->type==property)																printf("|%7s%-5d$%-10s","",head->price,"");
							else if(head->type==punish||head->type==start||head->type==fortune)							printf("|%7s%-5s %-10s","","","");
						}
						if(k==2){
							if(head->block_id==player_one.current_block_id&&head->block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
							else if(head->block_id!=player_one.current_block_id&&head->block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
							else if(head->block_id==player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
							else if(head->block_id!=player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s","","");
						}
						
					}
					else if(j==1)	printf("|%7s%-16s","","");
					else			printf("%8s%-16s","","");
				}
				else if(t==0){
					go_target_link(&head,j);
					if(k==0)		printf("|%7s%-16s","",head->name);
					if(k==1){
						if(head->type==tax)															printf("|%7s%-5d$%-10s","",head->rent,"");
						else if(head->type==property)												printf("|%7s%-5d$%-10s","",head->price,"");
						else if(head->type==punish||head->type==start||head->type==fortune)			printf("|%7s%-5s %-10s","","","");
					}
					if(k==2){
						if(head->block_id==player_one.current_block_id&&head->block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
						else if(head->block_id!=player_one.current_block_id&&head->block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
						else if(head->block_id==player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
						else if(head->block_id!=player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s","","");
					}
				}
				else if(t==6){
					go_target_link(&head,blockNumber-t-j);
					if(k==0)		printf("|%7s%-16s","",head->name);
					if(k==1)
					{
						if(head->type==tax)															printf("|%7s%-5d$%-10s","",head->rent,"");
						else if(head->type==property)												printf("|%7s%-5d$%-10s","",head->price,"");
						else if(head->type==punish||head->type==start||head->type==fortune)			printf("|%7s%-5s %-10s","","","");
					}
					if(k==2){
						if(head->block_id==player_one.current_block_id&&head->block_id==player_two.current_block_id)		printf("|%7s    %-12s",player_one.name,player_two.name);
						else if(head->block_id!=player_one.current_block_id&&head->block_id==player_two.current_block_id)	printf("|%7s%-16s",player_two.name,"");
						else if(head->block_id==player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s",player_one.name,"");
						else if(head->block_id!=player_one.current_block_id&&head->block_id!=player_two.current_block_id)	printf("|%7s%-16s", "","");
					}
				}
				head=board;
			}
			printf("|\n");
			++k;
		}
		k=0,++t;
	}
	for(i=0 ; i<24*7+1 ; ++i)
	printf("-");
	printf("\n");
}
void go_target_link(struct block** head,int target_block_id)
{
	/* This function is a special type of function for moving linked node to another linked list node */
	int i=0;
	for(i=0 ; i<target_block_id ; ++i)
		(*head)=(*head)->next;
	/*-------------------------------------------------------------------------------------------------*/
}
void passTurn(int *turnPlayer)
{
	/* Passing the turn of the Gamer */
	if(*turnPlayer==cap) 		*turnPlayer=car;
	else if(*turnPlayer==car)	*turnPlayer=cap;
	/*--------------------------------------------End---------------------------------------- */
}
void moveGamer(struct player* player_one, struct player* player_two,int dice,int *turnPlayer)
{
	/*Moving the Gamer */
	if(*turnPlayer==cap)			player_one->current_block_id=(player_one->current_block_id+dice)%blockNumber;
	else if(*turnPlayer==car)		player_two->current_block_id=(player_two->current_block_id+dice)%blockNumber;
}
void round_allowance(struct block* current_block,struct player* current_player,int dice)
{
	/* It is adding the money to the bank account */
	if((current_player->current_block_id+dice)>23) 
	{
		current_player->account=current_player->account+10000;
		if(current_player->type==cap)		printf("--> Computer has earned 10000$ because of completing the tour !\n\n");
		else if(current_player->type==car) 	printf("--> %s has earned 10000$ because of completing the tour !\n\n",current_player->name);
	}
	/*--------------END--------------------------------------------------------------------------*/
}