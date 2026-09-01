#include "ColaPiezas.hpp"
#include <random>

/**
* @brief Generador de numeros aleatorios de instanciación
* única para toda la clase.
*/
namespace {
	std::mt19937& generadorAleatorio() {
		static std::mt19937 generador(std::random_device{}());
		return generador;
	}
};

std::vector<TipoPieza> ColaPiezas::generarOrdenAleatorio() const {
	std::vector<TipoPieza> tipos = {
		TipoPieza::I, TipoPieza::O, TipoPieza::T,
		TipoPieza::S, TipoPieza::Z, TipoPieza::J, TipoPieza::L
	};
	
	for(int i = static_cast<int>(tipos.size()) - 1; i > 0; i--){
		std::uniform_int_distribution<int> distribucion(0, i);
		int j = distribucion(generadorAleatorio());
		std::swap(tipos[i], tipos[j]);
	}
	
	return tipos;
}

void ColaPiezas::generarBolsa() {
	std::vector<TipoPieza> orden = generarOrdenAleatorio();
	
	for(TipoPieza tipo : orden) {
		cola.encolar(Pieza(tipo));
	}
}

void ColaPiezas::asegurarSuficientesPiezas() {
	const int UMBRAL_MINIMO = 7;
	
	if(cola.obtenerTamanno() < UMBRAL_MINIMO){
		generarBolsa();
	}
}

ColaPiezas::ColaPiezas() {
	generarBolsa();
	generarBolsa();
}

Pieza ColaPiezas::obtenerSiguiente() {
	Pieza siguiente = cola.desencolar();
	asegurarSuficientesPiezas();
	return siguiente;
}

std::vector<Pieza> ColaPiezas::verProximas(int cantidad) const {
	std::vector<Pieza> resultado;
	
	cola.recorrer([&resultado, cantidad](const Pieza& pieza){
		if(static_cast<int>(resultado.size()) < cantidad){
			resultado.push_back(pieza);
		}
	});
	
	return resultado;
}

bool ColaPiezas::estaVacia() const {
	return cola.esVacia();
}
