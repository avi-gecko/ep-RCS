#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H
#include "structs.h"

extern unsigned int numOfEnt;
extern unsigned int numOfDict_T;
extern unsigned int numOfDict_P;
extern DATA *data;
extern DICT_T *dict_t;
extern DICT_P *dict_p;
extern MAIN_DATA *main_data;

void showDoc();
void createData();
void openDoc();
void createDict_P();
void createDict_T();
void creatMain_Data();

#endif // DOCUMENTVIEW_H
