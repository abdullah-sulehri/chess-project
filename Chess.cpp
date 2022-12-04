#include<iostream>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<conio.h>
#include<cmath>
#include<ctime>
#include<stdlib.h>
using namespace std;
char board[8][8];
void initialize();
void rowAddress();
void columnAddress();
void printBoard();
int move(string);
int destCheck(char, char);
void startGame();
void loadGame();
int player=1;
int moveInput();
fstream gameFile;
char gameType;
void errorMessage();
int player1Seconds=30;
int player2Seconds=10*60;
long chessTimer=0;
bool checkp1();
bool checkp2();
bool checkmate2(char board[8][8]);
bool checkmate1(char board[8][8]);
void errorMessage()
{
	cout<<"Invalid Move, press any key to continue..."<<endl;
	getche();
}
int moveInput()
{
	cout<<"Player "<< player<<" move";
	if(gameType=='R' || gameType=='r'){
		cout<<", seconds remaining : ";
		if(player==1){
			cout<<player1Seconds;
		}else
		{
			cout<<player2Seconds;
		}
	}

	cout<<endl;
	char moveChars[5];
	string moveString;
	cout<<"Enter your move or write RES to resign game : ";
	gets(moveChars);
	if(strlen(moveChars)>=3 && strcmp(moveChars,"END")==0)
	{
		if (player==1){
			cout<<"Player 1 Resigned"<<endl<<"Player 2 won the game "<<endl;
		}
		else{
			cout<<"Player 2 Resigned"<<endl<<"Player 1 won the game "<<endl;
		}
		gameFile.close();
		return 0;
	}
	else if(strlen(moveChars)==5) 
	{
		int c=move(moveChars);
		gameFile<<(moveChars)<<endl;
		return c;	
	}
	else
	{
		cout<<"invalid Input";
		getche();
		return 1;		
	}
}
int destCheck(char source, char destination)
{
	if(destination==' ')
	{
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

int main()
{
	char game;
	cout<<"Enter Game type (C for classic R for rapid): ";
	cin>>gameType;
	cout<<"Enter N for new game and L to load existing game : ";
	cin>>game;
	cout<<endl;
	if(game=='N' || game=='n')
	{
		gameFile.open("chess-game.txt",ios::out);
		chessTimer=time(0);
		initialize();
		startGame();	
	}
	else if (game=='L' || game=='l')
	{
		initialize();
		loadGame();
		startGame();
	}
//	else 
//	{
//		cout<<"Please enter a Valid character "<<endl;
//		startGame();
//	}
	
}
void initialize(){
	board[0][0]='r';
	board[0][1]='n';
	board[0][2]='b'; //for testing putting spaces in b q 
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
	board[7][2]='B'; //for testing putting spaces at B Q 
	board[7][3]='Q';
	board[7][4]='K';
	board[7][5]='B';
	board[7][6]='N';
	board[7][7]='R';
	}
void loadGame(){
	string moveString;
	gameFile.open("chess-game.txt",ios::in);
	player=1;
	char ch=' ';
	//getline reads one line from gameFile and put it in moveString var
	//returns 0 if there is no more line to read
	while (getline (gameFile, moveString)) {
  		move(moveString); 
  		printBoard();
  		if(ch==' '){
  		  	cout<<"Press space to continue, any other key to jump to last move";
  			ch=getche();	
		}
  	}
	gameFile.close();
	gameFile.open("chess-game.txt",ios::app);
}
void startGame()
{
	int cont=1;
	do
	{
		printBoard();
		cont=moveInput();
	}
	while(cont==1);
}


void rowAddress() //prints a,b,c row
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
void printBoard(){
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

}

int move(string moveString)
{
	//cout<<sa<<": "<<da;
	
	int scol=   (int)moveString.at(0) - 97;
	int srow = 8 - ((int)moveString.at(1) - 48);
	
	int dcol= (int)moveString.at(3) - 97;
	int drow= 8 - ((int)moveString.at(4) - 48);
	//cout<<scol<<", "<<srow<<", "<<dcol<<", "<<drow<<endl;
	
	if( scol>7 || dcol>7 || scol<0 || dcol<0 || drow<0 || drow>7 || srow<0 || srow>7 )
	{
		cout<<"Move is outside the board, select correct move, press any key to continue... ";
		getche();
		return 1;
	}
	int rowDiff;
	int colDiff;
	colDiff=abs(scol-dcol);
	rowDiff=abs(srow-drow);

	//cout<<colDiff<<", "<<rowDiff;
	//getche();
	
	//Pawn Move
		if(((board[srow][scol]=='P' && drow<srow && player==1) || (board[srow][scol]=='p' && srow<drow && player==2))
		  &&	destCheck(board[srow][scol],board[drow][dcol]))
			{
				if((srow==6 || srow==1) && rowDiff<=2 && colDiff==0 && board[drow][dcol]==' ')
				{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
				}
				else if(rowDiff==1 && colDiff==0 && board[drow][dcol]==' ')
				{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
				}
				else if(rowDiff==1 && colDiff==1 && board[drow][dcol]!=' ')
				{
					board[drow][dcol]=board[srow][scol];
					board[srow][scol]=' ';
				
				}
				else
				{
					errorMessage();
					return 1;
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
							else
							{
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
				errorMessage();
				return 1;
			}
		}
		//Rook Move
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
			}
			else
			{
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
				else
				{
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
					else
					{
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
				errorMessage();
				return 1;
			}
			
		}
		//king move
		else if ((board[srow][scol]=='K' && player==1 || board[srow][scol]=='k' && player==2) &&	destCheck(board[srow][scol],board[drow][dcol]))
		{
			if(player==1)
			{
			if(rowDiff>1 || colDiff>1)
			{
					
			if (colDiff==2 && drow==7 && dcol==2 && board[srow][0]=='R' && board[7][1]==' ' && board[7][2]==' ' && board[7][3]==' ')
			 {
				board[drow][dcol]=board[srow][scol];
			 	board[drow][3]=board[drow][0];
			 	board[srow][scol]=' ';
			 	board[drow][0]=' ';
			 }
			 else if(colDiff==2 && drow==7 && dcol==6 && board[drow][7]=='R' && board[drow][6]==' ' && board[drow][5]==' ' )
			 {
			 	board[drow][dcol]=board[srow][scol];
			 	board[drow][5]=board[drow][7];
			 	board[srow][scol]=' ';
			 	board[drow][7]=' ';
			 }
			 	else 
				{
				errorMessage();
				return 1;
				}
		}
			 else if((rowDiff==1 && colDiff==1) || (rowDiff==1 && colDiff==0) || (rowDiff==0 && colDiff==1))
			{
				if (destCheck(board[srow][scol],board[drow][dcol]))
				{
				board[drow][dcol]=board[srow][scol];
			    board[srow][scol]=' ';
				}
				else 
				{
				errorMessage();
				return 1;
				}
			}
		}
			 //castling player 2
			 else if(player==2)
			 {
			 	if (colDiff>1 || rowDiff>1)
			 	{
				
			 		if (colDiff==2 && drow==0 && dcol==2 && board[drow][0]=='r' && board[0][1]==' ' && board[0][2]==' ' && board[0][3]==' ')
			 		{
			 			board[drow][dcol]=board[srow][scol];
			 			board[drow][3]=board[drow][0];
			 			board[srow][scol]=' ';
			 			board[drow][0]=' ';
			 		}
			 		else if(colDiff==2 && drow==0 && dcol==6 && board[drow][7]=='r' && board[drow][6]==' ' && board[drow][5]==' ' )
			 		{
			 			board[drow][dcol]=board[srow][scol];
			 			board[drow][5]=board[drow][7];
			 			board[srow][scol]=' ';
			 			board[drow][7]=' ';
			 		}
			 			else 
				{
				errorMessage();
				return 1;
				}
			 	}
			 	else if((rowDiff==1 && colDiff==1) || (rowDiff==1 && colDiff==0) || (rowDiff==0 && colDiff==1))
				{
					if (destCheck(board[srow][scol],board[drow][dcol]))
					{
						board[drow][dcol]=board[srow][scol];
			    		board[srow][scol]=' ';
					}
					else 
					{
						errorMessage();
						return 1;
					}
				}
			}
		}
		else if ((board[srow][scol]=='B' && player==1) || (board[srow][scol]=='b' && player==2) 
			&& destCheck(board[srow][scol],board[drow][dcol]))
		{
			if(rowDiff!=colDiff)
			{
				errorMessage();
				return 1;
			}
			int rowStep,  colStep;
			if(srow<drow)
			{
				rowStep=1;
			}
			else
			{
				rowStep=-1;	
			}
			if(scol<dcol)
			{
				colStep=1;
			}
			else
			{
				colStep=-1;
			}
			int j=scol+colStep, checkDiag=1;
			
			for(int i=srow+rowStep;i!=drow;i+=rowStep){
				//cout<<i<<", "<<j<<endl;
				if(board[i][j]==' ')
				{
					checkDiag=1;
				}
				else
				{
					checkDiag=0;
					break;
				}
				j+=colStep;
			}
			if(checkDiag==1)
			{
				board[drow][dcol]=board[srow][scol];
				board[srow][scol]=' ';
			}
			else
			{
				errorMessage();
				return 1;
			}
		}
		//queen move
		else if((board[srow][scol]=='Q' && player==1 || board[srow][scol]=='q') && destCheck(board[srow][scol],board[drow][dcol]))
		{
				if(rowDiff!=colDiff)
			{
				errorMessage();
				return 1;
			}
			int rowStep,  colStep;
			if(srow<drow)
			{
				rowStep=1;
			}
			else
			{
				rowStep=-1;	
			}
			if(scol<dcol)
			{
				colStep=1;
			}
			else
			{
				colStep=-1;
			}
			int j=scol+colStep, checkDiag=1;
			
			for(int i=srow+rowStep;i!=drow;i+=rowStep){
				//cout<<i<<", "<<j<<endl;
				if(board[i][j]==' ')
				{
					checkDiag=1;
				}
				else
				{
					checkDiag=0;
					break;
				}
				j+=colStep;
			}
			if(checkDiag==1)
			{
				board[drow][dcol]=board[srow][scol];
				board[srow][scol]=' ';
			}
			else
			{
				errorMessage();
				return 1;
			}
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
			}
			else
			{
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
				else
				{
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
					else
					{
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
				errorMessage();
				return 1;
			}
		}
		
		else
		{
		errorMessage();
		return 1;
		}
	
	long currentTime=time(0);
	if(player==1){
		if(gameType=='R' || gameType=='r'){
			// chessTimer = initial time
			player1Seconds -= (currentTime-chessTimer);
			if(player1Seconds<=0){
				return 0;
			}
			player1Seconds+=10;
			chessTimer=currentTime;
			
		}

		player=2;
		if(checkp2()){
			cout<<"Check for player 2"<<endl;
			getche();
		}
	}
	else{
		if(gameType=='R' || gameType=='r'){
			player2Seconds -= (currentTime-chessTimer);
			if(player2Seconds<=0){
				return 0;
			}
			player2Seconds+=10;
			chessTimer=currentTime;
		}
		player=1;
		if(checkp1()){
			cout<<"check for player 1"<<endl;
			getche();
		}
	}
		
	return 1;
}
bool checkp1()
{
    bool check=0;
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j]=='K'&& player==1)
            {
                
                if(board[i-1][j-1]=='b'||board[i-1][j-1]=='p'||board[i-1][j-1]=='q'||board[i-1][j-1]=='k')
                {
                    check=1;
                    return(check);
                }
                if(board[i-1][j+1]=='b'||board[i-1][j+1]=='p'||board[i-1][j+1]=='q'||board[i-1][j+1]=='k')
                {
                    check=1;
                    return(check);
                }
                if(board[i+1][j+1]=='b'||board[i+1][j+1]=='q'||board[i+1][j+1]=='k')
                {
                    check=1;
                    return(check);
                }
                if(board[i+1][j-1]=='b'||board[i+1][j-1]=='q'||board[i+1][j-1]=='k')
                {
                    check=1;
                    return(check);
                }
                if(board[i-2][j-1]=='n'||board[i-2][j+1]=='n'||board[i+2][j-1]=='n'||board[i+2][j+1]=='n')
                {
                    check=1;
                    return(check);
                }
                
                //horizontal
                
                for(int k=1;board[i+k][j]==' ';k++)
                {
                    if(board[i+k+1][j]=='r'||board[i+k+1][j]=='q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i-k][j]==' ';k++)
                {
                    if(board[i-k-1][j]=='r'||board[i-k-1][j]=='q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i][j+k]==' ';k++)
                {
                    if(board[i][j+k+1]=='r'||board[i][j+k+1]=='q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i][j-k]==' ';k++)
                {
                    if(board[i][j-k-1]=='r'||board[i][j-k-1]=='q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                //horizontal end
                
                //diagonal
                
                for(int k=1;board[i+k][j+k]==' ';k++)
                {
                    if(board[i+k+1][j+k+1]=='b'||board[i+k+1][j+k+1]=='q')
                    {
                        check=1;
                    }
                }
                
                
            }//if
            else{
            	cout<<"Player 2 Wins";//end game krani idher
            	getche();
            	exit(0);
        		
			}
        }//for
    }//fn
}
bool checkp2()
{
    bool check=0;
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j]=='k'&& player==2)
            {
                
                if(board[i-1][j-1]=='B' || board[i-1][j-1]=='Q' || board[i-1][j-1]=='K')
                {
                    check=1;
                    return(check);
                }
                if(board[i-1][j+1]=='B' || board[i-1][j+1]=='Q' || board[i-1][j+1]=='K')
                {
                    check=1;
                    return(check);
                }
                if(board[i+1][j+1]=='B' || board[i+1][j+1]=='Q' || board[i+1][j+1]=='K' || board[i+1][j+1]=='P')
                {
                    check=1;
                    return(check);
                }
                if(board[i+1][j-1]=='B' || board[i+1][j-1]=='Q' || board[i+1][j-1]=='K' || board[i+1][j-1]=='P')
                {
                    check=1;
                    return(check);
                }
                if(board[i-2][j-1]=='N' || board[i-2][j+1]=='N' || board[i+2][j-1]=='N' || board[i+2][j+1]=='N')
                {
                    check=1;
                    return(check);
                }
                
                //horizontal
                
                for(int k=1;board[i+k][j]==' ';k++)
                {
                    if(board[i+k+1][j]=='R'||board[i+k+1][j]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i-k][j]==' ';k++)
                {
                    if(board[i-k-1][j]=='R' || board[i-k-1][j]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i][j+k]==' ';k++)
                {
                    if(board[i][j+k+1]=='R'||board[i][j+k+1]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                    for(int k=1;board[i][j-k]==' ';k++)
                {
                    if(board[i][j-k-1]=='R'||board[i][j-k-1]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                //horizontal end
                
                //diagonal
                
                for(int k=1;board[i+k][j+k]==' ';k++)
                {
                    if(board[i+k+1][j+k+1]=='B'||board[i+k+1][j+k+1]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i-k][j-k]==' ';k++)
                {
                    if(board[i-k-1][j-k-1]=='B'||board[i-k-1][j-k-1]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i+k][j-k]==' ';k++)
                {
                    if(board[i+k+1][j-k-1]=='B'||board[i+k+1][j-k-1]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
                for(int k=1;board[i-k][j+k]==' ';k++)
                {
                    if(board[i-k-1][j+k+1]=='B'||board[i-k-1][j+k+1]=='Q')
                    {
                        check=1;
                        return(check);
                    }
                }
                
               } //diagonal end
                
            }//if
            
            else{
            	cout<<"Player 1 Wins";//end game krani idher
            	getche();
            	exit(0);
        		
			}
            
        }//for input
    }//for outer
    return(check);
}//fn
//bool checkmate1(char board[8][8])
//{
//    bool checkmateup=0,checkmatedown=0,checkmateleft=0,checkmateright=0,checkmateupright=0,checkmateupleft=0;
//    bool checkmatedownright=0,checkmatedownleft=0;
//    bool owncheck=0;
//    bool checkmate=0;
//    
//    for(int i=0;i<8;i++)
//    {
//        for(int j=0;j<8;j++)
//        {
//            if(board[i][j]=='K'&&player==1)
//            {
//                owncheck=checkp1(board[i][j]);
//                checkmatedown=checkp1(board[i+1][j]);
//                checkmateup=checkp1(board[i-1][j]);
//                checkmateright=checkp1(board[i][j+1]);
//                checkmateleft=checkp1(board[i][j-1]);
//                checkmatedownright=checkp1(board[i+1][j+1]);
//                checkmatedownleft=checkp1(board[i+1][j-1]);
//                checkmateupright=checkp1(board[i-1][j+1]);
//                checkmateupleft=checkp1(board[i-1][j-1]);
//            }
//        }
//        
//    }
//    //Game end krani hai player 2 jeet gya by checkmate
//    
//    if(checkmateup==1 && checkmatedown==1 && checkmateleft==1 && checkmateright==1 && checkmateupright==1 &&checkmateupleft==1 &&
//    checkmatedownright==1 && checkmatedownleft==1)
//    {
//        return(1);
//    }
//        
//        return(0);
//}
//bool checkmate2(char board[8][8])
//{
//    bool checkmateup=0,checkmatedown=0,checkmateleft=0,checkmateright=0,checkmateupright=0,checkmateupleft=0;
//    bool checkmatedownright=0,checkmatedownleft=0;
//    bool owncheck=0;
//    bool checkmate=0;
//    
//    for(int i=0;i<8;i++)
//    {
//        for(int j=0;j<8;j++)
//        {
//            if(board[i][j]=='k'&&player==2)
//            {
//                owncheck=checkp2(board[i][j]);
//                checkmatedown=checkp2(board[i+1][j]);
//                checkmateup=checkp2(board[i-1][j]);
//                checkmateright=checkp2(board[i][j+1]);
//                checkmateleft=checkp2(board[i][j-1]);
//                checkmatedownright=checkp2(board[i+1][j+1]);
//                checkmatedownleft=checkp2(board[i+1][j-1]);
//                checkmateupright=checkp2(board[i-1][j+1]);
//                checkmateupleft=checkp2(board[i-1][j-1]);
//            }
//        }
//        
//    }
//    if(checkmateup==1 && checkmatedown==1 && checkmateleft==1 && checkmateright==1 && checkmateupright==1 &&checkmateupleft==1 &&
//    checkmatedownright==1 && checkmatedownleft==1)
//    {
//        return(1);
//    }
//        
//        return(0);
//}




