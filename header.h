//Luodaan int vakioita
const int AB_MAX = 13;	//Maksimiarvoja
const int DIFFERENT_SHIP_COUNT = 4;
const int MAX_SHOTS = 81;
const int MAX_STATICS = 7;
const int MAX_SHIPS = 6;	//Määritetään laivojen maksimimäärä per tyyppi

const int NO_ZERO = 0;	//Yleisimmin käytettyjä numeroita
const int NO_ONE = 1;
const int NO_TWO = 2;
const int NO_THREE = 3;
const int NO_FOUR = 4;
const int NO_FIVE = 5;
const int NO_SIX = 6;

const int HIGH_NO = 9999;	//Numeron virhearvo

const int CHAR_TO_NO = 48;	//Muutosarvoja
const int B_CHAR_TO_CORDINATE = 63;
const int S_CHAR_TO_CORDINATE = 95;
const int B_CHAR_TO_S_CHAR = 32;

//Luodaan char vakioita
const char HIGH_CHAR = 126;	//Kirjaimen virhearvo

const char P = 80;	//Yleisimmin käytettyjä kirjaimia
const char A = 65;
const char I = 73;
const char E = 69;
const char L = 76;
const char p = 112;
const char i = 105;
const char e = 101;
const char l = 108;
const char J = 74;
const char j = 106;
const char K = 75;
const char k = 107;

const char ZERO = 48;
const char TWO = 50;
const char THREE = 51;
const char FOUR = 52;
const char FIVE = 53;

const char HIT = 42;
const char MISS = 120;
const char SANK = 35;

const unsigned  char V_LINE = 196;	//Määritetään merkki vaakasuuntaiselle viivalle
const unsigned  char H_LINE = 179;	//Määritetään merkki pystysuuntaiselle viivalle
const char BACKGROUND = NO_ZERO;	//Määritetään tyhjät taulukon solut

//Luodaan tallennustiloja
struct cordinate	//Luodaan uusi tallennustila x ja y kordinaateille
{
	int y;
	int x;
};

//Ohjelmat jotka eivät palauta mitään
void make_empty_board(char[][AB_MAX], int);	//Muokkaavat päätaulukoita
void place_ships(char[][AB_MAX], int, int[], char[][AB_MAX]);
void ai_place_ships(char[][AB_MAX], int, int[], char[][AB_MAX]);
void add_secret_ships(char[][AB_MAX], int, int, int, char, int);
void ai_simulate_shooting(char[][AB_MAX], char[][AB_MAX], int,int [], char[][AB_MAX], int [], int);


void print_board(char[][AB_MAX], int);	//Tulostavat
void print_menu();
void print_save_menu();
void print_empty_line(int);
void print_clear();
void print_statics(int[], int, int []);



void settings(int[], int*, int*);	//Kirjoittavat ja hakevat tietoja erillisistä tiedostoista
void simple_save(char[][AB_MAX], char[][AB_MAX], int , int[], char[][AB_MAX]);
void simple_load(char[][AB_MAX], char[][AB_MAX], int , int[], char[][AB_MAX]);


void get_menu_selection(char *);	//Muokkaa merkkiä käyttäjän antamien tietojen mukaan
void get_delay(int *);

void get_ENTER();
void print_double_line();
void array_sorting(int [], int );


//Ohjelmat jotka palauttavat totta vai valhetta
bool get_continue_or_exit();	//Hankkivat käyttäjän syötön
bool get_save_or_not();
bool get_really_save();

bool add_ship(char[][AB_MAX], int, int, int, char, int);	//Muokkaavat päätaulukoita
bool shooting(char[][AB_MAX], char[][AB_MAX], int, int[], char[][AB_MAX], int [], int);
bool check_used_shot(cordinate [], cordinate , int  );
bool sank_all(char[][AB_MAX], char[][AB_MAX], int);
bool sank_or_not(char[][AB_MAX], char[][AB_MAX], int, int, cordinate, char[][AB_MAX], int [], int [], int);




//Ohjelmat jotka palauttavat integraalin
int get_option_save();	//Hankkivat käyttäjän syötön




//Ohjelmat jotka palauttavat merkin
char get_point();	//Hankkivat käyttäjän syötön

char shot(char[][AB_MAX], char[][AB_MAX], int, int, int,int[], int);

//Ohjelmat jotka palauttavat kordinaatit
cordinate get_cordinates(int size, char[][AB_MAX], int);	//Hankkivat käyttäjän syötön




