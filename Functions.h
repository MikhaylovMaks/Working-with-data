#pragma once

#include <forward_list>
#include <string>

using namespace std;

namespace Constants {
    const std::string dataFilePath = "data.txt";
}

struct Element {
    string name;
    int dealCount;
    double tradeVolume;
};

int getNumberFirst();
string getLetters();
void displayMenu();
void HprintList(forward_list<Element>& list);
void removeElem(forward_list<Element>& list);
void defaultValues(forward_list<Element>& list);
void sortirovka(forward_list<Element>& list);
void printList(const forward_list<Element>& list);
void loadFromFile(forward_list<Element>& list, const string& filename);
void saveFile(const forward_list<Element>& list, const string& filename);
void removeByName(forward_list<Element>& list, const string& fieldValue);
void removeByDealCount(forward_list<Element>& list, int fieldValue);
void removeByTradeVolume(forward_list<Element>& list, double fieldValue);