#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>



//Plateau de jeu
int plateau[2][6];
//Grenier joueur 1
int g1r=0;
//Grenier joueur 2
int g2r=0;
//tableau pour stocker la dernière case ou le joueur 1 a déposé la der,ière bille
int lastCaseJ1[2];
//tableau pour stocker la dernière case où le joueur 2 a déposé la der,ière bille
int lastCaseJ2[2];
//variable de fin
int fin = 0;
//Sert a gérer les erreur d'entrer
int error=0;



void clear(){
    system("cls");
    printf("\n \n \n \n");
}

//initialisation et affichage du plateau de jeu

void init()
{
    for(int i =0 ; i<2; i++){//boucle ligne
        for (int j=0;j<6; j++){//boucle colonne
            plateau[i][j] = 4 ;
        }
    }
//    clear();
//    afficheTab();
}

//Afficheur de plateau
void afficheTab(){
//        system("cls");
//        printf("\n \n \n \n");
        printf("| A || Z || E || R || T || Y ||");// peu etre a changer en ABCDEF/AZERTY pour plus de confort de jeu
        printf("  Grenier J1= %i \n",g1r);
        printf("----------------------------------------------\n");
    for(int i = 0 ;i<2; i++){
        for (int j =0 ; j<6; j++){
                if(plateau[i][j]>=10){
                    printf("|%i |",plateau[i][j]);
                }else{
                    printf("| %i |",plateau[i][j]);
                }
        }
        printf("\n");
    }
        printf("----------------------------------------------\n");
        printf("| A || Z || E || R || T || Y || ");
        printf(" Grenier J2= %i \n \n",g2r);
}

// convertie en valeur conforme pour nos choix
char convertiLettreEnChiffres(char lettre){
    lettre = tolower(lettre);
        switch(lettre){
        case 'a':
            error=0;
            return 0;
            break;
        case 'z':
            error=0;
            return 1;
            break;
        case 'e':
            error=0;
            return 2;
            break;
        case 'r':
            error=0;
            return 3;
            break;
        case 't':
            error=0;
            return 4;
            break;
        case 'y':
            error=0;
            return 5;
            break;
        case 'm':
            error=0;
            return 9;
            break;
        default:
            printf("Erreur lors de votre choix veuillez en choisir une autre svp \n");
            error=1;
            break;
        }
}

