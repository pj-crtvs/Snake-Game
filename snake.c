#include <stdio.h>
int menu_option (int a);
int mode_option (int a);
void easy ();
void difficult ();
void instructions ();
void menu () {
    printf("\nThe Snake Game");
    printf("\nType 1 Start Game");
    printf("\nType 2 Instructions");
    printf("\nType 3 Exit Game");
    printf("\nOption: ");
}
void mode () {
    printf("\nChoose Mode");
    printf("\nType 1 Easy");
    printf("\nType 2 Difficult");
    printf("\nOption: ");
}
int main () {
    menu();
    int a;
    scanf("%d", &a);
    menu_option (a);
}
int menu_option (int a) {
    if (a==1) {
        mode();
        int b;
        scanf ("%d", &b);
        mode_option (b);
    } else if (a==2) {
        instructions();
    } else if (a==3) {
        printf("Exiting the game.");
        return 0;
    } else {
        printf("%d is not an option. Option: ", a);
        int b;
        scanf("%d", &b);
        return menu_option (b);
    }
}
int mode_option (int a){
    if (a==1){
        easy();
    } else if (a==2){
        difficult();
    } else {
        printf("%d is not an option. Option: ", a);
        int b;
        scanf("%d", &b);
        return mode_option (b);
    }
}
void easy () {
    printf("Easy Mode");
}
void difficult () {
    printf("Difficulty Mode");
}
void instructions () {
    printf("\nPress W to go up, A to go left, S to go down, and D to go right.");
    printf("\nType 1 to return to menu: ");
    int a;
    scanf("%d", &a);
    if (a==1) {
        main();
    } else {
        printf("%d is not an option.\n", a);
        return instructions();
    }
}