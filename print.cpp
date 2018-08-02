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
* toiminta: Tulostaa kaksiuloitteisia char tyyppisiä taulukoita
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko ja tulostettavan osuuden koko
* paluuarvo(t): -
*
*-------------------------------------------------------------------------------------*/

void print_board(char board[][AB_MAX], int max)
{
	for (int y = NO_ZERO; y < max; ++y)	//Käy läpi ulkoisen taulukon solut max soluun asti
	{
		for (int x = NO_ZERO; x < max; ++x)	//Käy läpi sisäisen taulukon solut max soluun asti
		{
			cout << board[y][x];	//Tulostaa solun sisältämän merkin
		}
		cout << endl;	//Vaihtaa riviä pystysuunnassaolevan solun vaihtuessa
	}
}


/*----------------------------------------------------------------------------------------------------
*
* nimi: print_statics
* toiminta: Tulostetaan ja lasketaan tilastotitoja
* parametri(t): Taulukko tilastoille, laivojen kokonaismäärä ja erityyppisten laivojen määrä taulukko
* paluuarvo(t): -
*
*----------------------------------------------------------------------------------------------------*/

void print_statics(int statics[], int total_ships, int ship_NO[])	//Tulostetaan tilastoja
{
	const float FLOAT_ZERO = 0.00;	//Määritetään float arvoinen 0
	int counter = NO_ONE;	//Määritetään ja alustetaan laskureita
	int counter2 = NO_ONE;
	int counter3 = NO_ONE;
	int counter4 = NO_ONE;
	float effective = HIGH_NO;	//Määritetään tehokkuus muutuja ja asetetaan se korkeaan aloitusarvoon
	int effective_sunk;	//Määritetään apumuuttujian tehokkuudelle
	int effective_ship;
	int effective_type;
	int order[MAX_SHIPS + DIFFERENT_SHIP_COUNT];	//Määritetään taulukko uppoamisjärjestykselle
	cout << endl;
	cout << "Tilastotietoja" << endl;	//Tulostetaan otsikko
	print_double_line();
	cout << endl << endl;
	cout << "Laukauksia                            " << statics[NO_ZERO] << endl;	//Tulostetaan kokonaislaukausten määrä
	cout << "Ohiampumisia ennen osumaa:            " << statics[NO_ONE] << endl;	//Tulostetaan alussa ammutut ohiampumisia
	cout << endl;
	for (int x = NO_TWO + total_ships; x < total_ships * NO_TWO + NO_TWO; ++x)	//Käydään läpi kaikkien laivojen uppoamismäärät
	{
		if (statics[x] / NO_FIVE < effective && x - total_ships - NO_ONE <= ship_NO[NO_ZERO])	//Jos kyseessä on 5 kokoisen laivan tiedot ja se on tehokkain
		{
			effective_sunk = x - total_ships;	//Määritetään laukaus mikä upotti laivan
			effective = (float)statics[x] / NO_FIVE;	//Määritetään arvo tehokuudelle
			effective_type = NO_FIVE;	//Määritetään tehokkaimman laivan tyyppi
			effective_ship = x - total_ships - NO_ONE;	//Määritetään tehokkaimman laivan numero
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

	for (int y = NO_TWO; y < total_ships + NO_TWO; ++y)	//Käydään läpi kaikki laivat
	{
		if (y - NO_ONE <= ship_NO[NO_ZERO])	//Kun kyseessä on 5 kokoinen laiva
		{
			cout << counter << ". viidenkokoisen laiva upposi:       " << statics[y] << endl;	//Tulostetaan laivan uppoamislaukaus
			cout << counter << ". viidenkokoisen laivaan tarvittiin: " << statics[y + total_ships] << endl;	//Tulostetaan montako laukausta tarvittiin uppoamiseen
			++counter;
		}
		else if (y - NO_ONE - ship_NO[NO_ZERO] <= ship_NO[NO_ONE])	//Kun kyseessä on 4 kokoinen laiva tehdään sama
		{
			cout << counter2 << ". neljankokoinen laiva upposi:       " << statics[y] << endl;
			cout << counter2 << ". neljankokoiseen laivaan tarvittiin:" << statics[y + total_ships] << endl;
			++counter2;
		}
		else if (y - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] <= ship_NO[NO_TWO])	//Kun kyseessä on 3 kokoinen laiva tehdään sama
		{
			cout << counter3 << ". kolmenkokoinen laiva upposi:       " << statics[y] << endl;
			cout << counter3 << ". kolmenkokoinen laivaan tarvittiin: " << statics[y + total_ships] << endl;

			++counter3;
		}
		else if (y - NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] <= ship_NO[NO_THREE])	//Kun kyseessä on 2 kokoinen laiva tehdään sama
		{
			cout << counter4 << ". kahdenkokoinen laiva upposi:       " << statics[y] << endl;
			cout << counter4 << ". kahdenkokoinen laivaan tarvittiin: " << statics[y + total_ships] << endl;
			++counter4;
		}
	}
	for (int x = NO_ZERO; x < total_ships; ++x)	//Täytetään uppoamisjärjestys taulukko uppoamis laukaus tiedoilla
	{
		order[x] = statics[NO_TWO + x];
	}
	array_sorting(order, total_ships);	//Asetetaan uppoamisjärjestys taulukko suuruusjärjestykseen
	cout << endl << endl;
	cout << "Uppoamisjärjestys: " << endl;	
	for (int x = NO_ZERO; x < total_ships; ++x)	//Käydään kaikki laivat läpi
	{
		for (int y = NO_ZERO; y < total_ships; ++y)	//Käydään kaikki laivat läpi
		{
			if (order[x] == statics[NO_TWO + y])	//Jos järjestys vastaa uppoamista
			{
				if (y + NO_ONE <= ship_NO[NO_ZERO])		//Jos kyseessä on 5 kokoinen laiva
				{
					cout << x + NO_ONE << ") " << y + NO_ONE << ". viidenkokoisen laiva" << endl;	//Tulostetaan laivan numero ja tyyppi
				}
				else if (y + NO_ONE - ship_NO[NO_ZERO] <= ship_NO[NO_ONE])	//Jos kyseessä on 4 kokoinen laiva tehdään sama
				{
					cout << x + NO_ONE << ") " << y + NO_ONE - ship_NO[NO_ZERO] << ". nejänkokoinen laiva" << endl;
				}
				else if (y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] <= ship_NO[NO_TWO])	//Jos kyseessä on 3 kokoinen laiva tehdään sama
				{
					cout << x + NO_ONE << ") " << y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] << ". kolmenkokoinen laiva" << endl;
				}
				else if (y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] <= ship_NO[NO_THREE])	//Jos kyseessä on 2 kokoinen laiva tehdään sama
				{
					cout << x + NO_ONE << ") " << y + NO_ONE - ship_NO[NO_ZERO] - ship_NO[NO_ONE] - ship_NO[NO_TWO] << ". kahdenkokoinen laiva" << endl;
				}
			}
		}
	}
	cout << endl << endl;
	cout << "Tehokkain osumisjakso oli laukaukset  " << statics[effective_sunk] - (effective * effective_type) + NO_ONE << ". - " << statics[effective_sunk] << ". " << endl;	//Tulostetaan tehokkain osumisjakso
	cout << "                                      joilla upotettiin " << effective_ship << ". " << effective_type << " pituinen laiva." << endl;	//Tulostetaan mikä laiva oli kyseessä
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
* toiminta: Tulostaa välilyöntejä
* parametri(t): Tulostettavien välilyöntejen määrä
* paluuarvo(t): -
*
*--------------------------------------------------*/

