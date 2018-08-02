#include <iostream>
#include "header.h"
#include <fstream> 

using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::endl;
using std::cout;

/*--------------------------------------------------
*
* nimi: get_menu_selection
* toiminta: Hankkii valikon valinnan käyttäjältä
* parametri(t): valinta
* paluuarvo(t): -
*
*--------------------------------------------------*/

void get_menu_selection(char *selection)
{
	const char MENU_MIN = 49; //Määritetään minimi arvo (1)
	const char MENU_NO_MAX = 54; //Määritetään maksimi arvo (1)
	do
	{
		cin >> *selection;	//Tallennetaan käyttäjän syöttö
		if (*selection == l)	//Jos käyttäjä antoi l merkin muutetaan se L merkiksi
		{
			*selection = L;
		}
		if ((!cin) || *selection < MENU_MIN || (*selection > MENU_NO_MAX && *selection != L && *selection != l))	//Estetään loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << MENU_MIN << " - " << MENU_NO_MAX << " tai " << L << "/" << l << endl;	//Kerrotaan käyttäjälle väärästä arvosta
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			*selection = HIGH_CHAR;	//Asetetaan arvoksi ei käytetty merkki
		}
	} while (*selection == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan syöttö virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
	return;
}

/*-----------------------------------------------------
*
* nimi: get_cordinates
* toiminta: Hankkii kordinaatit käyttäjältä
* parametri(t): laudan koko, taulukko ja laivan tyyppi
* paluuarvo(t): kordinaatit
*
*-----------------------------------------------------*/

