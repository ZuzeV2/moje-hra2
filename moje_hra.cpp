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
    cout << "Game Over\n";
    exit(0);
    return true;
}

// Vraci nahodny pocet enemy (1-3)
// PUVODNE funkce nic nevracela, nyni vraci int
void soubojSequence(float &zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float enemyZivoty[3], int enemyReturn, float &mana, float maxmana, bool &neviditelnost){
    int cil;
    int akce;
    int inventar2;
    bool prazdny;
    int special;
//smycka pro opakovani vyberu
while(true){
        cout << "Mate " << zzivoty << " zivotu a " << mana << " many.\n";
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
    } else if (item == "Magickypotion") {
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
    if(Klasa == "Paladin"){
        cout << "Co chcete pouzit?\n";
        cout << "1 - Uder svetlem = 2 poskozeni vsem nepratelum (-2 mana)\n";
        cout << "2 - Oziveni = Pridani 2 zivotu (-2 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
        if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
        if(mana < 2){
            cout << "Nemas dost many\n";
            continue;
        }
        mana -= 2;

        if(special == 1){
            cout << "Pouzil jsi uder svetlem!";
            for (int i = 0; i < enemyReturn; i++){
                enemyZivoty[i] -= 2;
                if (enemyZivoty[i] < 0){
                    enemyZivoty[i] = 0;}
                    cout << "Nepratel#" << i + 1 << "ma ted: " << enemyZivoty[i] << " HP\n";

                }
            }
        else if (special == 2){
            zzivoty += 2;
            if (zzivoty > mxzivoty){
                zzivoty = mxzivoty;
            }
            cout << "Pouzil jsi oziveni. Mas ted: " << zzivoty << " zivotu\n";
        }
    return;
    }
    if (Klasa == "Lovec"){
     cout << "Co chcete pouzit?\n";
        cout << "1 - Smrtici sip = zasahne nepritele za 6 dmg (-2 mana)\n";
        cout << "2 - Ukryt ve stinu = Budes neporazitelny pri levelu (-5 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
     if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
        if(special == 1){
                if (mana < 2){
                    cout << "Nemate dostatek many\n";
                    continue;
                }
        else{
        do{
            cout << "Na ktereho nepritele chcete utocit?\n";
            for(int i = 0; i < enemyReturn; i++){
            cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
            }
            cin >> cil;
            cil--;
        }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

        mana -= 2;
        enemyZivoty[cil] -= 6;
        if(enemyZivoty[cil] < 0){
            enemyZivoty[cil] = 0;
        }
        cout << "Nepritel#" << cil + 1 << "ma ted: " << enemyZivoty[cil] << " HP\n";
        }
        }
        else if (special == 2){
                if(mana < 5){
                    cout << "Nemate dost many\n";
                    continue;
                }
                else{
                    mana -= 5;
                    neviditelnost = true;
                    cout <<"Pouzil jsi ukryt ve stinu, a ted na vas nepritele nebudou utocit\n";
                }
            }
            return;
        }
    if (Klasa == "Warlock"){
        cout << "Co chcete pouzit?\n";
        cout << "1 - Krvavy ritual = Obetovani 1 zivot za 2 many\n";
        cout << "2 - Temny vyboj = Udelej 10 dmg na nepritele (-2,5 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
     if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
     if(special == 1){
            if(zzivoty <= 1){
                cout << "Nemate dost zivotu\n";
                continue;
            }
            else if(mana >= maxmana){
                cout << "Nemate misto pro manu\n";
                continue;
            }
            else{
            zzivoty -= 1;
            mana += 2;
            if(mana > maxmana){
                mana = maxmana;
            }
            cout << "Pouzil jsi krvavy ritual!\n";
            cout << "Mas ted: " << zzivoty << " zivotu a " << mana << " many\n";
            }
        }
    else if (special == 2){
    if (mana < 2.5){
        cout << "Nemate dostatek many\n";
        continue;
    }
    else{
        do{
            cout << "Na ktereho nepritele chcete utocit?\n";
            for(int i = 0; i < enemyReturn; i++){
            cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
            }
            cin >> cil;
            cil--;
        }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

        mana -= 2.5;
        enemyZivoty[cil] -= 10;
        if(enemyZivoty[cil] < 0){
            enemyZivoty[cil] = 0;
        }
        cout << "Pouzil jste temny vyboj a nepritel#" << cil + 1 << "ma ted: " << enemyZivoty[cil] << " HP\n";
    }
    }
    return;
    }
    if (Klasa == "Mag"){
         cout << "Co chcete pouzit?\n";
        cout << "1 - Ohniva koule = 6 poskozeni jednomu nepriteli (-2 mana)\n";
        cout << "2 - Retezovy blesk = 5 poskozeni vsem nepratelum (-4 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
     if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
    if(special == 1){
        if(mana < 2){
            cout << "Nemate dostatek many\n";
            continue;
        }
        else{
              do{
            cout << "Na ktereho nepritele chcete utocit?\n";
            for(int i = 0; i < enemyReturn; i++){
            cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
            }
            cin >> cil;
            cil--;
        }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

        mana -= 2;
        enemyZivoty[cil] -= 6;
        if (enemyZivoty[cil] < 0){
            enemyZivoty[cil] = 0;
        }
        cout << "Nepritel#" << cil + 1 << "ma ted " << enemyZivoty[cil] << " HP\n";
        }
    }
    else if (special == 2){
            cout << "Pouzil jsi retezovy blesk!";
            for (int i = 0; i < enemyReturn; i++){
                enemyZivoty[i] -= 5;
                if (enemyZivoty[i] < 0){
                    enemyZivoty[i] = 0;}
                    cout << "Nepratel#" << i + 1 << "ma ted: " << enemyZivoty[i] << " HP\n";
                }
    }
        return;
    }
}
case 4:{
    cout << "Preskocil jsi svuj turn\n";
    return;
}
}
}
}
void generovaniEnemies(float &zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float &mana, float maxmana, float &penize2) {
    bool neviditelnost = false;
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
            penize2 += 5;
            break;
        }
    soubojSequence(zzivoty, mxzivoty, Inventar, Klasa, Utok, enemyZivoty, enemyReturn, mana, maxmana, neviditelnost);
    for(int i = 0; i < enemyReturn; i++){
            if(enemyZivoty[i] > 0){
                float poskozeni = static_cast<float>(rand()) / RAND_MAX * 0.9f + 0.1f;
        if(!neviditelnost){
    cout << "Nepritel#" << i + 1 << " zpusobil " << poskozeni << " poskozeni.\n";
        zzivoty -= poskozeni;
        cout << "Mas " << zzivoty << "zivotu\n";
        }
        else{
            cout << "Nepritel#" << i + 1 << " te nevidel a minul jeho utok\n";
        }

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
neviditelnost = false;
}
void generovaniMiniBoss(float &zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float &mana, float maxmana, float &penize2){
bool neviditelnost = false;
    int enemyReturn = 1;
    float enemyZivoty[1] = {15.0f};

    cout << "Objevil se mini boss s " << enemyZivoty[0] << " HP\n";
    while (true) {
        bool vsichniMrtvi = true;
        for (int i = 0; i < enemyReturn; i++) {
            if (enemyZivoty[i] > 0) {
                vsichniMrtvi = false;
                break;
            }
        }
        if (vsichniMrtvi) {
            cout << "Miniboss byl porazen!\n";
            penize2 += 15;
            break;
        }
    soubojSequence(zzivoty, mxzivoty, Inventar, Klasa, Utok, enemyZivoty, enemyReturn, mana, maxmana, neviditelnost);
    for(int i = 0; i < enemyReturn; i++){
            if(enemyZivoty[i] > 0){
                float poskozeni = static_cast<float>(rand()) / RAND_MAX * 2.5f + 0.5f;
        if(!neviditelnost){
    cout << "Miniboss zpusobil " << poskozeni << " poskozeni.\n";
        zzivoty -= poskozeni;
        cout << "Mas " << zzivoty << "zivotu\n";
        }
        else{
            cout << "Miniboss te nevidel a minul jeho utok\n";
        }

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
neviditelnost = false;
}
void soubojSequenceBoss(float &zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float enemyZivoty[3], int enemyReturn, float &mana, float maxmana, bool &neviditelnost, bool &hracZautocil){
 int cil;
    int akce;
    int inventar2;
    bool prazdny;
    int special;
//smycka pro opakovani vyberu
while(true){
        cout << "Mate " << zzivoty << " zivotu a " << mana << " many.\n";
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
     hracZautocil = true;
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
    } else if (item == "Magickypotion") {
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
 hracZautocil = false;
 return;
}
case 3:{
    if(Klasa == "Paladin"){
        cout << "Co chcete pouzit?\n";
        cout << "1 - Uder svetlem = 2 poskozeni vsem nepratelum (-2 mana)\n";
        cout << "2 - Oziveni = Pridani 2 zivotu (-2 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
        if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
        if(mana < 2){
            cout << "Nemas dost many\n";
            continue;
        }
        mana -= 2;

        if(special == 1){
            cout << "Pouzil jsi uder svetlem!";
            for (int i = 0; i < enemyReturn; i++){
                enemyZivoty[i] -= 2;
                if (enemyZivoty[i] < 0){
                    enemyZivoty[i] = 0;}
                    cout << "Nepratel#" << i + 1 << "ma ted: " << enemyZivoty[i] << " HP\n";

                }
                hracZautocil = true;
            }
        else if (special == 2){
            zzivoty += 2;
            if (zzivoty > mxzivoty){
                zzivoty = mxzivoty;
            }
            cout << "Pouzil jsi oziveni. Mas ted: " << zzivoty << " zivotu\n";
        }
    return;
    }
    if (Klasa == "Lovec"){
     cout << "Co chcete pouzit?\n";
        cout << "1 - Smrtici sip = zasahne nepritele za 6 dmg (-2 mana)\n";
        cout << "2 - Ukryt ve stinu = Budes neporazitelny pri levelu (-5 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
     if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
        if(special == 1){
                if (mana < 2){
                    cout << "Nemate dostatek many\n";
                    continue;
                }
        else{
        do{
            cout << "Na ktereho nepritele chcete utocit?\n";
            for(int i = 0; i < enemyReturn; i++){
            cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
            }
            cin >> cil;
            cil--;
        }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

        mana -= 2;
        enemyZivoty[cil] -= 6;
        if(enemyZivoty[cil] < 0){
            enemyZivoty[cil] = 0;
        }
        cout << "Nepritel#" << cil + 1 << "ma ted: " << enemyZivoty[cil] << " HP\n";
        hracZautocil = true;
        }
        }
        else if (special == 2){
                if(mana < 5){
                    cout << "Nemate dost many\n";
                    continue;
                }
                else{
                    mana -= 5;
                    neviditelnost = true;
                    cout <<"Pouzil jsi ukryt ve stinu, a ted na vas nepritele nebudou utocit\n";
                }
            }
            return;
        }
    if (Klasa == "Warlock"){
        cout << "Co chcete pouzit?\n";
        cout << "1 - Krvavy ritual = Obetovani 1 zivot za 2 many\n";
        cout << "2 - Temny vyboj = Udelej 10 dmg na nepritele (-2,5 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
     if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
     if(special == 1){
            if(zzivoty <= 1){
                cout << "Nemate dost zivotu\n";
                continue;
            }
            else if(mana >= maxmana){
                cout << "Nemate misto pro manu\n";
                continue;
            }
            else{
            zzivoty -= 1;
            mana += 2;
            if(mana > maxmana){
                mana = maxmana;
            }
            cout << "Pouzil jsi krvavy ritual!\n";
            cout << "Mas ted: " << zzivoty << " zivotu a " << mana << " many\n";
            }
        }
    else if (special == 2){
    if (mana < 2.5){
        cout << "Nemate dostatek many\n";
        continue;
    }
    else{
        do{
            cout << "Na ktereho nepritele chcete utocit?\n";
            for(int i = 0; i < enemyReturn; i++){
            cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
            }
            cin >> cil;
            cil--;
        }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

        mana -= 2.5;
        enemyZivoty[cil] -= 10;
        if(enemyZivoty[cil] < 0){
            enemyZivoty[cil] = 0;
        }
        cout << "Pouzil jste temny vyboj a nepritel#" << cil + 1 << "ma ted: " << enemyZivoty[cil] << " HP\n";
        hracZautocil = true;
    }
    }
    return;
    }
    if (Klasa == "Mag"){
         cout << "Co chcete pouzit?\n";
        cout << "1 - Ohniva koule = 6 poskozeni jednomu nepriteli (-2 mana)\n";
        cout << "2 - Retezovy blesk = 5 poskozeni vsem nepratelum (-4 mana)\n";
        cout << "0 - Nic\n";
        cin >> special;
     if (!(special == 1 || special == 2)){
                cout << "Zadali jste spatne cislo, nebo jste zrusili svuj attack\n";
            continue;
        }
    if(special == 1){
        if(mana < 2){
            cout << "Nemate dostatek many\n";
            continue;
        }
        else{
              do{
            cout << "Na ktereho nepritele chcete utocit?\n";
            for(int i = 0; i < enemyReturn; i++){
            cout << "Nepritel#" << i + 1 << "ma " << enemyZivoty[i] << "HP\n";
            }
            cin >> cil;
            cil--;
        }while(cil < 0 || cil >= enemyReturn || enemyZivoty[cil] <= 0);

        mana -= 2;
        enemyZivoty[cil] -= 6;
        if (enemyZivoty[cil] < 0){
            enemyZivoty[cil] = 0;
        }
        cout << "Nepritel#" << cil + 1 << "ma ted " << enemyZivoty[cil] << " HP\n";
        }
    }
    else if (special == 2){
            cout << "Pouzil jsi retezovy blesk!";
            for (int i = 0; i < enemyReturn; i++){
                enemyZivoty[i] -= 5;
                if (enemyZivoty[i] < 0){
                    enemyZivoty[i] = 0;}
                    cout << "Nepratel#" << i + 1 << "ma ted: " << enemyZivoty[i] << " HP\n";
                }
    }
        hracZautocil = true;
        return;
    }
}
case 4:{
    cout << "Preskocil jsi svuj turn\n";
    hracZautocil = false;
    return;
}
}
}
}

void generovaniBoss(float &zzivoty, float mxzivoty, string Inventar[5], string Klasa, float Utok, float &mana, float maxmana){
bool neviditelnost = false;
bool hracZautocil = false;
int BloomshadeRage = 0;
int kolabezutoku = 0;
bool aktivni = false;
    int enemyReturn = 1;
    float enemyZivoty[1] = {30.0f};

    cout << "Objevil se boss Bloomshade s " << enemyZivoty[0] << " HP\n";
    cout << "Vypada jako nevinna kvetina..\n";
    while (true) {
        bool vsichniMrtvi = true;
        for (int i = 0; i < enemyReturn; i++) {
            if (enemyZivoty[i] > 0) {
                vsichniMrtvi = false;
                break;
            }
        }
        if (vsichniMrtvi) {
            cout << "Bloomshade byl porazen!\n";
            break;
        }
    soubojSequenceBoss(zzivoty, mxzivoty, Inventar, Klasa, Utok, enemyZivoty, enemyReturn, mana, maxmana, neviditelnost, hracZautocil);
    if (enemyZivoty[0] > 0){
        if (!aktivni && hracZautocil){
            aktivni = true;
            cout << "Bloomshade se probudil a je rozliceny tvym utokem!\n";
        }

    if(aktivni){
        if (hracZautocil) {
            BloomshadeRage++;
            kolabezutoku = 0;
    } else{
        kolabezutoku++;
        if (kolabezutoku >= 2){
            BloomshadeRage--;
            cout << "Bloomshade se uklidnuje\n";
            if(BloomshadeRage <= 0){
                aktivni = false;
                BloomshadeRage = 0;
                cout << "Bloomshade se opet maskuje jako nevinna kvetina\n";
            }
        }
    }
    }
    float poskozeni = 5.0f * BloomshadeRage;
    if (!neviditelnost){
         cout << "Bloomshade zautocil silou prirody a zpusobil " << poskozeni << " poskozeni\n";
        zzivoty -= poskozeni;
        if (zzivoty < 0) zzivoty = 0;
        cout << "Mas " << zzivoty << " zivotu\n";
    }else {
        cout << "Bloomshade te nevidel a minul svuj utok.\n";
    }
     if (zzivoty <= 0) {
        bool konec = GameOver(zzivoty, Inventar, mxzivoty);
        if (konec) {
            cout << "Game Over.\n";
            return;
        }
        }
     else {
    cout << "Bloomshade nehybne stoji a ceka...\n";}
    }

neviditelnost = false;
}
}


// Vesnice: doplneni zivota nebo nakup
// Odstranen zbytecny parametr penizze, upravena signatura
void vesniceGenerovani(float &zivotyx, float mxzivotyx, string Inventar[5], float &mana, float maxmana, float &penize2) {
    int volba, volba2;
while(true){
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
            continue;

        case 2:
            do {
                cout << "1 - Susenka: 4 HP\n";
                cout << "2 - Revive: ozivi te kdybys zemrel\n";
                cout << "3 - Alkohol: 4 many\n";
                cout << "4 - Magicky potion: 5 HP a 5 many\n";
                cout << "5 - Nic\n";
                cin >> volba2;
            } while (!(volba2 >= 1 && volba2 <= 5));
              // Opraveno: puvodne spatna podminka (volba misto volba2 a chybne znamenko)

            switch (volba2) {
                case 1:
                    // TODO: implementace susenky
                    if(penize2 >= 5){
                        penize2 -= 5;
                    cout << "Koupil sis susenku.\n";
                     for (int i = 0; i < 5; i++) {
                        if (Inventar[i].empty()) {
                            Inventar[i] = "Susenka";
                            cout << "Susenka pridana do inventare na pozici " << i + 1 << ".\n";
                            break;
                        }
                    }}
                    if(penize2 < 5){
                        cout << "Nemate dost penez.\n";
                    }
                    break;

                case 2:
                    // TODO: implementace revive
                    if(penize2 >= 7){
                    cout << "Koupil sis revive. (Ulozeno do inventare.)\n";
                    for (int i = 0; i < 5; i++) {
                        if (Inventar[i].empty()) {
                            Inventar[i] = "Revive";
                            cout << "Revive pridano do inventare na pozici " << i + 1 << ".\n";
                            break;
                        }
                    }}
                    if(penize2 < 7){
                        cout << "Nemate dost penez.\n";
                    }
                    break;

                case 3:
                    // TODO: implementace alkoholu
                    if(penize2 >= 5){
                    cout << "Koupil sis alkohol.\n";
                    for (int i = 0; i < 5; i++) {
                        if (Inventar[i].empty()) {
                            Inventar[i] = "Alkohol";
                            cout << "Alkohol pridan do inventare na pozici " << i + 1 << ".\n";
                            break;
                        }
                    }}
                    if(penize2 < 5){
                        cout << "Nemate dost penez.\n";
                    }
                    break;

                case 4:
                    // TODO: implementace magickeho potiona
                    if(penize2 >= 15){
                    cout << "Koupil sis magicky potion.\n";
                    for (int i = 0; i < 5; i++) {
                        if (Inventar[i].empty()) {
                            Inventar[i] = "Magickypotion";
                            cout << "Magicky potion pridan do inventare na pozici " << i + 1 << ".\n";
                            break;
                        }
                    }}
                    if(penize2 < 15){
                        cout << "Nemate dost penez.\n";
                    }
                    break;

                case 5:
                    cout << "Nevybral jsi nic.\n";
                    break;
            }
            break;
            continue;

        case 3:
            cout << "Odejdes z vesnice.\n";
            return;
    }
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
void generujLevel(int Level, float &Zivoty, string Inventar[5], float mxzivoty, string klasa, float Utok, float &mana, float maxmana, float &penize2){
    cout << "Level: " << Level << "\n";

    // Kontrola game over - zbytecne ale necham protoze proc ne
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
        vesniceGenerovani(Zivoty, mxzivoty, Inventar, mana, maxmana, penize2);
        // PUVODNE se volalo bez parametru, opraveno
    }
    else if (Level >= 1 && Level <= 15 && !(Level == 3 || Level == 7 || Level == 6 || Level == 9 || Level == 12 || Level == 13 || Level == 15)){
        generovaniEnemies(Zivoty, mxzivoty, Inventar, klasa, Utok, mana, maxmana, penize2);
    }
    else if (Level == 7 || Level == 13){
        generovaniMiniBoss(Zivoty, mxzivoty, Inventar, klasa, Utok, mana, maxmana, penize2);
    }
    else if (Level == 15){
        generovaniBoss(Zivoty, mxzivoty, Inventar, klasa, Utok, mana, maxmana);
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
    float penize = 0.0f;

    // [zivoty, utok, mana] pro kazdou klasu
    float klasyy[4][3] = {
        {10, 3, 5},  // Paladin
        {9, 4, 4},  // Lovec
        {10, 3, 5},  // Warlock
        {8, 2, 6}   // Mag
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
                cout << "Zivoty: 10/10\n";
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
                cout << "Zivoty: 9/9\n";
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
                cout << "Zivoty: 10/10\n";
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
                cout << "Zivoty: 8/8\n";
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
        generujLevel(level, zivoty, inventar, maxzivoty, klasa3, utok, energie, maxenergie, penize);
        cout << "\n";
    }
cout << "Vyhral jsi!";
    return 0;
}
