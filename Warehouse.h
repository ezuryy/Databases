#ifndef HW1_2_WAREHOUSE_H
#define HW1_2_WAREHOUSE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <memory>
#include <experimental/filesystem>
#include <iterator>
namespace fs = std::experimental::filesystem;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::ofstream;
using std::fstream;
using std::ifstream;
using std::multimap;
using std::pair;
using std::vector;
using std::set;

class Warehouse {
protected:
    string Title;
    string Town;
    int Volume;

    Warehouse();

    Warehouse(const string &title, const string &town, const int &volume);

public:

    virtual void WriteToMemory() = 0;

    virtual ~Warehouse() = default;

    virtual void ReadFromMemory() = 0;

    virtual void Save(const string &name) = 0;

    virtual Warehouse& Open(const vector<string> &Line) = 0;

    string GetTitle() const;

    string GetTown() const;

    int GetVolume() const;

    virtual void Add() = 0;

    virtual void Erase() = 0;

    virtual void Edit() = 0;

    virtual int Count() = 0;
};

#endif //HW1_2_WAREHOUSE_H
