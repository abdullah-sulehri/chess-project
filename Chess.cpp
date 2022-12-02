#include<iostream>
#include<cstring>
#include<stdio.h>
#include<conio.h>
#include<cmath>
using namespace std;
char board[8][8];
void initialize();
void rowAddress();
void columnAddress();
void displayBoard();
void move(char[],char[]);
int destCheck(char, char);
int player=1;
int main()
{

	//initialize board
	initialize();
	displayBoard();
	//move('');
	//displayBoard();
	
}
void initialize(){
	board[0][0]='r';
	board[0][1]='n';
	board[0][2]='b';
	board[0][3]='q';
	board[0][4]='k';
	board[0][5]='b';
	board[0][6]='n';
	board[0][7]='r';

	for (int j=0;j<8;j++)
	{
		board[1][j]='p';
		board[6][j]='P';
	}
	
	for(int i=2;i<=5;i++)
	{
		for (int j=0;j<8;j++)
		{
			board[i][j]=' ';
		}
	}
	board[7][0]='R';
	board[7][1]='N';
	board[7][2]='B';
	board[7][3]='Q';
	board[7][4]='K';
	board[7][5]='B';
	board[7][6]='N';
	board[7][7]='R';
	}
void rowAddress()
{
	cout<<"    "<<(char)201;
	for(int i=1;i<=23;i++)
	{
		cout<<(char)205;
		if(i%3==0)
		{
			cout<<(char)203;
		}
		
	}
	cout<<(char)205<<(char)187;
	cout<<endl<<"    ";
	for(int i=97;i<=104;i++)
	{
		cout<<(char)186<<" "<<(char)i<<" ";
	}
	cout<<(char)186<<endl<<"    ";
	cout<<(char)200;
	for(int i=1;i<=23;i++)
	{
		cout<<(char)205;
		if(i%3==0)
		{
			cout<<(char)202;
		}
    }
    cout<<(char)205<<(char)188;
	cout<<endl;
	
}
void displayBoard(){
	system("cls");
	rowAddress();
	//firstline
	cout<<"    "<<(char)201;
	for(int i=1;i<=23;i++)
	{
		cout<<(char)205;
		if(i%3==0)
		{
			cout<<(char)203;
		}
    }
    cout<<(char)205<<(char)187;
	cout<<endl<<"  ";
	//data line
	for (int i=0;i<8;i++)
	{
		cout<<8-i<<" ";
		for (int j=0;j<8;j++)
		{
		cout<<(char)186<<" "<<board[i][j]<<" ";
		}
		cout<<(char)186<<endl<<"    ";
		
		//sperator
		if(i<7){
			cout<<(char)204;
			for(int k=0;k<8;k++)
			{
				cout<<(char)205<<(char)205<<(char)205;
				if(k<7)
				{
					cout<<(char)206;
				}
				else
				cout<<(char)185;
			}
			cout<<endl<<"  ";
		}
	 } 
	 //last line
	 	cout<<(char)200;
	for(int i=1;i<=23;i++)
	{
		cout<<(char)205;
		if(i%3==0)
		{
			cout<<(char)202;
		}
    }
    cout<<(char)205<<(char)188;
	cout<<endl;
	cout<<"Player "<< player<<" move"<<endl;
	char saddress[2],daddress[2];
	cout<<"Enter source address : ";
	gets(saddress);
	cout<<"Enter destination address: ";
	gets(daddress);
	
	move(saddress,daddress);
	//if(winCondition)
	// {displayWinBoard(); return; }
	//else displayBoard();

	displayBoard();
	
	
}

