#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int plateau[2][6];
int g1r=0;
int g2r=0;
int lastCaseJ1;
int lastCaseJ2;
bool fin = false;

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
    int raw = 0;
    int nbBille = plateau[0][choice];
    plateau[0][choice] = 0;
    //cas ou la premiuère case est choisie
    if (choice == 0){
       for (int i = nbBille;i>0;i--){
        plateau[1][choice]++;
        choice++;
        nbBille--;
        raw = 1;
        if(choice==5&&nbBille>1){
            plateau[0][choice]++;
            choice--;
            nbBille--;
            raw =0;
        }
       }
    }else{
    choice--;
    for (int i = nbBille;i>0;i--){
        plateau[0][choice] ++;
        choice--;
        nbBille--;
        raw = 0;
        if (choice == 0 && nbBille>1){
            plateau[1][choice]++;
            choice++;
            nbBille--;
            raw = 1;
        }
    lastCaseJ1[0] = raw;
    lastCaseJ1[1] = choice;
    }
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
    int raw = 1;
    plateau[1][choice] = 0;
    //cas ou le joueur choisie la dernière case de son plateau
    if (choice == 5){
       for (int i = nbBille;i>0;i--){
        plateau[0][choice]++;
        choice--;
        nbBille--;
        raw = 0;
        if(choice==0&&nbBille>1){
            plateau[1][choice]++;
            choice++;
            nbBille--;
            raw=1 ;
        }
       }
    }else{
    choice++;
    for (int i = nbBille;i>0;i--){
        plateau[1][choice] ++;
        choice++;
        nbBille--;
        raw =1 ;
        if (choice == 5 && nbBille>1){
            plateau[0][choice]++;
            choice--;
            nbBille--;
            raw=0
        }
    lastCaseJ2[0] = raw;
    lastCaseJ2[1] = choice;
    }
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

int game(){
while(fin==false){
    j1coup();
    j2coup();
}


}

int main()
{
    menu();
    return 0;
}
