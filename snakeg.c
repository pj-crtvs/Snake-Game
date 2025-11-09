#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ANSI-color-codes.h"

// functions to be called
void errorhandling(int a);
void mode();
void instructions();
void border(int a);
void food();
void blocks();
void randomcoor();
void head(int F);
void body(int F, int snake_x[], int snake_y[]);
void map(int F, int snake_x[], int snake_y[]);
void movement(int F, int snake_x[], int snake_y[]);
void gameover();
void win();
void playagain();
void exitgame();

// global variables
int i, j;
int snake_length = 0;
int score = 0;
char board[15][15];

int main()
{
    // resets all values and prints and takes value for menu
    snake_length = 0;
    score = 0;

    printf(BYEL "\nThe Snake Game\nChoose an option\n" COLOR_RESET BGRN "[1] Start\n" COLOR_RESET BBLU "[2] Instructions\n" COLOR_RESET BRED "[3] Exit\n" COLOR_RESET);

    int menu_opt;
    scanf("%d", &menu_opt);
    switch (menu_opt)
    {
    case 1:
        mode();
        break;
    case 2:
        instructions();
        break;
    case 3:
        exitgame();
        break;
    default:
        errorhandling(menu_opt);
        main();
        break;
    }
    return 0;
}

// takes the value as string and makes sure printing does not repeat infinitely when a wrong character/number is pressed
void errorhandling(int a)
{
    char option[100];
    fgets(option, 100, stdin);
    printf("\n\nNot an option. Try again.\n");
}

// prints the difficulty options and scans input for choice
void mode()
{
    printf(BYEL "\nMode\n" COLOR_RESET BBLU "[1] Easy\n" COLOR_RESET BRED "[2] Difficult\n" COLOR_RESET BGRN "[3] Back to Menu\n" COLOR_RESET);
    int diff_opt;
    scanf("%d", &diff_opt);
    switch (diff_opt)
    {
    case 1:
    case 2:
        border(diff_opt);
        break;
    case 3:
        main();
        break;
    default:
        errorhandling(diff_opt);
        mode();
        break;
    }
}

// prints instructions and takes input to return to menu
void instructions()
{
    printf(YELB "Instructions\n" reset);
    printf(BLUHB "\nNAVIGATION:" reset
                 "\nTo control the snake, press:\n"
                 "       - [W] to move UP         - [S] to move DOWN\n"
                 "       - [A] to move LEFT       - [D] to move RIGHT\n");
    printf(BLUHB "\n GAMEPLAY: " reset BGRN "\nYOU WIN" reset
                 " when your snake:"
                 "\n       1. Collect all the food [F] and the LAST TAIL element successfully exits through the portal [$].\n\n" BRED "YOU LOSE" reset
                 " when your snake hits:"
                 "\n       1. Its own body \n"
                 "       2. Borders [#] \n"
                 "       3. Blocks [B]\n");
    printf(BLUHB "\n TWO MODES: " reset BGRN "\n1. Easy Mode" reset
                 "\n     - [B] No blocks for this mode"
                 "\n     - [F] You will be asked to input how many food items to spawn (1 to 10)"
                 "\n     - Each food you consume will add +1 length to your snake and increase your score.\n" BRED "2. Difficult Mode" reset
                 "\n     - [B] You will be asked to input how many blocks to spawn (5 to 15)."
                 "\n     - [F] You will be asked to input how many food items to spawn (1 to 10)"
                 "\n     - Each food you consume will add +1 length to your snake and increase your score.\n\n");

    int instruct_opt;
    scanf("%d", &instruct_opt);

    switch (instruct_opt)
    {
    case 1:
        main();
        break;
    default:
        errorhandling(instruct_opt);
        instructions();
        break;
    }
}

// gives character values for the walls and the spaces
void border(int diff_opt)
{
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 30; j++)
        {
            if (i == 0 || i == 14 || j == 0 || j == 14)
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
    if (diff_opt == 1)
    {
        // separates input taking for easy mode and difficult mode
        food(); // easy mode
    }
    else
    {
        blocks(); // difficult mode
    }
}

// generates coordinates for the board
void randomcoor()
{
    i = rand() % 14;
    j = rand() % 14;
}

