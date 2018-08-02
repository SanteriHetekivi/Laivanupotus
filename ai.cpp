#include <iostream>
#include <ctime>
#include "header.h"

/*---------------------------------------------------------------------------------
*
* nimi: ai_place_ships
* toiminta: Ohjelma m‰‰ritt‰‰ laivojen paikat
* parametri(t): Kaksiuloitteinen char tyyppinen taulukko, k‰ytetyn osuuden koko ja
*				laivojen tiedot
* paluuarvo(t): -
*
*------------------------------------------------------------------------------------*/

void ai_place_ships(char board[][AB_MAX], int max, int ships[], char secret[][AB_MAX])
{
	srand((unsigned int)time(NULL));	//Haetaan seedi
	make_empty_board(board, max);	//Tyhjennet‰‰n mahdolliset vanhat laivat
	int min_value = NO_TWO;	//Asetetaan minimiarvo randomille
	int max_value = max - NO_THREE - min_value;	//Asetetaan maksimiarvo randomille
	int ship_type = NO_FIVE;	//M‰‰ritet‰‰n ensimm‰isten laivojen tyyppi
	char point = NULL;	//M‰‰ritet‰‰n ilmansuunnalle muuttuja
	int ran_point;	//M‰‰ritet‰‰n ilmansuunnan randomivalinnanne muutuja
	bool check;	//M‰‰ritet‰‰n tarkistukselle muutuja
	int counter = NO_ZERO;	//M‰‰ritet‰‰n ja nollataan laskuri
	int ship = NO_ZERO;	//M‰‰ritet‰‰n ja nollataan tarkasteltava laiva
	int y, x;	//M‰‰ritet‰‰n cordinaattien muutujat
	for (ship_type; ship_type > NO_ONE; --ship_type)	//K‰yd‰‰n l‰pi kaikki laivatyypit (5-2)
	{
		while (counter < ships[ship])	//K‰yd‰‰n l‰pi kaikki laivatyyppiin m‰‰ritellyt laivat
		{
			do
			{
				y = rand() % max_value + min_value;	//Arvotaan y kordinaatti
				x = rand() % max_value + min_value;	//Arvotaan x kordinaatti
				ran_point = rand() % NO_FOUR + NO_ONE;	//Arvotaan ilmansuunta (1-4)
				if (ran_point == NO_ONE)	//Tallennetaan ilmansuunnalle merkki sen mukaan mik‰ arvo arvottiin
				{
					point = P;
				}
				else if (ran_point == NO_TWO)
				{
					point = I;
				}
				else if (ran_point == NO_THREE)
				{
					point = E;
				}
				else if (ran_point == NO_FOUR)
				{
					point = L;
				}
				check = add_ship(board, max, y, x, point, ship_type);	//Tarkistetaan voiko laivan asettaa ja asetetaan jos onnistuu
			} while (check == false);	//Toistetaan kunnes laiva on saatu asetettua
			add_secret_ships(secret, max, y, x, point, ship_type);
			++counter;	//Siirryt‰‰n laivatyypin seuraavaan laivaan
		}
		counter = NO_ZERO; //Nollataan laskuri 
		++ship; // Siirryt‰‰n seuraavaan laivatyyppiin
	}
	return;
}

/*------------------------------------------------------------------------------------------------------------
*
* nimi: ai_simulate_shooting
* toiminta: Ohjelma simuloi ampumista
* parametri(t): Ammunnat sis‰lt‰v‰ kaksiuloitteinen taulukko, laivat sis‰lt‰v‰ kaksiuloitteinen taulukko,
* kent‰n koko, laivojen tiedot, salainen laivat sis‰lt‰v‰ kaksiuloitteinen taulukko, tilastotietotaulukko ja 
* laivojen lukum‰‰r‰
* paluuarvo(t): -
*
*------------------------------------------------------------------------------------------------------------*/

