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

}

void Handler::insert() {

}

void Handler::remove() {


}