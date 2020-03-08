#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <regex.h>
 
 
int main(){
   
    char * regexString = "([a-z]+\\:\\/{2})?(www\\.)?((\\w+\\.)+\\w+)\\/(\\w*\\/)*(\\w+\\.\\w+)$";
    regex_t regexCompiled;
    size_t maxGroups = 7;
    regmatch_t groupArray[maxGroups];
    regcomp(&regexCompiled, regexString, REG_EXTENDED);
   
    char **arr = malloc(10*sizeof(char*));    
    int Count_sentence = 0; //предложение №    
    int size = 10; //память в arr      
    char current_symbol;  
    do{
        int Count_symbol = 0; //символ в предложении
        int size_sentence = 10; //память в предложении  
        arr[Count_sentence] = malloc(size_sentence*sizeof(char));          
        current_symbol = getchar();
        do{
            if (Count_symbol == size_sentence - 2 ){
                size_sentence += 10;
                arr[Count_sentence] = realloc(arr[Count_sentence],size_sentence);
            }
            arr[Count_sentence][Count_symbol] = current_symbol;
            Count_symbol++;
            if (Count_symbol == 4){
                arr[Count_sentence][Count_symbol] = '\0';
                if (!strcmp(arr[Count_sentence],"Fin."))
                    break;
            }
            current_symbol = getchar();                
        }while (current_symbol != '\n');
        arr[Count_sentence][Count_symbol] = '\0';
        if (Count_sentence == size - 2 ){
            size += 10;
            arr = realloc(arr, size * sizeof(char*));
        }
        Count_sentence++;
    }while (strcmp(arr[Count_sentence-1],"Fin."));
    int k = 0;
    while (k < Count_sentence){
        if (regexec(&regexCompiled, arr[k], maxGroups, groupArray, 0) == 0){
            for(int j = groupArray[3].rm_so; j < groupArray[3].rm_eo; j++)
                printf("%c", arr[k][j]);
            printf(" - ");
            for(int i = groupArray[6].rm_so; i < groupArray[6].rm_eo; i++)
                printf("%c", arr[k][i]);
        }
        printf("\n");
        k++;
    }
    for (int i = 0; i < Count_sentence; i++){
        free(arr[i]);
    }
    free(arr);
    regfree(&regexCompiled);
   
    return 0;
}