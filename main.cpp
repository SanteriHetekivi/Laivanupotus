// TAMK, Ohjelmointikielet, jatko, kev‰t 2014
// Laivanupotus, laivanupotus
// Santeri Hetekivi, 13i220B
// santeri.hetekivi@eng.tamk.fi
// 40 h
// perustoiminnot, 1a, 1b, 2a, 2b, 2c, 2d, 2e

/*--------------------------------------------------
Aloitin laivanupostus pelin suunnittelelmisen
m‰‰ritt‰m‰ll‰ pelikent‰n make_empty_board
aliohjelmalla. T‰ll‰ aliohjelmalla loin
merkkitaulukon, joka toimisi pelin kentt‰n‰.
Alunperin suunnittelin aliohjelman vain toteuttamaan
7x7 pelikent‰n, mutta koska olin suunnitellut
aliohjelman helposti muokkautuvaksi niinkuin kaikki
aliohjelmani modulaarisuuden lis‰‰misen j‰lkeen
minun tarvitsi vain sitoa ohjelmalle l‰hetett‰v‰
taulukon koko muuttuja muutettavaan kent‰n kokoon.
Samalla myˆs sis‰lsin kordinaatit ja erotus
viivat taulukkoihin, jolloin sain yhden taulukon
tulostamisella print_board aliohjelmalla koko peli
taulun n‰kym‰‰n. Sen j‰lkeen aloin suunnitella
laivojen sioittelua jossa k‰ytin hyv‰kseni
kirjainten muokkaamista numeroiksi ja numeroiden
taulukon kordinaatteihin soveltamista.
T‰ss‰ minun t‰ytyi huomioida kordinaattien ja
erotusviivojen olemassa olo jolloin ampuminen
kahdelle ensimm‰iselle ja viimeiselle riville
ja sarakkeelle ei sallittu. Jolloin muokkasin
k‰ytt‰j‰n syˆtˆn 1 -> 2....  ja estin virheellisiin
kordinaatteihin ampumisen ottamalla k‰ytt‰j‰n syˆtteen
aina erillisess‰ aliohjelmassa. T‰ss‰ tapauksessa
get_cordinates toimi syˆttˆjen tallentamisessa,
muokkaamisessa ja virheellisen syˆtˆn tunnistamisesssa.
Alusta asti oletin k‰ytt‰j‰n olevan apina, joka
voi hakata n‰pp‰imistˆ‰ aivottomasti. N‰inollen
otin k‰ytt‰j‰n kaiken syˆtteen erillisiss‰ aliohjelmissa
ja vedin sen monen tarkastuseulan l‰pi. N‰in vain
oikeanlainen syˆttˆ p‰‰see l‰pi, eik‰ ohjelma myˆsk‰‰n
ala kiert‰m‰‰n loputtomasti. Laivojen sioittelu annettujen
kordinaattien ja ilmansuunnan j‰lkeen annettiin aliohjelman
place_ships hoiviin. Sioittelu oli naurettavan helppoa
oikeiden kordinaattien ja ilmansuunnan kanssa. Mutta
kun lis‰sin mahdollisuuden saada monta samanlaista laivaa
piti uppoamis tarkkailussa tulevien ongelmien takia
luoda uusi salainen taulukko johon add_secret_ships lis‰si
myˆs laivat. Ja add_ship aliohjelma asetettiin luuppaamaan
kaikki laivat l‰pi. Laivojen automaattinen asettelu oli
helppo toteuttaa luomalla kopio add_ship ohjelmasta ja
muuttamalla k‰ytt‰j‰n inputin satunnais numero generaattoriksi,
joka k‰vi l‰pi samat tarkistukset. Place_ships ja add_secret_ships
hyv‰ksyiv‰t, jo valmiiksi add_ship aliohjelman niille antamat
arvot, joten ai_place_ships aliohjelma pystyi suoraan antamaan
arvonsa niille, jolloin laivojen sioittelu onnistui ongelmitta.
Ampuminen oli seuraavana ja sen hoiti shooting  aliohjelma.
Shooting aliojelma toimi p‰‰osin samalla tavalla kuin
laivojen asettelukin ja shot kuin place_ships. Nyt hankittiin
k‰ytt‰j‰lt‰ vain kordinaatit, jolloin pystyin k‰ytt‰m‰‰n samaa
get_cordinates alihjelmaa, joka osasi tunnistaa kumpi ohjelmista
kutsui h‰nt‰ ja toteuttaa ohjelman poistumisen p kirjaimella ja
ampumisessa vakoilun sen mukaan. Uppoamisen tarkistuskin sank_or_not
aliohjelmalla oli helppoa kunnes lis‰sin modulaarisuuden, mutta
kiitos salaisen tarkistus taulukon lis‰‰misen peliin sek‰‰n ei
en‰‰ ollut ongelma. Lopuksi ohjelma tarkisti oltiinko kaikki
laivat upetettu sank_all aliojelmalla, joka k‰vi l‰pi
taulukot etsien viel‰ pinnalla olevia laivoja.
Ammunnan simuloinnissa k‰ytin peli tekoalyn suunnittelu filosofiaa
ai_simulate_shooting aliohjelma ei saanut vakoilla eik‰ olla
muutenkaan ep‰reilu ai. Pyrin ohjelmoida sen toiminaan niinkuin
olisi ihminen pystyen lukemaan vain laukaksia n‰ytt‰v‰‰
kentt‰‰. Kiitos edellisten toteutuksien hyv‰n yhteensopivuuden
ai_simulate_shooting pystyi suoraan syˆtt‰m‰‰n ampumis kordinaattinsa
samoihin aliohjelmiin kuin ihmisk‰ytt‰j‰kin ja saada samat tulokset.
Asetus tietdoston lukemiselle toteutin vahvan aliohjelman settings,
joka osasi jopa tarvittaessa luoda asetustiedoston itse, jos
k‰ytt‰j‰ olisi ep‰huomiossa poistanut sen. Se myˆs osaa muokata
k‰ytt‰j‰n antamia arvoja jos k‰ytt‰j‰n arvot vaarantaisi pelin
toimintaa. Esimerkiksi jos k‰ytt‰j‰ m‰‰ritt‰‰ taulukon kooksi 1x1
ohjelam muuntaa sen automaattisesti minimikokoonsa 5x5. Jos k‰ytt‰j‰
sitten haluaa ahtaa t‰h‰n 5x5 taulukkoon 100 kpl jokaista laivaa
ohjelma osaa pienent‰‰ laivojen m‰‰ri‰ kunnes ne turvallisesti mahtuvat
laudalle, jopa ai_place_ships aseteltavana. Tallentaminen ja Lataaminen
toimii yksinkertaisesti kirjoittamalla kaikki taulukot tiedostoon ja
lukemalla tiedoston arvot taulukkoihin. Tilastotietojen kanssa
k‰ytin varmasti kaikista eniten aikaa, koska modulaarisuus
teki siit‰ hyvin monimutkaista. Lopulta monien muuttujien sioittelun
eripuolille ohjelmaa j‰lkeen ja yritysten ja erehdysten toimesta
tilastotiedot toimivat jopa ammunnan simuloimisessa ja ne pystyy
lataamaan ja tallentamaan samasta tiedostosta kuin kaikki muutkin
tiedot. Alusta l‰htien p‰‰tin toteuttaa kaikki k‰ytt‰j‰n syˆtteiden
lukemiset erillisiss‰ aliohjelmissa ja pidempien tulostusten tekemisen
myˆs. T‰m‰ helpotti koodin luomista, kun menun tai taulukon
tulostaminen oli vain aliohjelmakutsun takana ja k‰ytt‰j‰n syˆte
aina puhdasta.
Enemm‰nkin aikaaviev‰, kuin haastava projekti. Modulaarisuuden
lis‰‰mien oli huomattavasti haastavin kohta, koska se 
vaikuttaa koko ohjelmaan ja tekee siit‰ virheherk‰n.
*--------------------------------------------------*/



