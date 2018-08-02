#include <iostream>
#include "header.h"

using std::endl;
using std::cout;
using std::cin;

/*------------------------------------------------------------------------------------------
*
* nimi: add_ship
* toiminta: Lis‰t‰‰n laivoja kaksiuloitteiseen taulukkoon
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko, k‰ytetyn osuuden koko, y kordinaatti,
*               x kordinaatti, laivan suunta ja  laivan tyyppi
* paluuarvo(t): true jos lis‰ys onnistui, false jos ei
*
*------------------------------------------------------------------------------------------*/

bool add_ship(char board[][AB_MAX], int max, int y, int x, char point, int type)
{
	if (y >= max - NO_TWO || y < NO_ONE || x >= max - NO_TWO || y <= NO_ONE) 	//Tarkistetaan viel‰ kerran ett‰ ohjelma on saanut kunnollisen arvon
	{
		return false;
	}
	int pieces = NO_ZERO;	//M‰‰ritet‰‰n laivanpalaslaskuri ja nollataan se
	if (point == e || point == E)	//Jos annettu suunta on etel‰
	{
		for (pieces; pieces < type; ++pieces)	//K‰yd‰‰n laivatyyppiin tarvittavat palaset l‰pi
		{
			if (y + pieces >= max - NO_TWO || y + pieces <= NO_ONE)
			{
				return false;	//Tarkistetaan mahtuuko laiva kyseiseen suuntaan
			}
			if (board[y + pieces][x] == NO_ZERO)	//Tarkistetaan onko tila vapaa
			{
				continue;
			}
			else	//Jos tila ei ole vapaa ilmoitetaan ettei laiva mahdu
			{
				return false;
			}
		}
		pieces = NO_ZERO;	//Nollataan laivanpalaslaskuri
		for (pieces; pieces < type; ++pieces)	//K‰yd‰‰n laivatyyppiin tarvittavat palaset l‰pi
		{
			board[y + pieces][x] = type + CHAR_TO_NO;	//Sioitetaan laiva paikallensa
		}
		return true;
	}
	//Toistetaan sama muille ilmansuunnille
	else if (point == i || point == I)	//Jos annettu suunta on it‰
	{
		for (pieces; pieces < type; ++pieces)
		{
			if (x + pieces >= max - NO_TWO || x + pieces <= NO_ONE) return false;
			if (board[y][x + pieces] == NO_ZERO)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		pieces = NO_ZERO;
		for (pieces; pieces < type; ++pieces)
		{
			board[y][x + pieces] = type + CHAR_TO_NO;
		}
		return true;
	}
	else if (point == p || point == P)	//Jos annettu suunta on pohjoinen
	{
		for (pieces; pieces < type; ++pieces)
		{
			if (y - pieces >= max - NO_TWO || y - pieces <= NO_ONE) return false;
			if (board[y - pieces][x] == NO_ZERO)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		pieces = NO_ZERO;
		for (pieces; pieces < type; ++pieces)
		{
			board[y - pieces][x] = type + CHAR_TO_NO;
		}
		return true;
	}
	else if (point == l || point == L)	//Jos annettu suunta on l‰nsi
	{
		for (pieces; pieces < type; ++pieces)
		{
			if (x - pieces >= max - NO_TWO || x - pieces <= NO_ONE) return false;
			if (board[y][x - pieces] == NO_ZERO)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		pieces = NO_ZERO;
		for (pieces; pieces < type; ++pieces)
		{
			board[y][x - pieces] = type + CHAR_TO_NO;
		}
		return true;
	}
	return false;	//Jos jostainsyyst‰ p‰‰dyt‰‰n t‰nne annetaan tieto ettei laiva mahdu
}

/*------------------------------------------------------------------------------------------
*
* nimi: add_secret_ships
* toiminta: Lis‰t‰‰n laivoja salaiseen kaksiuloitteiseen taulukkoon
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko, k‰ytetyn osuuden koko, y kordinaatti,
*               x kordinaatti, laivan suunta ja  laivan tyyppi
* paluuarvo(t): -
*
*------------------------------------------------------------------------------------------*/

void add_secret_ships(char secret[][AB_MAX], int max, int y, int x, char point, int ship_type)
{
	static int ship_no = NO_ZERO;
	int pieces = NO_ZERO;	//M‰‰ritet‰‰n laivanpalaslaskuri ja nollataan se
	if (point == e || point == E)	//Jos annettu suunta on etel‰
	{
		for (pieces; pieces < ship_type; ++pieces)	//K‰yd‰‰n laivatyyppiin tarvittavat palaset l‰pi
		{
			secret[y + pieces][x] = ship_no + CHAR_TO_NO;	//Sioitetaan laiva paikallensa
		}
		//Toistetaan sama muille ilmansuunnille
	}
	else if (point == i || point == I)	//Jos annettu suunta on it‰
	{
		for (pieces; pieces < ship_type; ++pieces)
		{
			secret[y][x + pieces] = ship_no + CHAR_TO_NO;
		}
	}
	else if (point == p || point == P)	//Jos annettu suunta on pohjoinen
	{
		for (pieces; pieces < ship_type; ++pieces)
		{
			secret[y - pieces][x] = ship_no + CHAR_TO_NO;
		}
	}
	else if (point == l || point == L)	//Jos annettu suunta on l‰nsi
	{
		for (pieces; pieces < ship_type; ++pieces)
		{
			secret[y][x - pieces] = ship_no + CHAR_TO_NO;
		}
	}
	++ship_no;
}

/*---------------------------------------------------------------------------------
*
* nimi: place_ships
* toiminta: K‰ytt‰j‰ m‰‰ritt‰‰ laivojen paikat
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko, k‰ytetyn osuuden koko ja
*				laivojen tiedot
* paluuarvo(t): -
*
*------------------------------------------------------------------------------------*/

void place_ships(char board[][AB_MAX], int max, int ships[], char secret[][AB_MAX])
{
	print_clear();
	make_empty_board(board, max);	//Tyhjennet‰‰n mahdolliset vanhat laivat
	int ship_type = NO_FIVE;	//M‰‰ritet‰‰n ensimm‰isten laivojen tyyppi
	char point;	//M‰‰ritet‰‰n ilmansuunnalle muuttuja
	bool check;	//M‰‰ritet‰‰n tarkistukselle muutuja
	int counter = NO_ZERO;	//M‰‰ritet‰‰n ja nollataan laskuri
	print_empty_line(NO_ONE);	//Tulostetaan yksi tyhj‰ rivi
	int ship = NO_ZERO;	//M‰‰ritet‰‰n ja nollataan tarkasteltava laiva
	cordinate cor;	//M‰‰ritet‰‰n kordinaateille muuttuja
	print_board(board, max);	//Tulostetaan taulukko
	for (ship_type; ship_type > NO_ONE; --ship_type)	//K‰yd‰‰n l‰pi kaikki laivatyypit (5-2)
	{
		while (counter < ships[ship])	//K‰yd‰‰n l‰pi kaikki laivatyyppiin m‰‰ritellyt laivat
		{
			do
			{
				cor = get_cordinates(max, board, ship_type);	//Tallennetaan k‰ytt‰j‰n syˆtt‰m‰t kordinaatit
				point = get_point();	//Tallennetaan k‰ytt‰j‰n syˆtt‰m‰ ilmansuunta
				check = add_ship(board, max, cor.y, cor.x, point, ship_type);	//Tarkistetaan voiko laivan asettaa ja asetetaan jos onnistuu
				if (check == false)	//Ilmoitetaan k‰ytt‰j‰lle laivan asettamisen ep‰onnistumisesta
				{
					cout << "Laiva ei mahdu !" << endl;
				}
			} while (check == false);	//Toistetaan kunnes laiva on saatu asetettua
			add_secret_ships(secret, max, cor.y, cor.x, point, ship_type);
			print_clear();
			print_board(board, max);	//Tulostetaan taulukko
			++counter;	//Siirryt‰‰n laivatyypin seuraavaan laivaan
		}
		counter = NO_ZERO;	//Nollataan laskuri 
		++ship;	//Siirryt‰‰n seuraavaan laivatyyppiin
	}
	print_board(board, max);	//Tulostetaan taulukko
	return;
}