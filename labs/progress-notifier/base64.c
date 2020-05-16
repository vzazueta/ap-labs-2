    /***********************************************************
    * Base64 library implementation                            *
    * @author Ahmed Elzoughby                                  *
    * @date July 23, 2017                                      *
    *                                                          *
    * Link:                                                    *
    * https://github.com/elzoughby/Base64/blob/master/base64.c *
    *                                                          *
    ***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "logger.h"

#define MAX_SIZE 102400

int fileSize;
int advanceRate;
int start = 0;
int progress = 0;
pid_t pid;
char base46_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

char *base64_encode(char *);
char *base64_decode(char *);

void sigusr1_handler(int);
void sigint_handler(int);

int main(int argc, char **argv){
      int rd;
      FILE *fileRead, *fileWrite;
      char *instruction, *filename;
      char input[MAX_SIZE];
      pid = getpid();

      signal(SIGUSR1, sigusr1_handler);
      signal(SIGINT, sigint_handler);

      if(argc < 2){
            errorf("Incorrect format");
            exit(1);
      }

      instruction = argv[1];
      filename = argv[2];

      fileRead = fopen(filename, "r");

      rd = fread(input, MAX_SIZE+1, 1, fileRead);
      if(rd == -1){
            errorf("Error in read()");
            exit(1);
      }
      
      fseek(fileRead, 0, SEEK_END);
      fileSize = ftell(fileRead);
      fseek(fileRead, 0, SEEK_SET);

      advanceRate = fileSize/100;

      //printf("\nfileSize: %d\nadvanceRate: %d\n", fileSize, advanceRate);

      if(strcmp("--encode", instruction) == 0){
            fileWrite = fopen("encoded.txt", "w");
          
            start++;
            fwrite( base64_encode(input), 1 , MAX_SIZE, fileWrite );
            
            printf("\n");

      } else if(strcmp("--decode", instruction) == 0){
            fileWrite = fopen("decoded.txt", "w");
            
            start++;
            fwrite( base64_decode(input), 1 , MAX_SIZE, fileWrite );

            printf("\n");

      } else {
            errorf("Incorrect format");
            exit(1);
      }

    return 0;
}



char* base64_encode(char* plain) {
      char counts = 0;
      char buffer[3];
      char* cipher = malloc(strlen(plain) * 4 / 3 + 4);
      int i = 0, c = 0;
      
      int advancement = advanceRate-1;

      for(i = 0; plain[i] != '\0'; i++) {
            
            if(i == advancement){
                  advancement += advanceRate;
                  progress++;
                  sleep(1);
            }
            
            buffer[counts++] = plain[i];
            if(counts == 3) {
                  cipher[c++] = base46_map[buffer[0] >> 2];
                  cipher[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
                  cipher[c++] = base46_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
                  cipher[c++] = base46_map[buffer[2] & 0x3f];
                  counts = 0;
            }
      }
     
      if(counts > 0) {
            cipher[c++] = base46_map[buffer[0] >> 2];
            if(counts == 1) {
                  cipher[c++] = base46_map[(buffer[0] & 0x03) << 4];
                  cipher[c++] = '=';
            } else {                      // if counts == 2
                  cipher[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
                  cipher[c++] = base46_map[(buffer[1] & 0x0f) << 2];
            }
            cipher[c++] = '=';
      }

      cipher[c] = '\0';   /* string padding character */
      return cipher;
}


char* base64_decode(char* cipher) {
      char counts = 0;
      char buffer[4];
      char* plain = malloc(strlen(cipher) * 3 / 4);
      int i = 0, p = 0;
      
      int advancement = advanceRate-1;

      for(i = 0; cipher[i] != '\0'; i++) {
            
            if(i == advancement){
                  advancement += advanceRate;
                  progress++;
                  sleep(1);
            }
            char k;

            for(k = 0 ; k < 64 && base46_map[k] != cipher[i]; k++);
            buffer[counts++] = k;
            if(counts == 4) {
                  plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
                  if(buffer[2] != 64)
                  plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
                  if(buffer[3] != 64)
                  plain[p++] = (buffer[2] << 6) + buffer[3];
                  counts = 0;
            }
      }

      plain[p] = '\0';    /* string padding character */
      return plain;
}

void sigusr1_handler(int signum)
{
      if ((signum == SIGUSR1) && (start == 0)) {
            write(STDOUT_FILENO, "Beginning Process!\n\0", 20);
      } else if((signum == SIGUSR1) && (start == 1) && (progress == 101)){
            write(STDOUT_FILENO, "Finished!\n\0", 20);
      } else {
            char buffer[20];      
            sprintf(buffer, "Progress: %d%%\n", progress);
            usleep(1);
            write(STDOUT_FILENO, buffer, 20);

      }
}

void sigint_handler(int signum)
{
    if (signum == SIGINT)
    {
      write(STDOUT_FILENO, "\nProcess was interrupted\n\n", 30);
      exit(1);
    }
}
