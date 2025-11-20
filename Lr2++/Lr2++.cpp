#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

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

int nextId = 1;

class Logger {
private:
    ofstream logFile;

public:
    Logger() {
        logFile.open("actions.log", ios::app);
        if (logFile.is_open()) {
            auto now = chrono::system_clock::now();
            auto time_t = chrono::system_clock::to_time_t(now);
            char timeStr[100];
            ctime_s(timeStr, sizeof(timeStr), &time_t);
            logFile << "=== LOG START " << timeStr;
            logFile.flush();

            cout << "Log file sozdan: actions.log" << endl;
        }
        else {
            cout << "OSHIBKA: Ne udalos sozdat log file!" << endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            auto now = chrono::system_clock::now();
            auto time_t = chrono::system_clock::to_time_t(now);
            char timeStr[100];
            ctime_s(timeStr, sizeof(timeStr), &time_t);
            logFile << "=== LOG END " << timeStr << endl;
            logFile.close();
        }
    }

    void log(const string& action) {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        char timeStr[100];
        ctime_s(timeStr, sizeof(timeStr), &time_t);
        for (int i = 0; i < 100; i++) {
            if (timeStr[i] == '\n' || timeStr[i] == '\r') {
                timeStr[i] = '\0';
                break;
            }
        }

        if (logFile.is_open()) {
            logFile << "[" << timeStr << "] " << action << endl;
            logFile.flush();
        }

        cout << "[LOG] " << action << endl;
    }
};

class Pipe {
public:
    int id;
    string name;
    int length;
    int width;
    bool working;

    Pipe() : id(nextId++) {}

    void input() {
        cout << "Vvedite nazvanie truby: ";
        getline(cin >> ws, name);
        cout << "Dlina: "; length = GetCorrectNumber(0, 100000);
        cout << "Shirina: "; width = GetCorrectNumber(0, 100000);
        cout << "Rabotaet (1 - da, 0 - net): "; working = GetCorrectNumber(0, 1);
    }

    void display() const {
        cout << "ID: " << id << " | Truba: " << name << ", dlina: " << length << ", shirina: " << width
            << ", status: " << (working ? "rabotaet" : "ne rabotaet") << endl;
    }

    void edit() {
        cout << "Rabotaet (1 - da, 0 - net): "; working = GetCorrectNumber(0, 1);
    }

    bool nameContains(const string& searchName) const {
        string lowerName = name;
        string lowerSearch = searchName;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
        return lowerName.find(lowerSearch) != string::npos;
    }
};

class KS {
public:
    int id;
    string name;
    int workshops;
    int working_workshops;
    bool station_working;

    KS() : id(nextId++) {}

    void input() {
        cout << "Vvedite nazvanie KS: ";
        getline(cin >> ws, name);
        cout << "Kolichestvo tsehov: "; workshops = GetCorrectNumber(0, 100000);
        cout << "Tsehov v rabote: "; working_workshops = GetCorrectNumber(0, workshops);
        cout << "Rabotaet (1 - da, 0 - net): "; station_working = GetCorrectNumber(0, 1);
    }

    void display() const {
        double unusedPercent = getUnusedPercent();
        cout << "ID: " << id << " | KS: " << name << ", tsehov: " << workshops
            << ", rabotaet: " << working_workshops << " (" << fixed << setprecision(1) << unusedPercent << "% ne ispolzuetsya)"
            << ", status: " << (station_working ? "rabotaet" : "ne rabotaet") << endl;
    }

    void edit() {
        cout << "Rabotaet (1 - da, 0 - net): "; station_working = GetCorrectNumber(0, 1);
    }

    bool nameContains(const string& searchName) const {
        string lowerName = name;
        string lowerSearch = searchName;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
        return lowerName.find(lowerSearch) != string::npos;
    }

    double getUnusedPercent() const {
        if (workshops == 0) return 0.0;
        return ((workshops - working_workshops) * 100.0) / workshops;
    }
};

class DataManager {
private:
    vector<Pipe> pipes;
    vector<KS> stations;
    Logger logger;

