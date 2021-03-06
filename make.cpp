#include <iostream>
#include "header.h"

/*------------------------------------------------------------------------------------
*
* nimi: make_empty_board
* toiminta: Määritetään kaksiuloitteisia char tyyppisen taulukon arvot
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko ja täytön osuuden koko
* paluuarvo(t): -
*
*-------------------------------------------------------------------------------------*/

void make_empty_board(char board[][AB_MAX], int max)	//Käydään läpi ulkoinen taulukko
{
	

	for (int y = NO_ZERO; y < max; ++y)	//Käydään läpi sisäinen taulukko
	{

		for (int x = NO_ZERO; x < max; ++x)
		{
			if ((y == NO_ZERO || y == max - NO_ONE) && (x < max - NO_TWO && x > NO_ONE))	//Määritetään ensimmäiselle ja viimeiselle (käytettävälle) vaakariville numerointi jättäen ensimmäisen ja viimeisen solun koskematta
			{
				board[y][x] = ZERO + x - NO_ONE;
			}
			else if ((x == NO_ZERO || x == max - NO_ONE) && (y < max - NO_TWO && y > NO_ONE))	//Määritetään ensimmäiselle ja viimeiselle (käytettävälle) pystyriville kirjaimet jättäen ensimmäisen ja (käytettävän) viimeisen vaakarivin solun koskematta
			{
				board[y][x] = A + y - NO_TWO;
			}
			else if ((y == NO_ONE || y == max - NO_TWO) && (x < max - NO_ONE && x > NO_ZERO))	//Määritetään toiselle ja toiseksiviimeiselle (käytettävälle) vaakariville merkki V_LINE jättäen ensimmäisen ja (käytettävän) viimeisen pystyrivin solun koskematta
			{
				board[y][x] = V_LINE;
			}
			else if ((x == NO_ONE || x == max - NO_TWO) && (y < max - NO_ONE && y > NO_ZERO))	//Määritetään toiselle ja toiseksiviimeiselle (käytettävälle) pystyriville merkki H_LINE jättäen ensimmäisen ja viimeisen (käytettävän) vaakarivin rivin solun koskematta
			{
				board[y][x] = H_LINE;
			}
			else
			{
				board[y][x] = BACKGROUND;	//Määritetään muihin soluihin merkki BACKGROUND
			}
		}
	}
	return;
}

/*------------------------------------------------------------------------------------
*
* nimi: array_sorting
* toiminta: Järjestellään taulukko pienimmästä arvosta suurimpaan
* parametri(t): Int tyyppinen taulukko ja sen koko
* paluuarvo(t): -
*
*-------------------------------------------------------------------------------------*/

void array_sorting(int num[], int size)
{
	int counter, count, first, temp;
	for (counter = size - NO_ONE; counter > NO_ZERO; counter--)
	{
		first = 0;	//Määritetään jonon ensimmäinen solu
		for (count = NO_ONE; count <= counter; ++count)	//Määritetään pienin arvo välillä counter - 1
		{
			if (num[count] > num[first])
				first = count;
		}
		temp = num[first];	//Vaihdetaan pienin ensimmäiseen paikkaan
		num[first] = num[counter];
		num[counter] = temp;
	}
	return;
}
