#ifndef HW1_2_FUNC_H
#define HW1_2_FUNC_H

#include "Shoes.h"
#include "Clothes.h"

vector<Warehouse *> MakeArray(const string &TypeOfFile);

void Create(const string &name);

void MarkTypeOfFile(const string &name, const string &type);

string CheckTypeOfFile(const string &Path, const string &name);

void ChangeNoteInList(const string &OldName, const string &NewName);

void SaveArrayToFile(const vector<Warehouse *> &arr, const string &name);

void ShowList(const string &Path);

vector<Warehouse *> OpenFileToGetArray(const string &name);

void ShowArray(const vector<Warehouse *> &arr);

void DeleteArray(vector<Warehouse *> &arr);

void DeleteWarehouseInFile(const string &Path, const string &name);

void DeleteFile(const string &name);

void RewriteArrayToFile(const string &Path, const string &Name,
                        const vector<Warehouse *> &Arr);

void Edit(vector<Warehouse *> &Arr, const string &ToDo);

int Count(const vector<Warehouse *> &Arr, const string &WarehouseName);

Warehouse *Find(const vector<Warehouse *> &Arr, const string &WarehouseName);

bool CompareTitles(Warehouse *Left, Warehouse *Right);

void SortByTitle(vector<Warehouse *> &Arr);

bool CompareVolumes(Warehouse *Left, Warehouse *Right);

void SortByVolume(vector<Warehouse *> &Arr);

vector<Warehouse *> SamplePercents(vector<Warehouse *> &Arr, const double &N);

vector<Warehouse *> SampleTown(vector<Warehouse *> &Arr, const string &Town);

string MakePathToFile(const string &Path, const string &Name);

void ContactWithUser(bool &GoOn, const string &Path);

#endif //HW1_2_FUNC_H
