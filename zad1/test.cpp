#include <iostream>
#include "lista.hpp"


int main() {

List<int> lista;
lista.push_back(1);
lista.push_back(2);
lista.push_back(3);
lista.push_back(4);
lista.push_back(5);

lista.print();
lista.clear();
std::cout << std::endl;

lista.push_back(1);
lista.push_back(2);
lista.push_back(3);
lista.push_back(4);
lista.push_back(5);

std::cout << "Insert method:\n";
auto it = lista.begin();
it++;
it++;

lista.insert(it, 10);
lista.print();

std::cout << "Remove method: \n";
lista.remove(it);
lista.print();
	return 0;
}
