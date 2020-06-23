#include "func.h"

vector<Warehouse *> MakeArray(const string &TypeOfFile) {//ввод с клавиатуры массива
    int count = 0;                                       //для записи в файл типа TypeOfFile
    string type;
    vector<Warehouse *> arr;
    cout << "How many warehouses do you want to add? ";
    cin >> count;
    try {
        for (int i = 0; i < count; ++i) {
            cout << "To add clothes enter 'c', to add shoes enter 's' : ";  //проверяем, соответствует ли класс,
            cin >> type;                                                    //который хотим записать в файл, типу файла
            if (type == "c" && (TypeOfFile == "clothes" || TypeOfFile == "hybrid")) {
                auto *Cl = new Clothes();
                Cl->WriteToMemory();
                arr.push_back(Cl);
            } else if (type == "s" && (TypeOfFile == "shoes" || TypeOfFile == "hybrid")) {
                auto *Sh = new Shoes();
                Sh->WriteToMemory();
                arr.push_back(Sh);
            } else {
                throw std::exception();
            }
        }
    }
    catch (...) {
        cout << "Undefined command or you try to add incorrect element of class.\n";
    }
    return arr;
}


void Create(const string &name) { //создание файла name
    string filename = name + ".csv";
    fstream file;
    file.open(filename, fstream::app);
    try {
        if (!file.is_open()) {
            throw std::exception();
        } else {
            cout << "The file " << filename << " was created successfully.\n";
        }
    }
    catch (...) {
        cout << "Error opening the file " << filename << ".\n";
    }
    file.close();
}

void MarkTypeOfFile(const string &name, const string &type) { //помечаем в списке файлов
    string filename = name + ".csv";                          //тип файла (гибридный или однотипный)
    fstream list;
    list.open("List.csv", fstream::app);
    if (list.is_open()) {
        list << name << ";" << type << "\n";
    }
    list.close();
}

string CheckTypeOfFile(const string &name) { //проверяем, существует ли файл name
    bool flag = false;                       //находим тип файла (поясняет, элементы каких классов
    string TypeOfFile;                       //должны храниться в файле)
    int count = 0;
    char Line[100][100];
    fstream list;
    list.open("List.csv");
    if (list.is_open()) {
        while (list.getline(Line[count], 100)) count++;
    }
    list.close();
    for (int i = 0; i < count; ++i) {
        string temp = Line[i];
        temp.erase(temp.find(";"), temp.size());
        if (temp == name) {
            TypeOfFile = Line[i];
            TypeOfFile.erase(0, TypeOfFile.find(";") + 1);
            cout << "Type Of File = " << TypeOfFile << endl;
            i = count;
            flag = true;
        }
    }
    if (!flag) throw std::invalid_argument("File does not exist.");
    return TypeOfFile;
}

void ChangeNoteInList(const string &OldName, const string &NewName) { //изменяем метку в List.csv
    //Deleting from file : copy lines                                 //при удалении/переименовании файла
    string filename = OldName + ".csv";         // filename = (string) file.csv
    const char *chFilename = filename.c_str();  // chFilename = (char*) file.csv
    int count = 0, pos = -1;
    char Line[100][100];
    string newline = NewName;
    fstream list;
    list.open("List.csv");
    if (list.is_open()) {
        while (list.getline(Line[count], 100)) count++;
    }
    list.close();
    for (int i = 0; i < count; ++i) {
        string temp = Line[i];
        string Name(temp.begin(), temp.begin() + temp.find(";"));
        if (Name == OldName) {
            pos = i;
            if (!NewName.empty()) {
                string ending(temp, temp.find(";"), temp.size() - temp.find(";"));
                newline += ending;
            }
        }
    }
    //Deleting from file : rewrite lines
    try {
        if (remove("List.csv") != 0) {
            throw std::exception();
        } else {
            cout << "File List.csv was delete successfully.\n";
            fstream lis;
            lis.open("List.csv", fstream::app);
            try {
                if (!lis.is_open()) {
                    throw std::exception();
                } else {
                    for (int i = 0; i < count; ++i) {
                        if (i != pos) {
                            lis << Line[i] << "\n";
                        } else if (i == pos && !newline.empty()) {
                            lis << newline << "\n";
                        } else if (i == pos && !newline.empty()) {
                            pos = -1;
                        }
                    }
                }
            }
            catch (...) {
                cout << "Error opening the file List.csv.\n";
            }
            lis.close();
        }
    }
    catch (...) {
        cout << "Error deleting the file " << filename << ".\n";
    }
}

