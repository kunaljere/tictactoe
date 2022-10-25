#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h> 

/*
How to run the game (For Windows):
    Create a new folder and place tictactoe.cpp in it.
    Open the command prompt and navigate to the directory
    Type "g++ tictactoe.cpp" and hit enter, assuming you have g++ installed on Windows
    An executable file will appear
    Type .\a.exe and hit enter, then the game will start
*/

using namespace std;

class Board
{
    //initializes a 2D vector and row and column variables
    public:
        vector<vector<char>> board;
        int row, col;

    //Board constructor
    Board(const int dim)
    {   
        //Row and columns have equal dimensions
        row = dim;
        col = dim;

        //Resizes board according to dimension and fills board with spaces
        board.resize(row);
        for (int r = 0; r < row; r++)
        {
            board[r].resize(col);
            for (int c = 0; c < col; c++)
            {
                board[r][c] = ' ';
            }
        }
    }
    
    //Iterates through board to display contents with delimeters
    void Display()
    {
        for (int r = 0; r < row; r++)
        {
            //Puts a '|' delimeter after each column
            for (int c = 0; c < col; c++)
            {
                if (c < col-1)
                    cout << board[r][c] << '|';
                else
                    cout << board[r][c];
            }

            //Puts a '-' delimeter after each row
            if (r < row-1)
            {
                cout << endl;
                cout << string((row*2)-1, '-') << endl;
            }

        }
    }

    //Adds letter to board
    void AddToBoard(char letter, int r, int c)
    {
        board[r][c] = letter;
    }

    //Checks if the row or column number is out of range of the board
    bool isOutOfRange(int rowNum, int colNum)
    {
        if (rowNum > row || colNum > col || rowNum < 1|| colNum < 1)
            return true;
        return false;    
    }

    //Returns letter at specific position from the board for the Player class
    char getLetter(int r, int c)
    {
        return board[r][c];
    }

    //Returns letter at specific position from board for the main function
    char getPositionLetter(int r, int c)
    {
        //Subtracts one because the input from the main function will be 1-dimension
        int r2 = r - 1;
        int c2 = c - 1;
        return board[r2][c2];
    }

    //Returns a list corresponding to the row number
    vector<char> getRowList(int index)
    {
        return board[index];
    }

    //Checks if all the elements of a vector are all the same
    bool CheckVector(vector<char> lst)
    {
        for (int i = 0; i < lst.size(); i++)
        {
            //Will return false automatically if there is a space 
            //or if the first element doesn't match the rest of the elements
            if (lst[i] == ' ')
                return false;
            else if (lst[0] != lst[i])
                return false;
        }
        return true;
    }

};


class Player
{
    //initializes name and letter variables
    public:
        string name;
        char letter;

    //Player constructor with a name and letter that can't be changed
    Player(string n, const char l)
    {
        name = n;
        letter = l;
    }

    //Calls the function that adds a letter to the board
    void Move(Board &board, int r, int c)
    {
        //Subtracts one because the input from the main function will be 1-dimension
        int r2 = r - 1;
        int c2 = c - 1;
        board.AddToBoard(letter, r2, c2);
    }

    //Checks if a Player won
    string CheckWin(Board board)
    {
        //initializes vectors of diagonal letters going right and left
        vector<char> diagLeftLst;
        vector<char> diagRightLst;

        
        for (int r = 0; r < board.row; r++)
        {     
            //Gets a row and check if elements in that row are all the same     
            vector<char> rowLst = board.getRowList(r);
            if (board.CheckVector(rowLst) == true)
                return "Player " + name + " won in row " + to_string(r+1) + "!";
            
            //Gets a list of all elements in a column and checks if elements of 
            //list are all the same
            vector<char> colLst;
            for (int c = 0; c < board.col; c++)
            {
                colLst.push_back(board.getLetter(c, r)); 
            }
            if (board.CheckVector(colLst) == true)
                return "Player " + name + " won in column " + to_string(r+1) + "!";
            
            
            //Adds elements diagonally to respective lists
            diagLeftLst.push_back(board.getLetter(r, r));
            diagRightLst.push_back(board.getLetter(r, board.row-1-r));
           
        }

        //Checks if diagonal lists have all the same elements
        if (board.CheckVector(diagLeftLst) == true || board.CheckVector(diagRightLst) == true)
            return "Player " + name + " won diagonally!";

        //returns a new line if there are no winners
        return "\n";

    }


};


