#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    int nap;
    string varos; // "PL" / "TV" / "NR"
    int darab;
};
vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
int osszes(string varos, int nap);
void feladat7();
void feladat8();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat7();
    feladat8();

    return 0;
}

void feladat1() {
    ifstream infile("rendel.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'rendel.txt' fajlt!" << endl;
        return;
    }

    Adat adat;
    while (infile >> adat.nap >> adat.varos >> adat.darab) {
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat:" << endl;

    cout << "A rendelesek szama: " << adatok.size() << endl;
}

void feladat3() {
    cout << "3. feladat:" << endl;

    int nap;
    cout << "Kerem, adjon meg egy napot: ";
    cin >> nap;

    int i = 0;
    for (const auto &adat : adatok) {
        if (adat.nap == nap) {
            ++i;
        }
    }

    cout << "A rendelesek szama az adott napon: " << i << endl;
}

void feladat4() {
    cout << "4. feladat:" << endl;

    set<int> rendelesi_napok;
    for (const auto &adat : adatok) {
        if (adat.varos == "NR") {
            rendelesi_napok.insert(adat.nap);
        }
    }

    int n = 0;
    for (int i = 1; i <= 30; ++i) {
        if (rendelesi_napok.find(i) == rendelesi_napok.end()) {
            ++n;
        }
    }

    cout << n << " nap nem volt a reklamban nem erintett varosbol rendeles"
         << endl;
}

void feladat5() {
    cout << "5. feladat:" << endl;

    int max = -1;
    for (const auto &adat : adatok) {
        if (adat.darab > max) {
            max = adat.darab;
        }
    }

    for (const auto &adat : adatok) {
        if (adat.darab == max) {
            cout << "A legnagyobb darabszam: " << max
                 << ", a rendeles napja: " << adat.nap << endl;
            break;
        }
    }
}

int osszes(string varos, int nap) {
    int s = 0;
    for (const auto &adat : adatok) {
        if (adat.varos == varos && adat.nap == nap) {
            s += adat.darab;
        }
    }

    return s;
}

void feladat7() {
    cout << "7. feladat:" << endl;

    cout << "A rendelt termekek darabszama a 21. napon PL: " << osszes("PL", 21)
         << " TV: " << osszes("TV", 21) << " NR: " << osszes("NR", 21) << endl;
}

int sum_rendeles(string varos, int kezd, int veg) {
    int s = 0;
    for (const auto &adat : adatok) {
        if (adat.varos == varos && adat.nap >= kezd && adat.nap <= veg) {
            ++s;
        }
    }

    return s;
}

void feladat8() {
    cout << "8. feladat:" << endl;

    ostringstream ss;
    ss << "Napok\t1..10\t11..20\t21..30" << endl
       << "PL\t" << sum_rendeles("PL", 1, 10) << "\t"
       << sum_rendeles("PL", 11, 20) << "\t" << sum_rendeles("PL", 21, 30)
       << endl
       << "TV\t" << sum_rendeles("TV", 1, 10) << "\t"
       << sum_rendeles("TV", 11, 20) << "\t" << sum_rendeles("TV", 21, 30)
       << endl
       << "NR\t" << sum_rendeles("NR", 1, 10) << "\t"
       << sum_rendeles("NR", 11, 20) << "\t" << sum_rendeles("NR", 21, 30)
       << endl;

    cout << ss.str();

    ofstream outfile("kampany.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a 'kampany.txt' fajlt!" << endl;
        return;
    }

    outfile << ss.str();

    outfile.close();
}
