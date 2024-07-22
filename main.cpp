#include "Functions.h"

#include <iostream>
#include <forward_list>

using namespace std;

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RU");
    forward_list<Element> list;
    loadFromFile(list, Constants::dataFilePath);
    int choice{ 0 };
    while (choice != 5) {
        displayMenu();
        cout << "Выберите действие: ";
        choice = getNumberFirst();
        switch (choice) {
        case 1:
            HprintList(list);
            break;
        case 2:
            removeElem(list);
            break;
        case 3:
            defaultValues(list);
            break;
        case 4:
            sortirovka(list);
            break;
        case 5:
            cout << "Выход.\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
    saveFile(list, Constants::dataFilePath);
    return 0;
}