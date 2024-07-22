#include "Functions.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int getNumberFirst() {
    while (true) {
        string input;
        getline(cin, input);

        if (input.empty() || input.length() != 1 || input.find_first_not_of("12345") != string::npos) {
            cout << "Неправильный ввод данных. Повторите\n";
        }
        else {
            return stoi(input);
        }
    }
}

string getLetters() {
    while (true) {
        string input;
        getline(cin, input);

        bool valid = true;
        bool wasSpace = false;
        if (input.empty() || input.front() == ' ' || input.back() == ' ') {
            valid = false;
        }
        else {
            for (char c : input) {
                if (isalpha(c)  || (c >= 'А' && c <= 'Я')  || (c >= 'а' && c <= 'я') ||  c == 'Ё'||  c == 'ё' || c == ' ') {
                    if (c == ' ') {
                        if (wasSpace) {
                            valid = false;
                            break;
                        }
                        wasSpace = true;
                    }
                    else {
                        wasSpace = false;
                    }
                }
                else {
                    valid = false;
                    break;
                }
            }
        }

        if (!valid) {
            cout << "Неправильный ввод данных. Повторите" << endl;
        }
        else {
            return input;
        }
    }
}

int getInt() {
    while (true) {
        string input;
        getline(cin, input);
        try {
            return stoi(input);
        }
        catch (...) {
            cout << "Неправильный ввод данных. Повторите\n";
        }
    }
}

double getDouble() {
    while (true) {
        string input;
        getline(cin, input);
        try {
            return stod(input);
        }
        catch (...) {
            cout << "Неправильный ввод данных. Повторите\n";
        }
    }
}

void displayMenu() {
    cout << "1) Печать всех элементов.\n";
    cout << "2) Удалить заданный элемент.\n";
    cout << "3) Присвоить всем элементам предустановленные значения.\n";
    cout << "4) Сортировка по полю.\n";
    cout << "5) Выход.\n";
}

void HprintList(forward_list<Element>& list) {
    printList(list);
}

void removeByName(forward_list<Element>& list, const string& fieldValue) {
    list.remove_if([&fieldValue](const Element& elem) {
        return elem.name == fieldValue;
        });
}

void removeByDealCount(forward_list<Element>& list, int fieldValue) {
    list.remove_if([&fieldValue](const Element& elem) {
        return elem.dealCount == fieldValue;
        });
}

void removeByTradeVolume(forward_list<Element>& list, double fieldValue) {
    list.remove_if([&fieldValue](const Element& elem) {
        return elem.tradeVolume == fieldValue;
        });
}

void removeElem(forward_list<Element>& list) {
    cout << "Выберите поле для удаления элементов:" << endl;
    cout << "1) Название ценной бумаги" << endl;
    cout << "2) Количество сделок" << endl;
    cout << "3) Объём торгов" << endl;

    int fieldChoice = getNumberFirst();

    switch (fieldChoice) {
    case 1: {
        cout << "Введите название ценной бумаги для удаления: ";
        string fieldValue = getLetters();
        removeByName(list, fieldValue);
        break;
    }
    case 2: {
        cout << "Введите количество сделок для удаления: ";
        int fieldValue = getInt();
        removeByDealCount(list, fieldValue);
        break;
    }
    case 3: {
        cout << "Введите объём торгов для удаления: ";
        double fieldValue = getDouble();
        removeByTradeVolume(list, fieldValue);
        break;
    }
    default:
        cout << "Неверный выбор. Удаление не выполнено.\n";
        return;
    }

    cout << "Элементы удалены.\n";
}

void defaultValues(forward_list<Element>& list) {
    Element defaultElem;
    cout << "Введите название ценной бумаги по умолчанию: ";
    defaultElem.name = getLetters();
    cout << "Введите количество сделок по умолчанию: ";
    defaultElem.dealCount = getInt();
    cout << "Введите объём торгов по умолчанию: ";
    defaultElem.tradeVolume = getDouble();

    for (auto& elem : list) {
        elem = defaultElem;
    }

    cout << "Предустановленные значения присвоены всем элементам.\n";
}

void sortirovka(forward_list<Element>& list) {
    cout << "Выберите поле для сортировки:\n";
    cout << "1) Название ценной бумаги\n";
    cout << "2) Количество сделок\n";
    cout << "3) Объём торгов\n";

    int choice = getNumberFirst();
    switch (choice) {
    case 1:
        list.sort([](const Element& a, const Element& b) {
            return a.name > b.name;
            });
        break;
    case 2:
        list.sort([](const Element& a, const Element& b) {
            return a.dealCount > b.dealCount;
            });
        break;
    case 3:
        list.sort([](const Element& a, const Element& b) {
            return a.tradeVolume > b.tradeVolume;
            });
        break;
    default:
        cout << "Неверный выбор. Сортировка не выполнена.\n";
        return;
    }

    cout << "Список отсортирован.\n";
}

void printList(const forward_list<Element>& list) {
    for (const auto& elem : list) {
        cout << "  " << elem.name << "  "
            << elem.dealCount << "  " << elem.tradeVolume << endl;
    }
}

void loadFromFile(forward_list<Element>& list, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Element elem;
        string dealCountStr, tradeVolumeStr;
        if (getline(iss, elem.name, ';') &&
            getline(iss, dealCountStr, ';') &&
            getline(iss, tradeVolumeStr, ';')) {
            try {
                elem.dealCount = stoi(dealCountStr);
                elem.tradeVolume = stod(tradeVolumeStr);
                list.push_front(elem);
            }
            catch (...) {
                cout << "Ошибка разбора данных: '\n'";
            }
        }
    }
    file.close();
}

void saveFile(const forward_list<Element>& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        return;
    }

    for (const auto& elem : list) {
        file << elem.name << ";" << elem.dealCount << ";" << elem.tradeVolume << ";\n";
    }

    file.close();
}