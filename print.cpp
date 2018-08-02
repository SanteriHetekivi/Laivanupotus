#include <iostream>
#include "header.h"
#include <string>

using std::endl;
using std::cout;
using std::cin;
using std::string;

/*------------------------------------------------------------------------------------
*
* nimi: print_board
* toiminta: Tulostaa kaksiuloitteisia char tyyppisi� taulukoita
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko ja tulostettavan osuuden koko
* paluuarvo(t): -
*
*-------------------------------------------------------------------------------------*/

void print_board(char board[][AB_MAX], int max)
{
	for (int y = NO_ZERO; y < max; ++y)	//K�y l�pi ulkoisen taulukon solut max soluun asti
	{
		for (int x = NO_ZERO; x < max; ++x)	//K�y l�pi sis�isen taulukon solut max soluun asti
		{
			cout << board[y][x];	//Tulostaa solun sis�lt�m�n merkin
		}
		cout << endl;	//Vaihtaa rivi� pystysuunnassaolevan solun vaihtuessa
	}
}


/*----------------------------------------------------------------------------------------------------
*
* nimi: print_statics
* toiminta: Tulostetaan ja lasketaan tilastotitoja
* parametri(t): Taulukko tilastoille, laivojen kokonaism��r� ja erityyppisten laivojen m��r� taulukko
* paluuarvo(t): -
*
*----------------------------------------------------------------------------------------------------*/

