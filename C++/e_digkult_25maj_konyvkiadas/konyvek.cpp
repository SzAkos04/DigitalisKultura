#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    int ev, negyedev;
    string eredet; // "ma" / "kf"
    string leiras;
    int peldanyszam; // <= 10 000
};
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
    ifstream infile("kiadas.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a 'kiadas.txt' fajlt!" << endl;
        return;
    }

    string ev, negyedev, eredet, leiras, peldanyszam;
    Adat adat;
    int i = 0;
    while (getline(infile, ev, ';') && getline(infile, negyedev, ';') &&
           getline(infile, eredet, ';') && getline(infile, leiras, ';') &&
           getline(infile, peldanyszam, '\n')) {
        adat.ev = stoi(ev);
        adat.negyedev = stoi(negyedev);
        adat.eredet = eredet;
        adat.leiras = leiras;
        adat.peldanyszam = stoi(peldanyszam);

        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    cout << "Szerzo: ";
    string szerzo;
    getline(cin, szerzo);

    int n = 0;
    for (const auto &adat : adatok) {
        if (adat.leiras.find(szerzo) != string::npos) {
            ++n;
        }
    }

    if (n > 0) {
        cout << n << " konyvkiadas" << endl;
    } else {
        cout << "Nem adtak ki" << endl;
    }
}

void feladat3() {
    cout << "3. feladat" << endl;

    int max = -1;
    for (const auto &adat : adatok) {
        if (adat.peldanyszam > max) {
            max = adat.peldanyszam;
        }
    }

    int n = 0;
    for (const auto &adat : adatok) {
        if (adat.peldanyszam == max) {
            ++n;
        }
    }

    cout << "Legnagyob peldanyszam: " << max << ", elofordult " << n
         << " alkalommal" << endl;
}

void feladat4() {
    cout << "4. feladat" << endl;

    double ido = 3000;
    string leiras;

    for (const auto &adat : adatok) {
        if (adat.ev + adat.negyedev * 0.25 < ido && adat.eredet == "kf" &&
            adat.peldanyszam >= 40000) {
            leiras = adat.leiras;
        }
    }

    for (const auto &adat : adatok) {
        if (adat.leiras == leiras) {
            cout << adat.ev << "/" << adat.negyedev << ". " << leiras << endl;
        }
    }
}

