#include <iostream>
#include "header.h"
#include <ctime>

using std::endl;
using std::cout;
using std::cin;

/*---------------------------------------------------------------------
*
* nimi: shot
* toiminta: Tarkistaa osuiko laikaus ja merkkaa osuman
* parametri(t): Osumat ja laivat sis�lt�v�t kaksiuloitteiset taulukkot
*				Talukkojen maksimikoko, ammuntakordinaatit y ja x
* paluuarvo(t): Joko x merkki tai laiva johon osuttiin.
*
*----------------------------------------------------------------------*/

char shot(char shots[][AB_MAX], char board[][AB_MAX], int max, int y, int x, int statics[], int total_ships)
{
	cout << endl;
	static int run = statics[total_ships * NO_TWO + NO_FOUR];
	static int start_miss = statics[total_ships * NO_TWO + NO_FIVE];
	static int total_shots = statics[NO_ZERO];
	static int miss_streak = statics[total_ships * NO_TWO + NO_SIX];
	if (y >= max - NO_TWO || y < NO_ONE || x >= max - NO_TWO || y <= NO_ONE)	//Jos jostainsyyst� saadaan kielletty laukas
	{
		return MISS;	//Palautetaan ettei osunut
	}
	++total_shots;
	statics[NO_ZERO] = total_shots;
	if (shots[y][x] == HIT || shots[y][x] == SANK)	//Jos ampuu kohtaan johon on jo osuttu
	{
		++miss_streak;
		statics[total_ships * NO_TWO + NO_SIX] = miss_streak;
		if (run == NO_ONE)
		{
			++start_miss;
			statics[total_ships * NO_TWO + NO_FIVE] = start_miss;
		}
		return MISS;	//Palautetaan ettei osunut
	}
	else if (board[y][x] >= 49 && board[y][x] <= 57 && board[y][x] != 0)	//Jos laukauksen kordinaatit ovat sama kuin laivan
	{
		if (run == NO_ONE)
		{
			statics[NO_ONE] = start_miss;
		}
		if (statics[total_ships * NO_TWO + NO_THREE] < miss_streak)
		{
			statics[total_ships * NO_TWO + NO_THREE] = total_shots - NO_ONE;
			statics[total_ships * NO_TWO + NO_TWO] = total_shots - miss_streak;
			miss_streak = NO_ZERO;
			statics[total_ships * NO_TWO + NO_SIX] = miss_streak;
		}
		++run;
		statics[total_ships * NO_TWO + NO_FOUR] = run;
		shots[y][x] = HIT;	//Merkit��n osuma taulukkoon
		return board[y][x];	//Palautetaan millaiseen laivaan osui
	}
	else	//Jos laukauksen kordinaatit eiv�t ole sama kuin laivan
	{
		if (run == NO_ONE)
		{
			++start_miss;
			statics[total_ships * NO_TWO + NO_FIVE] = start_miss;
		}
		++miss_streak;
		statics[total_ships * NO_TWO + NO_SIX] = miss_streak;
		shots[y][x] = MISS;	//Merkataan ohi ampuminen taulukkoon
		return MISS;	//Palautetaan ettei osunut
	}
}

/*---------------------------------------------------------------------------------------
*
* nimi: sank_or_not
* toiminta: Tarkistaa upposiko mik��n laiva osuman johdosta
* parametri(t): Osumat, laivat ja piilotettu laivat sis�lt�v�t kaksiuloitteiset taulukkot
*				Talukkojen maksimikoko, laivan tiedot, cordinaatit,
* paluuarvo(t): Joko true jos upposi tai false jos ei uponnut
*
*----------------------------------------------------------------------------------------*/

bool sank_or_not(char shots[][AB_MAX], char board[][AB_MAX], int max, int laiva, cordinate cor, char secret[][AB_MAX], int ship_no[], int statics[], int total_ships)
{
	int counter = NO_ZERO;	//M��ritet��n ja alustetaan laskuri
	char secret_char = secret[cor.y][cor.x];	//Haetaan mihin yksil�lliseen laivaan osuttiin
	if (statics[total_ships + NO_TWO + secret_char - CHAR_TO_NO] == NO_ZERO)
	{
		statics[total_ships + NO_TWO + secret_char - CHAR_TO_NO] = statics[NO_ZERO];
	}
	for (int y = 2; y < max - NO_TWO; ++y)	//K�y l�pi ulkoisen taulukon solut max soluun asti
	{
		for (int x = 2; x < max - NO_TWO; ++x)	//K�y l�pi sis�isen taulukon solut max soluun asti
		{
			if (secret[y][x] == secret_char && shots[y][x] != HIT)	//Jos kyseiseksi laivaksi merkitty solu ei ole merkitty osutuksi
			{
				return false;	//Palautetaan ettei uponnut
			}
		}
	}
	for (int y = 2; y < max - NO_TWO; ++y)	//K�y l�pi ulkoisen taulukon solut max soluun asti
	{
		for (int x = 2; x < max - NO_TWO; ++x)	//K�y l�pi sis�isen taulukon solut max soluun asti
		{
			if (secret[y][x] == secret_char)	//Jos solu on kyseisen laivan
			{
				shots[y][x] = SANK;	//M��ritet��n laiva uponneeksi
			}
		}
	}
	statics[total_ships + NO_TWO + secret_char - CHAR_TO_NO] = statics[NO_ZERO] - statics[total_ships + NO_TWO + secret_char - CHAR_TO_NO] + NO_ONE;
	statics[secret_char - CHAR_TO_NO + NO_TWO] = statics[NO_ZERO];
	return true;	//Jos p��st��n tarkistus l�pi palautetaan true
}

