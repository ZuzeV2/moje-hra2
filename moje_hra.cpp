#include <iostream>
#include <ctime>
#include <cstdlib>   // pridano pro srand() a rand()
#include <string>
using namespace std;

// Nahodne cislo generator
void Randomizer() {
    srand(static_cast<unsigned int>(time(0)));  // pridan static_cast<unsigned int>
}
// Kontrola game over: pokud v inventari existuje "Revive", ozyje se, jinak konec hry
// PUVODNE pracovalo s int&, nyni prijima float&, aby sedelo s typem zivoty
bool GameOver(float &zzivoty, string Inventar[5], float mxzivoty) {
    for (int i = 0; i < 5; i++) {
        if (Inventar[i] == "Revive") {
            cout << "Jste oziveny!\n";
            zzivoty = mxzivoty;
            Inventar[i].clear();  // Revive se spotrebuje
            return false;
        }
    }
    cout << "Sorry, nemas zadny revives.\n";
    return true;
}

// Vraci nahodny pocet enemy (1-3)
// PUVODNE funkce nic nevracela, nyni vraci int
void soubojSequence(float zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float enemyZivoty[3], int enemyReturn, float &mana, float maxmana){
    int akce;
    int inventar2;
    bool prazdny;
//smycka pro opakovani vyberu
while(true){
do{
cout << "Co chcete delat za akci?\n";
cout << "1 - Utok\n";
cout << "2 - Kouknot do inventare\n";
cout << "3 - Specialni abilitky\n";
cout << "4 - Preskocit svuj turn\n";
cin >> akce;
}while(!(akce == 1 || akce == 2 || akce == 3 || akce == 4));

switch(akce){
case 1:{
    int cil;

    do{
            cout << "Na ktereho nepritele chcete utocit?\n";
    for(int i = 0; i < enemyReturn; i++){
        cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
          }
    cin >> cil;
    cil--;
    }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

    //utok
    float poskozeni = Utok;
    enemyZivoty[cil] -= poskozeni;
     cout << "Utocil jsi nepritele " << cil + 1 << "a zpusobil jsi " << poskozeni << "poskozeni! Zbyle zivoty: " << enemyZivoty[cil] << "\n";
     if (enemyZivoty[cil] < 0){
        enemyZivoty[cil] = 0;
        cout << "Nepritel#" << cil + 1 << "zemrel\n";
     }
     return;
}
case 2:{
    prazdny = true;
    for (int i = 0; i < 5; i++) {
        if (!Inventar[i].empty()) {
            prazdny = false;
            break;
        }
    }
    if (prazdny) {
        cout << "Tvuj inventar je prazdny. Neni co pouzit.\n";
        continue;
    }

    cout << "Inventar: \n";
    for (int i = 0; i <5; i++){
        cout << i + 1 << " - " << Inventar[i] << "\n";
    }
    cout << "Chcete neco pouzit? (1 - 5 podle umisteni veci v inventari, 0 pro zruseni) \n";
    cin >> inventar2;

    if(inventar2 == 0){
        cout << "Rozhodl jste se nic nepouzit\n";
        continue;
    }
    inventar2--;

     if (inventar2 < 0 || inventar2 >= 5 || Inventar[inventar2].empty()) {
        cout << "Neplatna volba nebo prazdne misto.\n";
        continue;
    }
    string item = Inventar[inventar2];

    if (item == "Jablko") {
        zzivoty += 3;
        if (zzivoty > mxzivoty){
                zzivoty = mxzivoty;}
        cout << "Pouzil jsi jablko! Mas ted " << zzivoty << " HP.\n";
        }
        else if (item == "Susenka") {
        zzivoty += 4;
        if (zzivoty > mxzivoty){
        zzivoty = mxzivoty;}
        cout << "Snedl jsi susenku! Mas ted " << zzivoty << " HP.\n";
    }
    else if (item == "Alkohol") {
        mana += 4;
        if (mana > maxmana){
        mana = maxmana;
        }
        cout << "Vypil jsi alkohol. Mana je ted " << mana << ".\n";
    } else if (item == "Magicky potion") {
        zzivoty += 5;
        if (zzivoty > mxzivoty){
            zzivoty = mxzivoty;
        }
        mana += 5;
        if (mana > maxmana){
            mana = maxmana;
        }
        cout << "Pouzil jsi magicky potion! Mas " << zzivoty << " HP a " << mana << " many.\n";

}
        else{
    cout << "Sorry toto neuskutecnim.\n";
        }
 Inventar[inventar2].clear();
 return;
}
case 3:{
cout << "WIP\n";
return;
}
case 4:{
    cout << "Preskocil jsi svuj turn\n";
    return;
}
}
}
}

