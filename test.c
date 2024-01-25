#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{

    time_t rawtime;
    struct tm *timeinfo_1, *timeinfo_2;

    time(&rawtime);
    timeinfo_1 = localtime(&rawtime);
    printf("Current local time  %d:%d",timeinfo_1->tm_hour,timeinfo_1->tm_min);
  
    return 0;
}