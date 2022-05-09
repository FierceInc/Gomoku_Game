#include<iostream>
#include <random>
#include<windows.h>
#include <vector>
#include "game.h"
#include <fstream>
#include <string>
using namespace std;

int * readFromFile() {
    string size; //This takes the value of each line in the Input File
    int _size; //This will hole the integers converted from the [size]
    int i = 0;
    int *boardSize = new int[i]; //And Array for holding the values you get from the Input File
    ifstream Input("input.txt"); //Opens The File
    if(Input.is_open() && Input.peek() != Input.eof()) //Check if its Open or Not
    {
        while (!Input.eof()) //While you are not at the end of the file call this loop
        {
            getline(Input, size); //Read the file line by line
            _size = stoi(size); // Convert strings into intager... This return the integer in a string... [6 fries] will return 6;
            boardSize[i] = _size; // Insert the values to the array
            i++; // Increase the index
        }
    }
    else 
    {
        exit(10); // If the file is not open exit the program
    }
    Input.close();
    return boardSize;

};

// Here you check for wins; By taking the current board and looping through it to find 5 in a row;
bool checkWin(int **board, int playerPiece, int boardSize) 
{
     int spaces = boardSize % 5;
     for(int col = 0; col < boardSize; col++){
         for (int row = 0; row < boardSize - spaces; row++){
             if(board[col][row] == playerPiece && board[col][row + 1] == playerPiece && board[col][row + 2] == playerPiece && board[col][row + 3] == playerPiece && board[col][row + 4] == playerPiece) {
                 return true;
             }
         }    
     }
     for(int col = 0; col < boardSize - spaces; col++){
         for (int row = 0; row < boardSize ; row++){
             if(col <= spaces ) {
                    if(board[col][row] == playerPiece && board[col + 1][row] == playerPiece && board[col + 2][row] == playerPiece && board[col + 3][row] == playerPiece && board[col + 4][row] == playerPiece) {
                                    return true;
                                }
             }
         }    
     }

      for(int col = 0; col < boardSize - spaces; col++){
         for (int row = 0; row < boardSize - spaces; row++){
             if(col <= spaces ) {
                    if(board[col][row] == playerPiece && board[col + 1][row + 1] == playerPiece && board[col + 2][row + 2] == playerPiece && board[col + 3][row + 3] == playerPiece && board[col + 4][row + 4] == playerPiece) {
                                    return true;
                                }
             }
         }    
     }
 for(int col = 0; col < boardSize; col++){
         for (int row = spaces; row < boardSize ; row++){
             if(col <= spaces ) {
                    if(board[col][row] == playerPiece && board[col + 1][row - 1] == playerPiece && board[col + 2][row - 2] == playerPiece && board[col + 3][row - 3] == playerPiece && board[col + 4][row - 4] == playerPiece) {
                                    return true;
                                }
             }
         }    
     }
     return false;
}
bool checkTie(int **board, int boardSize) {
    Game game;
            int count = 0;
    for(int i = 0; i < boardSize; i++){

        for(int j = 0; j < boardSize; j++){
     
            if(board[i][j] != 0){
                count ++;
            }
             if(count >= (boardSize*boardSize)){
                return true;
            }

        }
    }
    return false;

}

void startGame() 
{
    Game game;
     srand (time(NULL));
    ofstream GomokuResults("gomokuResults.txt");
    int PlayerOneWins = 0;
    int PlayerTwoWins = 0;
    int indexForGameTurn = 0; // This is an index for each turn of the game it is number of how many games have been played
    while(true)
    {
       
        if(readFromFile()[indexForGameTurn] <= 0 || readFromFile()[indexForGameTurn] > 20){
            GomokuResults<<"wins alg1_"<<PlayerOneWins<<endl;
            GomokuResults<<"wins alg2_"<<PlayerTwoWins<<endl;
            break;
        }
        game.BOARD_SIZE = readFromFile()[indexForGameTurn];
        GomokuResults<<"size_"<<game.BOARD_SIZE<<"\n"; //Print the size before every game       
        game.createBoard(game.BOARD_SIZE);
        indexForGameTurn++; 

        
     
    while(true) {
    if(checkWin(game.board, game.alg_1, game.BOARD_SIZE)) {
            GomokuResults<<"win_alg1"<<"\n"<<endl;
            PlayerOneWins++; // Increase the number of wins for player one
            break;
        }
     if(checkWin(game.board, game.alg_2, game.BOARD_SIZE)) {
            GomokuResults<<"win_alg2"<<"\n"<<endl;
            PlayerTwoWins++; // Increase the number of wins for player one
            break;
        }
        if(checkTie(game.board, game.BOARD_SIZE)){
        break;
        };

        if(game.TURN == 0) {
                int x, y;
                  x = rand() % game.BOARD_SIZE;
                    y = rand() % game.BOARD_SIZE;
                while(game.getVal(game.board, y, x) != game.EMPTY_SPOT){
                    x = rand() % game.BOARD_SIZE;
                    y = rand() % game.BOARD_SIZE;
                }
            if(game.getVal(game.board, y, x) == game.EMPTY_SPOT){
                GomokuResults<<"r"<<y<<"c"<<x<<" alg1"<<endl;
                game.setMove(game.board, y, x, game.alg_1);
                game.TURN += 1;
               
            }
        }
        else  {
                int x, y;
                x = rand() % game.BOARD_SIZE;
                y = rand() % game.BOARD_SIZE;
                while(game.getVal(game.board, y, x) != game.EMPTY_SPOT){
                    x = rand() % game.BOARD_SIZE;
                    y = rand() % game.BOARD_SIZE;
                }
                if(game.getVal(game.board, y, x) == game.EMPTY_SPOT){
                    GomokuResults<<"r"<<y<<"c"<<x<<" alg2"<<endl;
                game.setMove(game.board, y, x, game.alg_2);
                game.TURN -=  1;
            }
        }      
        game.printBoard(game.board, game.BOARD_SIZE);
    }

}

}


int main() {
    startGame();
    cin.get();
    return  0;
}