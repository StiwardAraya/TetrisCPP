#include "PiezaHold.hpp"

PiezaHold::PiezaHold() {}

bool PiezaHold::hayPiezaGuardada() const {
	return !pila.esVacia();
}

Pieza PiezaHold::obtenerGuardada() {
	return pila.desapilar();
}

void PiezaHold::guardar(const Pieza& pieza) {
	pila.apilar(pieza);
}

const Pieza& PiezaHold::verGuardada() const {
	return pila.verTope();
}
