#include <stdio.h>
#include <stdlib.h>

void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char **argv) {
    int month, day;
    int year = strtol(argv[1], NULL, 10), yearday = strtol(argv[2], NULL, 10);
    char *monthName;
    char *namesOfMonths[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    month_day(year, yearday, &month, &day);

    monthName = namesOfMonths[month];

    printf("%s %d, %d\n", monthName, day, year);

    return 0;
}

void month_day(int year, int yearday, int *pmonth, int *pday){
    int leap = (year%4 == 0) && (year%100 != 0) || (year%400 == 0);
    int month, day, i;
    int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(leap){
      daysInMonths[1] += 1;
      
      for(i=0; i<12; i++){
        if(yearday <= daysInMonths[i]) {
          break;
        }
        yearday -= daysInMonths[i];
      }
    }
    else{
      for(i=0; i<12; i++){
        if(yearday <= daysInMonths[i]) {
          break;
        }
        yearday -= daysInMonths[i];
      }
    }
    
    *pday = yearday;
    *pmonth = i;
}
