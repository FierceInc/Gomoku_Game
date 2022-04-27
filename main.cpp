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
bool checkWin(int board[][100], int playerPiece, int boardSize) 
{
     int spaces = boardSize % 5; /* This gets the empty spaces eg in a 6X6 board we only need 1 empty space out of 6 to get 5 in a row so here if board size = 6 you get one if its 7 you get 2 if its 10 you get 0; You just need the remainder in each case*/

    for(int c =  0; c < boardSize - spaces; c++) // Here you subtract the extra spaces you dont need
    {   
        for (int r = 0; r < boardSize; r++)
        {

            // HORIZONTAL CHECK
           if(board[r][c] == playerPiece && board[r][c + 1] == playerPiece && board[r][c + 2] == playerPiece && board[r][c + 3] == playerPiece && board[r][c + 4] == playerPiece)
           {
               return true;
           }
            // This is self explaining. You in are going down with rows
            //VERTICAL CHECK
           if(board[r][c] == playerPiece && board[r + 1][c] == playerPiece && board[r + 2][c] == playerPiece && board[r + 3][c] == playerPiece && board[r+ 4][c] == playerPiece)
           {
               return true;
           }
        }
    }
// NOW YOU CHECK THE TWO DIAGONALS
// For POSITIVE DIAGONAL when rows increase columns increase this is what I've done here
    for(int c =  0; c < boardSize - spaces ; c++)
     {
         for (int r = 0; r < boardSize - spaces; r++) // This line is the difference from HORIZONTAL AND VERTICAL
        {
            // When row increases column increase;
            if(board[r][c] == playerPiece && board[r + 1][c + 1] == playerPiece && board[r + 2][c + 2] == playerPiece && board[r + 3][c + 3] == playerPiece && board[r + 4][c + 4] == playerPiece)
            {
                return true;
            }
        }
    }
    //NEGATIVE DIAGONAL
    for(int c =  0; c < boardSize - spaces ; c++) 
    {
        for (int r = spaces; r < boardSize; r++) // When row is equal to the extra spaces. if Column is 0 row is 1
        {

            //VISE VERSA
            if(board[r][c] == playerPiece && board[r - 1][c + 1] == playerPiece && board[r - 2][c + 2] == playerPiece && board[r - 3][c + 3] == playerPiece && board[r - 4][c + 4] == playerPiece)
            {
                return true;
            }
        }
    }
    return false; // This whole function returns false if none of the 4 conditions are met;
}

// The function below this line doesnt work 
void checkTie(int _board[][100], void (*_startGame)(), int boardSize){
    Game game;
    int count = 0;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(_board[i][j] != 0) {
                count++;
            }
            else if(_board[i][j] == 0){
                count = count;
            }
        if(count >= (boardSize * boardSize)) {
                    count = 0;

                    _startGame();
            }
            
        }
    }
}
// The function above this line doesnt work 