void SaveArrayToFile(const vector<Warehouse *> &arr, const string &name) { //сохранение массива элементов класса в файл
    for (auto j : arr)
        j->Save(name);
}

void ShowList() { //вывод списка существующих бд на экран (из List.csv)
    int count = 0;
    char Line[100][100];
    fstream list;
    list.open("List.csv");
    try {
        if (!list.is_open()) {
            throw std::exception();
        } else {
            while (list.getline(Line[count], 100)) count++;
        }
        for (int i = 0; i < count; ++i) {
            cout << Line[i] << endl;
        }
    }
    catch (...) {
        cout << "Error opening the file List.csv.\n";
    }
    list.close();
}

vector<Warehouse *> OpenFileToGetArray(const string &name) { //считываем массив из файла
    string filename = name + ".csv";
    int count = 0;
    char Line[100][100];
    vector<Warehouse *> arr;
    fstream file;
    file.open(filename);
    if (file.is_open()) {
        while (file.getline(Line[count], 100)) count++;
    } else {
        throw std::invalid_argument("File does not exist.");
    }
    file.close();
    for (int i = 0; i < count;) {
        string temp = Line[i];
        string Title = temp;
        Title.erase(Title.begin() + Title.find(";"), Title.end());
        Title += ";";                                                       //Title, Town, volumeStr
                                                                            //используются только для формирования
        temp.erase(temp.begin(), temp.begin() + temp.find(";") + 1); //первых;трех;параметров; для одного склада
        string Town = temp;
        Town.erase(Town.begin() + Town.find(';'), Town.end());
        Town += ";";

        temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
        string volumeStr = temp;
        volumeStr.erase(volumeStr.begin() + volumeStr.find(';'), volumeStr.end());
        volumeStr += ";";
        temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
        //const char *volumeChar = volumeStr.c_str();
        //int Volume = std::atoi(volumeChar);

        string FirstThreeParam = Title + Town;
        FirstThreeParam += volumeStr;
        temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
        temp.erase(temp.begin(), temp.begin() + temp.find(';') + 1);
        vector<string> ReadOneClass;
        string str = Line[i];
        while (str.find(FirstThreeParam) != string::npos && i < count) {
            ReadOneClass.emplace_back(Line[i]);
            ++i;
            str = Line[i];
        }
        if (temp.find(';') == string::npos) { //Open() для Shoes
            auto *Sh = new Shoes();
            Sh->Open(ReadOneClass);
            arr.push_back(Sh);
        } else {                                 //Open() для Clothes
            auto *Cl = new Clothes();
            Cl->Open(ReadOneClass);
            arr.push_back(Cl);
        }
    }
    return arr;
}

void ShowArray(const vector<Warehouse *> &arr) { //вывод массива
    for (auto i : arr)
        i->ReadFromMemory();
}

void DeleteArray(vector<Warehouse *> &arr) { //чистим память
    for (auto &i : arr)
        delete i;
}

void DeleteWarehouseInFile(const string &name) { //флаг нужен для проверки, что в файле есть TitleToDelete
    bool flag = false;
    string TitleToDelete;
    cout << "Enter Title to delete : ";
    cin >> TitleToDelete;
    vector<Warehouse *> Arr = OpenFileToGetArray(name); //если файла name нет, бросится std::invalid_argument
    for (int i = 0; i < Arr.size(); ++i) {
        if (Arr[i]->GetTitle() == TitleToDelete) {
            Arr.erase(Arr.begin() + i);
            flag = true;
        }
    }
    if (!flag) throw std::invalid_argument("This Warehouse not found.");
    RenameFile(name, name, Arr);
    cin.ignore();
}

void DeleteFile(const string &name) { //удаляем файл name
    string filename = name + ".csv";
    const char *chFilename = filename.c_str(); // chFilename = (char*) name.csv
    try {
        if (remove(chFilename) != 0) {
            throw std::exception();
        } else {
            cout << "File " << filename << " was delete successfully.\n";
            ChangeNoteInList(name, "");
        }
    }
    catch (...) {
        cout << "Error deleting the file " << filename << ".\n";
    }
}