void print_empty_line(int count)
{
	int counter = NO_ZERO;	//Alustetaan laskuri

	for (counter; counter < count; ++counter)	//Tulostetaan count muuttujan määrämä määrä välilyöntejä
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
	const int LINE_LENGTH = 16;	//Määritetään DOUBLE_LINE merkien määrän
	const unsigned char DOUBLE_LINE = 205;	//Määritetään 'kaksoisviiva'

	char line[LINE_LENGTH];		//Määritetään taulukko DOUBLE_LINE merkeille
	int counter = NO_ZERO;	//Määritetään ja alustetaan laskuri

	for (counter; counter < LINE_LENGTH; ++counter)	//Tallennetaan taulukkoon line DOUBLE_LINE merkkejä LINE_LENGTH määrittämä määrä
	{
		line[counter] = DOUBLE_LINE;
	}
	counter = NO_ZERO;	//Nollataan laskuri
	for (counter; counter < LINE_LENGTH; ++counter)	//Tulostetaan line taulukon koko sisältö
	{
		cout << line[counter];
	}
}

/*--------------------------------------------------
*
* nimi: print_clear
* toiminta: Tyhjentää ruudun
* parametri(t): -
* paluuarvo(t): -
*
*--------------------------------------------------*/

void print_clear()
{
	cout << string(500, '\n');	//Täytetään ruutu välinvaihdoilla
}
