#include <iostream>
#include "header.h"

/*------------------------------------------------------------------------------------
*
* nimi: make_empty_board
* toiminta: M‰‰ritet‰‰n kaksiuloitteisia char tyyppisen taulukon arvot
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko ja t‰ytˆn osuuden koko
* paluuarvo(t): -
*
*-------------------------------------------------------------------------------------*/

void make_empty_board(char board[][AB_MAX], int max)	//K‰yd‰‰n l‰pi ulkoinen taulukko
{
	

	for (int y = NO_ZERO; y < max; ++y)	//K‰yd‰‰n l‰pi sis‰inen taulukko
	{

		for (int x = NO_ZERO; x < max; ++x)
		{
			if ((y == NO_ZERO || y == max - NO_ONE) && (x < max - NO_TWO && x > NO_ONE))	//M‰‰ritet‰‰n ensimm‰iselle ja viimeiselle (k‰ytett‰v‰lle) vaakariville numerointi j‰tt‰en ensimm‰isen ja viimeisen solun koskematta
			{
				board[y][x] = ZERO + x - NO_ONE;
			}
			else if ((x == NO_ZERO || x == max - NO_ONE) && (y < max - NO_TWO && y > NO_ONE))	//M‰‰ritet‰‰n ensimm‰iselle ja viimeiselle (k‰ytett‰v‰lle) pystyriville kirjaimet j‰tt‰en ensimm‰isen ja (k‰ytett‰v‰n) viimeisen vaakarivin solun koskematta
			{
				board[y][x] = A + y - NO_TWO;
			}
			else if ((y == NO_ONE || y == max - NO_TWO) && (x < max - NO_ONE && x > NO_ZERO))	//M‰‰ritet‰‰n toiselle ja toiseksiviimeiselle (k‰ytett‰v‰lle) vaakariville merkki V_LINE j‰tt‰en ensimm‰isen ja (k‰ytett‰v‰n) viimeisen pystyrivin solun koskematta
			{
				board[y][x] = V_LINE;
			}
			else if ((x == NO_ONE || x == max - NO_TWO) && (y < max - NO_ONE && y > NO_ZERO))	//M‰‰ritet‰‰n toiselle ja toiseksiviimeiselle (k‰ytett‰v‰lle) pystyriville merkki H_LINE j‰tt‰en ensimm‰isen ja viimeisen (k‰ytett‰v‰n) vaakarivin rivin solun koskematta
			{
				board[y][x] = H_LINE;
			}
			else
			{
				board[y][x] = BACKGROUND;	//M‰‰ritet‰‰n muihin soluihin merkki BACKGROUND
			}
		}
	}
	return;
}

/*------------------------------------------------------------------------------------
*
* nimi: array_sorting
* toiminta: J‰rjestell‰‰n taulukko pienimm‰st‰ arvosta suurimpaan
* parametri(t): Int tyyppinen taulukko ja sen koko
* paluuarvo(t): -
*
*-------------------------------------------------------------------------------------*/

void array_sorting(int num[], int size)
{
	int counter, count, first, temp;
	for (counter = size - NO_ONE; counter > NO_ZERO; counter--)
	{
		first = 0;	//M‰‰ritet‰‰n jonon ensimm‰inen solu
		for (count = NO_ONE; count <= counter; ++count)	//M‰‰ritet‰‰n pienin arvo v‰lill‰ counter - 1
		{
			if (num[count] > num[first])
				first = count;
		}
		temp = num[first];	//Vaihdetaan pienin ensimm‰iseen paikkaan
		num[first] = num[counter];
		num[counter] = temp;
	}
	return;
}