void RenameFile(const string &OldName, const string &NewName,
                const vector<Warehouse *> &Arr) { //Удаляем OldName, создаем NewName, записываем Arr
    string OldFilename = OldName + ".csv";
    const char *ChOldFilename = OldFilename.c_str(); // chFilename = (char*) filename.csv
    try {
        if (remove(ChOldFilename) != 0) {
            throw std::exception();
        } else {
            cout << "The file " << OldFilename << " was deleted successfully.\n";
            Create(NewName);
            SaveArrayToFile(Arr, NewName);
            string TypeOfFile = CheckTypeOfFile(OldName);
            ChangeNoteInList(OldName, NewName);
        }
    }
    catch (...) {
        cout << "Error while deleting the file " << OldFilename << ".\n";
    }
}

vector<Warehouse *> Edit(vector<Warehouse *> &Arr, const string &ToDo) { //камень на распутье
    string TitleToEdit;                                                  //как именно изменить
    cout << "Enter Warehouse to edit : ";                                //содержимое склада TitleToEdit
    cin >> TitleToEdit;
    int i = 0;
    for (; Arr[i]->GetTitle() != TitleToEdit && i < Arr.size(); ++i) {
        if (i + 1 == Arr.size() && Arr[i]->GetTitle() != TitleToEdit)
            throw std::invalid_argument("This Warehouse not found.");
    }
    if (Arr[i]->GetTitle() == TitleToEdit) {
        if (ToDo == "add")
            Arr[i]->Add();
        else if (ToDo == "erase")
            Arr[i]->Erase();
        else if (ToDo == "edit")
            Arr[i]->Edit();
    }
    return Arr;
}

int Count(const vector<Warehouse *> &Arr, const string &WarehouseName) { //подсчет кол-ва товаров на складе
    int count = 0, i = 0;
    for (; Arr[i]->GetTitle() != WarehouseName && i < Arr.size(); ++i) {
        if (i + 1 == Arr.size() && Arr[i]->GetTitle() != WarehouseName)
            throw std::invalid_argument("This Warehouse not found.");
    }
    if (Arr[i]->GetTitle() == WarehouseName)
        count = Arr[i]->Count();
    return count;
}

Warehouse *Find(const vector<Warehouse *> &Arr, const string &WarehouseName) { //поиск склада по его названию
    int i = 0;
    for (; Arr[i]->GetTitle() != WarehouseName && i < Arr.size(); ++i) {
        if (i + 1 == Arr.size() && Arr[i]->GetTitle() != WarehouseName)
            throw std::invalid_argument("This Warehouse not found.");
    }
    if (Arr[i]->GetTitle() == WarehouseName)
        return Arr[i];
    return nullptr;
}

bool CompareTitles(Warehouse *Left, Warehouse *Right) { //сравниваем названия складов
    return (Left->GetTitle() < Right->GetTitle());
}

void SortByTitle(vector<Warehouse *> &Arr) { //сортируем по названию
    std::sort(Arr.begin(), Arr.end(), CompareTitles);
}

bool CompareVolumes(Warehouse *Left, Warehouse *Right) { //сравниваем объем складов
    return (Left->GetVolume() < Right->GetVolume());
}

void SortByVolume(vector<Warehouse *> &Arr) { //сортируем по объему
    std::sort(Arr.begin(), Arr.end(), CompareVolumes);
}

vector<Warehouse *> SamplePercents(vector<Warehouse *> &Arr, const double &N) { //выборка складов, заполненных менее
    vector<Warehouse *> NewArr;                                                 //чем на заданный процент
    for (auto &it : Arr) {
        double percent = 100 * (static_cast<double>(it->Count())) / (static_cast<double>(it->GetVolume()));
        if (percent < N) {
            NewArr.push_back(it);
        }
    }
    return NewArr;
}

vector<Warehouse *> SampleTown(vector<Warehouse *> &Arr, const string &Town) { //выборка складов, находящихся в
    vector<Warehouse *> NewArr;                                                //заданном городе
    for (auto &it : Arr) {
        if ((*it).GetTown() == Town) {
            NewArr.push_back(it);
        }
    }
    return NewArr;
}

