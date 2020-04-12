#include <stdio.h>
#include <stdarg.h>	
#include <stdlib.h>

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

char *convert(unsigned int num, int base) { 
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50]; 
	char *ptr; 
	
	ptr = &buffer[49]; 
	*ptr = '\0'; 
	
	do { 
		*--ptr = Representation[num%base]; 
		num /= base; 
	} while(num != 0); 
	
	return(ptr); 
}

int infof(char *format, ...){
	char *traverse, *s;
      int i;
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, BLUE, BLACK);

	for(traverse = format; *traverse != '\0'; traverse++) { 
		while(*traverse != '%') { 
	      	//printf("%c", *traverse);
			putchar(*traverse);
			traverse++; 
		} 
		
		traverse++; 

		switch(*traverse) { 
		      case 'c' : i = va_arg(arg, int);
					//if(i == -2147483648) return -1;
				      putchar(i);
				      break; 
						
			case 'd' : i = va_arg(arg, int); 
					//if(i == -2147483648) return -1;
					
					if(i<0) { 
				      	i = -i;
					      putchar('-');
					} 
					puts(convert(i, 10));
					break; 
						
			case 'o': i = va_arg(arg, unsigned int);
					//if(i == -2147483648) return -1;
					printf("%o", convert(i,8));
					break; 
						
			case 's': s = va_arg(arg, char *);
					//if(i == -2147483648) return -1;
					printf("%s", s); 
					break; 
						
			case 'x': i = va_arg(arg, unsigned int);
					//if(i == -2147483648) return -1; 
					printf("%x", convert(i,16));
					break; 
		}
      }
      
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	

	return 4;
}

int warnf(char *format, ...){
	char *traverse, *s;
      int i;
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, YELLOW, BLACK);

	for(traverse = format; *traverse != '\0'; traverse++) { 
	      while(*traverse != '%') { 
	      	//printf("%c", *traverse);
			putchar(*traverse);
			traverse++; 
		} 
		
		traverse++; 

		switch(*traverse) { 
		      case 'c' : i = va_arg(arg, int);
				      putchar(i);
				      break; 
						
			case 'd' : i = va_arg(arg, int); 
					if(i<0) { 
				      	i = -i;
					      putchar('-');
					} 
					puts(convert(i, 10));
					break; 
						
			case 'o': i = va_arg(arg, unsigned int);
					printf("%o", convert(i,8));
					break; 
						
			case 's': s = va_arg(arg, char *);
					printf("%s", s); 
					break; 
						
			case 'x': i = va_arg(arg, unsigned int); 
					printf("%x", convert(i,16));
					break; 
	      }	
      }
      
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	


	return 5;
}

int errorf(char *format, ...){
	char *traverse, *s;
      int i;
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, RED, BLACK);

	for(traverse = format; *traverse != '\0'; traverse++) { 
	      while(*traverse != '%') { 
	      	//printf("%c", *traverse);
			putchar(*traverse);
			traverse++; 
		} 
		
		traverse++; 

		switch(*traverse) { 
		      case 'c' : i = va_arg(arg, int);
				      putchar(i);
				      break; 
						
			case 'd' : i = va_arg(arg, int); 
					if(i<0) { 
				      	i = -i;
					      putchar('-');
					} 
					puts(convert(i, 10));
					break; 
						
			case 'o': i = va_arg(arg, unsigned int);
					printf("%o", convert(i,8));
					break; 
						
			case 's': s = va_arg(arg, char *);
					printf("%s", s); 
					break; 
						
			case 'x': i = va_arg(arg, unsigned int); 
					printf("%x", convert(i,16));
					break; 
	      }	
      }
      
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	


	return 6;
}

int panicf(char *format, ...){
	char *traverse, *s;
      int i;
      va_list arg; 
	va_start(arg, format);
	textcolor(BRIGHT, WHITE, RED);

	for(traverse = format; *traverse != '\0'; traverse++) { 
	      while(*traverse != '%') {
			putchar(*traverse);
			traverse++; 
		} 
		
		traverse++; 

		switch(*traverse) { 
		      case 'c' : i = va_arg(arg, int);
				      putchar(i);
				      break; 
						
			case 'd' : i = va_arg(arg, int); 
					if(i < 0) { 
				      	i = -i;
					      putchar('-');
					} 
					puts(convert(i, 10));
					break; 
						
			case 'o': i = va_arg(arg, unsigned int);
					printf("%o", convert(i,8));
					break; 
						
			case 's': s = va_arg(arg, char *);
					printf("%s", s); 
					break; 
						
			case 'x': i = va_arg(arg, unsigned int); 
					printf("%x", convert(i,16));
					break; 
	      }	
      }
      
      va_end(arg);
	textcolor(RESET, WHITE, BLACK);	


	return 666;
}
