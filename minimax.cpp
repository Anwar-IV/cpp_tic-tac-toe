#include <time.h>
#include <iostream>

using namespace std;

char board[3][3];
const char PLAYER = 'X';
const char AI = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
int minimax(int isMaximising);
void playerMove();
void computerMMove();
char returnWinner();
void computerMove();
void checkWinner(char *winner);
void printWinner(char);
int minimax(int isMaximising);

struct BestMove
{
    int i;
    int j;
};

int main()
{
    char winner = ' ';

    resetBoard();

    while (winner == ' ' && checkFreeSpaces() != 0)
    {
        computerMMove();
        printBoard();
        checkWinner(&winner);
        if (winner != ' ' || checkFreeSpaces() == 0)
            break;

        playerMove();
        checkWinner(&winner);
    }
    if (winner != ' ')
    {
        printWinner(winner);
    }
    else
    {
        cout << "It's a tie" << endl;
    }
}

void resetBoard()
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard()
{

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}
int checkFreeSpaces()
{
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
                freeSpaces--;
        }
    }
    return freeSpaces;
}
void playerMove()
{
    int rowNumber;
    int columnNumber;
    while (1)
    {
        cout << "Choose a row number: ( 1 , 2 , 3 )" << endl;
        cin >> rowNumber;
        cout << "Choose a column number: ( 1 , 2 , 3 )" << endl;
        cin >> columnNumber;

        if (rowNumber > 3 || rowNumber < 1 || columnNumber > 3 || columnNumber < 1)
        {
            cout << "\nPick a number between 1 and 3\n"
                 << endl;
            continue;
        }
        rowNumber--;
        columnNumber--;

        if (board[rowNumber][columnNumber] != ' ')
        {
            cout << "\nThat spot is already taken\n"
                 << endl;
            continue;
        }
        board[rowNumber][columnNumber] = PLAYER;
        break;
    }
}
void computerMove()
{
    srand(time(NULL));
    int column;
    int row;

    do
    {
        column = rand() % 3;
        row = rand() % 3;

        if (board[row][column] != ' ')
        {
            continue;
        }
        board[row][column] = AI;
        break;
    } while (board[row][column] != ' ');
}

void checkWinner(char *winner)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            // Horizontal
            if (board[j][0] != ' ' && board[j][0] == board[j][1] && board[j][1] == board[j][2])
            {
                *winner = board[j][0];
            }

            // Vertical
            else if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            {
                *winner = board[0][j];
            }

            // Diagonal
            else if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            {
                *winner = board[0][0];
            }
            else if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            {
                *winner = board[0][2];
            }
        }
    }
}

char returnWinner()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            // Horizontal
            if (board[j][0] != ' ' && board[j][0] == board[j][1] && board[j][1] == board[j][2])
            {
                return board[j][0];
            }

            // Vertical
            else if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            {
                return board[0][j];
            }

            // Diagonal
            else if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            {
                return board[0][0];
            }
            else if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[0][2])
            {
                return board[0][2];
            }
        }
    }

    return 'T';
}

void printWinner(char winner)
{
    cout << "And the winner is " << winner << endl;
}

void computerMMove()
{
    int bestscore = -1000;
    BestMove bestmove;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {

                board[i][j] = AI;
                int score = minimax(0);
                board[i][j] = ' ';
                if (score > bestscore)
                {
                    bestscore = score;
                    bestmove.i = i;
                    bestmove.j = j;
                }
            }
        }
    }
    board[bestmove.i][bestmove.j] = AI;
}

int minimax(int isMaximising)
{
    char winner = returnWinner();

    switch (winner)
    {
    case AI:
        return 1;
    case PLAYER:
        return -1;
    }
    if (checkFreeSpaces() == 0)
    {
        return 0;
    }

    if (isMaximising == 1)
    {
        int bestscore = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = AI;
                    int score = minimax(0);
                    board[i][j] = ' ';

                    if (score > bestscore)
                    {
                        bestscore = score;
                    }
                }
            }
        }
        return bestscore;
    }

    else
    {
        int bestscore = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = PLAYER;
                    int score = minimax(1);
                    board[i][j] = ' ';

                    if (score < bestscore)
                    {
                        bestscore = score;
                    }
                }
            }
        }
        return bestscore;
    }
}