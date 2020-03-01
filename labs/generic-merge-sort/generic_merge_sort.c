#include <stdio.h>
#include <string.h>

#define MAX 10
int arrayInt[MAX], tmpInt[MAX+1];
char arrayString[MAX][MAX], tmpString[MAX][MAX];

void sort(int left, int right);
void mergeSort(int left, int mid, int right);
void sortSt(int left, int right);
void mergeSortSt(int left, int mid, int right);

int main(int argc, char **argv[]){
      int i;
      char r;

      printf("\nOrdenar (maximo 10) Strings o Ints (s/i)?\n");
      r = getchar();
      printf("\n");

      if(r == 'i'){
            printf("Numeros a ordenar: \n");
            
            for(i = 0; i < MAX; i++){
                  scanf("%d", &arrayInt[i]);
            }
            
            sort(0, MAX);

            for(i = 0; i<MAX; i++){
                  printf("%d, ", arrayInt[i]);
            }

      }
      else if(r == 's'){
            printf("Palabras a ordenar: \n");
            
            for(i = 0; i < MAX; i++){
                  scanf("%s", &arrayString[i]);
            }
            
            sortSt(0, MAX);

            for(i = 1; i<MAX; i++){
                  printf("%s, ", arrayString[i]);
            }

      }

      printf("\n\n");

      return 0;
}

void sort(int left, int right){
      int mid;

      if(left<right){
            mid = (left+right) / 2;
            sort(left, mid);
            sort(mid+1, right);
            mergeSort(left, mid+1, right);
      }
}

void mergeSort(int left, int mid, int right){
      int i, lend, n, tmp;
      lend = (mid-1);
      tmp = left;
      n = (right-left+1);

      while(left <= lend && mid <= right){
            if(arrayInt[left] <= arrayInt[mid]) 
                  tmpInt[tmp++] = arrayInt[left++];
            else
                  tmpInt[tmp++] = arrayInt[mid++];
      }

      while(left <= lend) 
            tmpInt[tmp++] = arrayInt[left++];

      while(mid <= right) 
            tmpInt[tmp++] = arrayInt[mid++];

      for(i=0; i<n; i++, right--) 
            arrayInt[right] = tmpInt[right];

}

void sortSt(int left, int right){
      int mid;

      if(left<right){
            mid = (left+right) / 2;
            sortSt(left, mid);
            sortSt(mid+1, right);
            mergeSortSt(left, mid+1, right);
      }
}

void mergeSortSt(int left, int mid, int right){
      int i, lend, n, tmp;
      lend = (mid-1);
      tmp = left;
      n = (right-left+1);

      while(left <= lend && mid <= right){ 
            if(strcmp((arrayString[left]), (arrayString[mid])) <= 0) {
                  //printf("Menor o igual\n");
                  //printf("%s <= %s\n", arrayString[left], arrayString[mid]);
                  strcpy((tmpString[tmp++]), (arrayString[left++]));
            }
            else {
                  //printf("Mayor\n");
                  //printf("%s <= %s\n", arrayString[left], arrayString[mid]);
                  strcpy((tmpString[tmp++]), (arrayString[mid++]));
            }
      }

      while(left <= lend) 
            strcpy((tmpString[tmp++]), (arrayString[left++]));

      while(mid <= right) 
            strcpy((tmpString[tmp++]), (arrayString[mid++]));

      for(i=0; i<n; i++, right--) 
            strcpy((arrayString[right]), (tmpString[right]));

}