//coup Du joueur 1
int j1coup(){
    int choice;// Case coisie par le joueur
    int varIchoice;// index de la case (colonne) choisie si nbBilles >11
    int varIRaw;// index de la ligne choisi si nbBilles>11
    char lettre;
    printf("Joueur 1 veuillez choisir votre case de d%cpart svp \n",130);
    do{
        printf("choisissez une case entre 'a z e r t y ' || Utiliser la lettre 'M' pour retourner au menu\n");
        scanf("%s",&lettre);
        choice = convertiLettreEnChiffres(lettre);
        printf("choice aftel convert =  %i \n",choice);
    }while(error==1);

    // choix pour afficher le menu en plein jeu
    if (choice==9){
        fin =1;
        menu();
        return 0;
    }
    int raw = 0;//passe la ligne à celle du dessus plateau[0] : camps joueur 1
    int nbBille = plateau[raw][choice];// compteur du nombre de billes en main
    // si la case choisi est vide
    if(nbBille==0){
        printf("La case choisie est vide veuillez en choisir une autre");
        j1coup();
    }else{
        // memorisation des index si le nbbilles>11
        if(nbBille>11){
             varIchoice= choice;
             varIRaw= raw ;
        }
    plateau[raw][choice] = 0;//vide la case choisie
    //cas ou la premiuère case est choisie
    if (choice == 0 && raw==0 ){
           raw = 1; //passe la ligne à celle du dessous plateau [1]
       for (int i = nbBille;i>0;i--){
            //si on retombe sur la case choisie apres un tour de distribution
            if( varIchoice == choice && varIRaw == raw){
                        printf("Passe la case raw \n ");
                        raw=1;
            }
       //verifie le nbBille>0 avant de distribuer
            if(nbBille>0){
                plateau[raw][choice]++;//distribution
                nbBille--;
            }
       // printf("nbBilles = %i . choice = %i .\n",nbBille,choice);
       //si on atteint la dernière case du plateau de la ligne adverse
        if(choice==5&&nbBille>0 && raw == 1){
            raw =0;//change de ligne
            plateau[raw][choice]++;
            nbBille--;
        }
        // si on se trouve sur la ligne du dessous
        if(raw == 1 && nbBille>0){
            choice++;
        }else{
            //si on est sur la ligne du haut
            if(nbBille>0){
                choice--;
            }
       }
       printf("NbBilles = %i ,  et colonne = %i \n",nbBille,choice);
    }
    }else{
        //première distribution si la case choisie n'est pas une extremité
       choice--;
    for (int i = nbBille;i>0;i--){
            // gestion regles Boucle
        if(varIchoice==choice && varIRaw==raw){
                    printf("Passe la case choice-- \n ");
                    choice--;
            }
            //Si la première case est atteinte avec un restant de billes
        if (choice == 0 && nbBille>0 && raw == 0){
            plateau[raw][choice]++;
            nbBille--;
            raw=1;
        }else{
           plateau[raw][choice]++;
           nbBille--;
           //verif pour la prochaine distribution
           if(choice==5 && raw==1 && nbBille>0){
                raw=0;
           }else if(raw==1 && nbBille>0){
                choice++;
           }else if(nbBille>0){
                choice--;
           }
        }
        printf("NbBilles = %i ,  et colonne = %i \n",nbBille,choice);
    }
    }
    //index de la dernière case distribué
    lastCaseJ1[0] = raw;
    lastCaseJ1[1] = choice;
    //Partie ARTHUR
    clear();
    ramassageJ1();
    afficheTab();
    return plateau;
}
}



// fonction pour vérifier si la regles de l'affamer s'applique pour le joueur 1
int affamerJ1(){
    int affamer;//variables pour la regle de l'arffamer boolean a l'origine
    int colonne = lastCaseJ1[0];// index de la colonne de la dernière case joué
    for(int i =0 ; i<6 ;i++){
            //verifie si toute les case de la ligne ont entre 2 et 3 billes
       if(plateau[1][i]<4 && plateau[1][i]>1 && i<=lastCaseJ1[1]){
            affamer = 1; //true; pour le moment la regle peut s'appliquer
        }else{
            //verifie si la case est vide
            if(plateau[1][i]==0){
                affamer = 1;
            }else{
                affamer = 0; //false; La regle ne s'applique pas
                return affamer;
            }
        }
    }
    printf("La regle de l'affamer s'applique pour le joueur 1\n");
    //La regle s'applique
   return affamer;
}

// fonction pour vérifier si la regles de l'affamer s'applique pour le joueur 2
int affamerJ2(){
    int affamer;
    for(int i =0 ; i<6 ;i++){
        if(plateau[0][i]<4 && plateau[0][i]>1 && i>=lastCaseJ2[1] ){
            affamer = 1; //true ;
        }else{
            if(plateau[0][i]==0){
                affamer =1;
            }else{
                affamer = 0; //false la regle ne s'applique pas
                return affamer;
            }
        }
    }
    printf("La regle de l'affamer s'applique pour le joueur 2\n",affamer);
    return affamer;
}

