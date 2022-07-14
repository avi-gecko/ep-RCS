#include <stdio.h>
#include "inputFunc.h"
#include <string.h>

void clearBuff()
{
    while (getchar() != '\n');
}

void wait()
{
    char keyPressed = 0;
    while (scanf("%c", &keyPressed) == 1 && keyPressed != '\n');
}

void clearLine(char **line)
{
    *line[strcspn(*line, "\n")] = '\0';
}
