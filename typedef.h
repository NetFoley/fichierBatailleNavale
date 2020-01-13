#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED


typedef enum facing{up, left, down, right, }facing;

typedef struct gameBoat{
	int X;
	int Y;
	facing facing;
	int length;
}gameBoat;

typedef struct gameFleet{
    gameBoat boats[NBRBOAT];
}gameFleet;

typedef enum pixel{empty, hit}pixel;

typedef struct gameMap{
	pixel tGame[SIZE][SIZE];
}gameMap;

typedef struct bigGame{
    gameFleet fleet1;
    gameFleet fleet2;
    gameMap map1;
    gameMap map2;
}bigGame;

#endif // TYPEDEF_H_INCLUDED
