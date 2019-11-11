#include <stdio.h>
#include <stdlib.h>

void NoComment(FILE* file){ // Sert pour pouvoir skip les commentaires
    long cur = ftell(file);
    if(cur != 0 ){
        fseek(file, cur - 1, SEEK_SET);
    }
    char c = fgetc(file);
    if(c == '#'){
        while(c != '\n' && c != EOF){
            c = fgetc(file); 
            if(c == EOF){
                printf("Fin de lecture"); // surement a enlever par la suite
            }
        }
    }


}

void NoSpaces(FILE* file, char letter){ // Sert à enlever les espaces
    if(letter == ' '){
        long location = ftell(file);
        fseek(file,location-1,SEEK_SET);
        char c = letter;
        while(c == ' '){
            letter = fgetc(file);
        }    
    }  
}

int BrowseAndCountKey(FILE* file, long location){ // Doit etre appelé avant BrowseAndGiveKey
    int count = 0;
    fseek(file,location,SEEK_SET);
    char c = fgetc(file);
    while(c != '>'){ // tant qu'on a pas atteint la fin du nom
        if(c != ' ' || c != '>'){// on suprime les caracteres inutiles (espace & >)
            count++;
            c = fgetc(file);   
        }else {
            c = fgetc(file);
        }
    }
    return count;
} 

char* BrowseAndGiveKey(FILE* file, long location, int size){ // a utiliser apres BrowseAndCountKey, creer un tableau et insere les lettres
    int i = 0;
    fseek(file,location-1,SEEK_SET);
    char c = fgetc(file);
    char *keyTab = malloc(sizeof(char) * size);
    while(c != '>'){ // tant qu'on a pas atteint la fin du nom
        if(c != ' ' && c != '>'){
            keyTab[i] = c;
            i++;
            c = fgetc(file);   
        }else {
            c = fgetc(file);
        }
    }
    for(int i = 0; i != size - 1;i++){
        //printf("%c", keyTab[i]);//  print le tableau
    }
    //printf("\n");
    return keyTab;
}

char* GetKey(FILE* file, char carac) { // retourne le tableau avec la key
    char c = carac;
    if(c == '{'){
        c = fgetc(file);
        long location = ftell(file);
        int count = BrowseAndCountKey(file, location);
        if(count >= 0){
            char* keyTab = malloc(sizeof(char)*count);
            *keyTab = *BrowseAndGiveKey(file,location,count);
            return keyTab;
        }
    }
    return 0;
}

int BrowseAndCountValue(FILE* file, long location){ // Doit etre appelé avant BrowseAndGiveValue
    int count = 0;
    fseek(file,location,SEEK_SET);
    char c = fgetc(file);
    while(c != '}'){ // tant qu'on a pas atteint l'accolade
        if(c != ' '){ // on suprime les espaces inutiles
            count++;
            c = fgetc(file);   
        }else {
            c = fgetc(file);
        }
    }
    count++;
    return count;
} 

char* BrowseAndGiveValue(FILE* file, long location, int size){ // a utiliser apres BrowseAndCountValue, creer un tableau et insere les lettres
    int i = 0;
    fseek(file,location-1,SEEK_SET);
    char c = fgetc(file);
    char *valueTab = malloc(sizeof(char) * size);
    while(c != '}'){ // tant qu'on a pas atteint la fin du nom
        if(c != ' ' ){
            valueTab[i] = c;
            i++;
            c = fgetc(file);   
        }else {
            c = fgetc(file);
        }
    }
    for(int i = 0; i != size - 1;i++){
        printf("%c", valueTab[i]);//  print le tableau
    }
    printf("\n");
    return valueTab;
}

char* GetValue(FILE* file, char carac) { // retourne le tableau avec la key
    char c = carac;
    if(c == '>'){
        c = fgetc(file);
        long location = ftell(file);
        int count = BrowseAndCountValue(file, location);
        if(count >= 0){
            char* valueTab = malloc(sizeof(char)*count);
            *valueTab = *BrowseAndGiveValue(file,location,count);
            return valueTab;
        }
    }
    return 0;
}



static FILE* file;
long cursor;
int main(){
    file = fopen("test.sconf", "rt");
    //printf("%ld ", ftell(file));
    if(file != NULL){
        char c ;
        while(c != EOF){
            c = fgetc(file);
            NoComment(file);
            //NoSpaces(file,c);

            if(c != '#'){
               // printf("%c", c); // sert a print le fichier de config, a enlever par la suite
            }
            if(c == '{'){// si on tomb sur une accolade je lance l'appel de fonction
                //char *keyTab = GetKey(file,c); // recuperation de la key
                //free(keyTab); // mis temporairement a cette endroit pour ne pas l'oublier par la suite
            }
            if(c == '>'){
                char *valueTab = GetValue(file,c); // recuperation de la key
                free(valueTab); // mis temporairement a cette endroit pour ne pas l'oublier par la suite
            }
            cursor = ftell(file);
        
       }

    }else {
        printf("fuck that mother fuckin' shit");
    }
    
    fclose(file);
    return 0;
}

