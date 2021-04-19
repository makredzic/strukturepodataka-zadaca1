#pragma once
#include <iostream>
#include <list>

struct Handler {
    void print() const;
    void insert() ;
    void remove() ;

    private:
    std::list<char> list_;
    const char dna_[4] = {'A', 'T', 'C', 'G'};
		bool is_valid(const std::string&) const;
};

void Handler::print() const {

    std::cout << "\nDNA: ";
    for (auto item : list_) std::cout << item;
    std::cout << "\n\n";

}

bool Handler::is_valid(const std::string& str) const {

	//Provjera da li je unos validan to jeste da li sadrzi charater iz niza
	for (int i = 0; i < str.size(); ++i) {

		unsigned short count = 0;
		for (int j = 0; j < 4; ++j) {
			if (str[i] != dna_[j]) ++count;
		}

		if (count == 4) return false; //ako je count == 4 onda character str[i] ne odgovara ni jednom characteru iz niza
	}

	return true;
}

void Handler::insert() {

		std::string dna_input;
		unsigned short pos;

		std::cout << "Position: ";
		std::cin >> pos;

		bool isValid;	
		do {

			std::cout << "Value: ";
			std::cin >> dna_input;
			isValid = is_valid(dna_input); //provjera da li cijeli uneseni string sadrzi sve charactere iz definisanog niza

			if (!isValid) std::cout << "Nevalidan unos. Pokusajte ponovo.\n"; 
		} while (!isValid);
		std::cout << std::endl;
		
		//dodavanje na kraj liste
		if (pos == list_.size()) {
			for (int i = 0; i < dna_input.size(); ++i) list_.push_back(dna_input[i]);
		} else {

			auto it = list_.begin();
			for (int i = 0; i < pos; ++i) ++it; //pomjeri iterator sa pocetka za pos lokacija
			for (int i = 0; i < dna_input.size(); ++i) list_.insert(it, dna_input[i]); // prije iteratora insertuje jedan po jedan karakter

		}	

}

void Handler::remove() {

		std::cout << "Position: ";
    unsigned short pos;
    std::cin >> pos;

    std::cout << "\nLength: ";
    unsigned short len;
    std::cin >> len;

}
