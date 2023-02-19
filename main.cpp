#include <iostream>
#include <array>
#include <stdio.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

string difficulty_level[] = {"easy", "medium", "hard"};

bool iequals(const string &a, const string &b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b)
                      {
                          return tolower(a) == tolower(b);
                      });
}

struct BestMove
{
    int i, j;
};

class Tic_Tac_Toe
{

private:
    array<array<char, 3>, 3> board;
    const static char AI = 'X';
    const static char PLAYER = 'O';
    string level;

    void reset_board()
    {
        for (array<char, 3> &b : board)
        {
            for (char &move : b)
            {
                move = ' ';
            }
        }
    }
    void print_board()
    {
        printf("\n");
        printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
        printf("---|---|---\n");
        printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
        printf("---|---|---\n");
        printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    }

    int check_free_spaces()
    {
        int freeSpaces = 9;
        for (array<char, 3> &b : board)
        {
            for (char move : b)
            {
                if (move != ' ')
                    freeSpaces--;
            }
        }
        return freeSpaces;
    }

    char check_winner()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {

                // Horizontal
                if (board[j][0] != ' ' && board[j][0] == board[j][1] && board[j][1] == board[j][2])
                    return board[j][0];

                // Vertical
                else if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
                    return board[0][j];

                // Diagonal
                else if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
                    return board[0][0];
                else if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
                    return board[0][2];
            }
        }
        return 'T';
    }

    void player_move()
    {
        int rowNumber;
        int columnNumber;
        while (1)
        {
            cout << "\nChoose a row number: ( 1 , 2 , 3 )" << endl;
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

    void computer_move()
    {
        srand(time(NULL));
        int column;
        int row;
        do
        {
            column = rand() % 3;
            row = rand() % 3;

            if (board[row][column] != ' ')
                continue;

            board[row][column] = AI;
            break;
        } while (board[row][column] != ' ');
    }

    int minimax(int isMaximising)
    {
        char winner = check_winner();
        switch (winner)
        {
        case AI:
            return 1;
        case PLAYER:
            return -1;
        }
        if (check_free_spaces() == 0)
            return 0;

        if (isMaximising)
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
                            bestscore = score;
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
                            bestscore = score;
                    }
                }
            }
            return bestscore;
        }
    }

    void minimax_move()
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
    void starting_rounds()
    {
        // Medium Level - Randomize starting position
        if (level == difficulty_level[1])
        {
            computer_move();
            print_board();
            player_move();
        }
        // Hard level
        if (level == difficulty_level[2])
        {
            board[0][0] = AI;
            print_board();
            player_move();
            if (board[2][2] == ' ')
                board[2][2] = AI;
            else
                board[2][0] = AI;
            print_board();
            player_move();
        }
    }

public:
    Tic_Tac_Toe(string level) : board{}, level{level} {}

    void start_game()
    {
        reset_board();
        starting_rounds();
        // Main Game Loop
        while (check_free_spaces() != 0 || check_winner() != 'T')
        {
            if (level == difficulty_level[0])
                computer_move();
            else
                minimax_move();
            if (check_free_spaces() == 0 || check_winner() != 'T')
                break;
            print_board();
            player_move();
            if (check_free_spaces() == 0 || check_winner() != 'T')
                break;
        }
        // Handling Winner / Loser
        print_board();
        if (check_winner() == PLAYER)
            printf("\033[32m\nCongratulations!!! You Won!\n");
        else if (check_winner() == AI)
            printf("\033[31m\nSorry You Lost!!!\n");
        else
            printf("\033[34m\nIts a Tie!!!\n");

        // Checking if user wants to play again
        string play_again;
        printf("\033[36m\nWant to Play Again??? ");
        cin >> play_again;
        printf("\033[0m");
        if (iequals(play_again, "yes"))
            start_game();
        else
            printf("\033[1;32m\nThanks for playing!!!\n\n");
        exit(0);
    }
};

int main(int argc, char *argv[])
{
    bool match = false;
    string lower_cased = "";

    // Check argc is exactly 2
    if (argc != 2)
    {
        printf("Please enter a difficulty level ( easy | medium | hard )\n\t e.g ./main easy\n");
        exit(1);
    }

    for (const auto &i : difficulty_level)
    {
        if (iequals(i, argv[1]))
            match = true;
    }

    if (!match)
    {
        printf("Please enter one of the following difficulty levels ( easy | medium | hard )\n\t e.g ./main easy\n");
        exit(1);
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        lower_cased += tolower(argv[1][i]);
    }

    Tic_Tac_Toe game(lower_cased);
    game.start_game();
}