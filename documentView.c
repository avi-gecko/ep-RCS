#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "inputFunc.h"
#include "documentView.h"
#include "fileMenu.h"
#include "structs.h"

unsigned int numOfEnt = 0;
unsigned int numOfDict_T = 0;
unsigned int numOfDict_P = 0;
DATA *data = NULL;
DICT_P *dict_p = NULL;
DICT_T *dict_t = NULL;
MAIN_DATA *main_data = NULL;
static FILE *in = NULL, *fDict_T = NULL, *fDict_P = NULL;

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
    if ((fDict_T = fopen("./DICTIONARY/type.db", "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if ((fDict_P = fopen("./DICTIONARY/place.db", "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
}

void createData()
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
}

void createDict_T()
{
    if (!numOfDict_T)
    {
        while (!feof(fDict_T))
            if (getc(fDict_T) == '\n')
                numOfDict_T++;
        rewind(fDict_T);
    }
    unsigned int i = 0;
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    dict_t = (DICT_T *) malloc(sizeof(DICT_T) * numOfDict_T);
    while ((read = getline(&temp, &len, fDict_T)) != EOF)
    {
        dict_t[i].id = atoi(strtok(temp, ";"));
        dict_t[i].dictName = strtok(NULL, ";");
        temp = NULL;
        i++;
    }
    fclose(fDict_T);
}

void createDict_P()
{
    if (!numOfDict_P)
    {
        while (!feof(fDict_P))
            if (getc(fDict_P) == '\n')
                numOfDict_P++;
        rewind(fDict_P);
    }
    unsigned int i = 0;
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    dict_p = (DICT_P *) malloc(sizeof(DICT_P) * numOfDict_P);
    while ((read = getline(&temp, &len, fDict_P)) != EOF)
    {
        dict_p[i].id = atoi(strtok(temp, ";"));
        dict_p[i].dictName = strtok(NULL, ";");
        temp = NULL;
        i++;
    }
    fclose(fDict_P);
}

void creatMain_Data()
{
    unsigned int i;
    unsigned int j;
    main_data = (MAIN_DATA *) malloc(sizeof(MAIN_DATA) * numOfEnt);
    for (i = 0; i < numOfEnt; i++)
    {
        main_data[i].id = data[i].id;
        main_data[i].codeItem = data[i].codeItem;
        for (j = 0; j < numOfDict_T; j++)
            if (data[i].idType == dict_t[j].id)
            {
                main_data[i].type = dict_t[j].dictName;
                break;
            }
        for (j = 0; j < numOfDict_P; j++)
            if (data[i].idPlace == dict_p[j].id)
            {
                main_data[i].place = dict_p[j].dictName;
                break;
            }
        main_data[i].date = data[i].date;
        main_data[i].cost = data[i].cost;
    }
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
        createData();
    if (!dict_t)
        createDict_T();
    if (!dict_p)
        createDict_P();
    if (!main_data)
        creatMain_Data();
    system("clear");
    for (unsigned int i = 0 ; i < numOfEnt; i++)
        printf("| %-5d | %6s |\t %-25s \t| %-12s \t| %8s | %8d |\n", main_data[i].id, main_data[i].codeItem, main_data[i].type, main_data[i].place, main_data[i].date, main_data[i].cost);
    wait();
}
