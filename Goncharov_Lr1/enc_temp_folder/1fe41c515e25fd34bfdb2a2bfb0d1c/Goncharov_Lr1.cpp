#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
        cout << "Dlina: "; _length = GetCorrectNumber(0, 100000);
        cout << "Shirina: "; _width = GetCorrectNumber(0, 100000);
        cout << "Rabotaet (1 - da, 0 - net): "; _properties = GetCorrectNumber(0, 1);
    }

    void View() {
        if (_name.empty()) cout << "Truba ne naidena" << endl;
        else cout << "Truba: " << _name << ", dlina: " << _length << ", shirina: " << _width
            << ", status: " << (_properties ? "rabotaet" : "ne rabotaet") << endl;
    }

    void Edit() {
        if (!_name.empty()) {
            cout << "Rabotaet (1 - da, 0 - net): "; _properties = GetCorrectNumber(0, 1);
        }
        else cout << "Truba ne naidena" << endl;
    }

    void saveToFile(ofstream& out) {
        if (!_name.empty()) out << "PIPE:" << _name << "," << _length << "," << _width << "," << _properties << endl;
    }

    bool loadFromFile(const string& data) {
        if (data.find("PIPE:") == 0) {
            stringstream ss(data.substr(5));
            getline(ss, _name, ',');
            string temp;
            getline(ss, temp, ','); _length = stoi(temp);
            getline(ss, temp, ','); _width = stoi(temp);
            getline(ss, temp); _properties = stoi(temp);
            return true;
        }
        return false;
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
        cout << "Kolichestvo tsehov: "; _quantity = GetCorrectNumber(0, 100000);
        cout << "Tsehov v rabote: "; _count_work = GetCorrectNumber(0, _quantity);
        cout << "Rabotaet (1 - da, 0 - net): "; _station_class = GetCorrectNumber(0, 1);
    }

    void View() {
        if (_name.empty()) cout << "KS ne naiden" << endl;
        else cout << "KS: " << _name << ", tsehov: " << _quantity << ", rabotaet: " << _count_work
            << ", status: " << (_station_class ? "rabotaet" : "ne rabotaet") << endl;
    }

    void Edit() {
        if (!_name.empty()) {
            cout << "Rabotaet (1 - da, 0 - net): "; _station_class = GetCorrectNumber(0, 1);
        }
        else cout << "KS ne naiden" << endl;
    }

    void saveToFile(ofstream& out) {
        if (!_name.empty()) out << "KS:" << _name << "," << _quantity << "," << _count_work << "," << _station_class << endl;
    }

    bool loadFromFile(const string& data) {
        if (data.find("KS:") == 0) {
            stringstream ss(data.substr(3));
            getline(ss, _name, ',');
            string temp;
            getline(ss, temp, ','); _quantity = stoi(temp);
            getline(ss, temp, ','); _count_work = stoi(temp);
            getline(ss, temp); _station_class = stoi(temp);
            return true;
        }
        return false;
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
        case 0: return 0;
        case 1: pipe.add(); break;
        case 2: ks.add(); break;
        case 3: pipe.View(); ks.View(); break;
        case 4: pipe.Edit(); break;
        case 5: ks.Edit(); break;
        case 6: {
            ofstream out("data.txt");
            pipe.saveToFile(out);
            ks.saveToFile(out);
            cout << "Dannye sohraneny" << endl;
            break;
        }
        case 7: {
            ifstream in("data.txt");
            string line;
            while (getline(in, line)) {
                if (!pipe.loadFromFile(line) && !ks.loadFromFile(line)) {
                    cout << "Neznany format: " << line << endl;
                }
            }
            cout << "Dannye zagruzheny" << endl;
            break;
        }
        }
    }
}