cordinate get_cordinates(int size, char board[][AB_MAX], int ship)
{
	char max_B_char = size - NO_THREE + B_CHAR_TO_CORDINATE;	//Määritetään maksimi isoille kirjaimille
	char min_B_char = NO_TWO + B_CHAR_TO_CORDINATE;	//Määritetään minimi isoille kirjaimille
	char max_s_char = size - NO_THREE + S_CHAR_TO_CORDINATE;	//Määritetään maksimi pienille kirjaimille
	char min_s_char = NO_TWO + S_CHAR_TO_CORDINATE;	//Määritetään minimi isoille kirjaimille
	cordinate cor;	//Määritetään kordinaattifunktio
	char input1,input2c;	//Määritetään syöttöjen tallennustilat
	int input2;
	do
	{
		if (ship != NO_ZERO)	//Tarkistetaanko tuliko kutsu aliohjelmasta place_ships
		{
			cout << "Anna " << ship << ". pituisen laivan alkupiste : ";	//Tulostetaan place_ships tarvitsema kysely
		}
		else //Jos ei oltu
		{
			cout << "Anna ampumiskoordinaatit: ";	//Tulostetaan shooting tarvitsema kysely
		}
		cin >> input1;	//Tallennetaan käyttäjän syöttö
		if ((input1 == P || input1 == p) && ship == NO_ZERO)	//Jos oltiin aliohjelmassa shooting ja saatiin ensimmäiseksi arvoksi kirjain P
		{
			cor.y = P;	//Määritetään cor.y kirjaimeksi P ja palautetaan se ohjelmalle
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			return cor;
		}
		else if (input1 == 92 && ship == NO_ZERO)	//1b: Voit vakoilla laivojen siaintia jos olet aliohjelmassa shooting ja annoit arvon \@
		{
			cin >> input2c;	//Otetaan toinen merkki
			if (input2c == 64)
			{
				cout << "Pelitilanne on seuraava : " << endl;
				print_board(board, size);	//Tulostetaan laivojen siannit
			}
		}
		else
		{
			cin >> input2;
		}
		input2 += NO_ONE;	//Muutetaan input1 soveliaaseen muotoon char 1 = int 2
		//input2 -= CHAR_TO_NO - NO_ONE;	//Muutetaan input1 soveliaaseen muotoon char 1 = int 2
		if (input1 > 64 && input1 < 74) input1 = input1 - B_CHAR_TO_CORDINATE;	//Muutetaan input2 soveliaaseen muotoon
		else if (input1 > 96 && input1 < 106) input1 = input1 - S_CHAR_TO_CORDINATE;
		if ((!cin) || input1 > size - NO_THREE || input1 < NO_TWO || input2 > size - NO_THREE || input2 < NO_TWO)	//Estetään loputon kierto ja virheelliset arvot
		{
			if (input1 != 92 && input2 != 64 || ship != NO_ZERO)
			{
				cout << "Virheellinen arvo. Anna " << min_B_char << NO_ONE << "/" << min_s_char << NO_ONE << " - " << max_B_char << size - NO_FOUR << "/" << max_s_char << size - NO_FOUR << endl;	//Kerrotaan käyttäjälle väärästä arvosta
			}
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			input1 = HIGH_CHAR;	//Asetetaan arvoksi ei käytetty merkki
			input2 = HIGH_CHAR;	//Asetetaan arvoksi ei käytetty merkki
		}
	} while (input1 == HIGH_CHAR || input2 == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan syöttö virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
	cor.y = input1;
	cor.x = input2;
	return cor;	//Palautetaan kelvollinen tulos
}

/*-----------------------------------------------------
*
* nimi: get_point
* toiminta: Hankkii ilmansuunta käyttäjältä
* parametri(t): -
* paluuarvo(t): ilmansuunta
*
*-----------------------------------------------------*/

char get_point()
{
	char point;	//Määritellään muuttuja ilmansuunnalle
	do
	{
		cout << "Anna suunta (p(ohjoinen)/i(ta)/e(tela)/l(ansi): ";
		cin >> point;	//Tallennetaan käyttäjän syöte
		if (point == p || point == i || point == e || point == l)	//Jos ilmansuunta annettiin pinenä kirjaimena muutetaan se isoksi
		{
			point -= B_CHAR_TO_S_CHAR;
		}
		if ((!cin) || (point != P && point != I && point != E && point != L))	//Estetään loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << P << " , " << I << " , " << I << " tai " << L << endl;	//Kerrotaan käyttäjälle väärästä arvosta
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			point = HIGH_CHAR;	//Asetetaan arvoksi ei käytetty merkki
		}
	} while (point == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan syöttö virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	return point;	//Palautetaan kelvollinen tulos
}

/*-------------------------------------------------------
*
* nimi: get_continue_or_exit
* toiminta: Selvittää haluaako käyttäjä jatkaa
* parametri(t): -
* paluuarvo(t): true tai false riippuen käyttäjän syötöstä
*
*--------------------------------------------------------*/

bool get_continue_or_exit()
{
	char exit;	//Määritetään tallennustila syötteelle
	do
	{
		cout << endl <<"Jatkatko (J) vai lopetatko (L): ";	//Kysytään käyttäjältä haluaako hän jatkaa
		cin >> exit;
		if ((!cin) || (exit != J && exit != L && exit != j && exit != l))	//Estetään loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << J << "/" << j << " tai " << L << "/" << l << endl;	//Kerrotaan käyttäjälle väärästä arvosta
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			exit = HIGH_CHAR;	//Asetetaan arvoksi ei käytetty merkki
		}
	} while (exit == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan syöttö virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
	if (exit == J || exit == j)	//Jos käyttäjä haluaa jatkaa palautetaan false
	{
		return false;
	}
	else if (exit == L || exit == l)	//Jos käyttäjä haluaa lopettaa palautetaan true
	{
		return true;
	}
	else //Ohjelman ei pitäisi päästä tänne
	{
		return true;	//Palautetaan lopetuksen aiheuttava arvo
	}

}

/*--------------------------------------------------------
*
* nimi: get_really_save
* toiminta: Varmistaa haluaako käyttäjä tallentaa
* parametri(t): -
* paluuarvo(t): true tai false riippuen käyttäjän syötöstä
*
*---------------------------------------------------------*/

bool get_really_save()
{
	char really_save;
	do
	{
		cout << "Tallentaminen tapahtuu edellisen tallennuksen yli. Haluatko silti jatkaa ?(K/E): ";	//Varmistetaan haluaako käyttäjä tallentaa
		cin >> really_save;
		if ((!cin) || (really_save != K && really_save != E && really_save != k && really_save != e))	//Estetään loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << K << "/" << k << " tai " << J << "/" << j << endl;	//Tell user of the wrong value
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			really_save = HIGH_CHAR;	//Asetetaan arvoksi ei käytetty merkki
		}
	} while (really_save == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	if (really_save == e || really_save == E)	//Jos käyttäjä ei haluakkaan tallentaa palautetaan false
	{
		return false;
	}
	else if (really_save == K || really_save == k)	//Jos käyttäjä haluaa tallentaa palautetaan true
	{
		return true;
	}
	else //Ohjelman ei pitäisi päästä tänne
	{
		return false;	//Ilmoitetaan ettei tallenneta
	}

}

/*--------------------------------------------------
*
* nimi: get_delay
* toiminta: Hankkii viiveen pituuden käyttäjältä
* parametri(t): Muokattava viive muuttuja
* paluuarvo(t): -
*
*--------------------------------------------------*/

void get_delay(int *delay)
{
	do
	{
		cout << "Anna suunta viive sekunneissa (0 = painallaus): ";
		cin >> *delay;	//Tallennetaan käyttäjän syöte
		if ((!cin))	//Estetään loputon kierto
		{
			cout << "Virheellinen arvo. Anna numero." << endl;	//Kerrotaan käyttäjälle väärästä arvosta
			cin.clear();	//Resetoidaan syöttö virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
			*delay = HIGH_NO;	//Asetetaan arvoksi ei käytetty merkki
		}
	} while (*delay == HIGH_NO);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan syöttö virheet
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
	return;
}

/*--------------------------------------------------
*
* nimi: get_ENTER
* toiminta: Hankkii ENTER nappin painalluksen
* parametri(t): -
* paluuarvo(t): -
*
*--------------------------------------------------*/

void get_ENTER()
{
	cout << "Paina ENTER jatkaaksesi: ";
	cin.clear();	//Resetoidaan syöttö virheet
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//Jätetään huomioimatta kaikki merkit seuraavaan riviin asti
}
