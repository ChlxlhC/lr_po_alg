#include "KC.h"
#include <chrono>
#include <format>
#include <string>
#include <unordered_map>

using namespace std;
using namespace chrono;

void RepairPipeForEdit(unordered_map<int, Pipes>& pipe) {
    cout << "введите номер трубы, которую нужно отредактировать  (номера доступны: ";
    for (auto it = pipe.begin(); it != pipe.end(); ++it) {
        std::cout << it->first << " ";
    }
    cout << ")" << endl;
    int i = GetCorrectNumber(0, 1000);
    cout << "введите работает ли труба(1 - работает, 0 - в ремонте)" << endl;
    pipe.at(i).Edit();
}

void ErasePipeForEdit(unordered_map<int, Pipes>& pipe) {
    cout << "введите число (0 - удалить все трубы, 1 - удалить конкретную трубу)" << endl;
    bool del = GetCorrectNumber(0, 1);
    if (!del) {
        pipe.clear();
        cout << "все трубы удалены!!!" << endl;
    }
    else {
        bool d = 1;
        while (d) {
            cout << "хотите удалить трубу? (0 - нет, 1 - да )" << endl;
            bool pipe_cheak = GetCorrectNumber(0, 1);
            if (pipe_cheak && pipe.size() != 0) {
                cout << "введите номер трубы, которую хотите удалить (номера доступны: ";
                for (auto it = pipe.begin(); it != pipe.end(); ++it) {
                    std::cout << it->first << " ";
                }
                cout << ")" << endl;
                int number_del = GetCorrectNumber(1, int(pipe.size() + 1));
                pipe.erase(number_del);
            }
            else {
                cout << "трубы удалены!!!" << endl;
                d = 0;
            }
        }
    }
}

void EditPipe(unordered_map<int, Pipes>& pipe) {
    if (pipe.empty()) {
        cout << "трубы не найдены, добавьте трубу" << endl;
    }
    else {
        cout << "введите число (0 - отредактировать, 1 - удалить трубы)" << endl;
        bool cnt = GetCorrectNumber(0, 1);
        if (!cnt) {
            RepairPipeForEdit(pipe);
        }
        else {
            cout << "введите число (0 - удалить все трубы, 1 - удалить конкретную трубу)" << endl;
            bool del = GetCorrectNumber(0, 1);
            if (!del) {
                pipe.clear();
                cout << "все трубы удалены!!!" << endl;
            }
            else {
                ErasePipeForEdit(pipe);
            }
        }
    }
}

void RepairKC(unordered_map<int, KC>& kc) {
    cout << "Введите номер КС, которую нужно отредактировать (Номера доступны: ";
    for (auto it = kc.begin(); it != kc.end(); ++it) {
        std::cout << it->first << " ";
    }
    cout << ")" << endl;
    int i = GetCorrectNumber(0, 1000);
    cout << "Введите работает ли КС(1 - работает, 0 - в ремонте)" << endl;
    kc.at(i).Edit();
}

void EraseKC(unordered_map<int, KC>& kc) {
    cout << "Введите число (0 - удалить все КС, 1 - удалить конкретную КС)" << endl;
    bool del = GetCorrectNumber(0, 1);
    if (!del) {
        kc.clear();
        cout << "Все КС удалены" << endl;
    }
    else {
        bool d = 1;
        while (d) {
            cout << "Хотите удалить КС? (0 - нет, 1 - да )" << endl;
            bool ks_cheak = GetCorrectNumber(0, 1);
            if (ks_cheak && kc.size() != 0) {
                cout << "введите номер КС, которую хотите удалить (Номера доступны: ";
                for (auto it = kc.begin(); it != kc.end(); ++it) {
                    std::cout << it->first << " ";
                }
                cout << ")" << endl;
                int number_del = GetCorrectNumber(1, int(kc.size() + 1));
                kc.erase(number_del);
            }
            else {
                d = 0;
            }
        }
    }
}

void EditKC(unordered_map<int, KC>& kc) {
    if (kc.empty()) {
        cout << "КС не найден, добавьте КС" << endl;
    }
    else {
        cout << "Введите число (0 - Отредактировать, 1 - Удалить КС)" << endl;
        bool cnt = GetCorrectNumber(0, 1);
        if (!cnt) {
            RepairKC(kc);
        }
        else {
            EraseKC(kc);
        }
    }
}

void ErasePipes(unordered_map<int, Pipes>& pipes, vector<int>& id_p) {
    cout << "введите число (0 - удалить все трубы, 1 - удалить конкретную трубу)" << endl;
    bool del = GetCorrectNumber(0, 1);
    if (!del) {
        for (int id : id_p) {
            pipes.erase(id);
        }
        cout << "все трубы удалены!!!" << endl;
    }
    else {
        bool d = 1;
        while (d) {
            cout << "хотите удалить трубу? (0 - нет, 1 - да )" << endl;
            bool pipe_cheak = GetCorrectNumber(0, 1);
            if (pipe_cheak && pipes.size() != 0) {
                cout << "введите номер трубы, которую хотите удалить (номера доступны: ";
                for (int id : id_p) {
                    cout << id << " ";
                }
                cout << ")" << endl;
                int number_del = GetCorrectNumber(1, int(id_p.size()));
                pipes.erase(number_del);
            }
            else {
                cout << "трубы удалены!!!" << endl;
                d = 0;
            }
        }
    }
}

