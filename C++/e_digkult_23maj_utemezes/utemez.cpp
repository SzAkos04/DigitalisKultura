#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    int kezd_ho, kezd_nap;
    int veg_ho, veg_nap;
    string erdeklodok;
    string tema;
};
vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
int sorszam(int ho, int nap);
void feladat6();
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat6();
    feladat7();

    return 0;
}

void feladat1() {
    ifstream infile("taborok.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'taborok.txt' fajlt!" << endl;
        return;
    }

    Adat adat;
    while (infile >> adat.kezd_ho >> adat.kezd_nap >> adat.veg_ho >>
           adat.veg_nap >> adat.erdeklodok >> adat.tema) {
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;

    cout << "Az adatsorok szama: " << adatok.size() << endl;
    cout << "Az eloszor rogzitett tabor temaja: " << adatok.front().tema
         << endl;
    cout << "Az utoljara rogzitett tabor temaja: " << adatok.back().tema
         << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    bool found = false;
    for (const auto &adat : adatok) {
        if (adat.tema == "zenei") {
            cout << "Zenei tabor kezdodik " << adat.kezd_ho << ". ho "
                 << adat.kezd_nap << ". napjan." << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Nem volt zenei tabor." << endl;
    }
}

void feladat4() {
    cout << "4. feladat" << endl;

    int max = -1;
    for (const auto &adat : adatok) {
        if ((int)adat.erdeklodok.length() > max) {
            max = adat.erdeklodok.length();
        }
    }

    cout << "Legnepszerubbek:" << endl;

    for (const auto &adat : adatok) {
        if ((int)adat.erdeklodok.length() == max) {
            cout << adat.kezd_ho << " " << adat.kezd_nap << " " << adat.tema
                 << endl;
        }
    }
}

int sorszam(int ho, int nap) {
    int napok = 0;

    switch (ho) {
    case 6: {
        napok += nap - 15;
    } break;
    case 7: {
        napok += 30 + nap - 15;
    } break;
    case 8: {
        napok += 30 + 31 + nap - 15;
    } break;
    }

    return napok;
}

void feladat6() {
    cout << "6. feladat" << endl;

    int ho, nap;
    cout << "ho: ";
    cin >> ho;
    cout << "nap: ";
    cin >> nap;

    int i = 0;
    for (const auto &adat : adatok) {
        if (sorszam(ho, nap) >= sorszam(adat.kezd_ho, adat.kezd_nap) &&
            sorszam(ho, nap) <= sorszam(adat.veg_ho, adat.veg_nap)) {
            ++i;
        }
    }

    cout << "Ekkor eppen " << i << " tabor tart." << endl;
}

void feladat7() {
    cout << "7. feladat" << endl;

    char ch;
    cout << "Adja meg egy tanulo betujelet: ";
    cin >> ch;

    ofstream outfile("egytanulo.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    sort(adatok.begin(), adatok.end(), [](const Adat &a, const Adat &b) {
        return sorszam(a.kezd_ho, a.kezd_nap) < sorszam(b.kezd_ho, b.kezd_nap);
    });

    bool elmehet = true;
    for (const auto &adat : adatok) {
        if (adat.erdeklodok.find(ch) != string::npos) {
            outfile << adat.kezd_ho << "." << adat.kezd_nap << "-"
                    << adat.veg_ho << "." << adat.veg_nap << ". " << adat.tema
                    << endl;
            for (const auto &adatka : adatok) {
                if (adatka.erdeklodok.find(ch) != string::npos) {
                    if (sorszam(adatka.kezd_ho, adatka.kezd_nap) <
                            sorszam(adat.kezd_ho, adat.kezd_nap) &&
                        sorszam(adatka.veg_ho, adatka.veg_nap) >
                            sorszam(adat.veg_ho, adat.veg_nap)) {
                        elmehet = false;
                    }
                }
            }
        }
    }
    if (elmehet) {
        cout << "Elmehet mindegyik taborba." << endl;
    } else {
        cout << "Nem mehet el mindegyik taborba." << endl;
    }

    outfile.close();
}