// Coup joueur 2
int j2coup(){
    if(fin==1){
        return 0;
    }
    int varIchoice;// index de la case choisie si nbBilles >11
    int varIRaw;
    int choice;
    char lettre;
    printf("Joueur 2 veuillez choisir votre case de d%cpart svp \n",130);
   do{
        printf("choisissez une case entre 'a z e r t y ' || Utiliser la lettre 'M' pour retourner au menu\n");
        scanf("%s",&lettre);
        choice = convertiLettreEnChiffres(lettre);
        //printf("choice aftel convert =  %i \n",choice);
    }while(error==1);
    if (choice==9){
        fin =1;
        menu();
        return 0;
    }
    int raw = 1;// passe a la ligne du dessous
    int nbBille = plateau[raw][choice];
    if(nbBille==0){
        printf("La case choisie est vide veuillez en choisir une autre\n");
        j2coup();
    }else{
        //initialisation des variables pour la regles de boucles
        if(nbBille>11){
            varIchoice = choice;
            varIRaw= raw;
        }
    plateau[raw][choice] = 0;
    //cas ou le joueur 2 choisie la dernière case de son plateau
    if (choice == 5 && raw == 1){
        raw = 0;//passe a la ligne du dessus
       for (int i = nbBille;i>0;i--){
           // Si on repasse sur notre case de départ
            if( varIchoice == choice && varIRaw == raw){
                        printf("Passe la case raw \n ");
                        raw=0;
            }
            if(nbBille>0){
                plateau[raw][choice]++;
                nbBille--;
            }
        if(choice==0&&nbBille>0){
            raw=1 ;
            plateau[raw][choice]++;
            nbBille--;
        }
        if(raw == 0 && nbBille>0 ){
            choice--;
        }else{
            if(nbBille>0){
                choice++;
            }
        }
        printf("NbBilles = %i ,  et colonne = %i  et ligne = %i \n",nbBille,choice,raw);
       }
       //cas ou la case est differente de l'extremité != 5
    }else{
    choice++; //premier mouvement
    for (int i = nbBille;i>0;i--){
                    // gestion regles Boucle
        if(varIchoice==choice && varIRaw==raw){
            printf("Passe la case choice++ \n ");
            choice++;
            printf("Choice fin regle boucle = %i",choice);
            }
        if (choice == 5 && nbBille>0&&raw==1){
            plateau[raw][choice]++;// a check distrib probleme 12/12
            nbBille--;
            raw=0;
        }else{
            plateau[raw][choice]++;
            nbBille--;
            if(choice == 0 && raw==0 && nbBille>0){
                raw=1;
            }else if(raw==0 && nbBille>0){
                choice--;
            }else if(nbBille>0){
                choice++;
            }
        }
    }
    //printf("NbBilles = %i ,  et colonne = %i  ligne = %i \n",nbBille,choice,raw);
    }
    //printf("choice = %i \n",choice);
    }
    lastCaseJ2[0] = raw;
    lastCaseJ2[1] = choice;
    clear();
    ramassageJ2();
    afficheTab();
    return plateau;
}

//ramasse les billes et applique la regle de la raffle si possible
void ramassageJ1(){
    //index de la dernière case distribuer
    int ligne = lastCaseJ1[0];
    int colonne = lastCaseJ1[1];
    if(ligne==1){// si la dernière case jouer est sur la ligne adverse
            printf("id ramassage = %i =\n colonne = %i \n",plateau[ligne][colonne],colonne);
            //verifie Si la case contient entre 2 et 3 billes
    if (plateau[ligne][colonne]<=3 && plateau[ligne][colonne]>1){
            // verifie si l'a regle affamer est applicable
        if (affamerJ1()==0){
            printf("J1 Ramasse la dernière case \n");
            g1r+=plateau[ligne][colonne];// alimente le grenier du joueur
            plateau[ligne][colonne]=0; // vide la case
            //Verification  la raffle sur les lignes precedentes
            for(int i =colonne-1 ; i>-1 ;i--){
                    // si la case est contient un nombre de billes entre 2 et 3
                if(plateau[1][i]<4&& plateau[1][i]>1){
                    printf("Applique la rafle en case : %i\n",i);
                    g1r+=plateau[1][i];
                    plateau[1][i]=0;
                }
                else{
                    i=-1;
                }
            }
        }
    }
  }
}