void feladat5() {
    ostringstream ss;
    ss << "Ev\tMagyar kiadas\tMagyar peldanyszam\tKulfoldi kiadas\tKulfoldi "
          "peldanyszam\n";

    // 2020
    int magyar_kiadas_2020 = 0;
    int magyar_peldanyszam_2020 = 0;
    int kulfoldi_kiadas_2020 = 0;
    int kulfoldi_peldanyszam_2020 = 0;

    // 2021
    int magyar_kiadas_2021 = 0;
    int magyar_peldanyszam_2021 = 0;
    int kulfoldi_kiadas_2021 = 0;
    int kulfoldi_peldanyszam_2021 = 0;

    // 2022
    int magyar_kiadas_2022 = 0;
    int magyar_peldanyszam_2022 = 0;
    int kulfoldi_kiadas_2022 = 0;
    int kulfoldi_peldanyszam_2022 = 0;

    // 2023
    int magyar_kiadas_2023 = 0;
    int magyar_peldanyszam_2023 = 0;
    int kulfoldi_kiadas_2023 = 0;
    int kulfoldi_peldanyszam_2023 = 0;

    for (const auto &adat : adatok) {
        if (adat.ev == 2020) {
            if (adat.eredet == "ma") {
                magyar_kiadas_2020++;
                magyar_peldanyszam_2020 += adat.peldanyszam;
            } else {
                kulfoldi_kiadas_2020++;
                kulfoldi_peldanyszam_2020 += adat.peldanyszam;
            }
        } else if (adat.ev == 2021) {
            if (adat.eredet == "ma") {
                magyar_kiadas_2021++;
                magyar_peldanyszam_2021 += adat.peldanyszam;
            } else {
                kulfoldi_kiadas_2021++;
                kulfoldi_peldanyszam_2021 += adat.peldanyszam;
            }
        } else if (adat.ev == 2022) {
            if (adat.eredet == "ma") {
                magyar_kiadas_2022++;
                magyar_peldanyszam_2022 += adat.peldanyszam;
            } else {
                kulfoldi_kiadas_2022++;
                kulfoldi_peldanyszam_2022 += adat.peldanyszam;
            }
        } else if (adat.ev == 2023) {
            if (adat.eredet == "ma") {
                magyar_kiadas_2023++;
                magyar_peldanyszam_2023 += adat.peldanyszam;
            } else {
                kulfoldi_kiadas_2023++;
                kulfoldi_peldanyszam_2023 += adat.peldanyszam;
            }
        }
    }

    ss << "2020\t" << magyar_kiadas_2020 << "\t\t" << magyar_peldanyszam_2020
       << "\t\t\t" << kulfoldi_kiadas_2020 << "\t\t"
       << kulfoldi_peldanyszam_2020 << "\n";
    ss << "2021\t" << magyar_kiadas_2021 << "\t\t" << magyar_peldanyszam_2021
       << "\t\t\t" << kulfoldi_kiadas_2021 << "\t\t"
       << kulfoldi_peldanyszam_2021 << "\n";
    ss << "2022\t" << magyar_kiadas_2022 << "\t\t" << magyar_peldanyszam_2022
       << "\t\t\t" << kulfoldi_kiadas_2022 << "\t\t"
       << kulfoldi_peldanyszam_2022 << "\n";
    ss << "2023\t" << magyar_kiadas_2023 << "\t\t" << magyar_peldanyszam_2023
       << "\t\t\t" << kulfoldi_kiadas_2023 << "\t\t"
       << kulfoldi_peldanyszam_2023 << "\n";

    cout << ss.str() << endl;

    ofstream outfile("tabla.html");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a 'tabla.html' fajlt!" << endl;
        return;
    }

    outfile << "<table>\n<tr><th>Év</th><th>Magyar kiadás</th><th>Magyar "
               "példányszám</th><th>Külföldi kiadás</th><th>Külföldi "
               "példányszám</th></tr>\n<tr><td>2020</td><td>"
            << magyar_kiadas_2020 << "</td><td>" << magyar_peldanyszam_2020
            << "</"
               "td><td>"
            << kulfoldi_kiadas_2020 << "</td><td>" << kulfoldi_peldanyszam_2020
            << "</td></tr>\n<tr><td>2021</td><td>" << magyar_kiadas_2021
            << "</"
               "td><td>"
            << magyar_peldanyszam_2021 << "</td><td>"
            << kulfoldi_peldanyszam_2021 << "</td><td>"
            << kulfoldi_peldanyszam_2021
            << "</td></"
               "tr>\n<tr><td>2022</td><td>"
            << magyar_kiadas_2022 << "</td><td>" << magyar_peldanyszam_2022
            << "</td><td>" << kulfoldi_kiadas_2022
            << "</"
               "td><td>"
            << kulfoldi_peldanyszam_2022 << "</td></tr>\n<tr><td>2023</td><td>"
            << magyar_kiadas_2023
            << "</"
               "td><td>"
            << magyar_peldanyszam_2023 << "</td><td>" << kulfoldi_kiadas_2023
            << "</td><td>" << kulfoldi_peldanyszam_2023
            << "</td></tr>\n</table>";

    outfile.close();
}

void feladat6() {
    cout << "6. feladat" << endl;

    cout << "Legalabb ketszer, nagyobb peldanyszamban ujra kiadott konyvek:"
         << endl;

    map<string, int> konyvek_kiadas;
    map<string, int> konyvek_elso_peldanyszam;
    for (const auto &adat : adatok) {
        if (konyvek_elso_peldanyszam.find(adat.leiras) ==
            konyvek_elso_peldanyszam.end()) {
            konyvek_elso_peldanyszam[adat.leiras] = adat.peldanyszam;
        } else if (adat.peldanyszam > konyvek_elso_peldanyszam[adat.leiras]) {
            konyvek_kiadas[adat.leiras]++;
        }
    }

    for (const auto &konyv : konyvek_kiadas) {
        if (konyv.second >= 2) {
            cout << konyv.first << endl;
        }
    }
}
