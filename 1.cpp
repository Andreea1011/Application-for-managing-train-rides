//Fota-Lita Andreea-Gabriela, 321AC

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class actor{
public:
    string nume[500], functie[500];
    int nrDate = 0;

    void citirePersoane() // citirea actorilor din fisier
    {
        char c;
        ifstream fin;
        string linie;
        fin.open("persoane.csv", ios::in);
        while(getline(fin, linie)){
            int n = linie.length();
            char linieChar[n + 1];
            strcpy(linieChar, linie.c_str());

            char *cuvant = strtok(linieChar, ","); // separ cuvintele de virgula citite din linia fisierului csv
            nume[nrDate] = cuvant;
            cuvant = strtok(NULL, ",");
            functie[nrDate] = cuvant;

            nrDate++;
        }
    }

    void generareFiguranti() // adaugarea celor 132 figuranti
    {
        ofstream fout;
        fout.open("persoane.csv", ios::app);

        int i;
        for(i = nrDate; i < nrDate + 132; i++){
            nume[i] = "Figurant";
            functie[i] = "figurant";
            //fout << "Figurant" << "," << "Figurant" << endl;
        }
        nrDate = nrDate + 132;
    }

    void costAutocar() // calcularea costului transportului de la aeroport
    {
        int pretAutocar = 5680, nrAutocare;
        float costTotal;

        if(floor(nrDate / 50) == nrDate / 50) // verific daca nr de pers implicate se imparte exact la nr de locuri din autocar
            nrAutocare = nrDate / 50;
        else
            nrAutocare = nrDate / 50 + 1; // adaug 1 deoarece mai sunt persoane care ocupa un autocar, dar nu complet

        costTotal = pretAutocar * nrAutocare;
        costTotal = 2 * costTotal; // pretul dus-intors
        costTotal = costTotal / 4.65; // convertire in dolari

        // am folosit "fixed" pt a afisa si nr foarte mari
        ofstream fout1;
        fout1.open("costRomana.csv", ios::app);
        fout1 << fixed << "Transport" << "," << costTotal << endl; // adaugarea costului autocarelor la fisierul cu costurile totale

        ofstream fout2;
        fout2.open("costEngleza.csv", ios::app);
        fout2 << fixed << "Transportation" << "," << costTotal << endl;
    }
};

class monstru{
public:
    string numeMonstruRomana[500], numeMonstruEngleza[500];
    int pretMonstru[500];

    atribuireMonstru(int nrCategorie, int i){ // atribuirea clasei de monstru
        switch(nrCategorie){
        case 1:
            numeMonstruRomana[i] = "vampir";
            numeMonstruEngleza[i] = "vampire";
            pretMonstru[i] = 230;
            break;
        case 2:
            numeMonstruRomana[i] = "varcolac";
            numeMonstruEngleza[i] = "werewolf";
            pretMonstru[i] = 555;
            break;
        case 3:
            numeMonstruRomana[i] = "sirena";
            numeMonstruEngleza[i] = "mermaid";
            pretMonstru[i] = 345;
            break;
        case 4:
            numeMonstruRomana[i] = "clarvazator";
            numeMonstruEngleza[i] = "clairvoyant";
            pretMonstru[i] = 157;
            break;
        case 5:
            numeMonstruRomana[i] = "om";
            numeMonstruEngleza[i] = "human";
            pretMonstru[i] = 55;
            break;
        }
    }
};

class mancare{
public:
    string tipMancareRomana[500], tipMancareEngleza[500];
    int pretMancare[500];

    void atribuireMancare(int nrCategorie, int i) // atribuirea tipului de mancare pt fiecare pers(vegetariana etc)
    {
        switch(nrCategorie){
        case 1:
            tipMancareRomana[i] = "orice";
            tipMancareEngleza[i] = "anything";
            pretMancare[i] = 40;
            break;
        case 2:
            tipMancareRomana[i] = "vegetariana";
            tipMancareEngleza[i] = "vegetarian";
            pretMancare[i] = 33;
            break;
        case 3:
            tipMancareRomana[i] = "flexitariana";
            tipMancareEngleza[i] = "flexitarian";
            pretMancare[i] = 46;
            break;
        }
    }
};

