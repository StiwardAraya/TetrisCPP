#include <iostream>
#include "TCola.hpp"

int main(){
	TCola<int> colaPrueba;
	colaPrueba.encolar(0);
	colaPrueba.encolar(1);
	colaPrueba.encolar(2);
	colaPrueba.encolar(3);
	colaPrueba.encolar(4);
	colaPrueba.recorrer([](const int& x){
		std::cout << "[" << x << "] ";
	});
	std::cout << std::endl;
	int elementoExtraido = colaPrueba.desencolar();
	colaPrueba.recorrer([](const int& x){
		std::cout << "[" << x << "] ";
	});
	std::cout << std::endl;
	std::cout << "Extraido " << elementoExtraido << std::endl;
	int frenteCola = colaPrueba.verFrente();
	std::cout << "Frente actual " << frenteCola << std::endl;
	std::cout << "Tamaño de la cola: " << colaPrueba.obtenerTamanno() << std::endl;
	return 0;
}