void print_statics(int statics[], int total_ships, int ship_NO[])	//Tulostetaan tilastoja
{
	const float FLOAT_ZERO = 0.00;	//M��ritet��n float arvoinen 0
	int counter = NO_ONE;	//M��ritet��n ja alustetaan laskureita
	int counter2 = NO_ONE;
	int counter3 = NO_ONE;
	int counter4 = NO_ONE;
	float effective = HIGH_NO;	//M��ritet��n tehokkuus muutuja ja asetetaan se korkeaan aloitusarvoon
	int effective_sunk;	//M��ritet��n apumuuttujian tehokkuudelle
	int effective_ship;
	int effective_type;
	int order[MAX_SHIPS + DIFFERENT_SHIP_COUNT];	//M��ritet��n taulukko uppoamisj�rjestykselle
	cout << endl;
	cout << "Tilastotietoja" << endl;	//Tulostetaan otsikko
	print_double_line();
	cout << endl << endl;
	cout << "Laukauksia                            " << statics[NO_ZERO] << endl;	//Tulostetaan kokonaislaukausten m��r�
	cout << "Ohiampumisia ennen osumaa:            " << statics[NO_ONE] << endl;	//Tulostetaan alussa ammutut ohiampumisia
	cout << endl;
	for (int x = NO_TWO + total_ships; x < total_ships * NO_TWO + NO_TWO; ++x)	//K�yd��n l�pi kaikkien laivojen uppoamism��r�t
	{
		if (statics[x] / NO_FIVE < effective && x - total_ships - NO_ONE <= ship_NO[NO_ZERO])	//Jos kyseess� on 5 kokoisen laivan tiedot ja se on tehokkain
		{
			effective_sunk = x - total_ships;	//M��ritet��n laukaus mik� upotti laivan
			effective = (float)statics[x] / NO_FIVE;	//M��ritet��n arvo tehokuudelle
			effective_type = NO_FIVE;	//M��ritet��n tehokkaimman laivan tyyppi
			effective_ship = x - total_ships - NO_ONE;	//M��ritet��n tehokkaimman laivan numero
		}
		else if (statics[x] / NO_FOUR < effective && x - total_ships - NO_ONE - ship_NO[NO_ZERO] <= ship_NO[NO_ONE])	//Sama jos 4 kokoinen laiva on tehokkain
		{
			effective_sunk = x - total_ships;
			effective = (float)statics[x] / NO_FOUR;
			effective_type = NO_FOUR;
			effective_ship = x - total_ships - NO_ONE - ship_NO[NO_ZERO];
		}
		else if (statics[x] / NO_THREE < effective && x - total_ships - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] <= ship_NO[NO_TWO])	//Sama jos 3 kokoinen laiva on tehokkain
		{
			effective_sunk = x - total_ships;
			effective = (float)statics[x] / NO_THREE;
			effective_type = NO_THREE;
			effective_ship = x - total_ships - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE];
		}
		else if (statics[x] / NO_TWO < effective && x - total_ships - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] <= ship_NO[NO_THREE])	//Sama jos 2 kokoinen laiva on tehokkain
		{
			effective_sunk = x - total_ships;
			effective = (float)statics[x] / NO_TWO;
			effective_type = NO_TWO;
			effective_ship = x - total_ships - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO];
		}
	}

	for (int y = NO_TWO; y < total_ships + NO_TWO; ++y)	//K�yd��n l�pi kaikki laivat
	{
		if (y - NO_ONE <= ship_NO[NO_ZERO])	//Kun kyseess� on 5 kokoinen laiva
		{
			cout << counter << ". viidenkokoisen laiva upposi:       " << statics[y] << endl;	//Tulostetaan laivan uppoamislaukaus
			cout << counter << ". viidenkokoisen laivaan tarvittiin: " << statics[y + total_ships] << endl;	//Tulostetaan montako laukausta tarvittiin uppoamiseen
			++counter;
		}
		else if (y - NO_ONE - ship_NO[NO_ZERO] <= ship_NO[NO_ONE])	//Kun kyseess� on 4 kokoinen laiva tehd��n sama
		{
			cout << counter2 << ". neljankokoinen laiva upposi:       " << statics[y] << endl;
			cout << counter2 << ". neljankokoiseen laivaan tarvittiin:" << statics[y + total_ships] << endl;
			++counter2;
		}
		else if (y - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] <= ship_NO[NO_TWO])	//Kun kyseess� on 3 kokoinen laiva tehd��n sama
		{
			cout << counter3 << ". kolmenkokoinen laiva upposi:       " << statics[y] << endl;
			cout << counter3 << ". kolmenkokoinen laivaan tarvittiin: " << statics[y + total_ships] << endl;

			++counter3;
		}
		else if (y - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] <= ship_NO[NO_THREE])	//Kun kyseess� on 2 kokoinen laiva tehd��n sama
		{
			cout << counter4 << ". kahdenkokoinen laiva upposi:       " << statics[y] << endl;
			cout << counter4 << ". kahdenkokoinen laivaan tarvittiin: " << statics[y + total_ships] << endl;
			++counter4;
		}
	}
	for (int x = NO_ZERO; x < total_ships; ++x)	//T�ytet��n uppoamisj�rjestys taulukko uppoamis laukaus tiedoilla
	{
		order[x] = statics[NO_TWO + x];
	}
	array_sorting(order, total_ships);	//Asetetaan uppoamisj�rjestys taulukko suuruusj�rjestykseen
	cout << endl << endl;
	cout << "Uppoamisj�rjestys: " << endl;	
	for (int x = NO_ZERO; x < total_ships; ++x)	//K�yd��n kaikki laivat l�pi
	{
		for (int y = NO_ZERO; y < total_ships; ++y)	//K�yd��n kaikki laivat l�pi
		{
			if (order[x] == statics[NO_TWO + y])	//Jos j�rjestys vastaa uppoamista
			{
				if (y + NO_ONE <= ship_NO[NO_ZERO])		//Jos kyseess� on 5 kokoinen laiva
				{
					cout << x + NO_ONE << ") " << y + NO_ONE << ". viidenkokoisen laiva" << endl;	//Tulostetaan laivan numero ja tyyppi
				}
				else if (y + NO_ONE - ship_NO[NO_ZERO] <= ship_NO[NO_ONE])	//Jos kyseess� on 4 kokoinen laiva tehd��n sama
				{
					cout << x + NO_ONE << ") " << y + NO_ONE - ship_NO[NO_ZERO] << ". nej�nkokoinen laiva" << endl;
				}
				else if (y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] <= ship_NO[NO_TWO])	//Jos kyseess� on 3 kokoinen laiva tehd��n sama
				{
					cout << x + NO_ONE << ") " << y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] << ". kolmenkokoinen laiva" << endl;
				}
				else if (y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] <= ship_NO[NO_THREE])	//Jos kyseess� on 2 kokoinen laiva tehd��n sama
				{
					cout << x + NO_ONE << ") " << y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] << ". kahdenkokoinen laiva" << endl;
				}
			}
		}
	}
	cout << endl << endl;
	cout << "Tehokkain osumisjakso oli laukaukset  " << statics[effective_sunk] - (effective * effective_type) + NO_ONE << ". - " << statics[effective_sunk] << ". " << endl;	//Tulostetaan tehokkain osumisjakso
	cout << "                                      joilla upotettiin " << effective_ship << ". " << effective_type << " pituinen laiva." << endl;	//Tulostetaan mik� laiva oli kyseess�
	cout << "Pisin ohilaukausjakso oli ammunnat:   " << statics[total_ships * NO_TWO + NO_TWO] << ". - " << statics[total_ships * NO_TWO + NO_THREE] << endl;	//Tulostetaan pisin ohilaukausjakso
}

