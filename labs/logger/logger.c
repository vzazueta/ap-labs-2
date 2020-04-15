#include <stdio.h>
#include <stdarg.h>	
#include <stdlib.h>
#include <signal.h>

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

void textcolor(int attr, int fg, int bg)
{	char command[13];

	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int infof(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, BLUE, BLACK);
	vprintf(format, arg);
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	

	return 4;
}

int warnf(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, YELLOW, BLACK);
	vprintf(format, arg);
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	

	return 5;
}

int errorf(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, RED, BLACK);
	vprintf(format, arg);
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	

	return 6;
}

int panicf(char *format, ...){
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, WHITE, RED);
	vprintf(format, arg);
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);		
	fflush(stdout);
	raise(SIGABRT);
	
	return 666;
}