/*-------------------------------------------------------------------------
*
* nimi: sank_all
* toiminta: Tarkistaa onko kaikki uponneet
* parametri(t): Laivat ja osumat sis�lt�v�t kaksiuloitteiset taulukkot ja
*				Talukkojen maksimikoko
* paluuarvo(t): Joko true jos kaikki ovat uponeet tai false jos ei
*
*--------------------------------------------------------------------------*/

bool sank_all(char board[][AB_MAX], char shots[][AB_MAX], int max)
{
	for (int y = 2; y < max - NO_TWO; ++y)	//K�y l�pi ulkoisen taulukon solut max soluun asti
	{
		for (int x = 2; x < max - NO_TWO; ++x)	//K�y l�pi sis�isen taulukon solut max soluun asti
		{
			if (board[y][x] != NO_ZERO && shots[y][x] != SANK)	//Jos laivaksi merkitty solu ei ole merkitty upotetuksi
			{
				return false;
			}
		}
	}
	return true;	//Jos p��st��n tarkistus l�pi palautetaan true
}

/*---------------------------------------------------------------------------------------
*
* nimi: shooting
* toiminta: Ammutaan laivoja
* parametri(t): Osumat, Laivat ja piilotettu laivat sis�lt�v�t kaksiuloitteiset taulukkot
*				Talukkojen maksimikoko, laivojen tiedot
* paluuarvo(t): Joko true jos kaikki on upotettu tai false peli viel� kesken
*
*----------------------------------------------------------------------------------------*/

bool shooting(char shots[][AB_MAX], char board[][AB_MAX], int max, int ships_no[], char secret[][AB_MAX], int statics[], int total_ships)
{
	cordinate cor;	//M��ritet��n muuttuja kordinaateille
	int counter = NO_ZERO;	//M��ritet��n laskuri ja alustetaan.
	int ships[DIFFERENT_SHIP_COUNT];	//M��ritet��n laivojen tiedoille muokattava taulukko
	for (counter; counter < DIFFERENT_SHIP_COUNT; ++counter)	//Tallennetaan laivojen tiedot muokattavaan taulukkoon
	{
		ships[counter] = ships_no[counter];
	}
	bool sank = false;	//M��ritet��n uppoamiselle muuttuja ja alustetaan se false:ksi
	int x;	//M��ritet��n x kordinaatelle muuttuja
	bool victory = false;	//M��ritet��n voitolle muuttuja ja alustetaan se false:ksi
	char y;	//M��ritet��n y kordinaatelle muuttuja
	char hit_or_miss;	//M��ritet��n osumalle tallennustila
	static int start_misses;
	cout << endl;
	print_board(shots, max);	//Tulostetaan laukaukset sis�lt�v� taulukko
	do
	{
		
		cor = get_cordinates(max, board, NO_ZERO);	//Hankitaan k�ytt�j�lt� kordinaatit
		x = cor.x - NO_ONE;	//Tallennetaan cor.x k�ytt�j�lle sopivassa muodossa
		y = cor.y + B_CHAR_TO_CORDINATE;	//Tallennetaan cor.y k�ytt�j�lle sopivassa muodossa
		if (cor.y == P || cor.y == p)	//Jos saatiin cor.y:ksi P kirjain
		{
			return false;	//Palataan menuun kesken pelin
		}
		hit_or_miss = shot(shots, board, max, cor.y, cor.x, statics, total_ships);	//Tarkistetaan osuiko laukaus
		print_clear();	//Tyhjennet��n ruutu
		if (hit_or_miss != 120)	//Jos laukaus osui
		{
			cout << "Laukaus kohtaan " << y << x << " osui laivaan.";	//Ilmoitetaan osumasta k�ytt�j�lle
			cout << endl;
			sank = sank_or_not(shots, board, max, hit_or_miss, cor, secret, ships_no, statics, total_ships);	//Tarkistetaan upposiko laiva
			if (sank == true)	//Jos upposi
			{
				cout << "Laukaus kohtaan " << y << x << " upotti laivan.";	//Ilmoitetaan uppoamisesta k�ytt�j�lle
				victory = sank_all(board, shots, max);	//Tarkistetaan onko kaikki upotettu
				if (victory == true)	//Jos kaikki upotettu
				{
					return true;	//Palataan menuun ilmoittaen ett� peli on voitettu
				}
				cout << endl;
			}
		}
		else	//Jos ei osuttu 
		{
			cout << "Laukaus kohtaan " << y << x << " ei osunut.";	//Ilmoitetaan hudista k�ytt�j�lle
			cout << endl;
		}
		print_board(shots, max);	//Tulostetaan laukaukset sis�lt�v� taulukko
	} while (victory == false);	//Toistetaan kunnes kaikki on upotettu
	return true;	//Palataan menuun ilmoittaen ett� peli on voitettu
}