void ramassageJ2(){
    int ligne = lastCaseJ2[0];
    int colonne = lastCaseJ2[1];
    printf("colonne = %i\n",colonne);
    if(ligne==0){
            printf("J2= %i = \n",plateau[ligne][colonne]);
    if (plateau[ligne][colonne]<=3 && plateau[ligne][colonne]>1){
        if (affamerJ2()==0){ // 0 = false la regle de l'affamer ne s'applique pas
                printf("J2 Ramasse la dernière case : %i \n",colonne);
            g2r+=plateau[ligne][colonne];
            plateau[ligne][colonne]=0;
            for(int i =colonne+1 ;i<6;i++){
                if(plateau[0][i]<=3&& plateau[0][i]>1){
                    printf(" applique la rafle en case : %i\n",i);
                    g2r+=plateau[0][i];
                    plateau[0][i]=0;
                }
                else{
                    i=6;
                }
            }
        }else{
        printf("affamer bloque la capture J2\n");
        }
    }
}
}



// menu

void menu(){
    bool continuer=true;// gestion de la boucle du menu
    char lettre;// lettre pour le choix
    while(continuer){
        int choix=0;
        printf("      MENU : JEU AWALE\n\n");
        printf("Z - JOUER\n");
        printf("E - JOUER AVEC IAJ2\n");
        printf("R - REGLES\n");
        printf("T - REINITIALISER\n");
        printf("Y - QUITTER\n\n\n");
     do{
        printf("choisissez une case entre 'z e r t y' : \n");
        scanf("%s",&lettre);
        choix = convertiLettreEnChiffres(lettre);
        printf("choice aftel convert =  %i \n",choix);
    }while(error==1);
    //choix du menu
    switch(choix){
    case 1 :
        //init();
        fin=0;// gestion de la variables de fin pour eviter une boucle en reprise de partie
        clear();
        game();
        continuer=false;
        break;
    case 3 :
        printf("      REGLES\n\n");
        printf("    Plateau : La partie se joue sur le plateau de 2×6 trous.\n\n");
        printf("    Sens de la partie : antihoraire.\n");
        printf("    Greniers : Si votre awale contient deux greniers (trous plus grands a chacune des deux extremites) alors ils ne comptent pas comme des trous, ils ne servent qu a ranger les graines des joueurs. Le grenier d un joueur se situant a sa droite.\n");
        printf("    Capture : si la dernière graine est deposee dans un trou de l adversaire comportant deja 1 ou 2 graines, le joueur capture les 2 ou 3 graines resultantes. Les graines capturees sont alors sorties du jeu (grenier) et le trou est laisse vide.\n");
        printf("    Rafle : Lorsqu’un joueur s’empare de 2 ou 3 graines, si la case précédente contient également 2 ou 3 graines, elles sont capturées aussi et ainsi de suite.\n");
        printf("    Affamer : Un joueur n a pas le droit de jouer un coup qui prenne toutes les graines du camp adverse.\n");
        printf("    Boucle : Lorsqu'un joueur choisie une case avec 11 billes ou plus cela signifie que l'on fera un tour du plateau, dans ce cas la case choisie sera sauté .\n");
        continuer=false;
        break;
    case 5:
        printf("Bonne journee \n\n");
        exit(EXIT_SUCCESS);// arrete le programme
        continuer=false;
        break;
    case 2:
        fin=0;
        init();
        gameIA();
        continuer=false;
        break;
    case 4:
        init();
        printf("Votre partie a %ct%c r%cinitialiser \n\n",130,130,130,130);
        break;
    default:
        printf("ERREUR !\n\n");
        break;
        }
    }
}

//fonction d'une parti

int game(){
    //modif du plateau pour test
    printf("jeej \n");
    for (int i = 0 ; i<6 ;i++){
        plateau[0][i]=2;
        plateau[1][i]=4;
   }
    clear();
    afficheTab();
while(fin == 0){
    j1coup();
    finDeJeu();
    j2coup();
    finDeJeu();
}
return 0;
}