void move(char sa[2], char da[2])
{
	//cout<<sa<<": "<<da;
	
	int scol=   (int)sa[0] - 97;
	int srow = 8 - ((int)sa[1] - 48);
	
	int dcol= (int)da[0] - 97;
	int drow= 8 - ((int)da[1] - 48);
	int rowDiff;
	int colDiff;
	colDiff=abs(scol-dcol);
	rowDiff=abs(srow-drow);

	//cout<<colDiff<<", "<<rowDiff;
	gets(sa);
	
	//Pawn Move
		if(((board[srow][scol]=='P' && drow<srow && player==1) || (board[srow][scol]=='p' && srow<drow && player==2))
		  &&	destCheck(board[srow][scol],board[drow][dcol]))
		{
				if((srow==6 || srow==1) && rowDiff<=2 && colDiff==0 && board[drow][dcol]==' ')
				{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
				}else if(rowDiff==1 && colDiff==0 && board[drow][dcol]==' ')
				{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
				}
				else if(rowDiff==1 && colDiff==1 && board[drow][dcol]!=' ')
				{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
				
				}else
				{
					cout<<"Invalid Move "; getche();
					return;	
				}	//Pawn Promotion		
				if(player==1)
				{
				for(int i=0;i<8;i++)
				{
					if(board[0][i]=='P')
					{
						cout<<"PAWN PROMOTION "<<endl;
						cout<<"Enter Q to make Queen "<<endl;
						cout<<"Enter K to make king "<<endl;
						cout<<"Enter R to make Rook "<<endl;
						cout<<"Enter N to make Knight "<<endl;
						char ch;
						cin>>ch;
						if (ch=='Q' || ch=='K'|| ch=='N' || ch=='R')
						{
							board[0][i]=ch;
							break;
						}
						else
						{
							cout<<"Please Enter the Correct character ";
							i--;
						}
					}
				}
			}
				if(player==2)
				{
					for(int i=0;i<8;i++)
				{
					if(board[7][i]=='p')
					{
						cout<<"PAWN PROMOTION "<<endl;
						cout<<"Enter q to make Queen "<<endl;
						cout<<"Enter k to make king "<<endl;
						cout<<"Enter r to make Rook "<<endl;
						cout<<"Enter n to make Knight "<<endl;
						char ch;
						cin>> ch;
						if (ch=='q' || ch=='k'|| ch=='n' || ch=='r')
						{
							board[7][i]=ch;
							break;
						}
						else{
							cout<<"Please Enter The Correct Character ";
							i--;
						}
						
					}
				}
			}
					
				
			} 
		//Knight move
	    else if( (board[srow][scol]=='N'  && player==1 || board[srow][scol]=='n'  && player==2)
	    	&&	destCheck(board[srow][scol],board[drow][dcol]))
		{
			if (rowDiff==2 && colDiff==1)
			{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
			}
			else 
			{
				cout<<"Invalid Move ";
				getche();
				return;
			}
		}
	    else if ( (board[srow][scol]=='R' && player==1 || board[srow][scol]=='r' && player==2)
	    	&&	destCheck(board[srow][scol],board[drow][dcol]))
		{
			
			int checkrow=1,checkcol=1;
			
			if(drow>srow){
		
				for(int i=srow+1;i<drow;i++)
				{
					if(board[i][scol]==' ' )
					{
						checkrow=1;
					}
					else{
						checkrow=0;
						break;
					}
				}
			}else{
				for(int i=srow-1;i>drow;i--)
				{
					if(board[i][scol]==' ' )
					{
						checkrow=1;
					}
					else{
						checkrow=0;
						break;
					}
				}
			}
		if (dcol>scol)
			{
				for(int j=scol+1;j<dcol;j++)
				{
				if(board[srow][j]==' ')
				{
					checkcol=1;
				}
				else{
					checkcol=0;
					break;
				}
			}
		}
		else
		{
				for(int i=scol-1;i>dcol;i--)
				{
					if(board[srow][i]==' ' )
					{
						checkcol=1;
					}
					else{
						checkcol=0;
						break;
					}
				}
			}
			if(checkrow==1 && checkcol==1)
			{
				board[drow][dcol]=board[srow][scol];
				board[srow][scol]=' ';
			}
			else
			{
				cout<<"Invalid Move ";
				getche();
				return;
			}
			
		}
		//king move
		else if ((board[srow][scol]=='K' && player==1 || board[srow][scol]=='k' && player==2) &&	destCheck(board[srow][scol],board[drow][dcol]))
		{
			int qcastle=0;
			int kcastle=0;
			//if(rowDiff==1||colDiff==1)
			//{
			//	if (board[drow][dcol]==' ' && board[7][])
			//	{
			//		board[drow][dcol]=board[srow][scol];
			//	    board[srow][scol]=' ';
			//	}
			
			//castling Player 1
			if(player==1){
			
			 if (colDiff==2 && srow==7 && dcol==2 && board[srow][0]=='R')
			 {
			 	for(int i=1;i<scol;i++)
			 	{
			 		if(board[srow][i]==' ')
			 		{
			 			qcastle=1;
					 }
					 else
					 {
					 	qcastle=0;
					 	break;
					 }
				
				 }
			 }
			 else if(colDiff==1 && srow==7 && dcol==6 && board[srow][7]=='R')
			 {
			 	for(int i=scol+1;i<7;i++)
			 	{
			 		if(board[srow][i]==' ')
			 		{
			 			kcastle=1;
					 }
					 else{
					 	kcastle=0;
					 	break;
					 }
				 } 
			 }
			 if (qcastle==1)
			 {
			 	board[drow][dcol]=board[srow][scol];
			 	board[drow][scol-1]=board[drow][0];
			 	board[srow][scol]=' ';
			 	board[drow][0]=' ';
			 }
			 else if(kcastle==1)
			 {
			 	board[drow][dcol]=board[srow][scol];
			 	board[drow][scol+1]=board[drow][7];
			 	board[srow][scol]=' ';
			 	board[drow][7]=' ';
			 }
		}
			 //castling player 2
			 if(player==2)
			 {
			 if (colDiff==2 && srow==0 && dcol==2 && board[srow][0]=='r')
			 {
			 	for(int i=1;i<scol;i++)
			 	{
			 		if(board[srow][i]==' ')
			 		{
			 			qcastle=1;
					 }
					 else{
					 	qcastle=0;
					 	break;
					 }
				 }
			 }
			 else if(colDiff=1 && srow==7 && dcol==6 && board[srow][7]=='r')
			 {
			 	for(int i=scol+1;i<dcol;i++)
			 	{
			 		if(board[srow][i]==' ')
			 		{
			 			kcastle=1;
					 }
					 else{
					 	kcastle=0;
					 	break;
					 }
				 }
				 
			 }
		}
			
		}
	//	else if ((board[srow][scol]=='B' && player==1 || board[srow][scol]=='b') 
	//	&& destCheck(board[srow][scol],board[drow][dcol]))
	//	{
	//		if(rowDiff>=1 && colDiff>=1)
	//		{			
	//		int checkrow=1;
	//		if(drow>srow){
	//		for(int i=srow+1;i<drow;i++)
	//		{
	//			if(board[i][scol]=='')
	//		}
	//		}
			
		
	
	
		else
		{
		cout<<"Invalid Move "; 
		getche();
		return;	
		}
		
		

	
	if(player==1)
		player=2;
	else
		player=1;
	
	 
}

int destCheck(char source, char destination){
	if(destination==' '){
		return 1;
	}
	int sourceAscii= (int)source;
	int desAscii = (int)destination;
	
	if((sourceAscii>=65 && sourceAscii<=90 && desAscii>=97 && desAscii<=122) ||
		(desAscii>=65 && desAscii<=90 && sourceAscii>=97 && sourceAscii<=122) )
		return 1;
	else
		return 0;
	
}