// takes input for the number of blocks
void blocks()
{
    printf("Input the number of blocks between 5-15: ");
    int B;
    scanf("%d", &B);
    srand(time(NULL));
    if (B >= 5 && B <= 15)
    {
        // checks if input is between 5-15
        for (int c = 0; c < B; c++)
        {
            // increments c to place blocks equal to input B
            do
            {
                // repeats random coordinate generating while the generated coordinates are not a space
                randomcoor();
            } while (board[i][j] != ' ');

            board[i][j] = 'B'; // sets B as value for the space generated coordinates
        }
        if (board[1][1] == 'B')
        {
            // removes B value at origin of head and generates another coordinate of space
            do
            {
                randomcoor();
            } while (board[i][j] != ' ');
            board[i][j] = 'B';
        }
        food();
    }
    else
    {
        errorhandling(B);
        blocks();
    }
}

void food()
{
    // takes input for the number of food just like in blocks
    printf("Input the number of food between 1-10: ");
    int F;
    scanf("%d", &F);
    srand(time(NULL));

    if (F >= 1 && F <= 10)
    {
        // checks if input is between 1-10
        for (int c = 0; c < F; c++)
        {
            // increments c to be equal to input F
            do
            {
                // repeats random generate of coordinates while coordinates are not equal to space
                randomcoor();
            }

            while (board[i][j] != ' ');
            board[i][j] = 'F'; // sets space value to F
        }

        if (board[1][1] == 'F')
        {
            // removes F value at origin of head and generates new space coordinate
            do
            {
                randomcoor();
            } while (board[i][j] != ' ');
        }

        head(F);
    }

    else
    {
        errorhandling(F);
        food();
    }
}

void head(int F)
{
    // assigns F as the size of array of snake
    F = F + 2;
    int snake_x[F];
    int snake_y[F];
    snake_x[0] = 1;
    snake_y[0] = 1;
    body(F, snake_x, snake_y);
}

void body(int F, int snake_x[], int snake_y[])
{
    // updates the body and head
    i = snake_x[0];
    j = snake_y[0]; // takes first element of array of the snake as the coordinates

    if (i == 1 && j == 1)
    {
        // inputs @ at the origin
        board[i][j] = '@';
    }
    else if (board[i][j] == 'F')
    {
        // if the head eats the food, @ coordinates is updated and snake_length and score is incremented
        board[i][j] = '@';
        snake_length++;
        score += 100;
    }
    else if (board[i][j] == '#' || board[i][j] == 'B' || board[i][j] == 'o')
    {
        // if head hits the walls, blocks, or body, game ends
        gameover();
    }
    else
    {
        // updates head coordinates
        board[i][j] = '@';
    }

    for (int c = 1; c <= snake_length; c++)
    {
        // increments c until it is equal to snake_length to print body
        i = snake_x[c];
        j = snake_y[c];
        board[i][j] = 'o';
        if (c == snake_length)
        { // if c is equal to snake_length, then following coordinates are printed as space to erase previous body
            i = snake_x[c + 1];
            j = snake_y[c + 1];
            board[i][j] = ' ';
        }
    }

    i = snake_x[0];
    j = snake_y[0]; // inputs updated coordinates of snake_x[0] and snake_y[0] into i and j
    if (i == 7 && j == 14)
    {
        // if snake_x[0] and snake_y[0] coordinates are equal to the portal $, body is lessened
        for (int c = 0; c < F - 1; c++)
        {
            // place index c into body array and shifts elements from F-1 to 0
            snake_x[c] = snake_x[c + 1];
            snake_y[c] = snake_y[c + 1];
        }

        // decrements size of array and snake_length
        F--;
        snake_length--;
    }

    /*updates coordinates of head and body,
    e.g., if F=3 (input food is 1 + 2)
    c = 3, snake_x[c-1] = snake_x[c-2]
    -> snake_x[2] = snake_x[1]
    */
    for (int c = F; c >= 2; c--)
    {
        snake_x[c - 1] = snake_x[c - 2];
        snake_y[c - 1] = snake_y[c - 2];
    }

    map(F, snake_x, snake_y);
}

