#include <iostream>
using namespace std;

class Game {
    // Constants
    public:
        int alg_1 = 1;
        int alg_2 = 2;
        int EMPTY_SPOT = 0;
        
    // Variables
    public:
        int BOARD_SIZE;
        int TURN = 0;
        int **board = new int*[BOARD_SIZE];
        int ** createBoard(int rows) 
        {
            for(int i = 0; i < rows; ++i) {
            board[i] = new int[rows]; 
        }
         for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            board[i][j] = 0;
        }
    }    
        return board;

}       
    private:
    // Functions
    public:
    // [TODO] Remove the code below this line
    // This print the board ONLY FOR TESTING
       void printBoard(int **board, int board_size){
            for(int rowIndex = 0; rowIndex < board_size; rowIndex++) {
            for(int columnIndex = 0; columnIndex < board_size; columnIndex++) {
            cout<<board[rowIndex][columnIndex]<< " ";
        }
        cout<<endl;
    }
    cout<<endl;
        };
    // [TODO] Remove the code above this line

    // Set the move in the board
    void setMove(int **_board,int row, int col, int playerValue) {
           if(col < BOARD_SIZE && row < BOARD_SIZE) {
             _board[col][row] = playerValue;
        }
    }
    // Get value of the board;
    int getVal(int **_board, int row, int col){
        if(col < BOARD_SIZE && row < BOARD_SIZE) {
            return _board[col][row];
        }
        return 0;
	}
  
};

