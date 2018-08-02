#include <iostream>
#include <fstream>
#include "header.h"
#include <locale>


using std::cout;
using std::endl;

using std::ifstream;
using std::ofstream;
using std::ios;

/*---------------------------------------------------------------------
*
* nimi: settings
* toiminta: Hakee asetukset laivojen m‰‰rille ja p‰‰taulukkojen koolle
* parametri(t): Laivojen tietotaulukko ja p‰‰taulukkojen koko
* paluuarvo(t): -
*
*---------------------------------------------------------------------*/

void settings(int ships[], int* size, int *total_ships)
{
	const int DIFFERENSE = 4;	//M‰‰ritet‰‰n laivojen m‰‰r‰tietojen v‰li
	const int SIZE_POSITION = 74;	//M‰‰ritet‰‰n mist‰ lˆytyy taulukon koon m‰‰ritt‰v‰ arvo
	const int MAX_SIZE = 13;	//M‰‰ritet‰‰n taulukon maksimikoko
	const int MIN_SIZE = 7;	//M‰‰ritet‰‰n taulukon minimi koko
	const int EXTRA_SIZE = 15;
	const int MIN_SHIPS = 0;	//M‰‰ritet‰‰n laivojen minimim‰‰r‰ per tyyppi
	int ship = NO_ZERO;	//M‰‰ritet‰‰n laiva laskuri ja nollataan se
	int ship_position = 88;	//M‰‰ritet‰‰n laivojen m‰‰r‰tietojen paikka ja asetetaan se ensimm‰isen laivan tietojen kohdalle
	int size_inside;	//M‰‰ritet‰‰n tallennuspaikka laivojen sioitteluun m‰‰ritelty koko
	int size_ships_need = NO_ZERO;
	int count = NO_ZERO;
	ifstream data("laiva.txt");	//Avataan asetukset sis‰lt‰v‰ tiedosto laiva.txt
	if (!data.is_open())
	{
		ofstream file("laiva.txt");
		file << "# pelikentan_sivu :n pituus voi vaihdella valilla 5 ñ 9:\npelikentan_sivu: 7\nlaivat: 5:1 4:1 3:1 2:1\n# edellinen tarkoittaa: pelikentalla 5:n pituisia laivoja 2 kpl, 4:n pituisia 3 kpl, 3:n pituisia 1 kpl ja 1:n pituisia 1 kpl.";
	}
	ifstream myfile("laiva.txt");	//Avataan asetukset sis‰lt‰v‰ tiedosto laiva.txt

	if (myfile.is_open())	//Jos avaaminen onnistui
	{
		myfile.seekg(SIZE_POSITION, ios::beg);	//Asetetaan paikka kohtaan SIZE_POSITION
		myfile >> *size;	//Tallennetaan saatu arvo taulukon kooksi
		for (ship = NO_ZERO; ship < DIFFERENT_SHIP_COUNT; ++ship)	//K‰yd‰‰n l‰pi kaikkien laivojen m‰‰r‰tiedot
		{
			myfile.seekg(ship_position, ios::beg);	//Asetetaan paikka kohtaan ship_position
			myfile >> ships[ship];	//Tallennetaan kyseisen laivatyypin m‰‰r‰
			ship_position += DIFFERENSE;	//Siirryt‰‰n seuraavaan laivatyyppiin
		}
		myfile.close(); //Suljetaan tiedosto
	}
	else //Ilmoitetaan jos tiedostoa ei ole pystytty avaamaan
	{
		cout << "Error settings aliohjelmassa";
		system("pause");
	}
	size_inside = (*size) * (*size);	//M‰‰riet‰‰n tila laivoille
	size_inside -= EXTRA_SIZE;	//Annetaan lis‰tilaa jotta ai pystyy varmasti sioittamaan laivat
	*size += DIFFERENSE;	//Muutetaan annettu koko oikeaksi taulukon kooksi
	for (ship = NO_ZERO; ship < DIFFERENT_SHIP_COUNT; ++ship)	//Asetetaan laivojen m‰‰r‰ hyv‰ksyihin arvoihin
	{
		if (ships[ship] < MIN_SHIPS)
		{
			ships[ship] = MIN_SHIPS;
		}
		if (ships[ship] > MAX_SHIPS)
		{
			ships[ship] = MAX_SHIPS;
		}
	}
	for (ship = NO_ZERO; ship < DIFFERENT_SHIP_COUNT; ++ship)	//Lasketaan paljonko laivat tarvitsevat tilaa
	{
		size_ships_need += ships[ship] * (NO_FIVE - ship);
	}
	cout << "Poistetaan laivoja jotta kaikki mahtuvat !";
	while (size_ships_need > size_inside)	//Asetetaan laivojen m‰‰r‰ sellaisiksi ett‰ ne mahtuvat
	{
		if (count >= DIFFERENT_SHIP_COUNT)	//Kun k‰yty l‰pi kaikki tyypit aloitetaan uudelleen
		{
			count = NO_ZERO;
		}
		ships[count] -= NO_ONE;	//V‰hennet‰‰n laiva
		if (ships[count] < MIN_SHIPS)	//Estet‰‰n ettei voi tulla negatiivisi‰ arvoja
		{
			ships[count] = NO_ZERO;
		}
		size_ships_need = NO_ZERO;
		for (ship = NO_ZERO; ship < DIFFERENT_SHIP_COUNT; ++ship)	//Lasketaan paljonko laivat tarvitsevat tilaa
		{
			size_ships_need += ships[ship] * (NO_FIVE - ship);
		}
		cout << size_ships_need;
		++count;	//Siirryt‰‰n seuraavaan laivatyyppiin
	}
	for (ship = NO_ZERO; ship < DIFFERENT_SHIP_COUNT; ++ship)	//Lasketaan paljonko laivat tarvitsevat tilaa
	{
		*total_ships += ships[ship];
	}
	if (*size > MAX_SIZE)	//Jos annettu koko on liian suuri asetetaan kooksi suurin hyv‰ksytty koko
	{
		*size = MAX_SIZE;
	}
	if (*size < MIN_SIZE)	//Jos annettu koko on liian pieni asetetaan kooksi pienin hyv‰ksytty koko
	{
		*size = MIN_SIZE;
	}
	return;
}