void generovaniEnemies(float &zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float &mana, float maxmana) {
    int enemyReturn = rand() % 3 + 1;  // pridano return
    float enemyZivoty[3];

    for (int i = 0; i < enemyReturn; i++) {
        enemyZivoty[i] = 5.0f;
    }
    cout << "Objevilo se " << enemyReturn << " nepritel(e)!";
    while (true) {
        bool vsichniMrtvi = true;
        for (int i = 0; i < enemyReturn; i++) {
            if (enemyZivoty[i] > 0) {
                vsichniMrtvi = false;
                break;
            }
        }
        if (vsichniMrtvi) {
            cout << "Vsichni nepratele byli porazeni!\n";
            break;
        }
    soubojSequence(zzivoty, mxzivoty, Inventar, Klasa, Utok, enemyZivoty, enemyReturn, mana, maxmana);
    for(int i = 0; i < enemyReturn; i++){
            if(enemyZivoty[i] > 0){
                float poskozeni = static_cast<float>(rand()) / RAND_MAX * 0.9f + 0.1f;
    cout << "Nepritel#" << i + 1 << " zpusobil " << poskozeni << " poskozeni.\n";
        zzivoty -= poskozeni;
        cout << "Mas " << zzivoty << "zivotu\n";
            if(zzivoty <= 0){
        zzivoty = 0;
        bool konec = GameOver(zzivoty, Inventar, mxzivoty);
        if(konec){
            cout << "Game Over\n";
            return;
        }
    }
            }
    }
}
}

// Vesnice: doplneni zivota nebo nakup
// Odstranen zbytecny parametr penizze, upravena signatura
void vesniceGenerovani(float &zivotyx, float mxzivotyx, string Inventar[5], float &mana, float maxmana) {
    int volba, volba2;

    do {
        cout << "Vitej ve vesnici!\n";
        cout << "1 - Doplnit zivoty a manu (zdarma)\n";
        cout << "2 - Jit do obchodu\n";
        cout << "3 - Odejit\n";
        cin >> volba;
    } while (!(volba == 1 || volba == 2 || volba == 3));
      // Opravena podminka: kontrolujeme volba, ne volba2

    switch (volba) {
        case 1:
            zivotyx = mxzivotyx;
            mana = maxmana;
            cout << "Vsechny zivoty a mana byly obnoveny.\n";
            break;

        case 2:
            do {
                cout << "1 - Susenka: +? HP\n";
                cout << "2 - Revive: ozivi te kdybys zemrel\n";
                cout << "3 - Alkohol: +? many\n";
                cout << "4 - Magicky potion: +? HP a +? many\n";
                cout << "5 - Nic\n";
                cin >> volba2;
            } while (!(volba2 >= 1 && volba2 <= 5));
              // Opraveno: puvodne spatna podminka (volba misto volba2 a chybne znamenko)

            switch (volba2) {
                case 1:
                    // TODO: implementace susenky
                    cout << "Koupil sis susenku. (Jeji ucinek zatim nedefinovan.)\n";
                    break;

                case 2:
                    // TODO: implementace revive
                    cout << "Koupil sis revive. (Ulozeno do inventare.)\n";
                    for (int i = 0; i < 5; i++) {
                        if (Inventar[i].empty()) {
                            Inventar[i] = "Revive";
                            cout << "Revive pridano do inventare na pozici " << i + 1 << ".\n";
                            break;
                        }
                    }
                    break;

                case 3:
                    // TODO: implementace alkoholu
                    cout << "Koupil sis alkohol. (Jeho ucinek zatim nedefinovan.)\n";
                    break;

                case 4:
                    // TODO: implementace magickeho potiona
                    cout << "Koupil sis magicky potion. (Jeho ucinek zatim nedefinovan.)\n";
                    break;

                case 5:
                    cout << "Nevybral jsi nic.\n";
                    break;
            }
            break;

        case 3:
            cout << "Odejdes z vesnice.\n";
            break;
    }
}



