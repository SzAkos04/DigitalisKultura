#include <fstream>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Adat {
    int elso, utolso;
    char szin;
};
int n;
vector<Adat> adatok;

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
    ifstream infile("felajanlas.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'felajanlas.txt' fajlt!" << endl;
        return;
    }

    infile >> n;

    Adat a;
    while (infile >> a.elso >> a.utolso >> a.szin) {
        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;

    cout << "A felajanlasok szama: " << adatok.size() << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    cout << "A bejarat mindket oldalan ultethetok: ";
    int i = 1;
    for (const auto &adat : adatok) {
        if (adat.elso > adat.utolso) {
            cout << i << " ";
        }
        ++i;
    }
    cout << endl;
}

bool benne_van(Adat adat, int szam) {
    if (adat.elso < adat.utolso) {
        return adat.elso <= szam && adat.utolso >= szam;
    } else if (adat.utolso <= adat.elso) {
        return adat.elso <= szam || adat.utolso >= szam;
    }

    return false;
}

void feladat4() {
    cout << "4. feladat" << endl;

    cout << "Adja meg egy agyas sorszamat! ";
    int input;
    cin >> input;

    int db = 0;
    char elso_szin;
    bool found = false;

    for (const auto &adat : adatok) {
        if (benne_van(adat, input)) {
            ++db;
            if (!found) {
                elso_szin = adat.szin;
            }
            found = true;
        }
    }

    cout << "A felajanlok szama: " << db << endl;
    cout << "A viragagyas szine, ha csak az elso ultet: " << elso_szin << endl;
    cout << "A viragagyas szinei: ";
    set<char> szinek;
    for (const auto &adat : adatok) {
        if (benne_van(adat, input)) {
            szinek.insert(adat.szin);
        }
    }
    for (const auto &szin : szinek) {
        cout << szin << ' ';
    }
    cout << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;

    int s = 0;
    set<int> beultetett;
    for (const auto &adat : adatok) {
        for (int i = adat.elso; i <= adat.utolso; ++i) {
            ++s;
            beultetett.insert(i);
        }
    }

    bool jo = true;
    for (int i = 1; i <= n; ++i) {
        if (beultetett.find(i) == beultetett.end()) {
            jo = false;
        }
    }

    if (jo) {
        cout << "Minden agyas beultetesere van jelentkezo." << endl;
    } else {
        if (s >= n) {
            cout << "Atszervezessel megoldhato a beultetes." << endl;
        } else {
            cout << "A beultetes nem oldhato meg." << endl;
        }
    }
}

void feladat6() {
    ofstream outfile("szinek.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a 'szinke.txt' fajlt!" << endl;
        return;
    }

    outfile.close();
}
