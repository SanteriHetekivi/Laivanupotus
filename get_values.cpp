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
* toiminta: Hankkii valikon valinnan k�ytt�j�lt�
* parametri(t): valinta
* paluuarvo(t): -
*
*--------------------------------------------------*/

void get_menu_selection(char *selection)
{
	const char MENU_MIN = 49; //M��ritet��n minimi arvo (1)
	const char MENU_NO_MAX = 54; //M��ritet��n maksimi arvo (1)
	do
	{
		cin >> *selection;	//Tallennetaan k�ytt�j�n sy�tt�
		if (*selection == l)	//Jos k�ytt�j� antoi l merkin muutetaan se L merkiksi
		{
			*selection = L;
		}
		if ((!cin) || *selection < MENU_MIN || (*selection > MENU_NO_MAX && *selection != L && *selection != l))	//Estet��n loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << MENU_MIN << " - " << MENU_NO_MAX << " tai " << L << "/" << l << endl;	//Kerrotaan k�ytt�j�lle v��r�st� arvosta
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
			*selection = HIGH_CHAR;	//Asetetaan arvoksi ei k�ytetty merkki
		}
	} while (*selection == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan sy�tt� virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
	return;
}

/*-----------------------------------------------------
*
* nimi: get_cordinates
* toiminta: Hankkii kordinaatit k�ytt�j�lt�
* parametri(t): laudan koko, taulukko ja laivan tyyppi
* paluuarvo(t): kordinaatit
*
*-----------------------------------------------------*/