// Pravdepodobnost, ze se objevi strom (20%)
bool StromAppearance() {
    int sance = rand() % 100 + 1;
    return (sance < 20);
}

// Co spadne ze stromu
void stromFall(float &zzivoty, string Inventar[5]) {
    int sance = rand() % 100 + 1;

    if (sance < 70) {
        cout << "Nic nespadlo ze stromu, sorry broski.\n";
    }
    else if (sance < 90) {
        cout << "Spadlo jablko yipee!!\n";
        bool pridano = false;
        for (int i = 0; i < 5; i++) {
            if (Inventar[i].empty()) {
                Inventar[i] = "Jablko";
                cout << "Jablko pridano na pozici: " << i + 1 << ".\n";
                pridano = true;
                break;
            }
        }
        if (!pridano) {
            cout << "Inventar je plny!! :/.\n";
        }
    }
    else {
        cout << "Spadl vceli ul, -2 zivoty rip..\n";
        zzivoty -= 2;
        if (zzivoty < 0) {
            zzivoty = 0;
        }
    }
}

// Vygeneruje jeden level: kontrola zivota, vesnice, strom
void generujLevel(int Level, float &Zivoty, string Inventar[5], float mxzivoty, string klasa, float Utok, float &mana, float maxmana){
    cout << "Level: " << Level << "\n";

    // Kontrola game over
    if (Zivoty <= 0) {
        Zivoty = 0;
        bool over = GameOver(Zivoty, Inventar, mxzivoty);
        if (over) {
            cout << "Sorry, prohral jsi.\n";
            exit(0);
            // pokud GameOver vrati true, ukoncime program
        }
    }

    // Vesnice na urcitych levelech
    if (Level == 3 || Level == 6 || Level == 9 || Level == 12) {
        vesniceGenerovani(Zivoty, mxzivoty, Inventar, mana, maxmana);
        // PUVODNE se volalo bez parametru, opraveno
    }
    if (Level >= 1 && Level <= 15 && !(Level == 3 || Level == 6 || Level == 9 || Level == 12)){
        generovaniEnemies(Zivoty, mxzivoty, Inventar, klasa, Utok, mana, maxmana);
    }

    // Strom se muze objevit na kazdem levelu
    if (StromAppearance()) {
        cout << "Nasel si strom! Mozna neco z neho dostanes..\n";
        string decision22;
        cout << "Chces k nemu pristoupit? (a/n): ";
        cin >> decision22;
        if (decision22 == "a" || decision22 == "A") {
            cout << "Pristupujes ke stromu..\n";
            stromFall(Zivoty, Inventar);
        }
        else {
            cout << "Asi nemas rad stromy..\n";
        }
    }
}

// Stub pro utok - zatim jen vypisuje nahodne poskozeni
// PUVODNE nevyuzita funkce utok(int&, int&), nyni ma vhodnou signaturu

// Oziveni pomoci many
void oziveni(float &zivoty, float mxzivoty, int &mana) {
    if (mana < 1) {
        cout << "Nemas dostatek many.\n";
    }
    else if (zivoty < mxzivoty) {
        zivoty += 1;    // opraveno z "zivoty =+ 1" na "zivoty += 1"
        mana -= 1;      // opraveno z "mana =- 1" na "mana -= 1"
        cout << "Pridal sis jeden zivot yipee!\n";
    }
    else {
        cout << "Mas plne zivoty, broski.\n";
    }
}