int main()
{
    char playAgain = 'y';

    //loop to restart game
    while (playAgain == 'y')
    {
        //Prompt to enter dimension of board
        int dimension;
        cout << endl << "Enter dimensions of the board (one number): ";
        cin >> dimension;

        cout << endl << endl;

        //Prompt to enter name of Player 1 to create Player 1 object
        string name1;
        cout << "Player 1, enter your name: ";
        cin >> name1;
        Player player1(name1, 'x');

        cout << endl << endl;

        //Prompt to enter name of Player 2 to create Player 2 object
        string name2;
        cout << "Player 2, enter your name: ";
        cin >> name2;
        Player player2(name2, 'o');

        cout << endl << endl;

        //Creates board object and displays it
        Board board(dimension);
        board.Display();

        cout << endl << endl;

        //Loops through turns depending on dimension of the board
        for (int turn = 0; turn < pow(dimension, 2); turn++)
        {
            int row, col;
            
            //Player 1's turn
            if (turn % 2 == 0)
            {
                //Prompt to enter row and col positions of move
                cout << "Player " << name1 << ", enter new row and column numbers for your move (1-" << dimension << "): ";
                cin >> row >> col;

                //Checks if row, col inputted are out of range of board and asks for input again until row, col are in range
                if (board.isOutOfRange(row, col) == true)
                {
                    while(board.isOutOfRange(row, col) == true)
                    {
                        cout << "Player " << name1 << ", your position is out of range, please re-enter your position (1-" << dimension << "): ";
                        cin.clear();
                        cin.ignore(10, '\n');
                        cin >> row >> col;
                    }
                    cout << endl;
                }
                
                cout << endl;

                //Checks if position of row, col in board is already filled and asks for input again until they fill in an empty slot
                if (board.getPositionLetter(row, col) != ' ')
                {
                    while (board.getPositionLetter(row, col) != ' ')
                    {
                        cout << "Player " << name1 << ", the position you have entered has already been filled. Please enter a new position: ";
                        cin.clear();
                        cin.ignore(10, '\n');
                        cin >> row >> col;
                    }
                    cout << endl;
                }

                cout << endl;

                //Moves letter of player onto the board and displays it
                player1.Move(board, row, col);
                board.Display();

                //Checks if player has won the game and breaks out of the loop if they have
                if (player1.CheckWin(board) == "\n")
                    cout << endl << endl;
                else
                { 
                    cout << endl << endl << player1.CheckWin(board) << endl << endl;
                    break;
                }
                

            }
            //Everything for Player1 is repeated for Player 2
            else if (turn % 2 != 0)
            {
                cout << "Player " << name2 << ", enter new row and column numbers for your move (1-" << dimension << "): ";
                cin >> row >> col;

                if (board.isOutOfRange(row, col) == true)
                {
                    while(board.isOutOfRange(row, col) == true)
                    {
                        cout << "Player " << name2 << ", your position is out of range, please re-enter your position (1-" << dimension << "): ";
                        cin.clear();
                        cin.ignore(10, '\n');
                        cin >> row >> col;
                    }
                    cout << endl;
                }

                cout << endl;

                if (board.getPositionLetter(row, col) != ' ')
                {
                    while (board.getPositionLetter(row, col) != ' ')
                    {
                        cout << "Player " << name2 << ", the position you have entered has already been filled. Please enter a new position: ";
                        cin.clear();
                        cin.ignore(10, '\n');
                        cin >> row >> col;
                    }
                    cout << endl;
                }
                
                cout << endl;

                player2.Move(board, row, col);          
                board.Display();

                if (player2.CheckWin(board) == "\n")
                    cout << endl << endl;
                else
                { 
                    cout << endl << endl << player2.CheckWin(board) << endl << endl;
                    break;
                }        
            }
        }


        //Checks if either player has won the game. If no one has won, it is a tie
        if (player1.CheckWin(board) == "\n" && player2.CheckWin(board) == "\n")
        {
            cout << "It is a tie!" << endl;
        }

        //Asks if players would like to play again
        cout << "Would you like to play again (y/n)? ";
        cin >> playAgain;

    }

    return 0;

}