class complet : public actor , public monstru , public mancare{
public:
    void atribuireInformatii() // atribuirea cast-ului a mancarii si a machiajelor
    {
        int i, random;

        for(i = 0; i < nrDate; i++){
            size_t found1 = functie[i].find("actor");
            size_t found2 = functie[i].find("figurant");
            if(found1 != string::npos || found2 != string::npos){ // atribui machiaj doar actorilor/figurantilor
                random = 1 + (rand() % 3);
                atribuireMonstru(random, i);
                atribuireMancare(random, i);
            }
            else
                pretMonstru[i] = 0;

            random = 1 + (rand() % 3);
            atribuireMancare(random, i);
        }
    }

    void costHotel()
    {
        float i;
        int costPerNoapte = 0, nrCamereDuble;
        int nrPersoane = nrDate - 132; // nr pers fara figuranti

        if(floor(nrPersoane / 2) == nrPersoane / 2) // verific daca nr de pers implicate se imparte exact la nr de locuri din camera de 2
            nrCamereDuble = nrPersoane / 2;
        else
            nrCamereDuble = nrPersoane / 2 + 1; // adaug 1 deoarece e o pers care sta singura in camera pt ca e nr impar de oameni

        costPerNoapte = nrCamereDuble * 350 + (132 / 3) * 420; // nr de figuranti se imparte exact la 3, deci nu exista camera neocupata complet
        costPerNoapte = costPerNoapte / 4.65; // convertire in dolari

        ofstream fout1;
        fout1.open("costRomana.csv", ios::app);
        fout1 << fixed << "Cazare" << "," << costPerNoapte * 30 << "," << costPerNoapte * 45 << "," << costPerNoapte * 60 << "," << costPerNoapte * 100 << endl; // afisarea in fisier a costului cazarii pt 30, 45, 60 si 100 zile

        ofstream fout2;
        fout2.open("costEngleza.csv", ios::app);
        fout2 << fixed << "Accomodation" << "," << costPerNoapte * 30 << "," << costPerNoapte * 45 << "," << costPerNoapte * 60 << "," << costPerNoapte * 100 << endl;
    }

    void costMachiaj()
    {
        float costPerZi = 0;
        int i;

        for(i = 0; i < nrDate; i++){
            costPerZi = costPerZi + pretMonstru[i];
        }

        costPerZi = costPerZi / 4.65; // convertire in dolari

        ofstream fout1;
        fout1.open("costRomana.csv", ios::app);
        fout1 << fixed << "Machiaj" << "," << costPerZi * 30 << "," <<costPerZi * 45 << "," << costPerZi * 60 << "," << costPerZi * 100 << endl; // afisarea in fisier a costului machiajului pt 30, 45, 60 si 100 zile

        ofstream fout2;
        fout2.open("costEngleza.csv", ios::app);
        fout2 << fixed << "Make-up" << "," << costPerZi * 30 << "," <<costPerZi * 45 << "," << costPerZi * 60 << "," << costPerZi * 100 << endl;
    }

    void costMancareApa()
    {
        float costMancareZi = 0, costApaZi = 0, costTotalZi;
        int i;

        for(i = 0; i < nrDate; i++){
            costMancareZi = costMancareZi + pretMancare[i];
        }

        costApaZi = costApaZi + (6 / 2) * nrDate + (30 / 2) * nrDate + (0.8 * 8 / 2) * nrDate; // costul lichidelor consumate pe zi (nr pret per pers * nr pers)

        costTotalZi = costApaZi + costMancareZi;
        costTotalZi = costTotalZi / 4.65; // convertire in dolari

        ofstream fout1;
        fout1.open("costRomana.csv", ios::app);
        fout1 << fixed << "Mancare si apa" << "," << costTotalZi * 30 << "," << costTotalZi * 45 << "," << costTotalZi * 60 << "," << costTotalZi * 100 << endl; // afisarea in fisier a costului mancarii si a apei pt 30, 45, 60 si 100 zile

        ofstream fout2;
        fout2.open("costEngleza.csv", ios::app);
        fout2 << fixed << "Food and water" << "," << costTotalZi * 30 << "," << costTotalZi * 45 << "," << costTotalZi * 60 << "," << costTotalZi * 100 << endl;
    }