    template<typename T>
    T* findById(vector<T>& objects, int id) {
        for (auto& obj : objects) {
            if (obj.id == id) {
                return &obj;
            }
        }
        return nullptr;
    }

    template<typename T>
    bool deleteById(vector<T>& objects, int id) {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (it->id == id) {
                objects.erase(it);
                return true;
            }
        }
        return false;
    }

public:
    void addPipe() {
        Pipe newPipe;
        newPipe.input();
        pipes.push_back(newPipe);
        cout << "Truba dobavlena! ID: " << newPipe.id << " | Vsego trub: " << pipes.size() << endl;
        logger.log("Sozdana truba ID: " + to_string(newPipe.id) + " - " + newPipe.name);
    }

    void addKS() {
        KS newKS;
        newKS.input();
        stations.push_back(newKS);
        cout << "KS dobavlen! ID: " << newKS.id << " | Vsego KS: " << stations.size() << endl;
        logger.log("Sozdan KS ID: " + to_string(newKS.id) + " - " + newKS.name);
    }

    void viewAll() {
        cout << "\n=== VSE TRUBY (" << pipes.size() << ") ===" << endl;
        if (pipes.empty()) {
            cout << "Net trub" << endl;
        }
        else {
            for (const auto& pipe : pipes) {
                pipe.display();
            }
        }

        cout << "\n=== VSE KS (" << stations.size() << ") ===" << endl;
        if (stations.empty()) {
            cout << "Net KS" << endl;
        }
        else {
            for (const auto& station : stations) {
                station.display();
            }
        }
        logger.log("Prosmotr vseh objectov - trub: " + to_string(pipes.size()) + ", KS: " + to_string(stations.size()));
    }

    void editPipes() {
        if (pipes.empty()) {
            cout << "Net trub dlya redaktirovaniya" << endl;
            return;
        }

        cout << "\n=== REDAKTIROVANIE TRUB ===" << endl;
        cout << "1. Redaktirovat vse truby" << endl;
        cout << "2. Redaktirovat po ID" << endl;
        cout << "Vyberite deistvie: ";

        int choice = GetCorrectNumber(1, 2);

        if (choice == 1) {
            bool newStatus;
            cout << "Rabotaet (1 - da, 0 - net): ";
            newStatus = GetCorrectNumber(0, 1);

            for (auto& pipe : pipes) {
                pipe.working = newStatus;
            }
            cout << "Vse truby obnovleny! Status: " << (newStatus ? "rabotaet" : "ne rabotaet") << endl;
            logger.log("Massovoe obnovlenie trub - status: " + string(newStatus ? "rabotaet" : "ne rabotaet"));
        }
        else {
            cout << "Vvedite ID truby dlya redaktirovaniya: ";
            int id = GetCorrectNumber(1, nextId - 1);

            Pipe* pipe = findById(pipes, id);
            if (pipe) {
                bool oldStatus = pipe->working;
                pipe->edit();
                cout << "Truba s ID " << id << " obnovlena!" << endl;
                logger.log("Obnovlena truba ID: " + to_string(id) + " - status izmenen");
            }
            else {
                cout << "Truba s ID " << id << " ne naidena!" << endl;
                logger.log("Oshibka redaktirovaniya - truba s ID " + to_string(id) + " ne naidena");
            }
        }
    }

    void editStations() {
        if (stations.empty()) {
            cout << "Net KS dlya redaktirovaniya" << endl;
            return;
        }

        cout << "\n=== REDAKTIROVANIE KS ===" << endl;
        cout << "1. Redaktirovat vse KS" << endl;
        cout << "2. Redaktirovat po ID" << endl;
        cout << "Vyberite deistvie: ";

        int choice = GetCorrectNumber(1, 2);

        if (choice == 1) {
            bool newStatus;
            cout << "Rabotaet (1 - da, 0 - net): ";
            newStatus = GetCorrectNumber(0, 1);

            for (auto& station : stations) {
                station.station_working = newStatus;
            }
            cout << "Vse KS obnovleny! Status: " << (newStatus ? "rabotaet" : "ne rabotaet") << endl;
            logger.log("Massovoe obnovlenie KS - status: " + string(newStatus ? "rabotaet" : "ne rabotaet"));
        }
        else {
            cout << "Vvedite ID KS dlya redaktirovaniya: ";
            int id = GetCorrectNumber(1, nextId - 1);

            KS* ks = findById(stations, id);
            if (ks) {
                bool oldStatus = ks->station_working;
                ks->edit();
                cout << "KS s ID " << id << " obnovlen!" << endl;
                logger.log("Obnovlen KS ID: " + to_string(id) + " - status izmenen");
            }
            else {
                cout << "KS s ID " << id << " ne naiden!" << endl;
                logger.log("Oshibka redaktirovaniya - KS s ID " + to_string(id) + " ne naiden");
            }
        }
    }

    void deletePipes() {
        if (pipes.empty()) {
            cout << "Net trub dlya udaleniya" << endl;
            return;
        }

        cout << "\n=== UDALENIE TRUB ===" << endl;
        cout << "1. Udalit vse truby" << endl;
        cout << "2. Udalit po ID" << endl;
        cout << "Vyberite deistvie: ";

        int choice = GetCorrectNumber(1, 2);

        if (choice == 1) {
            int count = pipes.size();
            pipes.clear();
            cout << "Vse truby udaleny! Kolichestvo: " << count << endl;
            logger.log("Massovoe udalenie trub - udaleno: " + to_string(count));
        }
        else {
            cout << "Vvedite ID truby dlya udaleniya: ";
            int id = GetCorrectNumber(1, nextId - 1);

            if (deleteById(pipes, id)) {
                cout << "Truba s ID " << id << " udalena! Ostalos trub: " << pipes.size() << endl;
                logger.log("Udalena truba ID: " + to_string(id));
            }
            else {
                cout << "Truba s ID " << id << " ne naidena!" << endl;
                logger.log("Oshibka udaleniya - truba s ID " + to_string(id) + " ne naidena");
            }
        }
    }

    void deleteStations() {
        if (stations.empty()) {
            cout << "Net KS dlya udaleniya" << endl;
            return;
        }

        cout << "\n=== UDALENIE KS ===" << endl;
        cout << "1. Udalit vse KS" << endl;
        cout << "2. Udalit po ID" << endl;
        cout << "Vyberite deistvie: ";

        int choice = GetCorrectNumber(1, 2);

        if (choice == 1) {
            int count = stations.size();
            stations.clear();
            cout << "Vse KS udaleny! Kolichestvo: " << count << endl;
            logger.log("Massovoe udalenie KS - udaleno: " + to_string(count));
        }
        else {
            cout << "Vvedite ID KS dlya udaleniya: ";
            int id = GetCorrectNumber(1, nextId - 1);

            if (deleteById(stations, id)) {
                cout << "KS s ID " << id << " udalen! Ostalos KS: " << stations.size() << endl;
                logger.log("Udalena KS ID: " + to_string(id));
            }
            else {
                cout << "KS s ID " << id << " ne naiden!" << endl;
                logger.log("Oshibka udaleniya - KS s ID " + to_string(id) + " ne naiden");
            }
        }
    }

    void findObject() {
        cout << "Vvedite ID objecta dlya poiska: ";
        int id = GetCorrectNumber(1, nextId - 1);

        logger.log("Poisk objecta po ID: " + to_string(id));

        Pipe* pipe = findById(pipes, id);
        if (pipe) {
            cout << "Naiden object: ";
            pipe->display();
            return;
        }

        KS* ks = findById(stations, id);
        if (ks) {
            cout << "Naiden object: ";
            ks->display();
            return;
        }

        cout << "Object s ID " << id << " ne naiden!" << endl;
    }

    void searchPipes() {
        if (pipes.empty()) {
            cout << "Net trub dlya poiska" << endl;
            return;
        }

        cout << "\n=== POISK TRUB ===" << endl;
        cout << "1. Po nazvaniyu" << endl;
        cout << "2. Po priznaku 'v remonte'" << endl;
        cout << "3. Po priznaku 'rabotaet'" << endl;
        cout << "Vyberite tip poiska: ";

        int choice = GetCorrectNumber(1, 3);
        vector<Pipe> results;

        switch (choice) {
        case 1: {
            cout << "Vvedite chast nazvaniya dlya poiska: ";
            string searchName;
            getline(cin >> ws, searchName);

            for (const auto& pipe : pipes) {
                if (pipe.nameContains(searchName)) {
                    results.push_back(pipe);
                }
            }
            logger.log("Poisk trub po nazvaniyu: '" + searchName + "' - naideno: " + to_string(results.size()));
            break;
        }
        case 2: {
            for (const auto& pipe : pipes) {
                if (!pipe.working) {
                    results.push_back(pipe);
                }
            }
            logger.log("Poisk trub v remonte - naideno: " + to_string(results.size()));
            break;
        }
        case 3: {
            for (const auto& pipe : pipes) {
                if (pipe.working) {
                    results.push_back(pipe);
                }
            }
            logger.log("Poisk rabotayushih trub - naideno: " + to_string(results.size()));
            break;
        }
        }

        displaySearchResults(results, "trub");
    }

    void searchStations() {
        if (stations.empty()) {
            cout << "Net KS dlya poiska" << endl;
            return;
        }

        cout << "\n=== POISK KS ===" << endl;
        cout << "1. Po nazvaniyu" << endl;
        cout << "2. Po procentu nezadeistvovannyh tsehov" << endl;
        cout << "3. Rabotayushie KS" << endl;
        cout << "4. Nerabotayushie KS" << endl;
        cout << "Vyberite tip poiska: ";

        int choice = GetCorrectNumber(1, 4);
        vector<KS> results;

        switch (choice) {
        case 1: {
            cout << "Vvedite chast nazvaniya dlya poiska: ";
            string searchName;
            getline(cin >> ws, searchName);

            for (const auto& station : stations) {
                if (station.nameContains(searchName)) {
                    results.push_back(station);
                }
            }
            logger.log("Poisk KS po nazvaniyu: '" + searchName + "' - naideno: " + to_string(results.size()));
            break;
        }
        case 2: {
            cout << "Vvedite minimalny procent nezadeistvovannyh tsehov (0-100): ";
            double minPercent = GetCorrectNumber(0.0, 100.0);

            for (const auto& station : stations) {
                if (station.getUnusedPercent() >= minPercent) {
                    results.push_back(station);
                }
            }
            logger.log("Poisk KS po procentu nezadeistvovannyh tsehov: " + to_string(minPercent) + "% - naideno: " + to_string(results.size()));
            break;
        }
        case 3: {
            for (const auto& station : stations) {
                if (station.station_working) {
                    results.push_back(station);
                }
            }
            logger.log("Poisk rabotayushih KS - naideno: " + to_string(results.size()));
            break;
        }
        case 4: {
            for (const auto& station : stations) {
                if (!station.station_working) {
                    results.push_back(station);
                }
            }
            logger.log("Poisk nerabotayushih KS - naideno: " + to_string(results.size()));
            break;
        }
        }

        displaySearchResults(results, "KS");
    }

    void saveToFile() {
        string filename;
        cout << "Vvedite nazvanie file dlya sohraneniya (s razresheniem .txt): ";
        getline(cin >> ws, filename);

        if (filename.find(".txt") == string::npos) {
            filename += ".txt";
        }

        ofstream out(filename);
        if (!out.is_open()) {
            cout << "Oshibka sozdaniya file: " << filename << endl;
            logger.log("Oshibka sohraneniya - ne udalos sozdat file: " + filename);
            return;
        }

        out << "NEXT_ID:" << nextId << endl;

        for (const auto& pipe : pipes) {
            out << "PIPE:" << pipe.id << "," << pipe.name << "," << pipe.length << "," << pipe.width << "," << pipe.working << endl;
        }

        for (const auto& station : stations) {
            out << "KS:" << station.id << "," << station.name << "," << station.workshops << "," << station.working_workshops << "," << station.station_working << endl;
        }

        out.close();
        cout << "Dannye sohraneny v file: " << filename << "! Objectov: " << (pipes.size() + stations.size())
            << " (trub: " << pipes.size() << ", KS: " << stations.size() << ")" << endl;

        logger.log("Sohranenie dannyh v file: " + filename + " - uspeshno sohraneno " + to_string(pipes.size()) + " trub i " + to_string(stations.size()) + " KS");
    }

    void loadFromFile() {
        string filename;
        cout << "Vvedite nazvanie file dlya zagruzki (s razresheniem .txt): ";
        getline(cin >> ws, filename);

        if (filename.find(".txt") == string::npos) {
            filename += ".txt";
        }

        ifstream in(filename);
        if (!in.is_open()) {
            cout << "File ne naiden: " << filename << endl;
            logger.log("Oshibka zagruzki - file ne naiden: " + filename);
            return;
        }

        pipes.clear();
        stations.clear();

        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;

            if (line.find("NEXT_ID:") == 0) {
                nextId = stoi(line.substr(8));
            }
            else if (line.find("PIPE:") == 0) {
                Pipe pipe;
                stringstream ss(line.substr(5));
                string temp;

                getline(ss, temp, ','); pipe.id = stoi(temp);
                getline(ss, pipe.name, ',');
                getline(ss, temp, ','); pipe.length = stoi(temp);
                getline(ss, temp, ','); pipe.width = stoi(temp);
                getline(ss, temp); pipe.working = stoi(temp);

                pipes.push_back(pipe);
            }
            else if (line.find("KS:") == 0) {
                KS ks;
                stringstream ss(line.substr(3));
                string temp;

                getline(ss, temp, ','); ks.id = stoi(temp);
                getline(ss, ks.name, ',');
                getline(ss, temp, ','); ks.workshops = stoi(temp);
                getline(ss, temp, ','); ks.working_workshops = stoi(temp);
                getline(ss, temp); ks.station_working = stoi(temp);

                stations.push_back(ks);
            }
        }

        in.close();
        cout << "Dannye zagruzheny iz file: " << filename << "! Objectov: " << (pipes.size() + stations.size())
            << " (trub: " << pipes.size() << ", KS: " << stations.size() << ")" << endl;

        logger.log("Zagruzka dannyh iz file: " + filename + " - uspeshno zagruzheno " + to_string(pipes.size()) + " trub i " + to_string(stations.size()) + " KS");
    }