cordinate get_cordinates(int size, char board[][AB_MAX], int ship)
{
	char max_B_char = size - NO_THREE + B_CHAR_TO_CORDINATE;	//M��ritet��n maksimi isoille kirjaimille
	char min_B_char = NO_TWO + B_CHAR_TO_CORDINATE;	//M��ritet��n minimi isoille kirjaimille
	char max_s_char = size - NO_THREE + S_CHAR_TO_CORDINATE;	//M��ritet��n maksimi pienille kirjaimille
	char min_s_char = NO_TWO + S_CHAR_TO_CORDINATE;	//M��ritet��n minimi isoille kirjaimille
	cordinate cor;	//M��ritet��n kordinaattifunktio
	char input1,input2c;	//M��ritet��n sy�tt�jen tallennustilat
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
		cin >> input1;	//Tallennetaan k�ytt�j�n sy�tt�
		if ((input1 == P || input1 == p) && ship == NO_ZERO)	//Jos oltiin aliohjelmassa shooting ja saatiin ensimm�iseksi arvoksi kirjain P
		{
			cor.y = P;	//M��ritet��n cor.y kirjaimeksi P ja palautetaan se ohjelmalle
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
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
		if ((!cin) || input1 > size - NO_THREE || input1 < NO_TWO || input2 > size - NO_THREE || input2 < NO_TWO)	//Estet��n loputon kierto ja virheelliset arvot
		{
			if (input1 != 92 && input2 != 64 || ship != NO_ZERO)
			{
				cout << "Virheellinen arvo. Anna " << min_B_char << NO_ONE << "/" << min_s_char << NO_ONE << " - " << max_B_char << size - NO_FOUR << "/" << max_s_char << size - NO_FOUR << endl;	//Kerrotaan k�ytt�j�lle v��r�st� arvosta
			}
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
			input1 = HIGH_CHAR;	//Asetetaan arvoksi ei k�ytetty merkki
			input2 = HIGH_CHAR;	//Asetetaan arvoksi ei k�ytetty merkki
		}
	} while (input1 == HIGH_CHAR || input2 == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan sy�tt� virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
	cor.y = input1;
	cor.x = input2;
	return cor;	//Palautetaan kelvollinen tulos
}

/*-----------------------------------------------------
*
* nimi: get_point
* toiminta: Hankkii ilmansuunta k�ytt�j�lt�
* parametri(t): -
* paluuarvo(t): ilmansuunta
*
*-----------------------------------------------------*/

char get_point()
{
	char point;	//M��ritell��n muuttuja ilmansuunnalle
	do
	{
		cout << "Anna suunta (p(ohjoinen)/i(ta)/e(tela)/l(ansi): ";
		cin >> point;	//Tallennetaan k�ytt�j�n sy�te
		if (point == p || point == i || point == e || point == l)	//Jos ilmansuunta annettiin pinen� kirjaimena muutetaan se isoksi
		{
			point -= B_CHAR_TO_S_CHAR;
		}
		if ((!cin) || (point != P && point != I && point != E && point != L))	//Estet��n loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << P << " , " << I << " , " << I << " tai " << L << endl;	//Kerrotaan k�ytt�j�lle v��r�st� arvosta
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
			point = HIGH_CHAR;	//Asetetaan arvoksi ei k�ytetty merkki
		}
	} while (point == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan sy�tt� virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	return point;	//Palautetaan kelvollinen tulos
}

/*-------------------------------------------------------
*
* nimi: get_continue_or_exit
* toiminta: Selvitt�� haluaako k�ytt�j� jatkaa
* parametri(t): -
* paluuarvo(t): true tai false riippuen k�ytt�j�n sy�t�st�
*
*--------------------------------------------------------*/

bool get_continue_or_exit()
{
	char exit;	//M��ritet��n tallennustila sy�tteelle
	do
	{
		cout << endl <<"Jatkatko (J) vai lopetatko (L): ";	//Kysyt��n k�ytt�j�lt� haluaako h�n jatkaa
		cin >> exit;
		if ((!cin) || (exit != J && exit != L && exit != j && exit != l))	//Estet��n loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << J << "/" << j << " tai " << L << "/" << l << endl;	//Kerrotaan k�ytt�j�lle v��r�st� arvosta
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
			exit = HIGH_CHAR;	//Asetetaan arvoksi ei k�ytetty merkki
		}
	} while (exit == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan sy�tt� virheet
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
	if (exit == J || exit == j)	//Jos k�ytt�j� haluaa jatkaa palautetaan false
	{
		return false;
	}
	else if (exit == L || exit == l)	//Jos k�ytt�j� haluaa lopettaa palautetaan true
	{
		return true;
	}
	else //Ohjelman ei pit�isi p��st� t�nne
	{
		return true;	//Palautetaan lopetuksen aiheuttava arvo
	}

}

/*--------------------------------------------------------
*
* nimi: get_really_save
* toiminta: Varmistaa haluaako k�ytt�j� tallentaa
* parametri(t): -
* paluuarvo(t): true tai false riippuen k�ytt�j�n sy�t�st�
*
*---------------------------------------------------------*/

bool get_really_save()
{
	char really_save;
	do
	{
		cout << "Tallentaminen tapahtuu edellisen tallennuksen yli. Haluatko silti jatkaa ?(K/E): ";	//Varmistetaan haluaako k�ytt�j� tallentaa
		cin >> really_save;
		if ((!cin) || (really_save != K && really_save != E && really_save != k && really_save != e))	//Estet��n loputon kierto ja virheelliset arvot
		{
			cout << "Virheellinen arvo. Anna " << K << "/" << k << " tai " << J << "/" << j << endl;	//Tell user of the wrong value
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
			really_save = HIGH_CHAR;	//Asetetaan arvoksi ei k�ytetty merkki
		}
	} while (really_save == HIGH_CHAR);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	if (really_save == e || really_save == E)	//Jos k�ytt�j� ei haluakkaan tallentaa palautetaan false
	{
		return false;
	}
	else if (really_save == K || really_save == k)	//Jos k�ytt�j� haluaa tallentaa palautetaan true
	{
		return true;
	}
	else //Ohjelman ei pit�isi p��st� t�nne
	{
		return false;	//Ilmoitetaan ettei tallenneta
	}

}

/*--------------------------------------------------
*
* nimi: get_delay
* toiminta: Hankkii viiveen pituuden k�ytt�j�lt�
* parametri(t): Muokattava viive muuttuja
* paluuarvo(t): -
*
*--------------------------------------------------*/

void get_delay(int *delay)
{
	do
	{
		cout << "Anna suunta viive sekunneissa (0 = painallaus): ";
		cin >> *delay;	//Tallennetaan k�ytt�j�n sy�te
		if ((!cin))	//Estet��n loputon kierto
		{
			cout << "Virheellinen arvo. Anna numero." << endl;	//Kerrotaan k�ytt�j�lle v��r�st� arvosta
			cin.clear();	//Resetoidaan sy�tt� virheet
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
			*delay = HIGH_NO;	//Asetetaan arvoksi ei k�ytetty merkki
		}
	} while (*delay == HIGH_NO);	//Toistetaan kunnes saadaan kelvollinen tulos
	cin.clear();	//Resetoidaan sy�tt� virheet
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
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
	cin.clear();	//Resetoidaan sy�tt� virheet
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');	//J�tet��n huomioimatta kaikki merkit seuraavaan riviin asti
}
