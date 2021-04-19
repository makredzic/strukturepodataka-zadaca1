#pragma once
#include <iostream>
#include <list>
#include <stdexcept>
#include <iterator>

struct Handler {
    void print() const;
    void insert() ;
    void remove() ;

    private:
    std::list<char> list_;
    const char dna_[4] = {'A', 'T', 'C', 'G'};
		bool is_valid(const std::string&) const;
		short is_valid(short) const;
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

short Handler::is_valid(short position) const {

		if (position < 0) throw std::out_of_range("Pozicija(pos) moze biti samo broj > 0\n");
		if (position > list_.size()) return list_.size(); //ako je korisnik prekoracio duzinu liste kao pos, samo stavi element na kraj
		
		return position;
}

void Handler::insert() {

		std::string dna_input;
		short pos;

		std::cout << "Position: ";
		std::cin >> pos;

		try {
			pos = is_valid(pos); // pos>list_size() , ovdje ce se resetovat na kraj liste da bi program mogao nastaviti i dodati nove elemente na kraj liste
		} catch (const std::out_of_range& e) {throw e;} //ponovo error bacimo da ga u mainu uhvati try/catch kod poziva insert() metoda 

		//Unos i provjera validnosti DNA sekvence
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

    short pos, len;

		std::cout << "Position: ";
    std::cin >> pos;

		try {
			pos = is_valid(pos); // pos>list_size() , ovdje ce se resetovat na kraj liste da bi program mogao nastaviti i dodati nove elemente na kraj liste
		} catch (const std::out_of_range& e) {throw e;} //ponovo error bacimo da ga u mainu uhvati try/catch kod poziva insert() metoda 

    std::cout << "\nLength: ";
    std::cin >> len;

		if (len <= 0) throw std::out_of_range("Mozete ukloniti minimalno jedan clan DNA niza.\n");

		auto start = list_.begin(); // iterator na pocetak liste
		std::advance(start, pos); // iterator se pomjeri sa pocetka za pos elemenata u listi na pos. poziciju 

		//ako je len > distance izmedju lokacije od koje se brise u listi i kraja liste onda ce duzina elemanata biti jednaka toj distanci
		//drugim rijecima, izbrisat ce se onda svi elementi do kraja liste od lokacije start
		if (len > std::distance(start, list_.end())) len = std::distance(start, list_.end());

		//end je dokle se brise u listi i to se prvo postavi na isto kao start i onda se pomjeri za len u listi
		auto end = start;
		std::advance(end, len);

		list_.erase(start, end);

}