private:
    template<typename T>
    void displaySearchResults(const vector<T>& results, const string& typeName) {
        if (results.empty()) {
            cout << "Po zadannym kriteriyam " << typeName << " ne naideno." << endl;
        }
        else {
            cout << "\n=== NAIDENO " << results.size() << " " << typeName << " ===" << endl;
            for (const auto& obj : results) {
                obj.display();
            }
        }
    }
};

int main() {
    DataManager manager;

    while (true) {
        cout << "\n=== MENYU ===" << endl;
        cout << "1. Dobavit trubu" << endl;
        cout << "2. Dobavit KS" << endl;
        cout << "3. Prosmotr vseh objectov" << endl;
        cout << "4. Redaktirovat truby" << endl;
        cout << "5. Redaktirovat KS" << endl;
        cout << "6. Udalit truby" << endl;
        cout << "7. Udalit KS" << endl;
        cout << "8. Poisk objecta po ID" << endl;
        cout << "9. Poisk trub po filteru" << endl;
        cout << "10. Poisk KS po filteru" << endl;
        cout << "11. Sohranit v file" << endl;
        cout << "12. Zagruzit iz file" << endl;
        cout << "0. Vihod" << endl;
        cout << "Vyberite: ";

        int choice = GetCorrectNumber(0, 12);

        switch (choice) {
        case 0:
            return 0;
        case 1:
            manager.addPipe();
            break;
        case 2:
            manager.addKS();
            break;
        case 3:
            manager.viewAll();
            break;
        case 4:
            manager.editPipes();
            break;
        case 5:
            manager.editStations();
            break;
        case 6:
            manager.deletePipes();
            break;
        case 7:
            manager.deleteStations();
            break;
        case 8:
            manager.findObject();
            break;
        case 9:
            manager.searchPipes();
            break;
        case 10:
            manager.searchStations();
            break;
        case 11:
            manager.saveToFile();
            break;
        case 12:
            manager.loadFromFile();
            break;
        }
    }
}