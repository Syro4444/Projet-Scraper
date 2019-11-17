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
            c = fgetc(file);
        }    
    }  
}

int BrowseAndCountKey(FILE* file, long location){ // Doit etre appelé avant BrowseAndGiveKey
    int count = 0;
    fseek(file,location,SEEK_SET);
    char c = fgetc(file);
    while(c != '>'){ // tant qu'on a pas atteint la fin du nom
        if(c != ' ' || c != '>'){// on suprime les caracteres inutiles (espace & >)
            if(c == '-'){
                while(c == ' '){
                    c = fgetc(file);
                }
            }
            if(c != '>'){
                count++;
                c = fgetc(file);
            }
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
       printf("%c", keyTab[i]);//  print le tableau
    }
    //printf("\n");
    return keyTab;
}

char GetKey(FILE* file, char carac) { // retourne le tableau avec la key
    char c = carac;
    if(c == '{'){
        c = fgetc(file);
        long location = ftell(file);
        int count = BrowseAndCountKey(file, location);
        if(count >= 0){
            char keyTab = *BrowseAndGiveKey(file,location,count);
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

char GetValue(FILE* file, char carac) { // retourne le tableau avec la key
    char c = carac;
    if(c == '>'){
        c = fgetc(file);
        long location = ftell(file);
        int count = BrowseAndCountValue(file, location);
        if(count >= 0){
            char valueTab = *BrowseAndGiveValue(file,location,count);
            return valueTab;
        }
    }
    return 0;
}

char* GetTask(char letter, FILE* file){ 
    char c = letter;
    //printf("%c",c);
    if(c == '='){
        int loc = ftell(file);
        fseek(file,loc,SEEK_SET);
        c = fgetc(file);
        if(c == '='){
            while(c != '{'){
                c =fgetc(file);
            }
            long x = ftell(file);
            int count = BrowseAndCountKey(file,x);
            fseek(file,x,SEEK_SET);
            char* key = malloc(sizeof(char)*10);
            key[count] = GetKey(file,c);// comporte la key
            FILE* sys = fopen("sys.txt", "w");
            fputs(key,sys);
            fclose(sys);
            return key;
        }
    }
    return 0;
}

char* GetUrl(char* tab){
    int i = 0;
    while(tab[i] != 'u'){
        i++;
        printf("bug\n %c", tab[i]);
    }
    if(tab[i] =='u' && tab[i+1] == 'r' && tab[i + 2] == 'l'){
        i+=3;
        int memory = i;
        int count = 0;
        while(tab[i] != '+' || tab[i] != ';' ){
            count++;
            if(tab[i] == '\0'){
                printf("erreur dans le fichier de configuration");
                return 0;
            }
            i++;
        }
        char *urlTab = malloc(sizeof(char)*count);
        while(tab[i] != '+' || tab[i] != ';'){
            urlTab[i] = tab[i];
            i++;
        }
        return urlTab;
    }
    printf("fichier de configuration incorrect");
    return 0;
}

static FILE* sys;
static FILE* file;
long cursor;
int main(){
    file = fopen("test.sconf", "rt");
    //printf("%ld ", ftell(file));
    if(file != NULL){
        char c ;
        while(c != EOF){
            c = fgetc(file);
            //NoComment(file);
            //NoSpaces(file,c);
            if(c != '#'){
               // printf("%c", c); // sert a print le fichier de config, a enlever par la suite
            }
            if(c == '{'){// si on tomb sur une accolade je lance l'appel de fonction
                //char *keyTab = GetKey(file,c); // recuperation de la key
                //free(keyTab); // mis temporairement a cette endroit pour ne pas l'oublier par la suite    
            }
            if(c == '>'){
                //char *valueTab = GetValue(file,c); // recuperation de la value
                //free(valueTab); // mis temporairement a cette endroit pour ne pas l'oublier par la suite
            }
            
            if(c == '='){
                //printf("ok");

               // sys = fopen("sys.txt", "w");
                //char* tab = GetTask(c,file);
                //free(tab);
            }

            cursor = ftell(file);     
       }
    }else {
        printf("erreur lors de l'ouverture du fichier");
    }
    char* tab = malloc(sizeof(char)*150);
    tab = "fjfjfjjfjf;urlhttp://GGGGGGGGG.Fr;";

    char test[150] = "+urlHttp://OKKKK;";
    test[150] = *GetUrl(*tab);
    int Y = 0; 
    while(test[Y] != '\0'){
    printf("%c", test[Y]); 
    Y++;
    }
    //fclose(sys);
    fclose(file);
    return 0;
}