void ContactWithUser(bool &GoOn) {
    string s;
    cout << "> ";
    //cin.clear();
    getline(std::cin, s);

    if (s.find("create clothes ") != string::npos) { //создание БД для одежды
        string title(s, s.find('s') + 2, s.size() - s.find('s') - 1);
        Create(title);
        MarkTypeOfFile(title, "clothes");
    } else if (s.find("create shoes ") != string::npos) { //создание БД для обуви
        string title(s, s.find("s ") + 2, s.size() - s.find("s ") - 1);
        Create(title);
        MarkTypeOfFile(title, "shoes");
    } else if (s.find("create ") != string::npos) { //создание гибридной БД
        string title(s, s.find(' ') + 1, s.size() - s.find(' '));
        Create(title);
        MarkTypeOfFile(title, "hybrid");
    } else if (s.find("show databases") != string::npos) { //вывести список БД
        ShowList();
    } else if (s.find("write") != string::npos) { //запись массива в память и вывод
        vector<Warehouse *> arr = MakeArray("hybrid"); //массив в файл не сохраняется
        ShowArray(arr);
        DeleteArray(arr);
        cin.ignore();
    } else if (s.find("save ") != string::npos) { //Добавление в файл склада, введенного с клавиатуры
        string name(s, s.find(' ') + 1, s.size() - s.find(' '));
        try {
            string TypeOfFile = CheckTypeOfFile(name);
            vector<Warehouse *> arr = MakeArray(TypeOfFile);
            SaveArrayToFile(arr, name);
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("open ") != string::npos) { //Открыть, считать и вывести массив из файла
        string name(s, s.find(' ') + 1, s.size() - s.find(' '));
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            ShowArray(arr);
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("remove warehouse ") != string::npos) { //Удалить один склад из файла
        string name(s, s.find("se ") + 3, s.size() - s.find("se ") - 2);
        try {
            DeleteWarehouseInFile(name);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("remove ") != string::npos) { //Удалить файл
        string name(s, s.find(' ') + 1, s.size() - s.find(' '));
        DeleteFile(name);
    } else if (s.find("rename ") != string::npos) { //переименовать файл
        string OldName(s, s.find(' ') + 1, s.size());
        string NewName(OldName, OldName.find(' ') + 1, OldName.size());
        OldName.erase(OldName.find(' '), OldName.size());
        cout << "Old Name :" << OldName << endl;
        cout << "New Name :" << NewName << endl;
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(OldName);
            RenameFile(OldName, NewName, arr);
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("add ") != string::npos) { //добавить запись в файл
        string name(s, s.find(' ') + 1, s.size() - s.find(' '));
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            Edit(arr, "add");
            RenameFile(name, name, arr);
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("erase ") != string::npos) { //удалить запись из файла
        string name(s, s.find(' ') + 1, s.size() - s.find(' '));
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            Edit(arr, "erase");
            RenameFile(name, name, arr);
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("edit ") != string::npos) { //изменить запись в файле
        string name(s, s.find(' ') + 1, s.size() - s.find(' '));
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            Edit(arr, "edit");
            RenameFile(name, name, arr);
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("count ") != string::npos) { //посчитать кол-во продукции на складе
        string name(s, s.find(' ') + 1, s.size());
        string WarehouseName(name, name.find(' ') + 1, name.size());
        name.erase(name.find(' '), name.size());
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            int c = Count(arr, WarehouseName);
            cout << "The product quantity in " << WarehouseName << " is " << c << ".\n";
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("find ") != string::npos) { //найти и вывести склад
        string name(s, s.find(' ') + 1, s.size());
        string WarehouseName(name, name.find(' ') + 1, name.size());
        name.erase(name.find(' '), name.size());
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            Warehouse *Result = Find(arr, WarehouseName);
            Result->ReadFromMemory();
            DeleteArray(arr);
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("sort title ") != string::npos) { //отсортировать БД по названию
        string name(s, s.find('e') + 2, s.size() - s.find('e') - 1);
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            SortByTitle(arr);
            cout << "Save sorted array? (Saving to file " << name << ".csv) [y/n]\n> ";
            char ans;
            cin >> ans;
            if (ans == 'y') {
                RenameFile(name, name, arr);
            } else if (ans == 'n') {
                ShowArray(arr);
            }
            DeleteArray(arr);
            cin.ignore();
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("sort volume ") != string::npos) { //отсортировать БД по увеличению объема
        string name(s, s.find('e') + 2, s.size() - s.find('e') - 1);
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            SortByVolume(arr);
            cout << "Save sorted array? (Saving to file " << name << ".csv) [y/n]\n> ";
            char ans;
            cin >> ans;
            if (ans == 'y') {
                RenameFile(name, name, arr);
            } else if (ans == 'n') {
                ShowArray(arr);
            }
            DeleteArray(arr);
            cin.ignore();
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("piled ") != string::npos) { //создать выборку складов, заполненных менее чем на N%
        string str(s, s.find(' ') + 1, s.size() - s.find(' '));
        string name(str, 0, str.find(' '));
        string n(str, str.find(' ') + 1, s.size() - s.find(' '));
        double N = std::stod(n);
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            vector<Warehouse *> NewArray = SamplePercents(arr, N);
            cout << "Save new array? [y/n]\n> ";
            char ans;
            cin >> ans;
            if (ans == 'y') {
                cout << "Enter name of the new file : ";
                string NewName;
                cin >> NewName;
                Create(NewName);
                string TypeOfFile = CheckTypeOfFile(name);
                MarkTypeOfFile(NewName, TypeOfFile);
                SaveArrayToFile(NewArray, NewName);
            } else if (ans == 'n') {
                ShowArray(NewArray);
            }
            DeleteArray(arr);
            cin.ignore();
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("located in ") != string::npos) { //создать выборку складов, находяжихся в городе town
        string str(s, s.find("n ") + 2, s.size() - s.find("n ") - 1);
        string town(str, 0, str.find(' '));
        string name(str, str.find(' ') + 1, s.size() - s.find(' '));
        try {
            vector<Warehouse *> arr = OpenFileToGetArray(name);
            vector<Warehouse *> NewArray = SampleTown(arr, town);
            cout << "Save new array? [y/n]\n> ";
            char ans;
            cin >> ans;
            if (ans == 'y') {
                cout << "Enter name of the new file : ";
                string NewName;
                cin >> NewName;
                Create(NewName);
                string TypeOfFile = CheckTypeOfFile(name);
                MarkTypeOfFile(NewName, TypeOfFile);
                SaveArrayToFile(NewArray, NewName);
            } else if (ans == 'n') {
                ShowArray(NewArray);
            }
            DeleteArray(arr);
            cin.ignore();
        }
        catch (const std::invalid_argument &e) {
            cout << e.what() << "\n";
        }
    } else if (s.find("stop") != string::npos) { //выйти из программы
        GoOn = false;
    } else if (s.find("help") != string::npos) {
        cout << "To create DB enter 'create <DB_name>'\n\n";
        cout << "To create DB for clothes enter 'create clothes <DB_name>'\n\n";
        cout << "To create DB for shoes enter 'create shoes <DB_name>'\n\n";
        cout << "To add warehouse in DB enter 'save <DB_name>'\n\n";
        cout << "To show ist of DBs enter 'show databases'\n\n";
        cout << "To show DB enter 'open <DB_name>'\n\n";
        cout << "To remove warehouse from file enter 'remove warehouse <DB_name>'\n\n";
        cout << "To remove DB enter 'remove <DB_name>'\n\n";
        cout << "To rename DB enter 'rename <old_DB_name> <new_DB_name>'\n\n";
        cout << "To add note to warehouse enter 'add <DB_name>'\n\n";
        cout << "To erase note from warehouse enter 'erase <DB_name>'\n\n";
        cout << "To edit note in warehouse enter 'edit <DB_name>'\n\n";
        cout << "To calculate the product quantity in warehouse enter 'count <DB_name> <Warehouse_name>'\n\n";
        cout << "To find a warehouse in DB enter 'find <DB_name> <Warehouse_name>'\n\n";
        cout << "To sort warehouses by title enter 'sort title <DB_name>'\n\n";
        cout << "To sort warehouses by volume enter 'sort volume <DB_name>'\n\n";
        cout << "To find warehouses piled up less than N percents enter 'piled <DB_name> <N>'\n\n";
        cout << "To find warehouses located in Town enter 'located in <Town> <DB_name>'\n\n";
        cout << "To exit the program enter 'stop'\n\n";
    } else if (!s.empty()) {
        cout << "Undefined command. To show the commands enter 'help'\n";
    }
}