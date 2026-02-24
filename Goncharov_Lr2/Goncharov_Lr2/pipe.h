#pragma once
#include "utils.h"

using namespace std;


class Pipes {
public:
    void add();
    void View() const;
    void Edit();
    bool CheakByProperities(const bool properties) const;
    bool CheakByName(const string name) const;
    void SavePipe(ofstream& fout) const;
    void LoadPipe(ifstream& fin);
    int GetId() const;
private:
    int id = 0;
    static int nextId;
    string _name;
    int _length;
    int _width;
    bool _properties;
};