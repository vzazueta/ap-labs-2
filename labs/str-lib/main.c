#include <stdio.h>

int mystrlen(char *str);
char *mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int argc, char** argv[]){
      //printf("1");
      char *argv1 = (char *)argv[1];
      int argv1Length = mystrlen(argv1);
      char *argv2 = (char *)argv[2];
      char *argv3 = (char *)argv[3];
      char *newStr = mystradd(argv1, argv2);
      //printf("2");
      char* found;
      
      if(mystrfind(newStr, argv3) == 1) {
            found = "yes";
      } else {
            found = "no";
      }

      //printf("3");

      printf("Initial Length     \t: %d\n", argv1Length);
      //printf("4");
      printf("New String         \t: %s\n", newStr);
      printf("Substring was found\t: %s\n", found);

      return 0;
}
