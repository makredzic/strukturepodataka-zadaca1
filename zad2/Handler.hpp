#pragma once
#include <iostream>
#include <list>

struct Handler {
    void print() const;
    void insert() ;
    void remove() ;
    
    private: std::list<char> list_;
};

void Handler::print() const {

    std::cout << "DNA: ";
    for (auto item : list_) std::cout << item;
    std::cout << std::endl;

}

void Handler::insert() {

}

void Handler::remove() {


}