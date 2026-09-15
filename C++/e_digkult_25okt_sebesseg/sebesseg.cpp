#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int max_tav;
struct Adat {
    int tav;
    string jelzes;
    // 10 - 90 (2 char) => sebesseghatar
    // 4 - 32 char str  => telepules
    // ]                => telepules vege
    // #                => keresztezodes
    // %                =>
};
vector<Adat> adatok;

string varos_in_nev;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
void feladat6();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat6();

    return 0;
}

void feladat1() {
    ifstream infile("ut.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni az 'ut.txt' fajlt!" << endl;
        return;
    }

    infile >> max_tav;
    Adat adat;
    while (infile >> adat.tav >> adat.jelzes) {
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << endl << "2. feladat" << endl;

    cout << "A telepulesek neve:" << endl;

    for (const auto &adat : adatok) {
        if (adat.jelzes.length() >= 4) {
            cout << adat.jelzes << endl;
        }
    }
}

void feladat3() {
    cout << endl << "3. feladat" << endl;

    cout << "Adja meg a vizsgalt szakasz hosszat km-ben! ";
    double input;
    cin >> input;

    int min_v = 90;
    bool varosban = false;
    for (const auto &adat : adatok) {
        if (adat.tav > input * 1000) {
            break;
        }

        if (adat.jelzes.length() == 2 && stoi(adat.jelzes) < min_v) {
            min_v = stoi(adat.jelzes);
        } else if (adat.jelzes.length() >= 4 && 50 < min_v) {
            min_v = 50;
            varosban = true;
        } else if (adat.jelzes.at(0) == ']' && 90 < min_v) {
            min_v = 90;
            varosban = false;
        } else if (adat.jelzes.at(0) == '%') {
            if (varosban && 50 < min_v) {
                min_v = 50;
            } else if (!varosban && 90 < min_v) {
                min_v = 90;
            }
        }
    }

    cout << "Az elso " << input << " km-en " << min_v
         << " km/h volt a legalacsonyabb megengedett sebesseg." << endl;
}

void feladat4() {
    cout << endl << "4. feladat" << endl;

    bool varosban = false;
    int cur_varos_kezd = 0;
    double varosban_s = 0;

    for (const auto &adat : adatok) {
        if (adat.jelzes.length() >= 4) {
            varosban = true;
            cur_varos_kezd = adat.tav;
        }

        if (adat.jelzes == "]") {
            varosban = false;
            varosban_s += adat.tav - cur_varos_kezd;
        }
    }

    double szazalek = (varosban_s / static_cast<double>(max_tav)) * 100.0;
    cout << fixed << setprecision(2);
    cout << "Az ut " << szazalek << " szazaleka vezet telepulesen belul."
         << endl;
}

void feladat5() {
    cout << endl << "5. feladat" << endl;

    cout << "Adja meg egy telepules nevet! ";
    cin >> varos_in_nev;

    int hossz = 0;
    int kezdet = -1;
    int tablak = 0;
    for (const auto &adat : adatok) {
        if (adat.jelzes == varos_in_nev) {
            kezdet = adat.tav;
        }

        if (kezdet != -1 && adat.jelzes.length() == 2) {
            ++tablak;
        }

        if (kezdet != -1 && adat.jelzes == "]") {
            hossz = adat.tav - kezdet;
            break;
        }
    }

    cout << "A sebessegkorlatozo tablak szama: " << tablak << endl;
    cout << "Az ut hossza a telepulesen belul " << hossz << " meter." << endl;
}

struct Varos {
    string nev;
    int kezdet, veg;
};
vector<Varos> varosok;

void feladat6() {
    cout << endl << "6. feladat" << endl;

    Varos varos;
    for (const auto &adat : adatok) {
        if (adat.jelzes.length() >= 4) {
            varos.nev = adat.jelzes;
            varos.kezdet = adat.tav;
        } else if (adat.jelzes == "]") {
            varos.veg = adat.tav;
            varosok.push_back(varos);
        }
    }

    cout << "A legkozelebbi telepules: ";

    // check first and last
    if (varos_in_nev == varosok.at(0).nev) {
        cout << varosok.at(1).nev << endl;
        return;
    } else if (varos_in_nev == varosok.at(varosok.size() - 1).nev) {
        cout << varosok.at(varosok.size() - 2).nev << endl;
        return;
    }

    // elso es utolso kivetelevel loop varosokon
    for (int i = 1; i < varosok.size() - 1; ++i) {
        if (varosok.at(i).nev == varos_in_nev) {
            int tav_elozo = varosok.at(i).kezdet - varosok.at(i - 1).veg;
            int tav_kov = varosok.at(i + 1).kezdet - varosok.at(i).veg;

            if (tav_elozo < tav_kov) {
                cout << varosok.at(i - 1).nev << endl;
            } else if (tav_elozo > tav_kov) {
                cout << varosok.at(i + 1).nev << endl;
            } else {
                cout << varosok.at(i - 1).nev << endl;
            }
            return;
        }
    }
}
