#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>
#include <windows.h>

#include "boat.h"
#include "typedef.h"

void iniGameMap(gameMap * gameMap, int maxSize);
void checkInput(int * nUserInput, int maxSize);
int checkShoot(int X, int Y, gameFleet * fleet);
int drawMap(gameMap * gameMap, gameFleet * fleet);

#endif // GAMEMAP_H_INCLUDED
