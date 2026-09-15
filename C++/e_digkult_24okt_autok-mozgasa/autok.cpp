#include <cmath>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Adat {
    string rendszam;
    int ora, perc;
    int sebesseg;
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
    ifstream infile("jeladas.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'jeladas.txt' fajlt!" << endl;
        return;
    }

    Adat adat;
    while (infile >> adat.rendszam >> adat.ora >> adat.perc >> adat.sebesseg) {
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat:" << endl;

    const auto &adat = adatok.at(adatok.size() - 1);
    cout << "Az utolso jeladas idopontja " << adat.ora << ":" << adat.perc
         << ", a jarmu rendszama " << adat.rendszam << endl;
}

void feladat3() {
    cout << "3. feladat:" << endl;

    auto elso_rendszam = adatok.at(0).rendszam;
    cout << "Az elso jarmu: " << elso_rendszam << endl;
    cout << "Jeladasainak idopontjai: ";
    for (const auto &adat : adatok) {
        if (adat.rendszam == elso_rendszam) {
            cout << adat.ora << ":" << adat.perc << " ";
        }
    }
    cout << endl;
}

void feladat4() {
    cout << "4. feladat:" << endl;

    int ora, perc;
    cout << "Kerem, adja meg az orat: ";
    cin >> ora;
    cout << "Kerem, adja meg a percet: ";
    cin >> perc;

    int i = 0;
    for (const auto &adat : adatok) {
        if (adat.ora == ora && adat.perc == perc) {
            ++i;
        }
    }

    cout << "A jeladasok szama: " << i << endl;
}

void feladat5() {
    cout << "5. feladat:" << endl;

    int max_sebesseg = -1;
    for (const auto &adat : adatok) {
        if (max_sebesseg < adat.sebesseg) {
            max_sebesseg = adat.sebesseg;
        }
    }

    cout << "A legnagyobb sebesseg km/h: " << max_sebesseg << endl;
    cout << "A jarmuvek: ";
    for (const auto &adat : adatok) {
        if (adat.sebesseg == max_sebesseg) {
            cout << adat.rendszam << " ";
        }
    }
    cout << endl;
}

void feladat6() {
    cout << "6. feladat:" << endl;

    string rendszam;
    cout << "Kerem, adja meg a rendszamot: ";
    cin >> rendszam;

    double ut = 0.0;
    int prev_sebesseg = 0;
    double prev_ido = 0.0;

    for (const auto &adat : adatok) {
        if (adat.rendszam == rendszam) {
            ut += prev_sebesseg *
                  (adat.ora + ((double)adat.perc / 60) - prev_ido);
            cout << fixed << setprecision(1);
            cout << adat.ora << ":" << adat.perc << " " << ut << " km" << endl;
            prev_sebesseg = adat.sebesseg;
            prev_ido = adat.ora + ((double)adat.perc / 60);
        }
    }

    // nincs ilyen auto
    if (ut == 0) {
        cout << "Nincs '" << rendszam << "' rendszamu auto az adatok kozott!"
             << endl;
    }
}

void feladat7() {
    ofstream outfile("ido.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni az 'ido.txt' fajlt!" << endl;
        return;
    }

    // set<rendszam, pair<percek_kezd, percek_veg>>
    map<string, pair<int, int>> autok;
    int kezd, veg;
    for (size_t i = 0; i < adatok.size(); ++i) {
        if (autok.find(adatok.at(i).rendszam) == autok.end()) {
            int kezd = adatok.at(i).ora * 60 + adatok.at(i).perc;
            int veg = kezd;

            for (int j = static_cast<int>(adatok.size()) - 1; j >= 0; --j) {
                if (adatok.at(j).rendszam == adatok.at(i).rendszam) {
                    veg = adatok.at(j).ora * 60 + adatok.at(j).perc;
                    break;
                }
            }

            autok[adatok.at(i).rendszam] = make_pair(kezd, veg);
        }
    }

    for (const auto &a : autok) {
        outfile << a.first << " " << (floor(a.second.first / 60.0)) << " "
                << (a.second.first % 60) << " "
                << (floor(a.second.second / 60.0)) << " "
                << (a.second.second % 60) << endl;
    }

    outfile.close();
}
