#include <iostream>
#include "lista.hpp"

int main ()  {

  List<int> lista1;
  List<int> lista2;

  lista1.push_back(1);
  lista1.push_back(1);
  lista1.push_back(1);
  lista1.push_back(1);
  lista1.push_back(1);

  lista2.push_back(2);

  lista1.print();
  lista2.print();

  std::cout << std::endl;

  lista2 = std::move(lista1);
  lista2.push_back(6);
  lista1.push_back(9);
  
  lista2.print();
  lista1.print();

  std::cout << "TEST PUSH FRONT I BACK" << std::endl;
  lista1.clear();
  lista1.push_front(3);
  lista1.push_front(2);
  lista1.push_back(4);
  lista1.push_front(1);
	lista1.push_back(5);
  lista1.print();
	
	//lista1 = <1, 2, 3, 4, 5>
	auto it = lista1.begin();
	it++;
	it++;

	lista1.insert(it, 20); //izmedju 2 i 3 treba 420 bit
	// lista1.print();

  return 0;
}
