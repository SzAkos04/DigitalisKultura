#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Adat {
    // ELSO SOR
    string tipus;        // 1-2
    string kiado_orszag; // 3-5
    string nev;          // 6-44

    // MASODIK SOR
    string okmanyszam;          // 1-9
    int okmanyszam_ellenorzo;   // 10
    string nemzetiseg;          // 11-13
    string szuletesiido;        // 14-19
    int szuletesiido_ellenorzo; // 20
    string nem;                 // 21
    string ervenyesseg;         // 22-27
    int ervenyesseg_ellenorzo;  // 28
    string valaszthato;         // 29-42
    int valaszthato_ellenorzo;  // 43
    int osszesitett_ellenorzo;  // 44
};
Adat adat;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
int Elljegyszamolo(string str);
void feladat6();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    Elljegyszamolo("ABCD12349Z<");
    feladat6();

    return 0;
}

void feladat1() {
    cout << "1. feladat" << endl;

    cout << "Az allomany neve: ";
    string input;
    cin >> input;

    ifstream infile(input);
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a '" << input << "' fajlt!" << endl;
        return;
    }

    char c;
    for (int sor = 1; sor <= 2; ++sor) {
        for (int ch = 1; ch <= 44; ++ch) {
            infile >> c;
            if (sor == 1) {
                if (ch >= 1 && ch <= 2) {
                    adat.tipus.push_back(c);
                } else if (ch >= 3 && ch <= 5) {
                    adat.kiado_orszag.push_back(c);
                } else {
                    adat.nev.push_back(c);
                }
            } else {
                if (ch >= 1 && ch <= 9) {
                    adat.okmanyszam.push_back(c);
                } else if (ch == 10) {
                    adat.okmanyszam_ellenorzo = c - '0';
                } else if (ch >= 11 && ch <= 13) {
                    adat.nemzetiseg.push_back(c);
                } else if (ch >= 14 && ch <= 19) {
                    adat.szuletesiido.push_back(c);
                } else if (ch == 20) {
                    adat.szuletesiido_ellenorzo = c - '0';
                } else if (ch == 21) {
                    adat.nem.push_back(c);
                } else if (ch >= 22 && ch <= 27) {
                    adat.ervenyesseg.push_back(c);
                } else if (ch == 28) {
                    adat.ervenyesseg_ellenorzo = c - '0';
                } else if (ch >= 29 && ch <= 42) {
                    adat.valaszthato.push_back(c);
                } else if (ch == 43) {
                    adat.valaszthato_ellenorzo = c - '0';
                } else {
                    adat.osszesitett_ellenorzo = c - '0';
                }
            }
        }
    }

    infile.close();

    cout << adat.tipus << adat.kiado_orszag << adat.nev << endl
         << adat.okmanyszam << adat.okmanyszam_ellenorzo << adat.nemzetiseg
         << adat.szuletesiido << adat.szuletesiido_ellenorzo << adat.nem
         << adat.ervenyesseg << adat.ervenyesseg_ellenorzo << adat.valaszthato
         << adat.valaszthato_ellenorzo << adat.osszesitett_ellenorzo << endl;
}

void feladat2() {
    cout << "2. feladat" << endl;

    cout << "Az okmany tulajdonosa " << (adat.nem == "M" ? "ferfi" : "no")
         << "." << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    cout << "Aktualis datum: ";
    string input;
    cin >> input;

    int erveny_ev = stoi(adat.ervenyesseg.substr(0, 2));
    int erveny_ho = stoi(adat.ervenyesseg.substr(2, 2));
    int erveny_nap = stoi(adat.ervenyesseg.substr(4, 2));

    int ev = stoi(input.substr(0, 2));
    int ho = stoi(input.substr(2, 2));
    int nap = stoi(input.substr(4, 2));

    int erveny_napok = erveny_ev * 365 + erveny_ho * 30 + erveny_nap;
    int napok = ev * 365 + ho * 30 + nap;

    if (napok > erveny_napok) {
        cout << "Lejart." << endl;
    } else {
        cout << "Ervenyes." << endl;
    }
}

void feladat4() {
    cout << "4. feladat" << endl;

    string csaladinev;
    string utonev;

    bool space = false;
    bool isCsaladinev = true;

    for (const auto &ch : adat.nev) {
        if (ch == '<') {
            if (space) {
                isCsaladinev = false;
                space = false;
            } else {
                space = true;
                if (isCsaladinev) {
                    csaladinev.push_back(' ');
                } else {
                    utonev.push_back(' ');
                }
            }
        } else {
            space = false;
            if (isCsaladinev) {
                csaladinev.push_back(ch);
            } else {
                utonev.push_back(ch);
            }
        }
    }

    cout << "Csaladi nev: " << csaladinev << endl;
    cout << "Utonev: " << utonev << endl;
    cout << "A nev "
         << (adat.nev.at(adat.nev.length() - 1) == '<' ? "nem " : "")
         << "csonkolt." << endl;
}

int Elljegyszamolo(string str) {
    map<char, int> kodok;
    ifstream infile("kodok.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'kodok.txt' fajlt!" << endl;
    }

    char ch;
    int kod;
    while (infile >> ch >> kod) {
        kodok[ch] = kod;
    }

    infile.close();

    int sum = 0;
    int szorzo = 7;
    for (int i = 0; i < str.length(); ++i) {
        switch (i % 3) {
        case 0: {
            szorzo = 7;
        } break;
        case 1: {
            szorzo = 3;
        } break;
        case 2: {
            szorzo = 1;
        } break;
        }
        sum += kodok[str.at(i)] * szorzo;
    }
    return sum % 10;
}

void feladat6() {
    cout << "6. feladat" << endl;
    cout << "Okmanyszam ellenorzo szam" << endl
         << "  MRZ-kodban: " << adat.okmanyszam_ellenorzo
         << " / Szamitott ertek: " << Elljegyszamolo(adat.okmanyszam) << " "
         << (adat.okmanyszam_ellenorzo == Elljegyszamolo(adat.okmanyszam)
                 ? "HELYES"
                 : "HIBAS")
         << endl;

    cout << "Szuletesi ido ellenorzo szam" << endl
         << "  MRZ-kodban: " << adat.szuletesiido_ellenorzo
         << " / Szamitott ertek: " << Elljegyszamolo(adat.szuletesiido) << " "
         << (adat.szuletesiido_ellenorzo == Elljegyszamolo(adat.szuletesiido)
                 ? "HELYES"
                 : "HIBAS")
         << endl;

    cout << "Ervenyessegi ido ellenorzo szam" << endl
         << "  MRZ-kodban: " << adat.ervenyesseg_ellenorzo
         << " / Szamitott ertek: " << Elljegyszamolo(adat.ervenyesseg) << " "
         << (adat.ervenyesseg_ellenorzo == Elljegyszamolo(adat.ervenyesseg)
                 ? "HELYES"
                 : "HIBAS")
         << endl;
}
