#include <iostream>
#include <iomanip>
#include <random>
#include <conio.h>
#include <cassert>

using namespace std;

const int SIZE=4;
const int START_TILES=2;
const int TILE_VALUE[]={2, 4};

class Board{
	public:
	int board[SIZE][SIZE];
    Board(){
    	for(int i=0; i<SIZE; i++){
    	    for(int j=0; j<SIZE; j++){
    	        board[i][j]=0;
    	    }
    	}
    }
    
    void printBoard(int score){
        system("cls");
        cout<<"---------------------------------------------"<<endl;
        cout<<"------------------2048 Game------------------"<<endl;
		cout<<"---------------------------------------------"<<endl<<endl;
        cout<<"Score: "<<score<<endl;
        cout<<"---------------------------------------------"<<endl;
        for(int i=0; i<SIZE; i++){
            for (int j=0; j<SIZE; j++){
            	cout<<setw(9);
                if(board[i][j]==0) cout<<".";
                else cout<<board[i][j];
            }
            cout<<endl;
        }
        cout<<"----------------------------------------------"<<endl<<endl;
    }
};

class TileGenerator{
	public:
	static void generateTile(Board& board){
        vector<pair<int, int>>emptyPosition;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
               	if(board.board[i][j]==0) emptyPosition.push_back({i, j});
            }
        }
        if(emptyPosition.empty()) return;
        int randomIndex=rand()%emptyPosition.size();
        pair<int, int>randomPosition=emptyPosition[randomIndex];
        board.board[randomPosition.first][randomPosition.second]=TILE_VALUE[rand()%2];
    }
};

class Game{
	private:
    	Board gameBoard;
    	int score;
	public:
    	Game():score(0){
        	for (int i=0; i<START_TILES; i++){
        	    TileGenerator::generateTile(gameBoard);
        	}
    	}
    void startScreen(){
        cout<<"2048 game. Press any key to start."<<endl;
        _getch();
    }

    void keyboardInput(char input){
        switch(input){
            case 'a':
                moveLeft();
                break;
            case 's':
                moveDown();
                break;
            case 'w':
                moveUp();
                break;
            case 'd':
                moveRight();
                break;
            default:
                cout<<"To play the game use 'A', 'S', 'W', 'D' keys!"<<endl;
                system("PAUSE");
        }
    }
	
	void moveLeft(){
        for(int i=0; i<SIZE; i++){
            for(int j=1; j<SIZE; j++){
                if(gameBoard.board[i][j]!=0){
                    int temp=j;
                    while(temp>=1 && gameBoard.board[i][temp-1]==0){
                        gameBoard.board[i][temp-1]=gameBoard.board[i][temp];
                        gameBoard.board[i][temp]=0;
                        temp--;
                    }
                    if(temp>=1 && gameBoard.board[i][temp-1]==gameBoard.board[i][temp]){
                        gameBoard.board[i][temp-1]=gameBoard.board[i][temp-1]*2;
                        gameBoard.board[i][temp]=0;
                        score=score+gameBoard.board[i][temp-1];
                    }
                }
            }
        }
    }
    
    void moveRight(){
        for (int i=0; i<SIZE; i++){
            for (int j=SIZE-2; j>=0; j--){
                if(gameBoard.board[i][j]!=0){
                    int temp=j;
                    while(temp<SIZE-1 && gameBoard.board[i][temp+1]==0){
                        gameBoard.board[i][temp+1]=gameBoard.board[i][temp];
                        gameBoard.board[i][temp]=0;
                        temp++;
                    }
                    if(temp<SIZE-1 && gameBoard.board[i][temp+1]==gameBoard.board[i][temp]){
                        gameBoard.board[i][temp+1]=gameBoard.board[i][temp + 1]*2;
                        gameBoard.board[i][temp]=0;
                        score=score+gameBoard.board[i][temp+1];
                    }
                }
            }
        }
    }

    void moveUp(){
        for(int j=0; j<SIZE; j++){
            for(int i=1; i<SIZE; i++){
                if(gameBoard.board[i][j]!=0){
                    int temp=i;
                    while(temp>=1 && gameBoard.board[temp-1][j]==0){
                        gameBoard.board[temp-1][j]=gameBoard.board[temp][j];
                        gameBoard.board[temp][j]=0;
                        temp--;
                    }
                    if(temp>=1 && gameBoard.board[temp-1][j]==gameBoard.board[temp][j]){
                        gameBoard.board[temp-1][j]=gameBoard.board[temp-1][j]*2;
                        gameBoard.board[temp][j]=0;
                        score=score+gameBoard.board[temp-1][j];
                    }
                }
            }
        }
    }

    void moveDown(){
        for(int j=0; j<SIZE; j++){
            for(int i=SIZE-2; i>=0; i--){
                if(gameBoard.board[i][j]!=0){
                    int temp=i;
                    while(temp<SIZE-1 && gameBoard.board[temp+1][j]==0){
                        gameBoard.board[temp+1][j]=gameBoard.board[temp][j];
                        gameBoard.board[temp][j]=0;
                        temp++;
                    }
                    if(temp<SIZE-1 && gameBoard.board[temp+1][j]==gameBoard.board[temp][j]){
                        gameBoard.board[temp+1][j]=gameBoard.board[temp+1][j]*2;
                        gameBoard.board[temp][j]=0;
                        score=score+gameBoard.board[temp+1][j];
                    }
                }
            }
        }
    }
    void testStartingScore(){
    	int expectedScore=0;
    	int currentScore=score;
    	assert(currentScore==expectedScore);
	}
	
	void testStartingBoard(){
		int numberCount=0;
		for(int i=0; i<SIZE; i++){
			for(int j=0; j<SIZE; j++){
				if(gameBoard.board[i][j]!=0) numberCount++;
			}
		}
		assert(numberCount==2);
	}
	
	void testIsGameOver(){
		bool condition=isGameOver();
		assert(condition==false);
	}
	
    
    void playGame(){
        char input;
        do {
            gameBoard.printBoard(score);
            if(_kbhit()) {
                input=_getch();
                keyboardInput(input);
                TileGenerator::generateTile(gameBoard);
            }
        } 
		while(!isGameOver());
        cout<<"Game over! Your score is: "<<score<<endl;
        system("PAUSE");
    }
    
    bool isGameOver(){
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                if(gameBoard.board[i][j]==2048){
                    cout<<"You won!"<<endl;
                    return true;
                }
                if(gameBoard.board[i][j]==0) return false;
                if(gameBoard.board[i][j]==gameBoard.board[i][j+1] && j<SIZE-1) return false;
                if(gameBoard.board[i][j]==gameBoard.board[i+1][j] && i<SIZE-1) return false;
            }
        }
        return true;
    }
};

int main(){
    Game game;
    game.startScreen();
    game.testStartingScore();
    game.testStartingBoard();
    game.testIsGameOver();
    game.playGame();

    return 0;
}

