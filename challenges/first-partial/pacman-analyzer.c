#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
//#include <io.h>

#define REPORT_FILE "packages_report.txt"

void analyzeLog(char *logFile, char *report);

struct file{
      char name[64];
      char installDate[20];
      char upgradeDate[20];
      char removeDate[20];
      int upgrades;
};

struct file files[2048];

int main(int argc, char **argv) {

int p;

for(p=0; p<2048; p++){
      files[p].name[0] = '\0';
      files[p].installDate[0] = '\0';
      files[p].upgradeDate[0] = '\0';
      files[p].removeDate[0] = '\0';
      files[p].upgrades = 0;
}


    if (argc < 2) {
        printf("Usage:./pacman-analizer.o pacman.log\n");
        return 1;
    }

    analyzeLog(argv[1], REPORT_FILE);

    return 0;
}

void analyzeLog(char *logFile, char *report) {
      printf("Generating Report from: [%s] log file\n", logFile);

      char *file;
      int fd, i;
      int characters;
      char buffer[1], line[1024];
      int p;
      int upgraded, removed, installed;
      i = upgraded = removed = installed = 0;
      file = logFile;

      fd = open(file, O_RDONLY, 0600);

      if(fd == -1){
            printf("Unreadable");
            exit(1);
      }

      int lastInstalledIndex = 0;
      characters = read(fd, buffer, 1);

      for(;;)
      {
            characters = read(fd, buffer, 1);
            
            if(characters == -1){
                  printf("Error");
                  exit(1);
                  break;
            }
            else if(characters == 0) break;

            if(buffer[0] != '\n'){
                  line[i] = buffer[0];
                  i++;
                 
            }
            else{
                  line[i++] = '\n';
                  line[i] = '\0';
                  i=0;
                  int j=0;
                  char *result;
                  
                  if((result = strstr(line, "installed")) != NULL) {
                        char *doi, *position = strstr(result, " ")+1;
                        char nameOfProgram[64];
                        char dateOfInstall[20];

                        while(position[j] != ' '){
                              nameOfProgram[j] = position[j];
                              j++;
                        }

                        nameOfProgram[j] = '\0';
                        j=0;

                        while(files[j].name[0] != '\0'){
                              if(strcmp(files[j].name, nameOfProgram) == 0) {
                                    j = -1;
                                    break;
                              }
                              
                              j++;
                        }

                        if(j >= 0){
                              strcpy(files[j].name, nameOfProgram);
                              doi = strstr(line, "[")+1;
                              int k=0;

                              while(doi[k] != ']'){
                                    dateOfInstall[k] = doi[k];
                                    k++;
                              }

                              dateOfInstall[k] = '\0';
                              strcpy(files[j].installDate, dateOfInstall);
                              lastInstalledIndex = j;

                        }
                        
                        installed++;  
                  }
                  else if((result = strstr(line, "removed")) != NULL) {
                        char *dor, *position = strstr(result, " ")+1;
                        char nameOfProgram[64];
                        char dateOfRemove[20];
                        
                        while(position[j] != ' '){
                              nameOfProgram[j] = position[j];
                              j++;
                        }
                        nameOfProgram[j] = '\0';
                        j=0;
                        int comparison;

                        while(files[j].name[0] != '\0'){
                              if((comparison = strcmp(files[j].name, nameOfProgram)) == 0) {
                                    break;
                              }

                              j++;
                        }

                        if(comparison == 0){
                              dor = strstr(line, "[")+1;
                              int k=0;

                              while(dor[k] != ']'){
                                    dateOfRemove[k] = dor[k];
                                    k++;
                              }

                              dateOfRemove[k] = '\0';
                              strcpy(files[j].removeDate, dateOfRemove);
                             
                        }
                        
                        removed++;
                  }
                  else if((result = strstr(line, "upgraded")) != NULL) {
                        char *dou, *position = strstr(result, " ")+1;
                        char nameOfProgram[64];
                        char dateOfUpgrade[20];
                        
                        while(position[j] != ' '){
                              nameOfProgram[j] = position[j];
                              j++;
                        }
                        nameOfProgram[j] = '\0';
                        j=0;
                        int comparison;

                        while(files[j].name[0] != '\0'){
                              if((comparison = strcmp(files[j].name, nameOfProgram)) == 0) {
                                    break;
                              }

                              j++;
                        }

                        if(comparison == 0){
                              dou = strstr(line, "[")+1;
                              int k=0;

                              while(dou[k] != ']'){
                                    dateOfUpgrade[k] = dou[k];
                                    k++;
                              }

                              dateOfUpgrade[k] = '\0';
                              strcpy(files[j].upgradeDate, dateOfUpgrade);
                              
                              files[j].upgrades++;
                        }
                        
                        upgraded++;
                     
                  }

            }

      }

      int g;
      for(g = (lastInstalledIndex+1); p<2048; p++){
            files[g].name[0] = '\0';
            files[g].installDate[0] = '\0';
            files[g].upgradeDate[0] = '\0';
            files[g].removeDate[0] = '\0';
            files[g].upgrades = 0;
      }

      if(close(fd) == -1){
            
            printf("Unreadable");
            exit(1);
      }

      file = report;
      fd = open(file, O_CREAT | O_WRONLY, 0600);

      if(fd == -1){
            printf("Unwritable");
            exit(1);
      }

      size_t max_size = 1000;
      char input[max_size];
      int currentInstalled = (installed-removed);
      int j;

      strcpy(input, "Pacman Packages Report\n");
      characters = write(fd, input, strlen(input));

      for(j=0; j<8; j++){

            if(characters == -1){
                        printf("Error");
                        exit(1);
                        break;
            }
            else if(characters == 0) break;

            switch(j){
                  case 0:
                  strcpy(input, "----------------------\n");
                  characters = write(fd, input, strlen(input));
                  break;

                  case 1:
                  snprintf(input, max_size, "- Installed packages : %d\n", installed);
                  characters = write(fd, input, strlen(input));
                  break;

                  case 2:
                  snprintf(input, max_size, "- Removed packages   : %d\n", removed);
                  characters = write(fd, input, strlen(input));
                  break;

                  case 3:
                  snprintf(input, max_size, "- Upgraded packages  : %d\n", upgraded);
                  //input = "- Upgraded packages  : %d\n";
                  characters = write(fd, input, strlen(input));
                  break;

                  case 4:
                  snprintf(input, max_size, "- Current installed  : %d\n", currentInstalled);
                  characters = write(fd, input, strlen(input));
                  break;

                  case 5:
                  strcpy(input, "\n");
                  characters = write(fd, input, strlen(input));
                  break;

                  case 6:
                  strcpy(input, "List of packages\n");
                  characters = write(fd, input, strlen(input));
                  break;

                  case 7:
                  strcpy(input, "----------------\n");
                  characters = write(fd, input, strlen(input));
                  break;
            }

      }

      j=0;

      char upD[20], remD[20];
      int fileArraySize;

      for(fileArraySize=0; fileArraySize<2048; fileArraySize++){
            if(files[fileArraySize].name[0] == '\0') break;
      }
      

      for(j=0; j<fileArraySize; j++){
            if(strlen(files[j].upgradeDate) ==  0){
                  strcpy(upD, "-");
                  upD[1] = '\0';
            }
            else{
                  strcpy(upD, files[j].upgradeDate);
            }

            if(strlen(files[j].removeDate) ==  0){
                  strcpy(remD, "-");
                  remD[1] = '\0';
            }
            else{
                  strcpy(remD, files[j].upgradeDate);
            }

            if(files[j].name[0] != '\0'){
            snprintf(input, max_size, 
            "- Package Name         : %s\n"
            "   - Install date      : %s\n"
            "   - Last update date  : %s\n"
            "   - How many updates  : %d\n"
            "   - Removal date      : %s\n",
               files[j].name, files[j].installDate, upD, files[j].upgrades, remD);
           
            }
            characters = write(fd, input, strlen(input));
            
      }
      

      if(close(fd) == -1){
            printf("Unwritable");
            exit(1);
      }

      printf("Report is generated at: [%s]\n", report);
}
