#include <stdio.h>
#include <stdlib.h>

char* ConcatArgOpt(char* Arg, int sizeArg, char* Opt, int sizeOpt){

    char* concat = malloc(sizeof(char)*(sizeArg+sizeOpt+1));
    int compteur=0;

    for(int i=0; i<sizeArg; i++){
        concat[compteur] = Arg[i];                         // On copie les arguments
        compteur++;
    }

    concat[compteur] = '+';                                      // On ajoute le séparateur +
    compteur++;

    for(int i=0; i<sizeOpt; i++){
        concat[compteur] = Opt[i];                         // On copie les options
        compteur++;
    }
    return concat;
}



char* ConcatKeyValue(char* keyValue1, int size1, char* keyValue2, int size2){

    char* concat = malloc(sizeof(char)*(size2+size1+1));
    int compteur=0;

    for(int i=0; i<size1; i++){
        concat[compteur] = keyValue1[i];                         // On copie la premiere association de valeurs
        compteur++;
    }

    concat[compteur] = '/';                                      // On ajoute le séparateur /
    compteur++;

    for(int i=0; i<size2; i++){
        concat[compteur] = keyValue2[i];                         // On copie la premiere association de valeurs
        compteur++;
    }

    return concat;
}


int size(char* string){
    int compteur=0;
    for(int i=0; string[i]!='\0'; i++){
        compteur++;
    }
    return compteur;
}


char* FormateKeyValue(char* key, int sizeKey, char* value, int sizeValue){
    char* formate = malloc(sizeof(char)*(sizeKey+sizeValue+1));
    int compteur=0;

    for(int i=0; i<sizeKey; i++){
        formate[compteur] = key[i];
        compteur++;
    }

    formate[compteur] = ';';
    compteur++;

    for(int i=0; i<sizeValue; i++){
        formate[compteur] = value[i];
        compteur++;
    }

    

    return formate;

}

char* getActionOption(FILE* file, long cursor){

    char carac;
    int debutOptions = 0;
    int finAction = 0;
    char* key;
    char* value;
    int startKeyValue = 0;
    char* argument;
    int argumentVide = 0;
    char* option;
    int optionVide = 0;
    char* action;
    int compteur = 0;
    int count = 0;
    carac=fgetc(file);
    //printf("\n");
    
        while(carac != EOF && carac != '='){                        // tant que ce n'est pas le debut d'une autre action ou que ce soit la fin du fichier
            if(carac=='{' && startKeyValue==0){
                /*printf("avant getKey c : %c", carac);
                printf("avant getKey : %s", key);*/
                startKeyValue = 1;                
                cursor = ftell(file);
                key = GetKey(file,carac);
                fseek(file, (ftell(file)-cursor)*-1, SEEK_CUR);     // On remet le curseur a lendroit ou il était avant l'appel de la fonction
                //printf("key : %s \n", key);
            }
            else if(carac == '}' && startKeyValue==1 && debutOptions==0){                // si cest la fin d'une associations et que celle ci est un arguments
                //printf("Avant argument : %s \n", key);
                if(argumentVide==0){
                    argument = FormateKeyValue(key, size(key), value, size(value));             // si argument est vide on ajoute direct la premiere association
                    argumentVide=1;

                }else{
                    char* formate = FormateKeyValue(key, size(key), value, size(value));            // si il ya deja des association stocker
                    argument = ConcatKeyValue(argument, size(argument), formate, size(formate));    // On concatene ceux deja stocker avec le nouveau
                }
                
                //printf(" argument : %s \n", argument);
                free(key);
                free(value);
                startKeyValue = 0;
                //printf("Apres argument : %s \n", key);

            }else if(carac == '}' && startKeyValue==1 && debutOptions==1){                 // si cest la fin d'une associations et que celle ci est une option
                if(optionVide==0){
                    option = FormateKeyValue(key, size(key), value, size(value));             // si argument est vide on ajoute direct la premiere association
                    optionVide=1;

                }else{
                    char* formate = FormateKeyValue(key, size(key), value, size(value));            // si il ya deja des association stocker
                    option = ConcatKeyValue(option, size(option), formate, size(formate));    // On concatene ceux deja stocker avec le nouveau
                }
                free(key);
                free(value);
                startKeyValue = 0;

            }else if(carac == '>' && startKeyValue==1){                     // Debut de la partie value de l'association
                cursor = ftell(file);
                value = GetValue(file, carac);
                fseek(file, (ftell(file)-cursor)*-1, SEEK_CUR); 
                //printf(" value %s \n", value);
            }else if(carac == '+'){
                debutOptions = 1;
            }

            carac = fgetc(file);
        }

        if(debutOptions == 1){
            action = ConcatArgOpt(argument, size(argument), option, size(option));
        }

    return action;
}


static FILE* file;
long cursor;
int main(){
    file = fopen("/Users/vidalleo/Documents/C/Projet_WebScrapper/Projet-Scraper/test.sconf", "rt");

    if(file!=NULL){
        char row = fgetc(file);
        while(row!=EOF){
            printf("%c",row);
            if(row == '='){
                
                char* action = getActionOption(file,ftell(file));
                printf(" Action number one : %s", action);
                break;
            }
            row = fgetc(file);
        }
    }else{
        printf("cest die");
    }


    /*char* key = "Key";
    char* value = "Value";
    int size1 = 3;
    int size2 = 5;
    int size3 = 9;
    int size4 = 19;
    int size4bis;


    char* formate = FormateKeyValue(key,size1,value,size2);
    printf("%s\n",formate);
    char* formate2 = FormateKeyValue(key,size1,value,size2);
    char* concat = ConcatKeyValue(formate, size3, formate2, size3);
    printf("%s\n",concat);
    char* concat1 = ConcatKeyValue(concat, size4, formate2, size3);
    printf("%s\n",concat1);
    char* action = ConcatArgOpt(concat, size4, concat, size4);
    printf("%s\n",action);
    printf(" key : %s \n",key);
    printf(" value : %s \n",value);*/

}