void ai_simulate_shooting(char shots[][AB_MAX], char board[][AB_MAX], int size, int ships_no[], char secret[][AB_MAX], int statics[], int total_ships)
{
	srand((unsigned int)time(NULL));	//Haetaan seedi
	int y_max = size - NO_FOUR;	//M‰‰ritet‰‰n muuttujat
	int y_min = NO_TWO;
	int x_max = size - NO_FOUR;
	int x_min = NO_TWO;
	int x, y;
	cordinate cor;
	char hit_or_miss;
	bool taken_shots = false;
	bool victory = false;
	bool sank = false;
	int counter = NO_ONE;
	int delay = NO_ONE;
	print_board(shots, size); //Tulostetaan kentt‰
	get_delay(&delay);	//Haetaan taukoaika
	do
	{
		do	//Arvotaan ampumakohtia kunnes sopiva johon ei ole ammuttu ennen
		{
			cor.y = rand() % y_max + y_min;
			cor.x = rand() % y_max + y_min;
		} while (shots[cor.y][cor.x] != BACKGROUND || cor.y < NO_TWO || cor.y > size - NO_THREE || cor.x < NO_TWO || cor.y > size - NO_THREE);
		hit_or_miss = shot(shots, board, size, cor.y, cor.x, statics, total_ships);	//Ammutaan
		if (hit_or_miss != MISS)	//Jos osuttiin
		{
			sank = sank_or_not(shots, board, size, hit_or_miss, cor, secret, ships_no, statics, total_ships);	//Tarkistetaan upposiko
			print_clear();	//Tyhj‰t‰‰n ruutu
			print_board(shots, size);	//Tulostetaan kentt‰
			std::cout << cor.y << cor.x;	//Tulostetaan k‰yteyt arvot
			if (delay == NO_ZERO)	//Jos taukoaika oli 0 pyydet‰‰n enter painallus
			{
				get_ENTER();
			}
			else	//Muulloin odotetaan taukoaika
			{
				for (time_t wait = time(NULL) + delay; time(NULL) < wait;) {}
			}
			while (sank == false)	//Kun laiva ei ole uponnut
			{
				x = cor.x;	//M‰‰ritiet‰‰n v‰liaikaiset kordinaatit
				y = cor.y;
				if (cor.y >= NO_TWO && cor.y <= size - NO_THREE && cor.x >= NO_TWO && cor.y + counter <= size - NO_THREE && shots[cor.y][cor.x + counter] == BACKGROUND)	//Jos sallittua ammutaan viereiseen
				{
					x += counter; //Nostetaan v‰liaikaista kordinaattia laskurin verran
					hit_or_miss = shot(shots, board, size, cor.y, cor.x + counter, statics, total_ships);
					if (hit_or_miss != MISS)	//Jos osui nostetaan kordinaattia laskurin verran
					{
						cor.x += counter;
						sank = sank_or_not(shots, board, size, hit_or_miss, cor, secret, ships_no, statics, total_ships);	//Tarkistetaan upposiko
					}
				}
				//Jos ehdot eiv‰t t‰yty k‰yd‰‰n muut l‰heiset kohdat l‰pi samalla tavalla
				else if (cor.y - counter >= NO_TWO && cor.y <= size - NO_THREE && cor.x >= NO_TWO && cor.y <= size - NO_THREE && hit_or_miss == MISS && shots[cor.y][cor.x - counter] == BACKGROUND)
				{
					x -= counter;
					hit_or_miss = shot(shots, board, size, cor.y, cor.x - counter, statics, total_ships);
					if (hit_or_miss != MISS)
					{
						cor.x -= counter;
						sank = sank_or_not(shots, board, size, hit_or_miss, cor, secret, ships_no, statics, total_ships);
					}
				}
				else if (cor.y >= NO_TWO && cor.y + counter <= size - NO_THREE && cor.x >= NO_TWO && cor.y <= size - NO_THREE && hit_or_miss == MISS && shots[cor.y + counter][cor.x] == BACKGROUND)
				{
					y += counter;
					hit_or_miss = shot(shots, board, size, cor.y + counter, cor.x, statics, total_ships);
					if (hit_or_miss != MISS)
					{
						cor.y += counter;
						sank = sank_or_not(shots, board, size, hit_or_miss, cor, secret, ships_no, statics, total_ships);
					}
				}
				else if (cor.y >= NO_TWO && cor.y <= size - NO_THREE && cor.x - counter >= NO_TWO && cor.y <= size - NO_THREE && hit_or_miss == MISS && shots[cor.y - counter][cor.x] == BACKGROUND)
				{
					y -= counter;
					hit_or_miss = shot(shots, board, size, cor.y - counter, cor.x, statics, total_ships);
					if (hit_or_miss != MISS)
					{
						cor.y -= counter;
						sank = sank_or_not(shots, board, size, hit_or_miss, cor, secret, ships_no, statics, total_ships);
					}
				}
				else	//Jos ei voida ampua mihink‰‰n edelliseen poistutaan silmukasta ja jatketaan ohjelmaa tavallisesti
				{
					break;
				}
				print_clear();	//Tyhj‰t‰‰n ruutu
				print_board(shots, size);	//Tulostetaan kentt‰
				std::cout << y << x;	//Tulostetaan k‰yteyt v‰liaikaset kordinaatit
				if (delay == NO_ZERO)	//Jos taukoaika oli 0 pyydet‰‰n enter painallus
				{
					get_ENTER();
				}
				else	//Muulloin odotetaan taukoaika
				{
					for (time_t wait = time(NULL) + delay; time(NULL) < wait;) {}
				}
			}
			sank = false;	//M‰‰ritet‰‰n uppoamistatus ep‰todeksi
			victory = sank_all(board, shots, size);	//Tarkistetaan onko kaikki uponneet
		}
		else	//Jos ei osunut tulostetaan kentt‰, kordinaatit ja odotetaan m‰‰ritetty taukoaika
		{
			print_clear();
			print_board(shots, size);
			std::cout << cor.y << cor.x;
			if (delay == NO_ZERO)
			{
				get_ENTER();
			}
			else
			{
				for (time_t wait = time(NULL) + delay; time(NULL) < wait;) {}
			}
		}
	} while (victory == false);	//Toistetaan kunnes kaikki on upotettu
	//Tulostetaan viel‰ kentt‰ kordinaatit ja odotetaan enter painallusta ennen sulkemista
	print_clear(); 
	print_board(shots, size);
	std::cout << cor.y << cor.x;
	get_ENTER();
}