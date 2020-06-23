#include "Shoes.h"
#include "Clothes.h"
#include "func.h"

int main() {

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

    bool GoOn = true;

    while(GoOn) {
        ContactWithUser(GoOn);
    }

    return 0;
}

