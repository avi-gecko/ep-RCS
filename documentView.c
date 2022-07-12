#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "inputFunc.h"
#include "documentView.h"
#include "fileMenu.h"
#include "structs.h"

unsigned int numOfEnt = 0;
DATA *data = NULL;
FILE *in = NULL, *dictT = NULL, *dictP = NULL;

void openDoc()
{

    char path[256] = "./DATA/";
    strcat(path, choosedFile->dirItemName);
    if ((in = fopen(path, "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if ((dictT = fopen("./DICTIONARY/type.db", "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if ((dictP = fopen("./DICTIONARY/place.db", "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
}

void createStruct()
{
    if (!numOfEnt)
    {
        while (!feof(in))
            if (getc(in) == '\n')
                numOfEnt++;
        rewind(in);
    }
    unsigned int i = 0;
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    data = (DATA *) malloc(sizeof(DATA) * numOfEnt);
    while ((read = getline(&temp, &len, in)) != EOF)
    {
        data[i].id = atoi(strtok(temp, ";"));
        data[i].codeItem = strtok(NULL, ";");
        data[i].idType = atoi(strtok(NULL, ";"));
        data[i].idPlace = atoi(strtok(NULL, ";"));
        data[i].date = strtok(NULL, ";");
        data[i].cost = atoi(strtok(NULL, ";"));
        temp = NULL;
        i++;
    }
    fclose(in);
    fclose(dictT);
    fclose(dictP);
}

void showDoc()
{
    if (choosedFile)
        openDoc();
    else
    {
        system("clear");
        printf("файл не выбран. Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if (!data)
        createStruct();
    system("clear");
    for (unsigned int i = 0 ; i < numOfEnt; i++)
        printf("%d %s %d %d %s %d\n", data[i].id, data[i].codeItem, data[i].idType, data[i].idPlace, data[i].date, data[i].cost);
    wait();

}
