#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H
#include "structs.h"

extern unsigned int numOfEnt;
extern unsigned int numOfDict_T;
extern unsigned int numOfDict_P;
extern DATA *headData;
extern DICT_T *headDict_t;
extern DICT_P *headDict_p;
extern MAIN_DATA *headMain_data;
extern FILE *in, *fDict_T, *fDict_P;

void showDoc();
void createData();
void createDict_P();
void createDict_T();
void createMain_Data();
void putData(unsigned int, char *, unsigned int, unsigned int, char *, unsigned int);
void putDict_T(unsigned int, char *);
void putDict_P(unsigned int, char *);
void putMain_Data(unsigned int, char *, char *, char *, char *, unsigned int);
void matchItem(unsigned int, unsigned int, char **, char **);
void openFDict_P();
void openFDict_T();
void openIn();

#endif // DOCUMENTVIEW_H