void RepairPipes(unordered_map<int, Pipes>& pipes, vector<int>& id_p) {
    cout << "введите число (0 - отредактировать, 1 - удалить трубы)" << endl;
    bool cnt = GetCorrectNumber(0, 1);
    if (!cnt) {
        cout << "введите номер трубы, которую нужно отредактировать  (номера доступны: ";
        for (int id : id_p) {
            cout << id << " ";
        }
        cout << ")" << endl;
        int i = GetCorrectNumber(0, 1000);
        cout << "введите работает ли труба(1 - работает, 0 - в ремонте)" << endl;
        pipes.at(i).Edit();
    }
}

void FilterEditIdPipes(unordered_map<int, Pipes>& pipes, vector<int>& id_p) {
    cout << "Хотите отредактировать отфилтрованные трубы? (0 - нет , 1 - да)" << endl;
    bool cheak = GetCorrectNumber(0, 1);
    if (cheak) {
        RepairPipes(pipes, id_p);
    }
    else {
        ErasePipes(pipes, id_p);
    }
}

void NameFilterPipe(unordered_map<int, Pipes>& pipes) {
    cout << "введите имя трубы: " << endl;
    string name;
    INPUT_LINE(cin, name);
    vector<int> id_p;
    for (auto p : pipes) {
        if (p.second.CheakByName(name)) {
            p.second.View();
            id_p.push_back(p.first);
        }
    }
    if (id_p.empty()) {
        cout << "Фильтр с именем не нашел подходящей трубы" << endl;
    }
    else {
        FilterEditIdPipes(pipes, id_p);
    }
}

void RepairPipe(unordered_map<int, Pipes>& pipes) {
    cout << "введите число (0 - в ремонте, 1 - работает)" << endl;
    bool properities = GetCorrectNumber(0, 1);
    vector<int> id_p;
    for (auto p : pipes) {
        if (p.second.CheakByProperities(properities)) {
            p.second.View();
            id_p.push_back(p.first);
        }
    }
    if (id_p.empty()) {
        cout << "Фильтр по признаку в ремонте не нашел подходящей трубы" << endl;
    }
    else {
        FilterEditIdPipes(pipes, id_p);
    }
}

void FilterPipe(unordered_map<int, Pipes>& pipes) {
    if (pipes.empty()) {
        cout << "трубы не найдены, добавьте трубу" << endl;
    }
    else {
        cout << "введите число (филтровать по 0 - названию, 1 - по признаку в ремонте)" << endl;
        bool cheak = GetCorrectNumber(0, 1);
        if (cheak) {
            RepairPipe(pipes);
        }
        else {
            NameFilterPipe(pipes);
        }
    }
}

void FilterEditIdKC(unordered_map<int, KC>& kc, vector<int>& id_kc) {
    cout << "Хотите отредактировать отфилтрованные КС? (0 - нет , 1 - да)" << endl;
    bool cheak = GetCorrectNumber(0, 1);
    if (cheak) {
        cout << "Введите число (0 - Отредактировать, 1 - Удалить КС)" << endl;
        bool cnt = GetCorrectNumber(0, 1);
        if (!cnt) {
            cout << "Введите номер КС, которую нужно отредактировать (Номера доступны: ";
            for (int id : id_kc) {
                cout << id << " ";
            }
            cout << ")" << endl;
            int i = GetCorrectNumber(0, 1000);
            cout << "Введите работает ли КС(1 - работает, 0 - в ремонте)" << endl;
            kc.at(i).Edit();
        }
        else {
            cout << "Введите число (0 - удалить все КС, 1 - удалить конкретную КС)" << endl;
            bool del = GetCorrectNumber(0, 1);
            if (!del) {
                for (int id : id_kc) {
                    kc.erase(id);
                }
                cout << "Все КС удалены" << endl;
            }
            else {
                bool d = 1;
                while (d) {
                    cout << "Хотите удалить КС? (0 - нет, 1 - да )" << endl;
                    bool ks_cheak = GetCorrectNumber(0, 1);
                    if (ks_cheak && kc.size() != 0) {
                        cout << "введите номер КС, которую хотите удалить (Номера доступны: ";
                        for (int id : id_kc) {
                            cout << id << " ";
                        }
                        cout << ")" << endl;
                        int number_del = GetCorrectNumber(1, int(id_kc.size() + 1));
                        kc.erase(number_del);
                    }
                    else {
                        d = 0;
                    }
                }
            }
        }
    }
}

void FilterIdleWorkshopsKC(unordered_map<int, KC>& kc) {
    vector<int> id_kc;
    cout << "Введите процент незадействованных цехов: " << endl;
    int Idle = GetCorrectNumber(0, 100);
    for (auto s : kc) {
        if (s.second.IdleWorkshops() < Idle) {
            s.second.View();
            id_kc.push_back(s.first);
        }
    }
    FilterEditIdKC(kc, id_kc);
}

