#ifndef BOAT_H_INCLUDED
#define BOAT_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>
#include <windows.h>

#define SIZE 13
#define NBRBOAT 5

#include "gameMap.h"
#include "typedef.h"

void iniFleet(gameFleet * fleet);
void drawBoats(gameFleet * fleet, gameMap * map);
int placeBoat(gameBoat * boat, gameFleet * fleet, gameMap * gameMap);
void getBoats(int nJoueur, gameFleet * fleet, gameMap * map);
int checkBoat(gameFleet * fleet, gameBoat * boat, int X, int Y);

#endif // BOAT_H_INCLUDED