    void costInchiriere()
    {
        double costZeceZile = 998000, costCinciZile = 5 * 10000;

        costZeceZile = costZeceZile / 4.65; // convertire in dolari
        costCinciZile = costCinciZile / 4.65;

        ofstream fout1;
        fout1.open("costRomana.csv", ios::app);
        fout1 << fixed << "Inchiriere spatiu" << "," << costZeceZile * 3 << "," <<costZeceZile * 4 + costCinciZile << "," << costZeceZile * 6 << "," << costZeceZile * 10 << endl; // afisarea in fisier a costului inchirierii castelului pt 30, 45, 60 si 100 zile

        ofstream fout2;
        fout2.open("costEngleza.csv", ios::app);
        fout2 << fixed << "Rent for space" << "," << costZeceZile * 3 << "," <<costZeceZile * 4 + costCinciZile << "," << costZeceZile * 6 << "," << costZeceZile * 10 << endl;
    }

    void creareMeniu()
    {
        //generarea meniului in romana
        ofstream fout1;
        fout1.open("meniuRomana.csv", ios::app);
        fout1 << "Meniu vegetarian" << endl;
        fout1 << "Pasta de avocado cu paine integrala" << "," << "Supa de linte cu crutoane" << "," << "Salata greceasca cu tofu" << endl;
        fout1 << "Meniu flexitarian" << endl;
        fout1 << "Paine prajita cu oua ochiuri" << "," << "Orez brun fiert in zeama de legume" << "," << "Somon la gratar" << endl;
        fout1 << "Meniu obisnuit" << endl;
        fout1 << "Gofre cu sunca si ciuperci" << "," << "Snitel la cuptor si cartofi copti" << "," << "Pastrav la cuptor";

        //meniul in engleza
        ofstream fout2;
        fout2.open("meniuEngleza.csv", ios::app);
        fout2 << "Vegetarian menu" << endl;
        fout2 << "Avocado pasta with wholemeal bread" << "," << "Lentil soup with croutons" << "," << "Greek salad with tofu" << endl;
        fout2 << "Flexitarian menu" << endl;
        fout2 << "Fried bread with eggs" << "," << "Brown rice cooked in vegetable juice" << "," << "Grilled salmon" << endl;
        fout2 << "Usual menu" << endl;
        fout2 << "Waffles with ham and mushrooms" << "," << "Baked schnitzel and baked potatoes" << "," << "Baked trout";
    }

    void generareInformatiiActori()
    {
        ofstream fout1, fout2;
        fout1.open("actoriRomana.csv", ios::app);
        fout2.open("actoriEngleza.csv", ios::app);

        int i;
        for(i = 0; i < nrDate; i++){
            size_t found1 = functie[i].find("actor");
            size_t found2 = functie[i].find("figurant");
            if(found1 != string::npos || found2 != string::npos){ // afisez doar actorii/figurantuii
                fout1 << nume[i] << "," << numeMonstruRomana[i] << "," << tipMancareRomana[i] << endl;
                fout2 << nume[i] << "," << numeMonstruEngleza[i] << "," << tipMancareEngleza[i] << endl;
            }
        }
    }
};

int main()
{
    complet x;

    x.citirePersoane();
    x.generareFiguranti();
    x.atribuireInformatii();
    x.costAutocar();
    x.costHotel();
    x.costMachiaj();
    x.costMancareApa();
    x.costInchiriere();
    x.creareMeniu();
    x.generareInformatiiActori();

    return 0;
}
