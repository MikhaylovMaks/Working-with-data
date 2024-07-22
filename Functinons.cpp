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
            cout << "������������ ���� ������. ���������\n";
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
                if (isalpha(c)  || (c >= '�' && c <= '�')  || (c >= '�' && c <= '�') ||  c == '�'||  c == '�' || c == ' ') {
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
            cout << "������������ ���� ������. ���������" << endl;
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
            cout << "������������ ���� ������. ���������\n";
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
            cout << "������������ ���� ������. ���������\n";
        }
    }
}

void displayMenu() {
    cout << "1) ������ ���� ���������.\n";
    cout << "2) ������� �������� �������.\n";
    cout << "3) ��������� ���� ��������� ����������������� ��������.\n";
    cout << "4) ���������� �� ����.\n";
    cout << "5) �����.\n";
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
    cout << "�������� ���� ��� �������� ���������:" << endl;
    cout << "1) �������� ������ ������" << endl;
    cout << "2) ���������� ������" << endl;
    cout << "3) ����� ������" << endl;

    int fieldChoice = getNumberFirst();

    switch (fieldChoice) {
    case 1: {
        cout << "������� �������� ������ ������ ��� ��������: ";
        string fieldValue = getLetters();
        removeByName(list, fieldValue);
        break;
    }
    case 2: {
        cout << "������� ���������� ������ ��� ��������: ";
        int fieldValue = getInt();
        removeByDealCount(list, fieldValue);
        break;
    }
    case 3: {
        cout << "������� ����� ������ ��� ��������: ";
        double fieldValue = getDouble();
        removeByTradeVolume(list, fieldValue);
        break;
    }
    default:
        cout << "�������� �����. �������� �� ���������.\n";
        return;
    }

    cout << "�������� �������.\n";
}

void defaultValues(forward_list<Element>& list) {
    Element defaultElem;
    cout << "������� �������� ������ ������ �� ���������: ";
    defaultElem.name = getLetters();
    cout << "������� ���������� ������ �� ���������: ";
    defaultElem.dealCount = getInt();
    cout << "������� ����� ������ �� ���������: ";
    defaultElem.tradeVolume = getDouble();

    for (auto& elem : list) {
        elem = defaultElem;
    }

    cout << "����������������� �������� ��������� ���� ���������.\n";
}

void sortirovka(forward_list<Element>& list) {
    cout << "�������� ���� ��� ����������:\n";
    cout << "1) �������� ������ ������\n";
    cout << "2) ���������� ������\n";
    cout << "3) ����� ������\n";

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
        cout << "�������� �����. ���������� �� ���������.\n";
        return;
    }

    cout << "������ ������������.\n";
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
        cout << "������ �������� �����.\n";
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
                cout << "������ ������� ������: '\n'";
            }
        }
    }
    file.close();
}

void saveFile(const forward_list<Element>& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������ �������� �����.\n";
        return;
    }

    for (const auto& elem : list) {
        file << elem.name << ";" << elem.dealCount << ";" << elem.tradeVolume << ";\n";
    }

    file.close();
}