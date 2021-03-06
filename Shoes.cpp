#include "Shoes.h"

Shoes::Shoes() : Warehouse() {}

Shoes::Shoes(const string &title, const string &town, const int &volume,
             multimap<string, multimap<int, int>> &list) : Warehouse(title, town, volume), ListSh(list) {}

void Shoes::WriteToMemory() {
    string type;
    string Type;
    int Num, Size;
    cout << "Enter Title : ";
    cin >> Title;
    cout << "Enter Town : ";
    cin >> Town;
    cout << "Enter Volume : ";
    cin >> Volume;
    int n = 0;
    cout << "How many Types do you want to add? ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "---------" << i + 1 << "---------\n";
        cout << "Enter Type : ";
        cin >> Type;
        cout << "How many pairs Number-Size do you want to add? ";
        int m = 0;
        cin >> m;
        multimap<int, int> Inside;
        for (int j = 0; j < m; ++j) {
            cout << "Enter number of objects : ";
            cin >> Num;
            cout << "Enter size : ";
            cin >> Size;
            Inside.insert(pair<int, int>(Num, Size));
        }
        ListSh.insert(pair<string, multimap<int, int>>(Type, Inside));
    }
    cin.ignore();
}

void Shoes::ReadFromMemory() {
    cout << "TITLE";
    for (int i = 5; i < 20; ++i) cout << " ";
    cout << "TOWN";
    for (int i = 4; i < 20; ++i) cout << " ";
    cout << "VOLUME";
    for (int i = 6; i < 20; ++i) cout << " ";
    cout << "TYPE";
    for (int i = 4; i < 20; ++i) cout << " ";
    cout << "NUMBER";
    for (int i = 6; i < 10; ++i) cout << " ";
    cout << "SIZE\n";
    cout << Title;
    for (int i = Title.size(); i < 20; ++i) cout << " ";
    cout << Town;
    for (int i = Town.size(); i < 20; ++i) cout << " ";
    cout << Volume;
    string VolStr = std::to_string(Volume);
    for (int i = VolStr.size(); i < 20; ++i) cout << " ";
    for (auto it1 = ListSh.begin(); it1 != ListSh.end(); ++it1) {
        if (it1 != ListSh.begin())
            for (int i = 0; i < 60; ++i) cout << " ";
        cout << (*it1).first;
        for (int i = (*it1).first.size(); i < 20; ++i) cout << " ";
        for (auto it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2) {
            if (it2 != (*it1).second.begin())
                for (int i = 0; i < 80; ++i) cout << " ";
            cout << (*it2).first;
            string NumberStr = std::to_string((*it2).first);
            for (int i = NumberStr.size(); i < 10; ++i) cout << " ";
            cout << (*it2).second;
            string SizeStr = std::to_string((*it2).second);

            for (int i = SizeStr.size(); i < 10; ++i) cout << " ";
            cout << "\n";
        }
    }
}

void Shoes::Save(const string &name) {
    string filename = name + ".csv";
    string Vol = std::to_string(Volume);
    fstream file;
    file.open(filename, fstream::app);
    if (file.is_open()) {
        for (auto & it1 : ListSh) {
            for (auto it2 = it1.second.begin(); it2 != it1.second.end(); ++it2) {
                file << Title << ";" << Town << ";" << Volume << ";";
                file << it1.first << ";";
                file << (*it2).first << ";" << (*it2).second << "\n";
            }
        }
    }
    file.close();
}

Warehouse &Shoes::Open(const vector<string> &Line) {
    string temp = Line[0];
    Title = temp;
    Title.erase(Title.begin() + Title.find(';'), Title.end());

    temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
    Town = temp;
    Town.erase(Town.begin() + Town.find(';'), Town.end());

    temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
    string volumeStr = temp;
    volumeStr.erase(volumeStr.begin() + volumeStr.find(';'), volumeStr.end());
    temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
    const char *volumeChar = volumeStr.c_str();
    Volume = std::atoi(volumeChar);

    string TitleOfWarehouse = Title + ";" + Town + ";" + volumeStr + ";";
    string str = Line[0];

    for (int i = 0; i < Line.size() && str.find(TitleOfWarehouse) != string::npos;) {
        //удостоверимся, что в строке есть нужный нам склад
        str = Line[i];
        for (int j = 0; j < 3; ++j) {
            str.erase(str.begin(), str.begin() + str.find(';') + 1);
        }
        string type = str;
        type.erase(type.begin() + type.find(';'), type.end());//определяем тип продукции
        multimap<int, int> Inside;
        int k = 0; //счетчик чтобы следить, обрезали ли мы начало вектора или нет
        while (str.find(type) != string::npos) {
            if (k != 0) {
                for (int j = 0; j < 3; ++j) {
                    str.erase(str.begin(), str.begin() + str.find(';') + 1);
                }
            }
            str.erase(str.begin(), str.begin() + str.find(';') + 1);
            string numStr, sizeStr;
            numStr = str;
            numStr.erase(numStr.begin() + numStr.find(';'), numStr.end());
            const char *numChar = numStr.c_str();
            int Num = std::atoi(numChar);
            sizeStr = str;
            sizeStr.erase(sizeStr.begin(), sizeStr.begin() + +sizeStr.find(";") + 1);
            const char *sizeChar = sizeStr.c_str();
            int Size = std::atoi(sizeChar);
            Inside.insert(pair<int, int>(Num, Size));
            if (i + 1 < Line.size()) {
                ++i;
                str = Line[i];
            }
            ++k;
        }
        ListSh.insert(pair<string, multimap<int, int>>(type, Inside));
    }
    return *this;
}

