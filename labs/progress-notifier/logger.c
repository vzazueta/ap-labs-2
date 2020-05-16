#include <stdio.h>
#include <stdarg.h>	
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>

#define RESET		0
#define BRIGHT 		1
#define DIM			2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED			1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define WHITE		7

int logTypeBoolean = 0;

void textcolor(int attr, int fg, int bg)
{	char command[13];

	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int initLogger(char *logType) {
	
	if((strcmp(logType, "stdout") == 0) || (strcmp(logType, "") == 0)){
		printf("Initializing Logger on: %s\n", "stdout");
		logTypeBoolean = 0;    
	} else if(strcmp(logType, "syslog") == 0){
		printf("Initializing Logger on: %s\n", "syslog");
		logTypeBoolean = 1;    
	} else {
		printf("Incorrect log type");
	}
    	
	
}

int infof(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, BLUE, BLACK);
	
	if(logTypeBoolean == 0){
		vprintf(format, arg);
	} else if(logTypeBoolean == 1){
		vsyslog(LOG_INFO, format, arg);
	}

	textcolor(RESET, WHITE, BLACK);	
	va_end(arg);

	return 4;
}

int warnf(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, YELLOW, BLACK);
	
	if(logTypeBoolean == 0){
		vprintf(format, arg);
	} else if(logTypeBoolean == 1){
		vsyslog(LOG_WARNING, format, arg);
	}
	
	textcolor(RESET, WHITE, BLACK);
      va_end(arg);

	return 5;
}

int errorf(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, RED, BLACK);
	
	if(logTypeBoolean == 0){
		vprintf(format, arg);
	} else if(logTypeBoolean == 1){
		vsyslog(LOG_ERR, format, arg);
	}
	
	textcolor(RESET, WHITE, BLACK);
      va_end(arg);	

	return 6;
}

int panicf(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, WHITE, RED);
	
	if(logTypeBoolean == 0){
		vprintf(format, arg);
            fflush(stdout);
	} else if(logTypeBoolean == 1){
		vsyslog(LOG_EMERG, format, arg);
            //fflush(syslog);
	}
	
	textcolor(RESET, WHITE, BLACK);
      va_end(arg);	

      raise(SIGABRT);

	return 666;
}
