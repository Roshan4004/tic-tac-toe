#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char sq[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9' };

int checkwin();
void board();
int user_creation();
int login();
int play_func();
int change();
int leaderboard();

COORD coord = { 0, 0 };

void gotoxy(int x, int y) {
    coord.X = x; coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct users{
    char name[40];
    char pass[40];
    int score;
};


// This is the main function. It asks if they want to see leaerboard or play the game and call functions acordingly.

int main()
{
    gotoxy(13, 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 TIC TAC TOE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    int what;
    printf("\n\t--ENTER 1 TO SEE LEADERBOARD, 2 TO PLAY GAME:  ");
    scanf("%d",&what);
    if (what ==1){
        leaderboard();
    }else{
        play_func();
    }

    printf("\t\tEnter to quit.");
    getch();

    return 0;
}

// Here is the table showing player score with highest scorer up and so on

int leaderboard(){
    int play;
    printf("\n\t\t  -----------LEADERBOARD------------\n\n");
    printf("\t\tS.N.\t\tNAME\t\tSCORE\n");
    struct users init_user;
    struct users all[30];
    FILE* user_init;
    user_init = fopen("user_db1.txt", "r");
    int how_many=1;
    while(fread(&init_user,sizeof(init_user),1,user_init)){
        all[how_many-1]=init_user;
        how_many+=1;
    }
    struct users for_sort;
    for(int k=0;k<how_many-1;k++){
        for (int l=0;l<how_many-1;l++){
            if(all[k].score>all[l].score){
                for_sort=all[k];
                all[k]=all[l];
                all[l]=for_sort;
            }
        }
    }
    for(int k=0;k<how_many-1;k++){
        printf("\t\t%d\t\t%s\t\t%d\n",k+1,all[k].name,all[k].score);
    }
    printf("\n\n\t\t--ENTER 1 TO PLAY, 2 TO QUIT.");
    scanf("%d",&play);
    if (play==1){
        sq[1]='1';sq[2]='2';sq[3]='3';sq[4]='4';sq[5]='5';sq[6]='6';sq[7]='7';sq[8]='8';sq[9]='9';
        play_func();
    }else{
        return 0;
    }
}
// This is the most important function. Here the interface is shown and they actually play game here.

int play_func(){
    int player = 1, i, choice,ask;
    char mark;
    do
    {
        board();
        if (player%2 !=0){
            player=1;
        }
        else{
            player=2;
        }
        printf("\t\t--Player %d, enter a number:  ", player);
        scanf("%d", &choice);

        mark = (player == 1) ? 'X' : 'O';

        if (choice == 1 && sq[1] == '1')
            sq[1] = mark;
            
        else if (choice == 2 && sq[2] == '2')
            sq[2] = mark;
            
        else if (choice == 3 && sq[3] == '3')
            sq[3] = mark;
            
        else if (choice == 4 && sq[4] == '4')
            sq[4] = mark;
            
        else if (choice == 5 && sq[5] == '5')
            sq[5] = mark;
            
        else if (choice == 6 && sq[6] == '6')
            sq[6] = mark;
            
        else if (choice == 7 && sq[7] == '7')
            sq[7] = mark;
            
        else if (choice == 8 && sq[8] == '8')
            sq[8] = mark;
            
        else if (choice == 9 && sq[9] == '9')
            sq[9] = mark;
            
        else
        {
            printf("\t\tInvalid move ");

            player--;
            getch();
        }
        i = checkwin();

        player++;
    }while (i ==  - 1);
    
    board();
    
    if (i == 1){
        printf("\t\t--\aPlayer %d win \n", --player);
        printf("\t\t--\aPlayer %d Enter '1' if you want to save else Enter '2' to quit.  ",player++);
        scanf("%d",&ask);
        if (ask == 1){
            printf("\t\t--\aEnter '1' if you want to login else Enter '2' to register:  ");
            scanf("%d",&ask);
            if(ask == 1){
                login();
            }else if(ask == 2){
                user_creation();
            }else{
                printf("\t\t--\aInvalid input.Click Enter to close the program.");
                getchar();
            }
        }else if(ask==2){
            return 0;
        }else{
            printf("\t\t--\aInvalid input. Click Enter to close the program.");
            return 0;
        }
        }

    else{
        printf("\t\t--\aGame draw");
    }
}

// If user wants to increase score to existing username, they need to provide credentials which is done in this function

int login(){
    int found=1;
    FILE* user_read;
    FILE* user_write;
    user_read = fopen("user_db1.txt", "r");
    user_write=fopen("user_db2.txt", "w");
    if (user_read == NULL) {
        fprintf(stderr, "\nError opened file\n");
        return 1;
    }
    char input_user[50],input_pass[50];
    printf("\t\t--Enter your username: ");
    scanf("%s",&input_user);
    printf("\t\t--Enter your password: ");
    scanf("%s",&input_pass);
    struct users temp_read;
    while(fread(&temp_read,sizeof(temp_read),1,user_read)){
        if(strcmp(input_user,temp_read.name)==0 && strcmp(input_pass,temp_read.pass)==0){
            printf("\t\tUser found....\n"); 
            printf("\t\tCurrent score is: %d\n",temp_read.score);
            printf("\t\tUpdating....\n");
            printf("\t\tEnter to Update\n");
            found =0;
            getch();
            temp_read.score+=1;
            fwrite(&temp_read, sizeof(temp_read), 1, user_write);
        }else{
            fwrite(&temp_read, sizeof(temp_read), 1, user_write);
        }
    }
    fclose (user_read);
    fclose (user_write);
    if(found ==0){
        change();
    }else{
        printf("\t\tUser not found....\n"); 
        printf("\t\tEnter to go to leaderboard and choose play or quit.\n\n");
        getch();
        leaderboard();
    }
}

// If user wins and wants to update their score, this function is called.

int change(){
    FILE* user_read1;
    FILE* user_write1;
    user_write1 = fopen("user_db1.txt", "w");
    user_read1=fopen("user_db2.txt", "r"); 
    struct users temp3;
    while(fread(&temp3,sizeof(temp3),1,user_read1)){
        fwrite(&temp3,sizeof(temp3),1,user_write1);
    }
    fclose(user_write1);
    fclose (user_read1);
    printf("\t\tUpdated\n");
    printf("\t\tThe updated leaderboard:\n\n");
    leaderboard();
    return 0;
}

// Here, the user registers by entering username and password. Then data is saved to a file.

int user_creation(){
    FILE* user_write;
    user_write = fopen("user_db1.txt", "a+");
    if (user_write == NULL) {
        fprintf(stderr, "\nError opened file\n");
        return 1;
    }
    
    struct users registering;
    printf("\t\t--Enter name: ");
    scanf("%s",registering.name);
    printf("\t\t--Enter password: ");
    scanf("%s",registering.pass);
    registering.score=1;
    int flagged=fwrite(&registering,sizeof(registering),1,user_write);
    if(flagged){
        printf("\t\t\aYour record is saved in database!!\n");
        printf("\t\t\aSave to username %s next time you win..\n",registering.name);
        fclose(user_write);
        printf("\t\tThe updated leaderboard:\n\n");
        leaderboard();
        return 0;
    }else{
        return 1;
    }
}

// This function is called everytime someone makes a move. It checks if anyone won.

int checkwin()
{
    if (sq[1] == sq[2] && sq[2] == sq[3])
        return 1;
        
    else if (sq[4] == sq[5] && sq[5] == sq[6])
        return 1;
        
    else if (sq[7] == sq[8] && sq[8] == sq[9])
        return 1;
        
    else if (sq[1] == sq[4] && sq[4] == sq[7])
        return 1;
        
    else if (sq[2] == sq[5] && sq[5] == sq[8])
        return 1;
        
    else if (sq[3] == sq[6] && sq[6] == sq[9])
        return 1;
        
    else if (sq[1] == sq[5] && sq[5] == sq[9])
        return 1;
        
    else if (sq[3] == sq[5] && sq[5] == sq[7])
        return 1;
        
    else if (sq[1] != '1' && sq[2] != '2' && sq[3] != '3' &&
        sq[4] != '4' && sq[5] != '5' && sq[6] != '6' && sq[7] 
        != '7' && sq[8] != '8' && sq[9] != '9')

        return 0;
    else
        return  - 1;
}


// The animated board is shown using this function. A table format is shown.


void board()
{
    system("cls");
    gotoxy(13, 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 TIC TAC TOE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");

    printf("\n\n\t\tPlayer 1 (X)  -  Player 2 (O)\n\n\n");


    printf("\t\t\t     |     |     \n");
    printf("\t\t\t  %c  |  %c  |  %c \n", sq[1], sq[2], sq[3]);

    printf("\t\t\t_____|_____|_____\n");
    printf("\t\t\t     |     |     \n");

    printf("\t\t\t  %c  |  %c  |  %c \n", sq[4], sq[5], sq[6]);

    printf("\t\t\t_____|_____|_____\n");
    printf("\t\t\t     |     |     \n");

    printf("\t\t\t  %c  |  %c  |  %c \n", sq[7], sq[8], sq[9]);

    printf("\t\t\t     |     |     \n\n");
}