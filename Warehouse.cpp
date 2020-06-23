#include "Warehouse.h"

Warehouse::Warehouse() : Title(""), Town(""), Volume(0) {}

Warehouse::Warehouse(const string &title, const string &town, const int &volume) :
        Title(title), Town(town), Volume(volume) {}

string Warehouse::GetTitle() const {
    return Title;
}

int Warehouse::GetVolume() const {
    return Volume;
}

string Warehouse::GetTown() const {
    return Town;
}



