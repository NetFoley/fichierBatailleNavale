#include "gameMap.h"

int drawMap(gameMap * gameMap, gameFleet * fleet)
{
    int nHit = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = -1; i < SIZE; i++)
    {
        for(int j = -1; j < SIZE; j++)
        {
            if(i == -1)
            {
                if(j < 10)
                    printf("%i  ", j+1);
                else
                {
                    printf("%i ", j+1);
                }
                    continue;
            }
            if(j == -1)
            {
                if(i < 10)
                    printf("%i  ", i+1);
                else
                {
                    printf("%i ", i+1);
                }
                    continue;
            }
            switch(gameMap->tGame[i][j])
            {
            case hit:
                if(checkShoot(j, i, fleet))
                {
                    SetConsoleTextAttribute(hConsole, 10);
                    nHit++;
                }
                else
                    SetConsoleTextAttribute(hConsole, 12);
                printf("X  ");
                SetConsoleTextAttribute(hConsole, 7);
                break;

            default :
                printf("_  ");
            }
        }
        printf("\n");
    }
    printf("\n");
    return nHit;
}

int checkShoot(int X, int Y, gameFleet * fleet)
{
    int touche = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < NBRBOAT; k++)
            {
                for(int l = 0; l < fleet->boats[k].length; l++)
                {
                    switch(fleet->boats[k].facing)
                    {
                    case up:
                        if(fleet->boats[k].Y - l == Y && fleet->boats[k].X == X)
                        {
                            touche = 1;
                        }
                        break;
                    case down:
                        if(fleet->boats[k].Y + l == Y && fleet->boats[k].X == X)
                        {
                            touche = 1;
                        }
                        break;
                    case left:
                        if(fleet->boats[k].Y == Y && fleet->boats[k].X - l == X)
                        {
                            touche = 1;
                        }
                        break;
                    case right:
                        if(fleet->boats[k].Y == Y && fleet->boats[k].X + l == X)
                        {
                            touche = 1;
                        }
                        break;
                    default:
                        printf("Erreur dans la verification des bateaux. L'oriention du bateau (%i) etait incorrect : %i\n", i+1, fleet->boats[k].facing);
                    }
                }
            }
        }
    }
    return touche;
}

void checkInput(int * nUserInput, int maxSize)
{
    fflush(stdin);
    scanf("%i", nUserInput);

	int isNumber = 1;
	if(*nUserInput < 1 || *nUserInput > maxSize)
		isNumber = 0;

    while(isNumber==0)
    {
        fflush(stdin);
        printf("Entree incorrect (%i), entrez un nombre valide en 1 et %i.\n", *nUserInput, maxSize);
        scanf("%i", nUserInput);
        if(*nUserInput >= 1 || *nUserInput <= maxSize)
            isNumber = 1;
    }
}

void iniGameMap(gameMap * gameMap, int maxSize)
{
    for(int i = 0; i < maxSize; i++)
    {
        for(int j = 0; j < maxSize; j++)
        {
            gameMap->tGame[i][j] = empty;
        }
    }
}

