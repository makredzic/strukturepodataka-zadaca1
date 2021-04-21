#include <iostream>
#include "lista.hpp"

int main ()  {

	//Default konstruktor - prazna lista
	List<int> lista;

	//inserteri i iterator
	lista.push_back(3);
	lista.push_back(4);
	lista.push_front(1);

	auto it = lista.begin();
	lista.insert(it++, 0);
	lista.insert(it, 2);

	lista.print(); //print treba biti 0-4


	std::cout << "Copy lista: ";

	auto lista_cpy{lista}; // copy konstruktor
	lista_cpy.print();

	lista.clear(); // brisanje prve liste
	lista = std::move(lista_cpy); //move operator iz copy liste nazad u og

	std::cout << "Copy lista nakon move (treba biti prazna): ";
	lista_cpy.print();
	std::cout << "Originalna lista nakon move: ";
	lista.print();


	for (auto iter = lista.begin(); iter != lista.end(); ++iter) {
		std::cout << *iter << std::endl;
	}


	auto iter = lista.end(); --iter; //iterator na kraj pa onda pomjeren na zadnji element
	while(iter != lista.begin()) {
		std::cout << *iter << std::endl;
		--iter;
	}


	//Testiranje implementacije bidirekcionog iteratora
	// Foreach petlja jedino radi ako je potpuno ispravna implementacija
	// odgovarajuceg iteratora zajedno sa operatorima ==, !=
	// u ovom slucaju usput testiramo i da li su iteratori pravilno 
	// implementirani s obzirom da imaju 2 pointera, trenutni(p_) i prethodni(pPrev_)
	std::cout << "For loop print: ";
	for (auto& el : lista) {
		std::cout << el << " ";
	}
	std::cout << std::endl;

  return 0;
}
