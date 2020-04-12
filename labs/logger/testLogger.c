#include <stdio.h>

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char *argv){
      infof("Hola %s %s A00%d", "Victor", "Zazueta", 226702);
      warnf("Hola %s %s A00%d", "Victor", "Zazueta", 226702);
      errorf("Hola %s %s A00%d", "Victor", "Zazueta", 226702);
      panicf("Hola %s %s A00%d", "Victor", "Zazueta", 226702);
}