#include <iostream>
#include "header.h"


int main()
{
	char board[AB_MAX][AB_MAX];	//M‰‰ritet‰‰n pelikentt‰
	char shots[AB_MAX][AB_MAX];	//M‰‰ritet‰‰n ammuntataulu
	char secret[AB_MAX][AB_MAX];	//M‰‰ritet‰‰n laivojen tunnistukseen k‰ytett‰v‰ taulukko
	int size;	//M‰‰ritet‰‰n taulukkojen maximi koolle muuttuja
	int total_ships = NO_ZERO;
	int ships[DIFFERENT_SHIP_COUNT];	//M‰‰ritet‰‰n taulukko laivojen tiedoille
	char selection;	//M‰‰ritet‰‰n valikon valinnalle muuttuja
	bool victory = false;	//M‰‰ritet‰‰n pelin voittoarvolle muuttuja ja asetetaan se false:ksi
	bool exit;	//M‰‰ritet‰‰n ohjelman sammuttamiselle muuttuja
	settings(ships, &size, &total_ships);	//Haetaan asetukset
	int statics[MAX_STATICS + (MAX_SHIPS + DIFFERENT_SHIP_COUNT) * NO_TWO] = { NO_ZERO };
	statics[total_ships * NO_TWO + NO_FOUR] = NO_ONE;
	make_empty_board(board, size);	//M‰‰rtiet‰‰n tyhj‰t taulukot
	make_empty_board(shots, size);
	make_empty_board(secret, size);
	place_ships(board, size, ships, secret);	//Asetetaan laivat
	do
	{
		print_clear();	//Tyhjennet‰‰n ruutu
		print_menu();	//Tulostetaan valikko
		get_menu_selection(&selection);	//Haetaan valikon valinta
		switch (selection)
		{
		case '1':	//Jos valinta oli 1 asetetaan laivat
		{
			make_empty_board(board, size);	//M‰‰rtiet‰‰n tyhj‰t taulukot
			make_empty_board(shots, size);
			make_empty_board(secret, size);
			place_ships(board, size, ships, secret);
			victory = false;
			continue;
		}
		case '2':	//Jos valinta oli 2 aletaan pelata
		{
			if (victory == true)
			{
				make_empty_board(board, size);	//M‰‰ritiet‰‰n tyhj‰t taulukot
				make_empty_board(shots, size);
				make_empty_board(secret, size);
				int statics[MAX_STATICS + (MAX_SHIPS + DIFFERENT_SHIP_COUNT) * NO_TWO] = { NO_ZERO };
				place_ships(board, size, ships, secret);
				victory = false;
			}
			victory = shooting(shots, board, size, ships, secret, statics, total_ships);
			if (victory == true)	//Jos k‰ytt‰j‰ voitti pelin
			{
				print_statics(statics, total_ships, ships);	//2d) Tulostetaan tilastotietodot	
				exit = get_continue_or_exit();	//Kysyt‰‰n haluaako h‰n lopettaa
				if (exit == true)	//Jos h‰n halusi lopettaa sammutetaan ohjelma
				{
					return 0;
				}
				else //Jos h‰n ei halunnut lopettaa resetataan taulukot ja asetetaan voittomuuttuja false:ksi
				{
					continue;
				}
				continue;
			}
			continue;
		}
		case '3':	//Jos valinta oli 3 ohjelma asettaa laivat
		{
			make_empty_board(board, size);	//M‰‰rtiet‰‰n tyhj‰t taulukot
			make_empty_board(shots, size);
			make_empty_board(secret, size);
			ai_place_ships(board, size, ships, secret);
			victory = false;
			continue;
		}
		case '4':	//Jos valinta oli 4 ja ei olla voitettu tallennetaan peli
		{
			if (victory == false)
			{
				simple_save(board, shots, size, statics, secret);
				continue;
			}
			continue;
		}
		case '5':	//Jos valinta oli 5 ladataan peli
		{
			simple_load(board, shots, size, statics, secret);
			continue;
		}
		case '6':	//Jos valinta oli 6 simuloidaan ampumista
		{
			if (victory == true)
			{
				make_empty_board(board, size);	//M‰‰ritiet‰‰n tyhj‰t taulukot
				make_empty_board(shots, size);
				make_empty_board(secret, size);
				int statics[MAX_STATICS + (MAX_SHIPS + DIFFERENT_SHIP_COUNT) * NO_TWO] = { NO_ZERO };
				place_ships(board, size, ships, secret);
				victory = false;
			}
			ai_simulate_shooting(shots, board, size, ships, secret, statics, total_ships);
			print_statics(statics, total_ships, ships);	//2d) Tulostetaan tilastotietodot
			exit = get_continue_or_exit();	//Kysyt‰‰n haluaako h‰n lopettaa
			if (exit == true)	//Jos h‰n halusi lopettaa sammutetaan ohjelma
			{
				return 0;
			}
			else //Jos h‰n ei halunnut lopettaa resetataan taulukot ja asetetaan voittomuuttuja false:ksi
			{
				make_empty_board(board, size);	//M‰‰rtiet‰‰n tyhj‰t taulukot
				make_empty_board(shots, size);
				make_empty_board(secret, size);
				victory = false;
				continue;

			}
			continue;
		}
		case 'L':	//Jos valinta oli L/l sammutetaan ohjelma
		{
			return 0;
		}
		}
	} while (selection != L);	//Toistetaan kunnes saadaan L
	return 0;	//Sammutetaan ohjelma
}