void Shoes::Add() {
    cout << "Enter 'type' to add new type with several pairs number-size to array.\n";
    cout << "Enter 'numbers' to add new pair number-size to array.\n> ";
    string ans;
    cin >> ans;
    if (ans == "type") {
        string NewType;
        int Num = 0, Size = 0, m = 0;
        cout << "Enter type to add : ";
        cin >> NewType;
        cout << "How many pairs Number-Size do you want to add? ";
        cin >> m;
        multimap<int, int> Inside;
        for (int j = 0; j < m; ++j) {
            cout << "Enter number of objects : ";
            cin >> Num;
            cout << "Enter size : ";
            cin >> Size;
            Inside.insert(pair<int, int>(Num, Size));
        }
        this->ListSh.insert(pair<string, multimap<int, int>>(NewType, Inside));
    } else if (ans == "numbers") {
        string Type;
        int Num = 0, Size = 0;
        cout << "Enter type : ";
        cin >> Type;
        cout << "Enter number of objects : ";
        cin >> Num;
        cout << "Enter size : ";
        cin >> Size;
        this->AddNumbers(Type, pair<int, int>(Num, Size));
    }
    cin.ignore();
}

void Shoes::Erase() {
    cout << "Enter 'type' to erase one type from array.\n";
    cout << "Enter 'numbers' to erase one pair number-size.\n> ";
    string ans;
    cin >> ans;
    if (ans == "type") {
        cout << "Enter type to erase : ";
        string OldType;
        cin >> OldType;
        this->EraseType(OldType);
    } else if (ans == "numbers") {
        cout << "Enter type to erase : ";
        string OldType;
        cin >> OldType;
        cout << "Enter number to erase : ";
        int OldNumber = 0, OldSize = 0;
        cin >> OldNumber;
        cout << "Enter size to erase : ";
        cin >> OldSize;
        this->EraseNumbers(OldType, OldNumber, OldSize);
    }
    cin.ignore();
}

void Shoes::Edit() {
    //Erase old data
    cout << "Enter type to edit : ";
    string OldType;
    cin >> OldType;
    cout << "Enter number to edit : ";
    int OldNumber = 0, OldSize = 0;
    cin >> OldNumber;
    cout << "Enter size to edit : ";
    cin >> OldSize;

    //Add new data
    int Num = 0, Size = 0;
    cout << "Enter number of objects : ";
    cin >> Num;
    cout << "Enter size : ";
    cin >> Size;
    this->EraseNumbers(OldType, OldNumber, OldSize);
    this->AddNumbers(OldType, pair<int, int>(Num, Size));
    cin.ignore();
}

void Shoes::EraseType(const string &OldType) {
    bool flag = false;
    for (auto it = ListSh.begin(); it != ListSh.end(); ++it) {
        if ((*it).first == OldType) {
            ListSh.erase(it);
            flag = true;
        }
    }
    if (!flag) throw std::invalid_argument("Type not found.");
}

void Shoes::EraseNumbers(const string &OldType, const int &OldNumber, const int &OldSize) {
    bool flag = false;
    for (auto & it1 : ListSh) {
        if (it1.first == OldType) {
            for (auto it2 = it1.second.begin(); it2 != it1.second.end(); ++it2) {
                if ((*it2).first == OldNumber && (*it2).second == OldSize) {
                    it1.second.erase(it2);
                    flag = true;
                }
            }
        }
    }
    if (!flag) throw std::invalid_argument("Type or element not found.");
}

void Shoes::AddNumbers(const string &Type, const pair<int, int> &NewPair) {
    for (auto & it1 : ListSh) {
        if (it1.first == Type) {
            it1.second.insert(NewPair);
        }
    }
}

int Shoes::Count() {
    int count = 0;
    for (auto & it1 : ListSh) {
        for (auto & it2 : it1.second) {
            count += it2.first;
        }
    }
    return count;
}