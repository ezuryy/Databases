#ifndef HW1_2_SHOES_H
#define HW1_2_SHOES_H

#include "Warehouse.h"

class Shoes : public Warehouse {

    multimap<string, multimap<int, int>> ListSh;

public:

    Shoes();

    Shoes(const string &title, const string &town, const int &volume,
          multimap<string, multimap<int, int>> &list);

    void WriteToMemory() override;

    void ReadFromMemory() override;

    void Save(const string &name) override;

    Warehouse &Open(const vector<string> &Line) override;

    void Add() override;

    void Erase() override;

    void Edit() override;

    void EraseType(const string &OldType);

    void EraseNumbers(const string &OldType, const int &OldNumber, const int &OldSize);

    void AddNumbers(const string &Type, const pair<int, int> &NewPair);

    int Count() override;
};


#endif //HW1_2_SHOES_H
