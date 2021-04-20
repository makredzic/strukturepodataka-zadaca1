#include <iostream>
#include "lista.hpp"

int main ()  {

	//Default konstruktor - prazna lista
	List<int> lista;

	//inserteri

	List<int> lista2;
	lista2.push_back(1);
	lista2.push_front(0);
	lista2.push_back(2);
	lista2.push_back(3);
	lista2.push_back(4);
	lista2.push_back(5);

	auto it2 = lista2.begin();
	it2++;
	lista2.insert(it2, 100);
	lista2.print();
  return 0;

}