int main() {
    Randomizer();

    string jmeno;
    string decision2 = "Ne";
    int decision1;
    string klasa3;

    float maxzivoty = 0.0f;
    float zivoty = 0.0f;
    float utok = 0.0f;
    float maxenergie = 0.0f;
    float energie = 0.0f;

    // [zivoty, utok, mana] pro kazdou klasu
    float klasyy[4][3] = {
        {5, 3, 5},  // Paladin
        {4, 4, 4},  // Lovec
        {5, 3, 5},  // Warlock
        {3, 2, 6}   // Mag
    };

    string inventar[5] = {};  // inicializace prazdnym stringem na kazde pozici

    cout << "Jak se chcete jmenovat?: ";
    cin >> jmeno;

    // Vyber tridy
    do {
        cout << "Jakou klasu chcete? (1 - Paladin, 2 - Lovec, 3 - Warlock, 4 - Mag): ";
        cin >> decision1;

        switch (decision1) {
            case 1:
                cout << "Zivoty: 5/5\n";
                cout << "Utok: 3\n";
                cout << "Mana: 5/5\n";
                cout << "Chcete si vybrat Paladina? ";
                cin >> decision2;
                if (decision2 == "Ano") {
                    maxzivoty = klasyy[0][0];
                    utok      = klasyy[0][1];
                    maxenergie = klasyy[0][2];
                    klasa3 = "Paladin";
                    cout << "Vybrali jste si Paladina.\n";
                }
                break;

            case 2:
                cout << "Zivoty: 4/4\n";
                cout << "Utok: 4\n";
                cout << "Mana: 4/4\n";
                cout << "Chcete si vybrat Lovce? ";
                cin >> decision2;
                if (decision2 == "Ano") {
                    maxzivoty = klasyy[1][0];
                    utok      = klasyy[1][1];
                    maxenergie   = klasyy[1][2];
                    klasa3 = "Lovec";
                    cout << "Vybrali jste si Lovce.\n";
                }
                break;

            case 3:
                cout << "Zivoty: 5/5\n";
                cout << "Utok: 3\n";
                cout << "Mana: 5/5\n";
                cout << "Chcete si vybrat Warlocka? ";
                cin >> decision2;
                if (decision2 == "Ano") {
                    maxzivoty = klasyy[2][0];
                    utok      = klasyy[2][1];
                    maxenergie   = klasyy[2][2];
                    klasa3 = "Warlock";
                    cout << "Vybrali jste si Warlocka.\n";
                }
                break;

            case 4:
                cout << "Zivoty: 3/3\n";
                cout << "Utok: 2\n";
                cout << "Mana: 6/6\n";
                cout << "Chcete si vybrat Maga? ";
                cin >> decision2;
                if (decision2 == "Ano") {
                    maxzivoty = klasyy[3][0];
                    utok      = klasyy[3][1];
                    maxenergie   = klasyy[3][2];
                    klasa3 = "Mag";
                    cout << "Vybrali jste si Maga.\n";
                }
                break;

            default:
                cout << "Spatne cislo, zkus to znovu.\n";
                break;
        }
    } while (decision2 != "Ano");
      // Dokud uzivatel nenapise "Ano", pokracuje smycka

    // Nastaveni aktualniho zivota po vyberu tridy
    energie = maxenergie;
    zivoty = maxzivoty;  // doplneno, jinak by zivoty nebyly inicializovane
// mini boss = level 7, 13
//boss = level 15
// Prochazeni Levely 1-15
    for (int level = 1; level <= 15; level++) {
        generujLevel(level, zivoty, inventar, maxzivoty, klasa3, utok, energie, maxenergie);
        cout << "\n";
    }

    return 0;
}
