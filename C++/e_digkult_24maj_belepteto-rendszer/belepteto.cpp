#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*
   int ora = floor(adat.ido / 60.0);
   int perc = adat.ido % 60;
   outfile << (ora < 10 ? "0" : "") << ora << ":"
   << (perc < 10 ? "0" : "") << perc << endl;
*/

struct Adat {
    string kod;
    int ido; // percben
    int esemeny;
};
vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
void feladat6();
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat6();
    feladat7();

    return 0;
}

void feladat1() {
    ifstream infile("bedat.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'bedat.txt' fajlt!" << endl;
        return;
    }

    Adat adat;
    string ido;
    while (infile >> adat.kod >> ido >> adat.esemeny) {
        // parse ido
        adat.ido = stoi(ido.substr(0, 2)) * 60 + stoi(ido.substr(3, 2));
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    for (int i = 0; i < adatok.size(); ++i) {
        if (adatok.at(i).esemeny == 1) {
            int ora = floor(adatok.at(i).ido / 60.0);
            int perc = adatok.at(i).ido % 60;

            cout << "Az elso tanulo " << (ora < 10 ? "0" : "") << ora << ":"
                 << (perc < 10 ? "0" : "") << perc
                 << "-kor lepett be a fokapun." << endl;
            break;
        }
    }

    for (int i = adatok.size() - 1; i >= 0; --i) {
        if (adatok.at(i).esemeny == 2) {
            int ora = floor(adatok.at(i).ido / 60.0);
            int perc = adatok.at(i).ido % 60;

            cout << "Az utolso tanulo " << (ora < 10 ? "0" : "") << ora << ":"
                 << (perc < 10 ? "0" : "") << perc
                 << "-kor lepett ki a fokapun." << endl;
            break;
        }
    }
}

void feladat3() {
    ofstream outfile("kesok.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a 'kesok.txt' fajlt!" << endl;
        return;
    }

    for (const auto &adat : adatok) {
        if (adat.ido > 7 * 60 + 50 && adat.ido < 8 * 60 + 15) {
            int ora = floor(adat.ido / 60.0);
            int perc = adat.ido % 60;
            outfile << (ora < 10 ? "0" : "") << ora << ":"
                    << (perc < 10 ? "0" : "") << perc << " " << adat.kod
                    << endl;
        }
    }

    outfile.close();
}

void feladat4() {
    cout << "4. feladat" << endl;

    int i = 0;
    for (const auto &adat : adatok) {
        if (adat.esemeny == 3) {
            ++i;
        }
    }

    cout << "A menzan aznap " << i << " tanulo ebedelt." << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;

    set<string> kolcsonzok;
    for (const auto &adat : adatok) {
        if (adat.esemeny == 4) {
            kolcsonzok.insert(adat.kod);
        }
    }

    cout << "Aznap " << kolcsonzok.size()
         << " tanulo kolcsonzott a konyvtarban." << endl;

    set<string> menzan;
    for (const auto &adat : adatok) {
        if (adat.esemeny == 3) {
            menzan.insert(adat.kod);
        }
    }

    cout << ((kolcsonzok.size() > menzan.size())
                 ? "Tobben voltak, mint a menzan."
                 : "Nem voltak tobben, mint a menzan.")
         << endl;
}

void feladat6() {
    cout << "6. feladat" << endl;

    cout << "Az erintett tanulok:" << endl;
    set<string> bent;
    for (const auto &adat : adatok) {
        if (adat.ido <= 10 * 60 + 50) {
            switch (adat.esemeny) {
            case 1: {
                bent.insert(adat.kod);
            } break;
            case 2: {
                bent.erase(adat.kod);
            } break;
            default: {
            } break;
            }
        } else if (adat.ido > 10 * 60 + 50 && adat.ido < 11 * 60) {
            if (adat.esemeny == 1 && bent.find(adat.kod) != bent.end()) {
                cout << adat.kod << " ";
            }
        } else {
            break;
        }
    }
    cout << endl;
}

void feladat7() {
    cout << "7. feladat" << endl;

    cout << "Egy tanulo azonositoja=";
    string kod;
    cin >> kod;

    int belep_ido = -1;
    int kilep_ido;
    for (int i = 0; i < adatok.size(); ++i) {
        if (adatok.at(i).kod == kod && adatok.at(i).esemeny == 1) {
            belep_ido = adatok.at(i).ido;
            break;
        }
    }

    if (belep_ido == -1) {
        cout << "Ilyen azonositoju tanulo aznap nem volt az iskolaban." << endl;
        return;
    }

    for (int i = adatok.size() - 1; i >= 0; --i) {
        if (adatok.at(i).kod == kod && adatok.at(i).esemeny == 2) {
            kilep_ido = adatok.at(i).ido;
            break;
        }
    }

    cout << "A tanulo erkezese es tavozasa kozott "
         << floor((kilep_ido - belep_ido) / 60.0) << " ora es "
         << ((kilep_ido - belep_ido) % 60) << " perc telt el." << endl;
}
