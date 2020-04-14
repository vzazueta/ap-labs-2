#include <stdio.h>

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char *argv){
      infof("\nHola %s %s A00%dTu calificacion es: %f", "Victor", "Zazueta", 226702, 99.9999);
      warnf("\n\nHola %s %s A00%dTu calificacion es: %f", "Victor", "Zazueta", 226702, 99.9999);
      errorf("\n\nHola %s %s A00%dTu calificacion es: %f", "Victor", "Zazueta", 226702, 99.9999);
      panicf("\n\nHola %s %s A00%dTu calificacion es: %f", "Victor", "Zazueta", 226702, 99.9999);
      printf("\n\n");
}
