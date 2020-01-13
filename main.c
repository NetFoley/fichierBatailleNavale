#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>
#include <windows.h>

#include "boat.h"
#include "gameMap.h"

/*bataille naval
2 joueurs
ascii
enregistrer les résultats des parties dans un fichier en binaire*/



int main()
{
    char cUserInput;

    printf("Bataille naval\n P : jouer une partie\n S: voir les scores\n Q : quitter le jeu\n\n");
	do
	{
		cUserInput = getch();
	}while(cUserInput != 'p' && cUserInput != 'q' && cUserInput != 's' && cUserInput != 'P' && cUserInput != 'Q' && cUserInput != 'S');


	if(cUserInput == 'p' || cUserInput == 'P')
	{
	    printf("La partie commence\n");
		int play = 1;
        int turn = -1;
        int replay = 0;
        gameFleet P1Boats;
        gameFleet P2Boats;

        gameMap P1GameMap;
        gameMap P2GameMap;

        iniGameMap(&P1GameMap, SIZE);
        iniGameMap(&P2GameMap, SIZE);

        iniFleet(&P1Boats);
        iniFleet(&P2Boats);

        getBoats(1, &P1Boats, &P1GameMap);

        system("cls");

        getBoats(2, &P2Boats, &P2GameMap);

        int nHit1 = 0;
        int nHit2 = 0;
		while(play && nHit1 < 2+3+3+4+5 && nHit2 < 2+3+3+4+5)
		{
		    int userInputX;
		    int userInputY;
		    if(replay == 0)
            {
                turn++;
                userInputX = 0;
                userInputY = 0;
                system("cls");
                printf("Joueur %i\n", turn%2+1);
                getch();
            }
            replay = 0;
			if(turn % 2)
            {
                nHit1 = drawMap(&P1GameMap, &P1Boats);
                drawBoats(&P1Boats, &P2GameMap);

                printf("Tour de joueur %i, ou tirer en X ? ", turn%2+1);
                checkInput(&userInputX, SIZE);

                printf("Tour de joueur %i, ou tirer en Y ? ", turn%2+1);
                checkInput(&userInputY, SIZE);
                userInputX -= 1;
                userInputY -= 1;

                P1GameMap.tGame[userInputY][userInputX] = hit;
                if(checkShoot(userInputX, userInputY, &P2Boats))
                {
                    printf("TOUCHE ! Vous pouvez rejouer !\n");
                    replay = 1;
                }

            }
            else
            {
                nHit2 = drawMap(&P2GameMap, &P2Boats);
                drawBoats(&P2Boats, &P1GameMap);

                printf("Tour de joueur %i, ou tirer en X ?", turn%2+1);
                checkInput(&userInputX, SIZE);

                printf("Tour de joueur %i, ou tirer en Y ?", turn%2+1);
                checkInput(&userInputY, SIZE);
                userInputX -= 1;
                userInputY -= 1;

                P2GameMap.tGame[userInputY][userInputX] = hit;
                if(checkShoot(userInputX, userInputY, &P1Boats))
                {
                    printf("TOUCHE ! Vous pouvez rejouer !\n");
                    replay = 1;
                }
            }


        }
		printf("Fin de la partie !\n");
		drawBoats(&P1Boats, &P2GameMap);
		drawBoats(&P2Boats, &P1GameMap);

        bigGame game;

        game.fleet1 = P1Boats;
        game.fleet2 = P2Boats;
        game.map1 = P1GameMap;
        game.map2 = P2GameMap;

        FILE * pFile;
        //ECRITURE DU DERNIER SCORE
        pFile = fopen("score.bin","wb");
        if (pFile!=NULL)
        {
            /*
            for(int i = 0; i < SIZE; i++)
            {
                for(int j = 0; j < SIZE; j++)
                {
                    fwrite(P1Boats , sizeof(gameFleet), 1, pFile);
                }
            }*/
            fwrite(&game , sizeof(bigGame), 1, pFile);
            fclose(pFile);
        }
        else
        {
            printf("Erreur dans l'ecriture du score");
        }

	}
	else if(cUserInput == 'S' || cUserInput == 's')
    {
        bigGame game;
        FILE * pFile;
        //TENTATIVE DE LECTURE DU FICHIER
        pFile = fopen("score.bin", "rb");
        if (pFile != NULL)
        {
            //RECUPERER LA STRUCTURE
            fread(&game, sizeof(bigGame), 1, pFile);
            drawBoats(&game.fleet1, &game.map2);
            drawBoats(&game.fleet2, &game.map1);
            fclose(pFile);
        }
        else
        {
            printf("Aucun ancien score trouve\n");
        }

    }
    return 0;
}
