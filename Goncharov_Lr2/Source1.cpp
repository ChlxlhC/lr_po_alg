#include "Goncharov_Lr2.h"



void Pipes::add() {
    MyPipe pipe;
    cout << "Введите название трубы: ";
    INPUT_LINE(cin, pipe._name);
    cout << "Введите размеры трубы (длину): ";
    pipe._length = GetCorrectNumber(0, 100000);
    cout << "Введите размеры трубы (ширину): ";
    pipe._width = GetCorrectNumber(0, 100000);
    cout << "Введите работает ли труба(1 - работает, 0 - в ремонте): ";
    pipe._properties = GetCorrectNumber(0, 1);
    _Pipes[_size++] = pipe;
}
void Pipes::View() const {
    if (_Pipes.empty()) {
        cout << "Трубы не найдены, добавьте трубу" << endl;
    }
    else {
        cout << _Pipes.size() << endl;
        for (const auto& [i, pipe] : _Pipes) {
            cout << "Номер трубы: " << i << " Название: " << pipe._name << ", длина: " << pipe._length << " ширина: " << pipe._width << " класс трубы: " << pipe._properties << endl;
        }
    }
}
void Pipes::Edit() {
    if (_Pipes.empty()) {
        cout << "Трубы не найдены, добавьте трубу" << endl;
    }
    else {
        cout << "Введите номер трубы, которую нужно отредактировать" << endl;
        int i = GetCorrectNumber(0, 1000);
        cout << "Введите работает ли труба(1 - работает, 0 - в ремонте)" << endl;
        _Pipes.at(i)._properties = GetCorrectNumber(0, 1);
    }
}
void Pipes::output_file() const {
    if (_Pipes.empty()) {
        cout << "Труба не найдена, добавьте трубу" << endl;
    }
    else {
        ofstream out;
        out.open("data_pipes_ks.txt");
        for (const auto& [i, pipe] : _Pipes) {
            out << "Номер трубы: " << i << " Название: " << pipe._name << " длина: " << pipe._length << " ширина: " << pipe._width << " класс трубы: " << pipe._properties << endl;
        }
        out.close();
    }
}
void Pipes::input_file() const {
    ifstream in;
    in.open("data_pipes_ks.txt");
    string line;
    while (getline(in, line)) {
        cout << line << " ";
    }
    cout << endl;
    in.close();
}


void KS::add() {
    MyKs ks;
    cout << "Введите название КС: ";
    INPUT_LINE(cin, ks._name);
    cout << "Введите количество цехов: ";
    ks._quantity = GetCorrectNumber(0, 100000);
    cout << "Введите количество цехов в работе: ";
    ks._count_work = GetCorrectNumber(0, 100000);
    cout << "Введите запуск КС(1 - запустить, 0 - остановка): ";
    ks._station_class = GetCorrectNumber(0, 1);
    _Ks[_size] = ks;
}
void KS::View() const {
    if (_Ks.empty()) {
        cout << "КС не найден, добавьте КС" << endl;
    }
    else {
        for (const auto& [i, ks] : _Ks) {
            cout << "Номер КС: " << i << " Название: " << ks._name << ", количество цехов: " << ks._quantity << " количество цехов в работе: " << ks._count_work << " класс станции: " << ks._station_class << endl;
        }
    }
}
void KS::Edit() {
    if (_Ks.empty()) {
        cout << "КС не найден, добавьте КС" << endl;
    }
    else {
        cout << "Введите номер КС, которую нужно отредактировать" << endl;
        int i = GetCorrectNumber(0, 1000);
        cout << "Введите запуск КС(1 - запустить, 0 - остановка)" << endl;
        _Ks.at(i)._station_class = GetCorrectNumber(1, 0);
    }
}
void KS::output_file() const {
    if (_Ks.empty()) {
        cout << "КС не найден, добавьте КС" << endl;
    }
    else {
        ofstream out("data_pipes_ks.txt", ios::app);
        for (const auto& [i, ks] : _Ks) {
            cout << "Номер КС: " << i << " Название: " << ks._name << ", количество цехов: " << ks._quantity << " количество цехов в работе: " << ks._count_work << " класс станции: " << ks._station_class << endl;
        }
        out.close();
    }
}