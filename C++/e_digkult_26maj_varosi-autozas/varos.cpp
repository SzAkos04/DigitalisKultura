#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string ID;
struct Adat {
    int kezdet, veg, vegsebesseg;
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
    cout << "1. feladat" << endl;
    cout << "Kerem adja meg az auto azonositojat! ";
    cin >> ID;

    ifstream infile(ID + string(".txt"));
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a '" << ID << ".txt' fajlt!" << endl;
        return;
    }

    Adat a;
    while (infile >> a.kezdet >> a.veg >> a.vegsebesseg) {
        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    for (int i = 0; i < adatok.size(); ++i) {
        if (adatok.at(i).vegsebesseg > 0) {
            cout << "Az auto a " << adatok.at(i).kezdet
                 << ". masodpercben indult el." << endl;
            break;
        }
    }

    cout << "Az auto a megfigyeles vegen "
         << adatok.at(adatok.size() - 1).vegsebesseg
         << " m/s sebesseggel haladt." << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    for (const auto &adat : adatok) {
        if (adat.vegsebesseg > 14) {
            cout << "Az auto atlepte a sebesseghatart." << endl;
            return;
        }
    }
    cout << "Az auto nem lepte at a sebesseghatart." << endl;
}

void feladat4() {
    cout << "4. feladat" << endl;

    int max_t = -1;
    int max_kezdet = -1;
    int cur_v = 0;
    int cur_t = 0;

    for (const auto &adat : adatok) {
        if (cur_v == 0 && max_t < adat.kezdet - cur_t) {
            max_kezdet = cur_t;
            max_t = adat.kezdet - cur_t;
        }

        cur_v = adat.vegsebesseg;
        cur_t = adat.veg;
    }

    cout << "A leghosszabb allasido " << max_kezdet << " es "
         << (max_kezdet + max_t) << " kozott volt." << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;

    cout << "Mikor vizsgaljuk az auto sebesseget? ";
    int input;
    cin >> input;

    Adat a;
    int cur_v;
    for (const auto &adat : adatok) {
        if (adat.kezdet < input && adat.veg > input) {
            a = adat;
            break;
        }
        cur_v = adat.vegsebesseg;
    }

    double v1 = cur_v;
    double v2 = a.vegsebesseg;
    double t1 = a.kezdet;
    double t2 = a.veg;
    double t = input;

    double v = v1 + ((v2 - v1) / (t2 - t1)) * (t - t1);

    cout << "Az auto sebessege a(z) " << input << ". masodpercben " << v
         << " m/s volt." << endl;
}

void feladat6() {
    cout << "6. feladat" << endl;

    double s = 0;
    int cur_v = 0;
    int cur_t = 0;

    for (size_t i = 0; i < adatok.size(); ++i) {
        // gyorsulo szakasz
        const auto &adat = adatok.at(i);

        s += (cur_v + adat.vegsebesseg) / 2.0 * (adat.veg - adat.kezdet);

        cur_v = adat.vegsebesseg;
        cur_t = adat.veg;

        // linearis szakasz
        if (i + 1 < adatok.size()) {
            const auto &next_adat = adatok.at(i + 1);
            s += cur_v * (next_adat.kezdet - cur_t);
            cur_t = next_adat.kezdet;
        }
    }

    cout << "A megtett ut: " << s << " meter." << endl;
}

void feladat7() {
    ofstream outfile(string("v") + ID + string(".txt"));
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a '"
             << string("v") + ID + string(".txt") << "' fajlt!" << endl;
        return;
    }

    int prev_v = 0;
    for (const auto &adat : adatok) {
        outfile << adat.kezdet << "\t" << prev_v << endl;
        outfile << adat.veg << "\t" << adat.vegsebesseg << endl;
        prev_v = adat.vegsebesseg;
    }

    outfile.close();
}
