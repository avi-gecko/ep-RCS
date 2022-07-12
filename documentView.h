#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H
#include "structs.h"

extern unsigned int numOfEnt;
extern DATA *data;
extern FILE *in, *dictT, *dictP;

void showDoc();
void createStruct();
void openDoc();


#endif // DOCUMENTVIEW_H
