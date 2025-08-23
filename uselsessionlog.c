#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int readFile(FILE *file, char data[]) {
    int maxStreamLen = 1024 * 10 ;
    if (file == NULL)
    {
        return 1;
    }
    char buff[2048];
    while (fgets(buff, 255, file) !=NULL)
    {   
        if(strlen(data)>=maxStreamLen){
            printf("WARNING: max stream length %d exceeded... reader shall exit");
            break;
            return 0;
        }
        strcat(data, buff);
    }

    return 0;
}

int main (){
    char fileDir[] = "session.log";
    FILE *logFile = fopen(fileDir, "r");
    char fdat[10024];
    if (readFile(logFile, fdat) == 0 ){
        printf("%s\n", fdat);
    } else {
        char choice[4]="y";
        char y[4] = "y";
        printf("No such file or directory... Do you want to create file(y/n)? ");
        scanf("%s", choice);
        if (choice[0] == y[0])
        {
            FILE *initLogFile = fopen(fileDir, "w");
            printf("Creating file: %s\n",fileDir);
            fprintf(initLogFile,"SESSION LOG:");
            fclose(initLogFile);
            printf("%s created\n",fileDir);
        }
        else
        {
            printf("Process terminated");
        }
    }
    fclose(logFile);
    return 0;
}