#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char empty[255];

int readFile(FILE *file, char data[],int maxLines) {
    int maxStreamLen = 1024 * 5 ;
    int lineCount = 0;
    if (file == NULL)
    {
        return 1;
    }
    char buff[2048];
    while (fgets(buff, 255, file) !=NULL)
    {
        lineCount++;
        if (lineCount > maxLines) {
            break;
        }
        if(strlen(data)>=maxStreamLen){
            printf("WARNING: max stream length %d exceeded... reader shall exit");
            break;
            return 0;
        }
        strcat(data, buff);
    }

    return 0;
}

int main () {
    int maxQLength = 20;
    char questionsDir[] = "data/questions.txt";
    char schemeDir[] = "data/qscheme.txt";
    char qoptionsDir[] = "data/qoptions.txt";
    char optCharIndexes[] = "ABCDE";
    char questions [20][64] = {};
    char options[20][5][64] ={};
    char scheme[20];
    int score = 0;
    int qSize = sizeof(questions)/sizeof(questions[1]);
    FILE *qquestionsFile = fopen(questionsDir,"r");
    FILE *qoptionsFile = fopen(qoptionsDir,"r");
    FILE *qschemeFile = fopen(schemeDir,"r");
    if(qquestionsFile==NULL||qoptionsFile==NULL||qschemeFile==NULL){
        printf("Incomplete assets... Please ensure all 3 [%s & %s & %s] files exist.", questionsDir, qoptionsDir, schemeDir);
        exit(1);
    }
    char tempQ[1024*5] = "";
    char tempO[1024*5] = "";
    int qReadStatus = readFile(qquestionsFile, tempQ,20);
    int oReatStatus=readFile(qoptionsFile, tempO,20);
    int sReadStatus=readFile(qschemeFile, scheme, 1);
    if (qReadStatus + oReatStatus + sReadStatus > 0)
    {
        printf("Read data files failed... exiting.");
        exit(1);
    }
    char buff[255] = "";
    int charCount = 0;
    int qCount = 0;

    // Questions To Array
    for (int i = 0; i < sizeof(tempQ); i++) {
        if (tempQ[i] == '\n') {
            continue;  
        }
        buff[charCount] = tempQ[i];
        buff[charCount+1] = '\0';
        charCount++;
        // printf("%c", tempQ[i]);
        if (tempQ[i] == ',' || charCount > 64) {
            charCount = 0;
            if(!strlen(buff)){
                maxQLength = qCount;
                qSize = qCount;
                break;
            }
            strcpy(questions[qCount],buff);
            strcpy(buff,"");
            qCount++;
            if (qCount>maxQLength||(!tempQ[i]&&!tempQ[i+1]&&!tempQ[i+2])){
                break;
            }
        }
        qSize = sizeof(questions) / sizeof(questions[1]);
    }

    qCount = 0;
    charCount = 0;
    int optCount = 0;
    char optBuff[64]="";
    for (int i = 0; i < strlen(tempO); i++) {
        if (tempO[i] == ',' || charCount >= 64) {
            strcpy(options[qCount][optCount], optBuff);
            optBuff[0] = '\0';
            optCount++;
            charCount = 0;
            continue;
        }
        if (tempO[i] == ';'||optCount>sizeof(optCharIndexes)) {
            strcpy(options[qCount][optCount], optBuff);
            qCount++;
            charCount = 0;
            optCount = 0;
            continue;
        }
        if (qCount>maxQLength)
        {
            break;
        }
        if(tempO[i]=='\n') {
            continue;
        }
        optBuff[charCount] = tempO[i];
        optBuff[charCount + 1] = '\0';
        
        charCount++;
    }
    qCount = 0;
    charCount = 0;

    for (int i = 0; i < qSize; i++) {
        if (!strlen(questions[i])){
            qSize = i;
            break;
        }
        printf("***********************************\n");
        printf("%d. %s\n", i+1, questions[i]);
        for (int j = 0; j < sizeof(options[0])/sizeof(options[0][0]); j++) {
            if(!strlen(options[i][j])){
                break;
            }
            printf("(%c): %s\n", optCharIndexes[j], options[i][j]);
        }
        printf(": ");
        char uInput[]="F";
        scanf("%s",uInput);
        // scanf("%c");
        if (toupper(scheme[i]) == toupper(uInput[0]))
        {
            printf("**|  %c %s %c |**",toupper(scheme[i]),"👍",toupper(uInput[0]));
            score++;
        }
        else
        {
            if(uInput[0]=='k' || uInput[0]=='q'){
                printf("Terminating process...\n");
                qSize = i;
                break;
            }
            printf("**|  %c %s %c |**",toupper(scheme[i]),"👎",toupper(uInput[0]));
        }
        printf("\n");
    }
    printf("***********************************\n\n");
    printf("You scored: %d/%d",score,qSize);
    printf("\n\n***********************************\n");
    return 0;
}

