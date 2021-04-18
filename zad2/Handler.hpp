#pragma once
#include <iostream>
#include <list>

struct Handler {
    void print() const;
    void insert() ;
    void remove() ;

    private:
    const char dna_[4] = {'A', 'T', 'C', 'G'};
    std::list<char> list_;
};

void Handler::print() const {

    std::cout << "DNA: ";
    for (auto item : list_) std::cout << item;
    std::cout << std::endl;

}

void Handler::insert() {

    std::cout << "Position: ";
    unsigned short pos;
    std::cin >> pos;

    std::cout << "\nValue: ";

}

void Handler::remove() {

    std::cout << "Position: ";
    unsigned short pos;
    std::cin >> pos;

    std::cout << "\nLength: ";
    unsigned short len;
    std::cin >> len;

}