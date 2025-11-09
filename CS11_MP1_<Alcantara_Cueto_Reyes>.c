#include "ANSI-color-codes.h" // for coloring
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// other functions to be called
void game_menu();
void game_level();
void game_easy();
void game_difficult();
void game_start(int food_num, int block_num);
void game_board(int food_num, int block_num);
void game_field();
void move_snake(char move);
void game_instructions();
void game_outcome();
void game_end();
void errorhandling(int a);

// global variables
int i, j, game_over, food_num, block_num, snake_length, game_score, total_food, food_eaten, game_result, exit_phase = 0;
int board_height = 15;
int board_width = 15;
char board[15][15];
int portal_x = 14;
int portal_y = 7;
int snake_x[15 * 15];
int snake_y[15 * 15];

int main()
{
    srand(time(NULL));
    game_menu();
    return 0;
}

// ensures there is no infinite printing when input is not one of the choices
void errorhandling(int a)
{
    char option[100];
    fgets(option, 100, stdin);
    printf("\nNot an option. Try again.\n");
}

// displays and takes input for menu
void game_menu()
{
    int menu_opt;

    do
    {
        printf(YELB "\n The Snake Game:" reset);
        printf(BYEL "\nChoose an option:\n" reset UGRN "(1) Start Game\n" reset UBLU "(2) Instructions\n" reset URED "(3) Exit\n" reset);
        scanf("%d", &menu_opt);
        switch (menu_opt)
        {
        case 1:
            game_level();
            break;
        case 2:
            game_instructions();
            break;
        case 3:
            game_end();
            break;
        default:
            errorhandling(menu_opt);
            break;
        }
    } while (menu_opt >= 1 && menu_opt <= 3); // input 1 to 3 only
}

// displays and takes input for difficulty level
void game_level()
{
    exit_phase = 0;
    int difficulty_opt;
    do
    {
        printf(BYEL "\nSelect the difficulty:" reset UGRN "\n(1) Easy" reset URED "\n(2) Difficult" reset UBLU "\n(3) Back to Menu\n" reset);
        scanf("%d", &difficulty_opt);
        switch (difficulty_opt)
        {
        case 1:
            game_easy();
            break;
        case 2:
            game_difficult();
            break;
        case 3:
            game_menu();
            break;
        default:
            errorhandling(difficulty_opt);
            break;
        }
    } while (difficulty_opt != 1 && difficulty_opt != 2 && difficulty_opt != 3);
}

// take input for food in easy mode
void game_easy()
{
    printf(BGRN "\nEasy Mode\n" reset);
    block_num = 0;
    do
    {
        printf("Input the number of food/s (1-10): ");
        scanf("%d", &food_num);
        errorhandling(food_num);
    } while (food_num < 1 || food_num > 10);
    printf("\n");
    game_start(food_num, block_num);
}

// take input for food and blocks in difficult mode
void game_difficult()
{
    printf(BRED "\nDifficult Mode\n" reset);
    do
    {
        printf("Input the number of blocks (5-15): ");
        scanf("%d", &block_num);
        errorhandling(block_num);
    } while (block_num < 5 || block_num > 15);

    do
    {
        printf("Input the number of food/s (1-10): ");
        scanf("%d", &food_num);
        errorhandling(food_num);
    } while (food_num < 1 || food_num > 10);

    printf("\n");
    game_start(food_num, block_num);
}

void game_start(int food_num, int block_num)
{
    game_board(food_num, block_num);
    char move;
    // if hindi pa nag-eend yung game na nakabase sa move_snake func, continue lang yung pag-input
    while (!game_over)
    {
        game_field();
        printf("Enter a move (W/A/S/D) or 'M' to Return to Menu:\n");
        scanf(" %c", &move);
        printf("\n");
        move_snake(move);
    }
    game_field();   // print the game itself
    game_outcome(); // outcome ng game pag nagtapos
}