/*--------------------------------------------------
*
* nimi: print_menu
* toiminta: Tulostaa aloitusvalikko
* parametri(t): -
* paluuarvo(t): -
*
*--------------------------------------------------*/

void print_menu()
{
	cout << "Laivanupotuspeli" << endl;	//Tulostetaan otsikko
	print_double_line();
	cout << endl;
	cout << endl;
	cout << "Valinnat:" << endl;	//Tulostetaan menuvalinnat
	cout << "1) Syota laivat" << endl;
	cout << "2) Pelaa" << endl;
	cout << "3) Arvo laivojen sijainnit" << endl;
	cout << "4) Talleta pelitilanne" << endl;
	cout << "5) Lataa pelitilanne" << endl;
	cout << "6) Simuloi ampumista" << endl;
	cout << "L) Lopeta" << endl;;
	cout << "Valintasi: ";
}

/*--------------------------------------------------
*
* nimi: print_empty_line
* toiminta: Tulostaa v�lily�ntej�
* parametri(t): Tulostettavien v�lily�ntejen m��r�
* paluuarvo(t): -
*
*--------------------------------------------------*/

void print_empty_line(int count)
{
	int counter = NO_ZERO;	//Alustetaan laskuri

	for (counter; counter < count; ++counter)	//Tulostetaan count muuttujan m��r�m� m��r� v�lily�ntej�
	{
		cout << endl;
	}
}

/*--------------------------------------------------
*
* nimi: print_clear
* toiminta: Tulostaa kaksoisviivan
* parametri(t): -
* paluuarvo(t): -
*
*--------------------------------------------------*/

void print_double_line()
{
	const int LINE_LENGTH = 16;	//M��ritet��n DOUBLE_LINE merkien m��r�n
	const unsigned char DOUBLE_LINE = 205;	//M��ritet��n 'kaksoisviiva'

	char line[LINE_LENGTH];		//M��ritet��n taulukko DOUBLE_LINE merkeille
	int counter = NO_ZERO;	//M��ritet��n ja alustetaan laskuri

	for (counter; counter < LINE_LENGTH; ++counter)	//Tallennetaan taulukkoon line DOUBLE_LINE merkkej� LINE_LENGTH m��ritt�m� m��r�
	{
		line[counter] = DOUBLE_LINE;
	}
	counter = NO_ZERO;	//Nollataan laskuri
	for (counter; counter < LINE_LENGTH; ++counter)	//Tulostetaan line taulukon koko sis�lt�
	{
		cout << line[counter];
	}
}

/*--------------------------------------------------
*
* nimi: print_clear
* toiminta: Tyhjent�� ruudun
* parametri(t): -
* paluuarvo(t): -
*
*--------------------------------------------------*/

void print_clear()
{
	cout << string(500, '\n');	//T�ytet��n ruutu v�linvaihdoilla
}
