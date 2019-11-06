#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char** RecupKeyValeur(char* row){
    char** res = malloc(sizeof(char*)*2);
    for(int i=0; i<2; i++){
        res[i] = malloc(sizeof(char) * strlen(row));
    }

    for(int i=0; i<strlen(row); i++){

        if(row[i] == '{'){                                                // Si on rencontre le caractère { c'est qu'une association {KEY -> VALUE} commence

            int index = 0;
            for(int j=i+1; (row[j+1]!='-' && row[j+2]!='>'); j++){        //On récupere la la KEY de l'association {KEY -> VALUE}
                res[0][index] = row[j];                                   //et on la stocke dans le 1er champs du tableau que retourne la fonction
                index++;
                i = j;
            }

            res[0][index+1]='\0';
            index=0;

            for(int j=i+5; row[j]!='}'; j++){                         //On récupere la la VALUE de l'association {KEY -> VALUE}
                res[1][index] = row[j];                               //et on la stocke dans le 2eme champs du tableau que retourne la fonction
                index++;
            }
            res[1][index+1]='\0';
            break;
        }
    }

    return res;                                                       // La fonction retourne un tableau deux dimensions de chaine de caractere
}                                                                     // Qui contient en 1er champ la KEY et en deuxieme champs la VALUE de l'association {KEY -> VALUE}


int main() {

    FILE* f = fopen("../test.txt","r");
    if (f != NULL){
        printf("Le fichier est ouvert \n");
    }else{
        printf("Erreur lors de l'ouverture du fichier");
    }

    char row[100];
    while(fgets(row, 100, f) != NULL){
        printf("%s \n", row);
    }

    /*char* str = malloc( sizeof(char)*50);
    str = "   {KEY -> 36666}";
    printf("start : %s \n", str);
    char ** rep = RecupKeyValeur(str);
    printf("end : ");
    for(int i=0; i<2; i++){
        printf("%s ", rep[i]);
    }*/
    return 0;
}