//Verifie si la ligne est vide pour la fin de parti

int siLigneVide(int ligne){
    int ligneVide;
    for (int i = 0 ; i<6 ;i++){
        if (plateau[ligne][i]==0){
            ligneVide=1; // La ligne est vide;
        }else{
            ligneVide=0; // la ligne n'est pas vide
            return ligneVide;
        }
    }
    return ligneVide;
}





int finDeJeu(){
    if(g1r==26 || siLigneVide(1)==1){// a voir pour la regles des 26 billes
        printf("\n\nVictoire Du joueur 1 Toutes mes f%clicitations \n\n",130);
        fin==1;
        menu();
    }
    if(g2r==26 || siLigneVide(0)==1){
        printf("\n\nVictoire Du joueur 2 Toutes mes f%clicitations \n\n",130);
        fin==1;
        menu();
    }
    return fin;
}



// fonction pour l'ia en joueur 2
int iaJ2(){
    if(fin==1){
        return 0;
    }
    int varIchoice;
    int varIRaw;
    int choice;
    int nbMaxbilles=0;
    int indexmax;
    // boucle pour choisir la case avec le plus grand nombre de billes et definir le choix de l'ia
    for(int i=0;i<6;i++){
        if(plateau[1][i]>=nbMaxbilles){
            nbMaxbilles=plateau[1][i];
            indexmax=i;
        }
    }
    choice=indexmax;
    printf("Joueur IA choisie la case de d%cpart: %i \n",130,choice);
    int raw = 1;
    int nbBille = plateau[raw][choice];
    if(nbBille==0){
        printf("La case choisie est vide veuillez en choisir une autre\n");
        j2coup();
    }else{
        if(nbBille>11){
            varIchoice = choice;
            varIRaw= raw;
        }
    plateau[raw][choice] = 0;
    if (choice == 5 && raw == 1){
        raw = 0;
       for (int i = nbBille;i>0;i--){
            if( varIchoice == choice && varIRaw == raw){
                        printf("Passe la case raw \n ");
                        raw=0;
            }
            if(nbBille>0){
                plateau[raw][choice]++;
                nbBille--;
            }
        if(choice==0&&nbBille>0){
            raw=1 ;
            plateau[raw][choice]++;
            nbBille--;
        }
        if(raw == 0 && nbBille>0 ){
            choice--;
        }else{
            if(nbBille>0){
                choice++;
            }
        }
        printf("NbBilles = %i ,  et colonne = %i  et ligne = %i \n",nbBille,choice,raw);
       }
    }else{
    choice++;
    for (int i = nbBille;i>0;i--){
        if(varIchoice==choice && varIRaw==raw){
            printf("Passe la case choice++ \n ");
            choice++;
            printf("Choice fin regle boucle = %i",choice);
            }
        if (choice == 5 && nbBille>0&&raw==1){
            plateau[raw][choice]++;
            nbBille--;
            raw=0;
        }else{
            plateau[raw][choice]++;
            nbBille--;
            if(choice == 0 && raw==0 && nbBille>0){
                raw=1;
            }else if(raw==0 && nbBille>0){
                choice--;
            }else if(nbBille>0){
                choice++;
            }
        }
    }
    printf("NbBilles = %i ,  et colonne = %i  ligne = %i \n",nbBille,choice,raw);
    }
    printf("choice = %i \n",choice);
    }
    lastCaseJ2[0] = raw;
    lastCaseJ2[1] = choice;
    clear();
    printf(" L'IA a choisie la case %i \n",indexmax);
    ramassageJ2();
    afficheTab();
    return plateau;
}


int gameIA(){
    clear();
    afficheTab();
    while(fin == 0){
        j1coup();
        finDeJeu();
        iaJ2();
        finDeJeu();
    }
return 0;
}

int main(){
    init();
    menu();
    return 0;
}