/*-------------------------------------------------------
*
* nimi: simple_save
* toiminta: Kirjoitetaan p‰‰taulukot tiedostoon
* parametri(t): char muotoiset p‰‰taulukot ja niiden koko
* paluuarvo(t): -
*
*-------------------------------------------------------*/

void simple_save(char board[][AB_MAX], char shots[][AB_MAX], int size, int statics[], char secret[][AB_MAX])
{
	print_clear();
	bool really_save;	//M‰‰ritet‰‰n tallennuksen varmistus
	really_save = get_really_save();	//Tallennetaan tieto haluaako k‰ytt‰j‰ varmasti tallentaa
	if (really_save == true)	//Jos k‰ytt‰j‰ haluaa tallentaa
	{
		ofstream save_file("pelitilanne.txt");	//Avataan tallennustiedosto pelitilanne.txt
		if (save_file.is_open())	//Jos avaaminen onnistui
		{
			for (int x = NO_ZERO; x < size; ++x)	//Kirjoitetaan koko taulukko tiedostoon
			{
				for (int y = NO_ZERO; y < size; ++y)
				{

					save_file << board[x][y];
				}
			}
			save_file << endl;
			for (int x = NO_ZERO; x < size; ++x)	//Kirjoitetaan koko taulukko tiedostoon
			{
				for (int y = NO_ZERO; y < size; ++y)
				{

					save_file << shots[x][y];
				}
			}
			save_file << endl;
			for (int x = NO_ZERO; x < size; ++x)	//Kirjoitetaan koko taulukko tiedostoon
			{
				for (int y = NO_ZERO; y < size; ++y)
				{

					save_file << secret[x][y];
				}
			}
			save_file << endl;
			for (int x = NO_ZERO; x < (MAX_STATICS + (MAX_SHIPS + DIFFERENT_SHIP_COUNT) * NO_TWO); ++x)	//Kirjoitetaan koko taulukko tiedostoon
			{
				save_file << statics[x] << endl;
			}
			save_file.close();	//Suljetaan tiedosto
		}
		else //Ilmoitetaan jos tiedostoa ei ole pystytty avaamaan
		{
			cout << "Error simple_save aliohjelmassa" << endl;
		}
	}
	else	//Jos k‰ytt‰j‰ ei haluakkaan tallentaa niin palataan p‰‰valikkoon
	{
		return;
	}
	return;
}

/*-------------------------------------------------------
*
* nimi: simple_load
* toiminta: T‰ytet‰‰n p‰‰taulukot tiedostosta
* parametri(t): char muotoiset p‰‰taulukot ja niiden koko
* paluuarvo(t): -
*
*-------------------------------------------------------*/

void simple_load(char board[][AB_MAX], char shots[][AB_MAX], int size, int statics[], char secret[][AB_MAX])
{
	print_clear();
	ifstream save_file("pelitilanne.txt");	//Avataan tallennustiedosto pelitilanne.txt
	if (save_file.is_open())	//Jos avaaminen onnistui
	{
		for (int x = NO_ZERO; x < size; ++x)	//Tallennetaan tiedot koko taulukkoon
		{
			for (int y = NO_ZERO; y < size; ++y)
			{

				save_file >> board[x][y];
			}
		}
		for (int x = NO_ZERO; x < size; ++x)	//Tallennetaan tiedot koko taulukkoon
		{
			for (int y = NO_ZERO; y < size; ++y)
			{

				save_file >> shots[x][y];
			}
		}
		for (int x = NO_ZERO; x < size; ++x)	//Kirjoitetaan koko taulukko tiedostoon
		{
			for (int y = NO_ZERO; y < size; ++y)
			{

				save_file >> secret[x][y];
			}
		}
		int x = 0;
		while (x < (MAX_STATICS + (MAX_SHIPS + DIFFERENT_SHIP_COUNT) * NO_TWO) && save_file >> statics[x])
		{
			++x;
		}
		save_file.close();	//Suljetaan tiedosto
	}
	else	//Ilmoitetaan jos tiedostoa ei ole pystytty avaamaan
	{
		cout << "Error simple_load aliohjelmassa" << endl;
	}
	return;
}
