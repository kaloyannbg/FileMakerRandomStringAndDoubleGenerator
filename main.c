#include "includes.h"

char *makeRandomString()
{
    int randomStringLen = rand() % MAX_RANDOM_NUMBER; // from 0 to 19
    int randomN = 0;
    char *randStr = malloc(randomStringLen + 1);

    randomStringLen = randomStringLen < 6 ? randomStringLen = 6 : randomStringLen;

    for (int i = 0; i < randomStringLen; i++)
    {
        randomN = rand() % ENGLISH_ALPHABET_COUNT; // random
        randStr[i] = randomN + ASCII_A_CHAR;
    }
    randStr[e_zeroPos] = toupper(randStr[e_zeroPos]);
    randStr[randomStringLen] = TERMINATION_ZERO;
    return randStr;
}

char *makeRandomDoubleString()
{
    int randomPosBeforeDot = rand() % MAX_RANDOM_DOUBLE_NUM; // from 0 to 5

    randomPosBeforeDot = randomPosBeforeDot < MAX_NUMBERS_BEFORE_DOT ? MAX_NUMBERS_BEFORE_DOT : randomPosBeforeDot;

    char *randStr = malloc(randomPosBeforeDot + e_totalPos); // WE COUNT THE DOT, TWO NUMBERS AFTER DOT AND TERMINATION \0 ,

    for (int i = 0; i < randomPosBeforeDot; i++)
    {
        randStr[i] = (rand() % 10) + '0';
    }

    randStr[e_zeroPos] = randStr[e_zeroPos] == '0' ? randStr[e_zeroPos] = '9' : randStr[e_zeroPos];

    randStr[randomPosBeforeDot] = DOT;

    int afterDot = randomPosBeforeDot + e_firstPosAfterDot, endAfterDot = randomPosBeforeDot + e_lastPos;

    for (int i = afterDot; i < endAfterDot; i++)
    {
        randStr[i] = (rand() % MAX_TEN) + '0';
    }

    randStr[endAfterDot] = TERMINATION_ZERO;

    return randStr;
}

void putInFileTwo(int inputRepeats, char *fName, char *fName2, int flag)
{
    char *randomStr = NULL, *randomDouble = NULL;

    char fullFileName[64] = {0};

    char fullFileName2[64] = {0};

    sprintf(fullFileName, "%s_%d.TXT", fName, inputRepeats);

    sprintf(fullFileName2, "%s_%d.TXT", fName2, inputRepeats);

    FILE *fpToInvoicesWTF = fopen(fullFileName, "r");
    FILE *fpToSecond = fopen(fullFileName2, "w");

    if (fpToSecond == NULL || fpToInvoicesWTF == NULL)
    {
        printf(" -- You have problem with file: %s or %s -- ", fName, fName2);
        exit(1);
    }

    if (flag == 1)
    {

        int halfLen = inputRepeats / 2;
        char buffer[128] = {0};
        char *fileGets = fgets(buffer, 128, fpToInvoicesWTF);
        int i = 1;
        char *token = strtok(buffer, ";");

        randomDouble = makeRandomDoubleString();
        fprintf(fpToSecond, "%s;%s", token, randomDouble);

        while (halfLen > i)
        {
            fileGets = fgets(buffer, 128, fpToInvoicesWTF);
            token = strtok(buffer, ";");
            randomDouble = makeRandomDoubleString();
            fprintf(fpToSecond, "\n%s;%s", token, randomDouble);
            i++;
        }

        fclose(fpToInvoicesWTF);

        fseek(fpToSecond, 0, SEEK_END);
        i = 0;
        halfLen = inputRepeats % 2 != 0 ? halfLen + 1 : halfLen;

        while (halfLen > i)
        {
            randomStr = makeRandomString();
            randomDouble = makeRandomDoubleString();
            fprintf(fpToSecond, "\n%s;%s", randomStr, randomDouble);
            i++;
        }
    }
    else if (flag == 2)
    {
        randomStr = makeRandomString();
        randomDouble = makeRandomDoubleString();
        fprintf(fpToSecond, "%s;%s", randomStr, randomDouble);

        int countRepeat = 1;
        while (countRepeat < inputRepeats)
        {
            randomStr = makeRandomString();
            randomDouble = makeRandomDoubleString();
            fprintf(fpToSecond, "\n%s;%s", randomStr, randomDouble);
            countRepeat++;
        }
    }
    fclose(fpToSecond);
    fclose(fpToInvoicesWTF);
    free(randomDouble);
    free(randomStr);
}

void putRandomStringsAndDoublesInFiles(char *fName, char *fName2, int inputRepeats, int flag)
{

    char *randomStr = NULL, *randomDouble = NULL;

    char fullFileName[64] = {0};

    sprintf(fullFileName, "%s_%d.TXT", fName, inputRepeats);

    FILE *fpToInvoices = fopen(fullFileName, "w");

    if (fpToInvoices == NULL)
    {
        printf(" -- You cant open file. -- ");
        exit(1);
    }
    randomStr = makeRandomString();
    randomDouble = makeRandomDoubleString();
    fprintf(fpToInvoices, "%s;%s", randomStr, randomDouble);

    int countRepeat = 1;
    while (countRepeat < inputRepeats)
    {
        randomStr = makeRandomString();
        randomDouble = makeRandomDoubleString();
        fprintf(fpToInvoices, "\n%s;%s", randomStr, randomDouble);
        countRepeat++;
    }
    fclose(fpToInvoices);
    free(randomDouble);
    free(randomStr);
    putInFileTwo(inputRepeats, fName, fName2, flag);
}

int getInt()
{
    char buffer[128] = {0};
    fgets(buffer, 128, stdin);
    return atoi(buffer);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    system("cls");
    printf(" *********************************************\n");
    printf(" ***   GENERATE FILES FROM RANDOM VALUES   ***\n");
    printf(" ***  GENERATE STRINGS WITH DOUBLE NUMBERS ***\n");
    printf(" ***          KALOYAN ANGELOV              ***\n");
    printf(" *********************************************\n\n");

    printf(" ** Enter rows: ");

    int inputRepeats = getInt();

    while (inputRepeats <= 1)
    {
        printf(" -- Please, enter valid rows number bigger than 1: ");
        inputRepeats = getInt();
    }

    printf("\n ** IMPORTANT: ALL DOUBLE VALUES IS RANDOM!!! ** \n");
    printf("\n ** Do you want to copy 50%% of NAMES from file: %s to %s? \n", FILE_INVOICES_NAME, FILE_PAYMENTS_NAME);
    printf("\n ** 1. Yes \n");
    printf(" ** 2. No \n\n");
    printf(" -- Enter 1 or 2: ");

    int choiceBetweenCopyOrNot = getInt();

    while (choiceBetweenCopyOrNot != 1 && choiceBetweenCopyOrNot != 2)
    {
        printf(" -- Enter 1 or 2: ");
        choiceBetweenCopyOrNot = getInt();
    }

    putRandomStringsAndDoublesInFiles(FILE_INVOICES_NAME, FILE_PAYMENTS_NAME, inputRepeats, choiceBetweenCopyOrNot);

    printf("\n *** Your files are created sucesfully *** \n\n *** ");

    system("pause");

    return 0;
}