void FilterNameKC(unordered_map<int, KC>& kc) {
    vector<int> id_kc;
    cout << "Введите имя трубы: " << endl;
    string name;
    INPUT_LINE(cin, name);
    for (auto s : kc) {
        if (s.second.CheakByName(name)) {
            s.second.View();
            id_kc.push_back(s.first);
        }
    }
    FilterEditIdKC(kc, id_kc);
}

void FilterKC(unordered_map<int, KC>& kc) {
    if (kc.empty()) {
        cout << "кс не найдены, добавьте кс" << endl;
    }
    else {
        cout << "введите число (филтровать по 0 - названию, 1 - по  проценту незадействованных цехов)" << endl;
        bool cheak = GetCorrectNumber(0, 1);
        if (cheak) {
            FilterIdleWorkshopsKC(kc);
        }
        else {
            FilterNameKC(kc);
        }
    }

}

void SaveAll(const unordered_map<int, Pipes>& pipes,
    const unordered_map<int, KC>& stations,
    const string& filename)
{
    std::ofstream f(filename);
    if (!f.is_open()) {
        cout << "Ошибка: невозможно открыть файл для записи.\n";
        return;
    }

    f << "PIPES " << pipes.size() << "\n";
    for (const auto& [id, pipe] : pipes)
        pipe.SavePipe(f);

    f << "STATIONS " << stations.size() << "\n";
    for (auto& [id, station] : stations)
        station.SaveKC(f);

    std::cout << "Data saved to " << filename << "\n";
}

void LoadAll(unordered_map<int, Pipes>& pipes,
    unordered_map<int, KC>& stations,
    const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        cout << "Ошибка: невозможно открыть файл для чтения.\n";
        return;
    }

    pipes.clear();
    stations.clear();

    std::string section;
    while (f >> section) {
        if (section == "PIPES") {
            size_t count;
            f >> count;
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (size_t i = 0; i < count; ++i) {
                Pipes p;
                p.LoadPipe(f);
                pipes.emplace(p.GetId(), p);
            }
        }
        else if (section == "STATIONS") {
            size_t count;
            f >> count;
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (size_t i = 0; i < count; ++i) {
                KC s;
                s.LoadKC(f);
                stations.emplace(s.GetId(), s);
            }
        }
    }

    std::cout << "Данные успешно загружены из " << filename << "\n";
}
void PrintKcPipe(unordered_map<int, Pipes>& pipe, unordered_map<int, KC>& kc) {
    if (kc.empty()) {
        cout << "КС не найден, добавьте КС" << endl;
    }
    else {
        for (auto s : kc) {
            s.second.View();
        }
    }
    if (pipe.empty()) {
        cout << "трубы не найдены, добавьте трубу" << endl;
    }
    else {
        for (auto p : pipe) {
            p.second.View();
        }
    }
}


int main()
{
    auto now = system_clock::now();
    time_t now_c = system_clock::to_time_t(now);
    tm tm;
    localtime_s(&tm, &now_c);
    redirect_output_wrapper cerr_out(cerr);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d_%m_%Y_%H_%M_%S");
    std::string time = oss.str();

    ofstream logfile("log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);
    setlocale(LC_ALL, "");
    unordered_map<int, KC> kc;
    unordered_map<int, Pipes> pipes;
    while (true) {
        cout << "1. Добавить трубу 2. Добавить КС 3. Просмотр всех объектов 4. Просмотр труб по фильтру 5. Просмотр КС по фильтру 6. Редактировать трубу 7. Редактировать КС 8. Сохранить 9. Загрузить 0. Выход" << endl;
        switch (GetCorrectNumber(0, 9)) {
        case 0: {
            cout << "Вы закончили цикл" << endl;
            exit(0);
        }
        case 1: {
            Pipes p;
            p.add();
            pipes.emplace(p.GetId(), p);
            break;
        }
        case 2: {
            KC s;
            s.add();
            kc.emplace(s.GetId(), s);
            break;
        }
        case 3: {
            PrintKcPipe(pipes, kc);
            break;
        }
        case 4: {
            FilterPipe(pipes);
            break;
        }
        case 5: {
            FilterKC(kc);
            break;
        }
        case 6: {
            EditPipe(pipes);
            break;
        }
        case 7: {
            EditKC(kc);
            break;
        }
        case 8: {
            string filename;
            cout << "Введите имя файла для сохранения (без расширения): ";
            INPUT_LINE(cin, filename);
            if (filename.empty()) {
                std::cout << "Имя файла не может быть пустым.\n";
                break;
            }
            SaveAll(pipes, kc, filename + ".txt");

            break;
        }
        case 9: {
            string filename;
            cout << "Введите имя файла для сохранения (без расширения): ";
            INPUT_LINE(cin, filename);
            if (filename.empty()) {
                cout << "Имя файла не может быть пустым.\n";
                break;
            }
            LoadAll(pipes, kc, filename + ".txt");
            break;
        }
        }
    }
}