void map(int F, int snake_x[], int snake_y[])
{
    if (F == snake_length + 2)
    { // changes board[7][14] value into $ when it is not equal to head or body
        if (board[7][14] != '@' || board[7][14] != 'o')
        {
            board[7][14] = '$';
        } // clears blocks in board
        for (i = 0; i < 15; i++)
        {
            for (j = 0; j < 15; j++)
            {
                if (board[i][j] == 'B')
                {
                    board[i][j] = ' ';
                }
            }
        }
    }

    // prints board with colors, red for walls and blocks, green for food, blue for body and yellow for portal
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (board[i][j] == '#' || board[i][j] == 'B')
            {
                printf(BRED " %c" COLOR_RESET, board[i][j]);
            }
            else if (board[i][j] == 'F')
            {
                printf(BGRN " %c" COLOR_RESET, board[i][j]);
            }
            else if (board[i][j] == '$')
            {
                printf(BGRN " %c" COLOR_RESET, board[i][j]);
            }
            else if (board[i][j] == '@' || board[i][j] == 'o')
            {
                printf(BYEL " %c" COLOR_RESET, board[i][j]);
            }
            else
            {
                printf(" %c", board[i][j]);
            }
        }
        printf("\n");
    }

    printf("Points: %d\n", score);
    printf("W/A/S/D to move or M to go back to Menu\n");
    int check = 0; // value checking for win status
    for (i = 1; i < 14; i++)
    { // checks only index of playing board
        for (j = 1; j < 14; j++)
        {
            char tempboard = board[i][j]; // places value of board coordinates into temporary variable
            if (board[i][j] != ' ')
            { // if coordinates have value other than space, then it is given character value of 1
                tempboard = '1';
            }
            else
            { // if coordinates have value of space, then it is given character value of 0
                tempboard = '0';
            } // variable check is updated by dividing ascii value of tempboard over the ascii value of 1 plus the value of check
            check = tempboard / 49 + check;
        }
    } // since 49/49 = 1, if check is equal to 0, then all ascii values of the clear board is 48, which means the board is clear
    if (check == 0)
    {
        win(); // proceeds to win statement
    }
    movement(F, snake_x, snake_y);
}

void movement(int F, int snake_x[], int snake_y[])
{
    // takes input for movement
    char move;
    scanf(" %c", &move);
    int n;
    i = snake_x[0];
    j = snake_y[0];
    board[i][j] = ' '; // clears previous position of head

    if (i == 7 && j == 13)
    {
        // sets to gameover if snake is in front of portal and user does not press d/D
        switch (move)
        {
        case 'W':
        case 'w':
        case 'A':
        case 'a':
        case 'S':
        case 's':
            gameover();
            break;
        case 'M':
        case 'm':
            main(); // returns to menu
            break;
        default:
            n = sizeof(move); // converts character into number for errorhandling
            errorhandling(n);
            break;
        }
    }
    else
    {
        // movement if snake_x[0] and snake_y[0] is not at portal
        switch (move)
        {
        // updates position based on movement
        case 'W':
        case 'w':
            snake_x[0]--;
            break;
        case 'A':
        case 'a':
            snake_y[0]--;
            break;
        case 'S':
        case 's':
            snake_x[0]++;
            break;
        case 'D':
        case 'd':
            snake_y[0]++;
            break;
        case 'M':
        case 'm':
            main(); // returns to menu
            break;
        default:
            n = sizeof(move); // converts character into number for errorhandling
            errorhandling(n);
            board[i][j] = '@';
            map(F, snake_x, snake_y);
            break;
        }
    }
    body(F, snake_x, snake_y);
}

void win()
{
    printf(BGRN "\nYou win!\n" COLOR_RESET);
    playagain();
}

void gameover()
{
    printf(BRED "\nGame over!\n" COLOR_RESET);
    playagain();
}

// prints and scans option to play again or not
void playagain()
{
    printf(BYEL "\nDo you want to play again?\n" reset BGRN "[1] Yes\n" reset BRED "[2] Exit\n" reset);

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        main();
        break;
    case 2:
        exitgame();
        break;
    default:
        errorhandling(a);
        playagain();
        break;
    }
}

void exitgame()
{
    printf(BRED "\nGame Terminated.\n" reset);
    exit(0);
}