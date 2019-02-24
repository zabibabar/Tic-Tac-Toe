#include <stdio.h>
#define N 3
//Declaring global variables and methods
char board[N*N];
int player = 1;
void PrintBoard();
int checkForWinner();
void playGame();

int main ()
{
    char replay;
    //loops until user doesn't want to replay the game
    do  {   
        for (int i = 0; i < N*N; i++)
        {
            *(board+i) = ' ';
        }
        PrintBoard();
        playGame();
        //Checks for the result of the game
        if (checkForWinner() == 1)
            printf("\n**** Player %d wins! ****\n", --player);
        else
            printf("\n**** The game has ended in a draw ****\n");


        printf("\nWould you like to play again? (y/n): ");
        scanf(" %c", &replay);  
        
        if (replay == 'n')
            printf("**** Thank you for playing Tic-Tac-Toe! ****\n");
        //Reset the values to blank space
        for (int i = 0; i < (N*N); i++)
        { 
            *(board + i) = ' ';
        }

    }   while (replay == 'y');  

return 0;
}
//prints the board
void PrintBoard()
{
    printf("\n Tic-Tac-Toe \n");

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf(" %c ", *(board+ i*N+j));
            if (j < N-1) printf("|");
        }
        if (i < N-1)
        {   
            printf("\n");
            for(int a = 0; a < N; a++)
            {
                printf("---");
                if (a < N-1) printf("+");
            }
        }
        printf("\n");
    }
}

int checkForWinner()
{ 
    //check if rows have the same mark
    int count = 0;
        for (int i = 0; i < N*N; i = i+N)
        {
            for (int j = i+1; j <i+N ; j++)
            {
                if (*(board+i) != *(board+j))
                    break;
                if (*(board+i) == *(board+j) && *(board+i) != ' ')
                    count++;
            }
            if (count == N-1)
                return 1;
            else
                count = 0;
        }
        //check if column has the same mark
        for (int i = 0; i < N; i++)
        {
            for (int j = i+N; j < N*N; j = j+N)
            {   
                if (*(board+i) != *(board+j))
                    break;
                if (*(board+i) == *(board+j) && *(board+i) != ' ')
                    count++;
            }
            if (count == N-1)
                return 1;
            else
                count = 0;
        }
        //checks the diagnols
        for (int i = 0; i < N; i++)
        {
            if (i == 0)
            {
                for (int j = N+1; j < N*N; j = j+N+1)
                {
                    if (*board == *(board+j) && *board != ' ')
                    count++;
                }
            if (count == N-1)
                return 1;
            else
                count = 0;
                      
            }       

            if (i == N-1)
            {
                for (int j = 2*N-2; j < N*N; j = j+N-1)
                {
                    if (*(board+i) == *(board+j) && *(board+i) != ' ')
                        count++;
                }
                if (count == N-1)
                    return 1;
                else 
                    count = 0;
            }        
        }     
    return 0;
}

void playGame()
{
    int row, col, choice, i, moves = 0;
    char mark;
    //loops until a decisive result is reached
    do  {
        player = (player % 2) ? 1 : 2;
        printf("Current move: Player %d\n\n", player);
        do
        {
            printf("Enter row: ");
            scanf("%d", &row);
            if (row >N-1)
                printf("Invalid move\n\n");
        } while (row > N-1);
        do  {
            printf("Enter column: ");
            scanf("%d", &col);
            if (col >N-1)
                printf("Invalid move\n\n");         
        } while (col >N-1);
        
        choice = N*row + col;

        for (int i = 0; i < N*N; i++)
        {
            mark = (player == 1) ? 'X' : 'O';

            if (i == choice && *(board + i) == ' ')
                *(board+i) = mark;
            else if (i == choice && *(board + i) != ' ')
            {
                printf("invalid move\n");
                player --;
            }
        }
        PrintBoard();
        i = checkForWinner();
        player ++;
        moves++;
        printf("%d\n", moves);
        if (moves == N*N)
            break;
    
    }   while (i == 0);
}