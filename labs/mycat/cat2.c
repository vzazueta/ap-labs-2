#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int read2(int f){
    char buffer[1];
    int x;

    x = read(f, buffer, 1);

    if(x == 0){
        return EOF;
    } else if(x == -1) {
        printf("Error Read\n");
        exit(1);
    }

    return buffer[0];
}

void write2(int f, char c){
    if(write(f, &c, 1) == -1){
        printf("Error Write\n");
        exit(1);
    }
}

void filecopy(int ifp, int ofp)
{
    int read2(int);
    void write2(int, char);
    int character;

    while((character = read2(ifp)) != EOF){
        write2(ofp, character);
    }
}

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
    //printf("0");
    int fd, i = 1;
    void filecopy(int, int);
    //char *prog = argv[0];   /* program name for errors */
    //printf("1");
    
    
    if (argc == 1){  /* no args; copy standard input */
        //printf("2");
        filecopy(fileno(stdin), fileno(stdout));
    } else{
        while (--argc > 0){
            //printf("3");
            if((fd = open(argv[i++], O_RDONLY, 0600)) == NULL){
                printf("Null");
            } else if (fd == -1){
                printf("Error Open\n");
                exit(1);
            } else {            
                filecopy(fd, fileno(stdout));
                
                if(close(fd) == -1 ){
                    printf("Error Close\n");
                    exit(1);
                }
            }
        }
    }

    return 0;
}
