#include <stdio.h>

int mystrlen(char *str){
      int i=0;
      
      while((str[i]) != '\0'){
            if((str[i] == '\n') || (str[i] == ' ') || (str[i] == '\t')) continue;
            i++;
      }

      return i;
}

char *mystradd(char *origin, char *addition){
      char* new = origin;
      int i=0, j=0;

      while((origin[i]) != '\0'){
            new[i] = origin[i];
            i++;
      }
      
      while((addition[j]) != '\0'){
            (new[i]) = (addition[j]);
            i++;
            j++;
      }

      return new;
}

int mystrfind(char *origin, char *substr){
      int i=0, j=0;

      while((origin[i]) != '\0'){
            //printf("1");
            if((origin[i]) == (substr[j])){
                  while((origin[i++]) == (substr[j++])){
                        //printf("%c, %c\n", (origin[i]), (substr[j]));
                        if((substr[j]) == '\0') return 1;
                  }
            } else i++;
            j=0;   
      }
      
      return 0;
}
