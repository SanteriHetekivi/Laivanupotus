# Laivanupotus
End work for programming languages course from my first school year. (2014)

--------------------------------
Aloitin laivanupostus pelin suunnittelelmisen määrittämällä pelikentän make_empty_board aliohjelmalla.   
Tällä aliohjelmalla loin merkkitaulukon, joka toimisi pelin kenttänä.  
Alunperin suunnittelin aliohjelman vain toteuttamaan 7x7 pelikentän, mutta koska olin suunnitellut aliohjelman helposti muokkautuvaksi  niinkuin kaikki aliohjelmani modulaarisuuden lisäämisen jälkeen bminun tarvitsi vain sitoa ohjelmalle lähetettävä taulukon koko muuttuja muutettavaan kentän kokoon.  
Samalla myös sisälsin kordinaatit ja erotus viivat taulukkoihin, jolloin sain yhden taulukon tulostamisella print_board aliohjelmalla koko peli taulun näkymään.  
Sen jälkeen aloin suunnitella laivojen sioittelua jossa käytin hyväkseni kirjainten muokkaamista numeroiksi ja numeroiden taulukon kordinaatteihin soveltamista.  
Tässä minun täytyi huomioida kordinaattien ja erotusviivojen olemassa olo jolloin ampuminen kahdelle ensimmäiselle ja viimeiselle riville ja sarakkeelle ei sallittu.  
Jolloin muokkasinkäyttäjän syötön 1 -> 2....  ja estin virheellisiin kordinaatteihin ampumisen ottamalla käyttäjän syötteen aina erillisessä aliohjelmassa.  
Tässä tapauksessa get_cordinates toimi syöttöjen tallentamisessa, muokkaamisessa ja virheellisen syötön tunnistamisesssa.  
Alusta asti oletin käyttäjän olevan apina, joka voi hakata näppäimistöä aivottomasti.  
Näinollen otin käyttäjän kaiken syötteen erillisissä aliohjelmissa ja vedin sen monen tarkastuseulan läpi.  
Näin vain oikeanlainen syöttö pääsee läpi, eikä ohjelma myöskään ala kiertämään loputtomasti.  
Laivojen sioittelu annettujen kordinaattien ja ilmansuunnan jälkeen annettiin aliohjelman place_ships hoiviin. Sioittelu oli naurettavan helppoa oikeiden kordinaattien ja ilmansuunnan kanssa. 
Mutta kun lisäsin mahdollisuuden saada monta samanlaista laivaa piti uppoamis tarkkailussa tulevien ongelmien takia luoda uusi salainen taulukko johon add_secret_ships lisäsi myös laivat.  
Ja add_ship aliohjelma asetettiin luuppaamaan kaikki laivat läpi. Laivojen automaattinen asettelu oli helppo toteuttaa luomalla kopio add_ship ohjelmasta ja muuttamalla käyttäjän inputin satunnais numero generaattoriksi, joka kävi läpi samat tarkistukset. Place_ships ja add_secret_ships hyväksyivät, jo valmiiksi add_ship aliohjelman niille antamat arvot, joten ai_place_ships aliohjelma pystyi suoraan antamaan arvonsa niille, jolloin laivojen sioittelu onnistui ongelmitta.  
Ampuminen oli seuraavana ja sen hoiti shooting  aliohjelma.  
Shooting aliojelma toimi pääosin samalla tavalla kuin laivojen asettelukin ja shot kuin place_ships.  
Nyt hankittiin käyttäjältä vain kordinaatit, jolloin pystyin käyttämään samaa get_cordinates alihjelmaa, joka osasi tunnistaa kumpi ohjelmista kutsui häntä ja toteuttaa ohjelman poistumisen p kirjaimella ja ampumisessa vakoilun sen mukaan.  
Uppoamisen tarkistuskin sank_or_not aliohjelmalla oli helppoa kunnes lisäsin modulaarisuuden, mutta kiitos salaisen tarkistus taulukon lisäämisen peliin sekään ei enää ollut ongelma.  
Lopuksi ohjelma tarkisti oltiinko kaikki laivat upetettu sank_all aliojelmalla, joka kävi läpi taulukot etsien vielä pinnalla olevia laivoja.  
Ammunnan simuloinnissa käytin peli tekoalyn suunnittelu filosofiaa ai_simulate_shooting aliohjelma ei saanut vakoilla eikä olla muutenkaan epäreilu ai.  
Pyrin ohjelmoida sen toiminaan niinkuin olisi ihminen pystyen lukemaan vain laukaksia näyttävää kenttää.  
Kiitos edellisten toteutuksien hyvän yhteensopivuuden ai_simulate_shooting pystyi suoraan syöttämään ampumis kordinaattinsa samoihin aliohjelmiin kuin ihmiskäyttäjäkin ja saada samat tulokset.  
Asetus tietdoston lukemiselle toteutin vahvan aliohjelman settings, joka osasi jopa tarvittaessa luoda asetustiedoston itse, jos käyttäjä olisi epähuomiossa poistanut sen.  
Se myös osaa muokata käyttäjän antamia arvoja jos käyttäjän arvot vaarantaisi pelin toimintaa.  
Esimerkiksi jos käyttäjä määrittää taulukon kooksi 1x1 ohjelam muuntaa sen automaattisesti minimikokoonsa 5x5.  
Jos käyttäjä sitten haluaa ahtaa tähän 5x5 taulukkoon 100 kpl jokaista laivaa ohjelma osaa pienentää laivojen määriä kunnes ne turvallisesti mahtuvat laudalle, jopa ai_place_ships aseteltavana.  
Tallentaminen ja Lataaminen toimii yksinkertaisesti kirjoittamalla kaikki taulukot tiedostoon ja lukemalla tiedoston arvot taulukkoihin. Tilastotietojen kanssa käytin varmasti kaikista eniten aikaa, koska modulaarisuus teki siitä hyvin monimutkaista.  
Lopulta monien muuttujien sioittelun eripuolille ohjelmaa jälkeen ja yritysten ja erehdysten toimesta tilastotiedot toimivat jopa ammunnan simuloimisessa ja ne pystyy lataamaan ja tallentamaan samasta tiedostosta kuin kaikki muutkin tiedot.  
Alusta lähtien päätin toteuttaa kaikki käyttäjän syötteiden lukemiset erillisissä aliohjelmissa ja pidempien tulostusten tekemisen myös. 
Tämä helpotti koodin luomista, kun menun tai taulukon tulostaminen oli vain aliohjelmakutsun takana ja käyttäjän syöte aina puhdasta.  
Enemmänkin aikaavievä, kuin haastava projekti.   
Modulaarisuuden lisäämien oli huomattavasti haastavin kohta, koska se vaikuttaa koko ohjelmaan ja tekee siitä virheherkän.