// set the values for the board
void game_board(int food_num, int block_num)
{
    // initial position ang index 1,1
    snake_x[0] = 1;
    snake_y[0] = 1;
    // initial values
    game_over = 0;
    snake_length = 1;
    game_score = 0;
    total_food = food_num;
    food_eaten = 0;
    game_score = 0;
    // index 0 and 14 are blocks of both columns and rows
    for (i = 0; i < board_height; i++)
    {
        for (j = 0; j < board_width; j++)
        {
            if (i == 0 || i == board_height - 1 || j == 0 || j == board_width - 1)
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
    // Random placement of food/s from index 1 to 13
    for (i = 0; i < food_num; i++)
    {
        int r, c;
        do
        {
            r = rand() % (board_height - 2) + 1;
            c = rand() % (board_width - 2) + 1;
        } while (board[r][c] != ' ');
        board[r][c] = 'F';
    }
    // Random placement of blocks from index 1 to 13
    for (i = 0; i < block_num; i++)
    {
        int r, c;
        do
        {
            r = rand() % (board_height - 2) + 1;
            c = rand() % (board_width - 2) + 1;
        } while (board[r][c] != ' ');
        board[r][c] = 'B';
    }
    // Dont put food/block in index 1,1 since it's the initial place of snake
    if (board[1][1] == 'B' || board[1][1] == 'F')
    {
        board[1][1] = ' ';
        int r, c;
        do
        {
            r = rand() % (board_height - 2) + 1;
            c = rand() % (board_width - 2) + 1;
        } while (board[r][c] != ' ');
    }
}

void game_field()
{
    char tempboard[board_height][board_width];
    for (i = 0; i < board_height; i++)
    { // rows
        for (j = 0; j < board_width; j++)
        { // columns
            tempboard[i][j] = board[i][j];
        }
    }
    // 1 to 13 lang ang game field ng snake
    // index 1 yung body ng snake
    for (i = 1; i < snake_length; i++)
    {
        if (snake_x[i] > 0 && snake_x[i] < board_height - 1 && snake_y[i] > 0 && snake_y[i] < board_width - 1)
        {
            tempboard[snake_x[i]][snake_y[i]] = 'o';
        }
    }
    // index 0 yung head ng snake
    if (snake_x[0] > 0 && snake_x[0] < board_height - 1 && snake_y[0] > 0 && snake_y[0] < board_width - 1)
    {
        tempboard[snake_x[0]][snake_y[0]] = '@';
    }

    // printing the whole board and components niya w color
    for (i = 0; i < board_height; i++)
    {
        for (int j = 0; j < board_width; j++)
        {
            if (tempboard[i][j] == '#' || tempboard[i][j] == 'B')
            {
                printf(BRED " %c" COLOR_RESET, tempboard[i][j]);
            }
            else if (tempboard[i][j] == '@' || tempboard[i][j] == 'o')
            {
                printf(BYEL " %c" COLOR_RESET, tempboard[i][j]);
            }
            else if (tempboard[i][j] == '$' || tempboard[i][j] == 'F')
            {
                printf(BGRN " %c" COLOR_RESET, tempboard[i][j]);
            }
            else
            {
                printf(" %c", tempboard[i][j]);
            }
        }
        printf("\n");
    }
    // for scoring and food eaten count
    printf("Score: %d\n", game_score);
    printf("Food Eaten: %d / %d\n", food_eaten, total_food);
}

void move_snake(char move)
{ // movement and conditions of collisions
    // for the body to follow the last index of head
    for (int i = snake_length - 1; i > 0; i--)
    {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }
    /*
    Para sa movements of snake:
    W - subtract 1 index to go up
    S - add 1 index to go down
    A - subtract 1 index to go left
    D - add 1 index to go right
    */
    switch (move)
    {
    case 'w':
    case 'W':
        snake_x[0]--;
        break;
    case 's':
    case 'S':
        snake_x[0]++;
        break;
    case 'a':
    case 'A':
        snake_y[0]--;
        break;
    case 'd':
    case 'D':
        snake_y[0]++;
        break;
    case 'm':
    case 'M':
        main();
        break;
    default:
        errorhandling(move);
        break;
    }
    // if head collided with the body
    for (int i = 1; i < snake_length; i++)
    {
        if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
        {
            game_over = 1;
            return;
        }
    }
    char head_collision = board[snake_x[0]][snake_y[0]];
    // Winning time after the snake eaten all the foods
    if (food_eaten == total_food && head_collision == '$')
    {
        exit_phase = 1;
    }

    if (exit_phase == 1)
    {
        if (snake_x[snake_length - 1] == portal_y && snake_y[snake_length - 1] == portal_x)
        { // last tail dapat para manalo
            game_over = 2;
            // remove the parts of snake na nasa portal na
            for (i = 0; i < snake_length; i++)
            {
                snake_x[i - 1] = -1;
                snake_y[i - 1] = -1;
            }
            return;
        }
        return;
    }

    // if na-kain yung food
    if (head_collision == 'F')
    {
        game_score += 100;
        snake_length++;
        food_eaten++;
        board[snake_x[0]][snake_y[0]] = ' ';
        if (food_eaten == total_food)
        { // if nakain na lahat ng food
            for (int i = 0; i < board_height; i++)
            {
                for (int j = 0; j < board_width; j++)
                {
                    if (board[i][j] == 'B')
                    {
                        board[i][j] = ' '; // clear the board
                    }
                }
            }
            board[portal_y][portal_x] = '$'; // replace index 14,7 with the portal
        }
    }

    // if nagcollide sa fence or blocks
    if ((head_collision == '#' || head_collision == 'B') && head_collision != '$')
    {
        game_over = 1;
        return;
    }
}

void game_instructions()
{
    int instruc_opt;
    do
    {
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

        printf(UYEL "Press (1) to go back to Menu\n" reset URED "Press (2) to Exit\n" reset);
        scanf("%d", &instruc_opt);
        switch (instruc_opt)
        {
        case 1:
            game_menu();
            break;
        case 2:
            game_end();
            break;
        default:
            errorhandling(instruc_opt);
            game_instructions();
            break;
        }
    } while (instruc_opt != 1 && instruc_opt != 2); // while the input is not 1 or 2, repeat the instructions funtion
}

void game_outcome()
{
    int end_opt;
    if (game_over == 1)
    {
        printf(BHRED "\nGame over!\n" reset);
        printf(BYEL "\nDo you want to play again?\n" reset UGRN "(1) Yes (Return to menu) \n" reset URED "(2) No (Exit game)\n" reset);
    }
    else if (game_over == 2)
    {
        printf(BHGRN "\nYou win!\n" reset);
        printf(BYEL "\nDo you want to play again?\n" reset UGRN "(1) Yes (Return to menu) \n" reset URED "(2) No (Exit game)\n" reset);
    }
    do
    {
        scanf("%d", &end_opt);
        switch (end_opt)
        {
        case 1:
            game_menu();
            break;
        case 2:
            game_end();
            break;
        default:
            errorhandling(end_opt);
            game_outcome();
            break;
        }
    } while (end_opt != 1 && end_opt != 2); // while the input is not 1 or 2, repeat the 'play again?'
}

void game_end()
{
    printf(BRED "\nGame Terminated.\n" reset);
    exit(0); // terminate the game
}