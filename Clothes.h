#ifndef HW1_2_CLOTHES_H
#define HW1_2_CLOTHES_H

#include "Warehouse.h"

class Clothes : public Warehouse {

    multimap<string, multimap<int, pair<int, int>>> ListCl;

public:

    Clothes();

    Clothes(const string &title, const string &town, const int &volume,
            multimap<string, multimap<int, pair<int, int>>> &list);

    void WriteToMemory() override;

    void ReadFromMemory() override;

    void Save(const string &name) override;

    Warehouse &Open(const vector<string> &Line) override;

    void Add() override;

    void Erase() override;

    void Edit() override;

    void EraseType(const string &OldType);

    void EraseNumbers(const string &OldType, const int &OldNumber, const int &OldSize, const int &OldHeight);

    void AddNumbers(const string &Type, const pair<int, pair<int, int>> &NewPair);

    int Count() override;
};

#endif //HW1_2_CLOTHES_H
