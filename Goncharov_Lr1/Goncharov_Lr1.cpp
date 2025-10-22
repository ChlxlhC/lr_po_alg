#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
T GetCorrectNumber(T min, T max) {
    T x;
    while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Vvedite chislo (" << min << "-" << max << "): ";
    }
    return x;
}

class Pipes {
public:
    void add() {
        cout << "Vvedite nazvanie truby: ";
        getline(cin >> ws, _name);
        cout << "Dlina: ";
        _length = GetCorrectNumber(0, 100000);
        cout << "Shirina: ";
        _width = GetCorrectNumber(0, 100000);
        cout << "Rabotaet (1 - da, 0 - na remonte): ";
        _properties = GetCorrectNumber(0, 1);
    }

    void View() {
        if (_name.empty()) {
            cout << "Truba ne naidena" << endl;
        }
        else {
            cout << "Truba: " << _name << ", dlina: " << _length
                << ", shirina: " << _width << ", status: "
                << (_properties ? "rabotaet" : "v remonte") << endl;
        }
    }

    void Edit() {
        if (!_name.empty()) {
            cout << "Rabotaet (1 - da, 0 - na remonte): ";
            _properties = GetCorrectNumber(0, 1);
        }
        else {
            cout << "Truba ne naidena" << endl;
        }
    }

    void saveToFile() {
        if (!_name.empty()) {
            ofstream out("data.txt", ios::app);
            out << "Truba: " << _name << ", " << _length << ", " << _width
                << ", " << _properties << endl;
        }
    }

    void loadFromFile() {
        ifstream in("data.txt");
        if (!in.is_open()) {
            cout << "File ne naiden!" << endl;
            return;
        }
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
    }

private:
    string _name;
    int _length, _width;
    bool _properties;
};

class KS {
public:
    void add() {
        cout << "Vvedite nazvanie KS: ";
        getline(cin >> ws, _name);
        cout << "Kolichestvo tsehov: ";
        _quantity = GetCorrectNumber(0, 100000);
        cout << "Tsehov v rabote: ";
        _count_work = GetCorrectNumber(0, _quantity);
        cout << "Zapusk KS (1 - da, 0 - net): ";
        _station_class = GetCorrectNumber(0, 1);
    }

    void View() {
        if (_name.empty()) {
            cout << "KS ne naiden" << endl;
        }
        else {
            cout << "KS: " << _name << ", tsehov: " << _quantity
                << ", rabotaet: " << _count_work << ", status: "
                << (_station_class ? "zapushena" : "ostanovlena") << endl;
        }
    }

    void Edit() {
        if (!_name.empty()) {
            cout << "Zapusk KS (1 - da, 0 - na remonte): ";
            _station_class = GetCorrectNumber(0, 1);
        }
        else {
            cout << "KS ne naiden" << endl;
        }
    }

    void saveToFile() {
        if (!_name.empty()) {
            ofstream out("data.txt", ios::app);
            out << "KS: " << _name << ", " << _quantity << ", "
                << _count_work << ", " << _station_class << endl;
        }
    }

private:
    string _name;
    int _quantity, _count_work;
    bool _station_class;
};

int main() {
    Pipes pipe;
    KS ks;

    while (true) {
        cout << "\n1. Dobavit trubu\n2. Dobavit KS\n3. Prosmotr\n4. Redaktirovat trubu\n"
            << "5. Redaktirovat KS\n6. Sohranit\n7. Zagruzit\n0. Vihod\nVyberite: ";

        switch (GetCorrectNumber(0, 7)) {
        case 0:
            cout << "Vihod iz programmy..." << endl;
            return 0;
        case 1: pipe.add(); break;
        case 2: ks.add(); break;
        case 3: pipe.View(); ks.View(); break;
        case 4: pipe.Edit(); break;
        case 5: ks.Edit(); break;
        case 6:
            ofstream("data.txt").close();
            pipe.saveToFile();
            ks.saveToFile();
            cout << "Dannye sohraneny" << endl;
            break;
        case 7: pipe.loadFromFile(); break;
        }
    }
}