#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int plateau[2][6];
int g1r;
int g2r;
int lastCaseJ1;
int lastCaseJ2;


void init()
{

    for(int i =0 ; i<2; i++){
        for (int j=0;j<6; j++){
            //printf("4");
            plateau[i][j] = 4 ;
            //printf("Vu tableau");
            printf("| %i |",plateau[i][j]);
        }
    printf(" Gr \n");
    }

}

void afficheTab(){
    for(int i = 0 ;i<2; i++){
        for (int j =0 ; j<6; j++){
            printf("| %i |",plateau[i][j]);
        }
        printf(" GR \n");
    }

}

int j1coup(){
    int choice;
    printf("Joueur 1 veuillez choisir votre case de d%cpart svp \n",130);
    printf("choisissez une case entre 0 et 5 || Utiliser le nombre 256 pour retourner au menu\n");
    scanf("%d",&choice);
    if (choice==256){
        menu();
    }
    int nbBille = plateau[0][choice];
    plateau[0][choice] = 0;
    choice--;
    for (int i = nbBille;i>0;i--){
        plateau[0][choice] ++;
        choice--;
        nbBille--;
        if (choice == 0 && nbBille>1){
            plateau[1][choice]++;
            choice++;
        }
    lastCaseJ1 = i;
    }
    afficheTab();
    return plateau;
}

bool affamerJ1(){
    bool affamer;
    for(int i =0 ; i>6 ;i++){
        if(plateau[1][i]==2||plateau[1][i]==3){
            affamer = true;
        }else{
            affamer = false;
            return affamer;
        }
    }
    return affamer;
}

bool affamerJ2(){

    bool affamer;
    for(int i =0 ; i>6 ;i++){
        if(plateau[0][i]==2||plateau[0][i]==3){
            affamer = true;
        }else{
            affamer = false;
            return affamer;
        }
    }
    return affamer;
}

int ramassage();

int j2coup(){
    int choice;
    printf("Joueur 2 veuillez choisir votre case de d%cpart svp \n",130);
    printf("choisissez une case entre 0 et 5 || Utiliser le nombre 256 pour retourner au menu\n");
    scanf("%d",&choice);
    if (choice==256){
        menu();
    }
    int nbBille = plateau[1][choice];
    plateau[1][choice] = 0;
    choice++;
    for (int i = nbBille;i>0;i--){
        plateau[1][choice] ++;
        choice++;
        nbBille--;
        if (choice == 6 && nbBille>1){
            plateau[0][choice]++;
            choice--;
        }
    lastCaseJ2 = i;
    }
    afficheTab();
    return plateau;
}

int menu(){

    bool continuer=true;

    while(continuer){
    int choix;
    printf("      MENU : JEU AWALE\n\n");
    printf("1 - JOUER\n");
    printf("2 - REGLES\n");
    printf("3 - QUITTER\n\n\n");
    scanf("%i",&choix);


    switch(choix){
    case 1 :
        init();
        j1coup();
        j2coup();
        printf("test tab : %i", plateau[2][3]);
        break;
    case 2 :
        printf("      REGLES\n\n");
        break;
    case 3 :
        printf("Bonne journee \n\n");
        continuer=false;
        return 0;
        break;
    default:
        printf("ERREUR !\n\n");
        }
    }
}

int main()
{
    menu();
    return 0;
}
