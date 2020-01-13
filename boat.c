
#include "boat.h"

void iniFleet(gameFleet * fleet)
{
    int TAILLEBATEAUX[NBRBOAT] = {2,3,3,4,5};
    for(int i = 0; i < NBRBOAT; i++)
    {
        fleet->boats[i].length = TAILLEBATEAUX[i];
        fleet->boats[i].facing = up;
        fleet->boats[i].X = -1;
        fleet->boats[i].Y = -1;
    }
}

int placeBoat(gameBoat * boat, gameFleet * fleet, gameMap * gameMap)
{
    int nX, nY;
    printf("Rentrez la position X : ");
    checkInput(&nX, SIZE);

    printf("Rentrez la position Y : ");
    checkInput(&nY, SIZE);

    printf("\n");
    nX -= 1;
    nY -= 1;

    char userInput;
    printf("Orientation du bateau ? (Haut/Gauche/Bas/Droite)(Z/Q/S/D)\n");
    do
    {
        userInput = getch();
    }while(userInput != 'Z' && userInput != 'Q' && userInput != 'S' && userInput != 'D' && userInput != 'z' && userInput != 'q' && userInput != 's' && userInput != 'd');

    switch(userInput)
    {
    case 'Z' :
        boat->facing = up;
        break;
    case 'z' :
        boat->facing = up;
        break;
    case 'Q' :
        boat->facing = left;
        break;
    case 'q' :
        boat->facing = left;
        break;
    case 'D' :
        boat->facing = right;
        break;
    case 'd' :
        boat->facing = right;
        break;
    case 'S' :
        boat->facing = down;
        break;
    case 's' :
        boat->facing = down;
        break;
    }
    printf("%c\n", userInput);

    int verif = 1;
    verif = checkBoat(fleet, boat, nX, nY);
    if(verif)
    {
        boat->X = nX;
        boat->Y = nY;
    }
    else
    {
        printf("Erreur, la case du bateau est prise\n");
        return 0;
    }

    printf("L'emplacement X(%i) Y(%i) est disponible\n\n", nX, nY);
    return 1;
}

int checkBoat(gameFleet * fleet, gameBoat * boat, int X, int Y)
{
    int spaceFree = 1;

    for(int j = 0; j < NBRBOAT; j++)
    {
        printf("Bateau %i X(%i) Y(%i)\n", j, fleet->boats[j].X+1, fleet->boats[j].Y+1);
        for(int i = 0; i < boat->length; i++)
        {
            switch(boat->facing)
            {
            case up:
                if((fleet->boats[j].Y == Y - i && fleet->boats[j].X == X) || Y - i < 0)
                {
                    spaceFree = 0;
                    printf("Collision avec le bateau num %i\n", j);
                }
                break;
            case down:
                if((fleet->boats[j].Y == Y + i && fleet->boats[j].X == X) || Y + i > SIZE)
                {
                    spaceFree = 0;
                    printf("Collision avec le bateau num %i\n", j);
                }
                break;
            case left:
                if((fleet->boats[j].Y == Y && fleet->boats[j].X == X) - i || X - i < 0)
                {
                    spaceFree = 0;
                    printf("Collision avec le bateau num %i\n", j);
                }
                break;
            case right:
                if((fleet->boats[j].Y == Y && fleet->boats[j].X == X + i) || X + i > SIZE)
                {
                    spaceFree = 0;
                    printf("Collision avec le bateau num %i\n", j);
                }
                break;
            default:
                printf("Erreur dans la verification des bateaux. L'oriention du bateau (%i) etait incorrect : %i\n", i+1, boat->facing);
            }
        }
    }

    return spaceFree;
}

void getBoats(int nJoueur, gameFleet * fleet, gameMap * map)
{
    printf("Placement des bateaux du joueur %i\n", nJoueur);
    for(int i = 0; i < NBRBOAT; i++)
    {
        drawBoats(fleet, map);

        printf("Bateau numero %i ( taille %i )\n", i+1, fleet->boats[i].length);

        int nEntry = placeBoat(&fleet->boats[i], fleet, map);

        while(nEntry == 0)
        {
            printf("Veuillez recommencer la saisie :\n");
            nEntry = placeBoat(&fleet->boats[i], fleet, map);
        }
    }
}

void drawBoats(gameFleet * fleet, gameMap * map)
{
    char outputChar = '_';
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
            for(int k = 0; k < NBRBOAT; k++)
            {
               for(int l = 0; l < fleet->boats[k].length; l++)
                {
                if(outputChar  == '_')
                {
                    switch(fleet->boats[k].facing)
                    {
                    case up:
                        if(fleet->boats[k].Y - l == i && fleet->boats[k].X == j)
                        {
                            outputChar = '1' + k;
                        }
                        else
                        {
                            //printf("X %i I %i Y %i J %i\n", fleet->boats[k].Y, i, fleet->boats[k].X, j);
                            outputChar = '_';
                        }
                        break;
                    case down:
                        if(fleet->boats[k].Y + l == i && fleet->boats[k].X == j)
                        {
                            outputChar  = '1' + k;
                        }
                        else
                        {
                            outputChar = '_';
                        }
                        break;
                    case left:
                        if(fleet->boats[k].Y == i && fleet->boats[k].X - l == j)
                        {
                            outputChar = '1' + k;
                        }
                        else
                        {
                            outputChar = '_';
                        }
                        break;
                    case right:
                        if(fleet->boats[k].Y == i && fleet->boats[k].X + l == j)
                        {
                            outputChar = '1' + k;
                        }
                        else
                        {
                            outputChar = '_';
                        }
                        break;
                    default:
                        printf("Erreur dans la verification des bateaux. L'oriention du bateau (%i) etait incorrect : %i\n", i+1, fleet->boats[k].facing);
                    }
                }
            }
            }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if(map->tGame[i][j] == hit)
            SetConsoleTextAttribute(hConsole, 12);

        printf("%c  ", outputChar);
        SetConsoleTextAttribute(hConsole, 7);
        outputChar = '_';
        }
    printf("\n");
    }
}