// This start the game and executes every thing;
void startGame()
{
    Game game; //This is an object of the game class;

    ofstream Results("gomokuResults.txt"); // Here I create the output file named gomokuResults.txt;

    srand(time(0)); /* This sets the seed for the random numbers generated -- 
    This is so we don't get any patterns in the numbers generated */

// Here Im keeping track of the scores for both players;
    int PlayerOneWins = 0;
    int PlayerTwoWins = 0;
    bool  Winner = false;
    int indexForGameTurn = 0; // This is an index for each turn of the game it is number of how many games have been played
    while(true)
    {
    /* Here we are checking if the size we get from the file is now less or equal 5  because numbers less than 6 will return a memory 
    error in our validation functions*/
       
      if(readFromFile()[indexForGameTurn] > 5) 
      {
          game.BOARD_SIZE = readFromFile()[indexForGameTurn]; // Dynamically set the size of the board to the size in the Input.txt file;
          Results<<"size_"<<game.BOARD_SIZE<<"\n"; //Print the size before every game
        indexForGameTurn++; // Increase the number of the games played in each turn
      }
      //  This is if the size goes under the minimum board size which is 6; then we exit the loop;
      else 
      {
          Results<<"wins alg1_"<<PlayerOneWins<<"\n"; // print the wins summary in the Results file in a new line.
          Results<<"wins alg2_"<<PlayerTwoWins<<"\n"; // print the wins summary in the Results file in a new line.
          break;
      }
  
    int board[100][100] = {0}; // Initialize the board for each game; Setting it back to empty 
//   Now this is the playing process.
      while(true)
      {
          if(checkWin(board, game.alg_1, game.BOARD_SIZE)) 
          {
                Winner = true;
                PlayerOneWins++; // Increase the number of wins for player one
                cout<<"win_alg1"<<endl; //DELETE THIS LINE AFTER TESTING ********;
                Results<<"win_alg1"<<"\n\n"; //Print the result if alg2 wins

                break; //Game over we exit the loop and start a new game;
          }
          else if(checkWin(board, game.alg_2, game.BOARD_SIZE)) 
          {  
                Winner = true; 
                PlayerTwoWins++;  // Increase the number of wins for player two
                cout<<"win_alg2"<<endl; //DELET THIS LINE
                Results<<"win_alg2"<<"\n\n"; //Print the result if alg2 wins
                
                break;  //Game over we exit the loop and start a new game;
          }
          else 
          {
             checkTie(board, startGame, game.BOARD_SIZE); // Call the check tie function
          }

          if (game.TURN == 0) //First Turn;
          {
              int x, y;
            /* Change the values of X and Y to [cin>>x] and [cin>>y] FOR DEBUGING AND TESTING*/
                x = rand() % game.BOARD_SIZE; //Genarate a random row
    		    y = rand() % game.BOARD_SIZE; //Genarate a random column

              while(game.getVal(board, x, y) != game.EMPTY_SPOT) //This is to make sure the same spot is not played twice I think it saves time I might be    wrong
              {

                  x = rand() % game.BOARD_SIZE; //Genarate a random row
    		        y = rand() % game.BOARD_SIZE; //Genarate a random column

              }

              if (game.getVal(board, x, y)== game.EMPTY_SPOT) 
              {
                cout<<"r"<<y << "c"<<x<<"      alg"<< game.alg_1<< endl; //DELETE THIS TOO

                Results<<"r"<<y<<"c"<<x<<" alg"<< game.alg_1<<"\n"; // Print the move for player one in the results file
    		    game.setMove(board,x, y, game.alg_1); // Set the move in the board

                  game.TURN += 1; //Increase Turn Buy One; Here Turn Is Going To Be One
    		    }
              else 
              {
                  game.TURN = game.TURN; // This is here incase for any reason the algo plays an invalid spot we make it play again
              }
    		}

      else
      {
          int x, y;

    		x = rand() % game.BOARD_SIZE;
    		y = rand() % game.BOARD_SIZE;

          while(game.getVal(board, x, y) != game.EMPTY_SPOT) //This is to make sure the same spot is not played twice I think it saves time I might be wrong
          {
            x = rand() % game.BOARD_SIZE;
    		y = rand() % game.BOARD_SIZE;
          }
         if (game.getVal(board, x, y) == game.EMPTY_SPOT) 
         {
            cout<<"r"<<y << "c"<< x <<"        alg"<< game.alg_2<< endl; //DELETE LINE

            Results<<"r"<<y<<"c"<<x<<" alg"<< game.alg_2<<"\n";  // Print the move for player one in the results file

    		game.setMove(board,x, y, game.alg_2); // Set the move in the board

            game.TURN -= 1; // Decrement the turn 
    	}
        else 
        {
            game.TURN = game.TURN; // Dont change turn if move is invalid
        }
      } 

         game.printBoard(board, game.BOARD_SIZE); //DELETE LINE
      }

    }
    Results.close(); // Close the file after the games are done;
    _Exit(10);
}
 




int main() {
    startGame();
    cin.get();
}