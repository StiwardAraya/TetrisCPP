#include "EstadosManager.hpp"
#include "Estado.hpp"

EstadosManager::EstadosManager() {
}

EstadosManager::~EstadosManager() {
	while (!estados.esVacia()) {
		Estado* actual = estados.desapilar();
		delete actual;
	}
}

void EstadosManager::apilarEstado(Estado* nuevoEstado) {
	if(!estados.esVacia()) {
		estados.verTope()->alSalir();
	}
	
	estados.apilar(nuevoEstado);
	nuevoEstado->alEntrar();
}

void EstadosManager::desapilarEstado() {
	if (estados.esVacia()) {
		return;
	}
	
	Estado* actual = estados.desapilar();
	actual->alSalir();
	delete actual;
	
	if (!estados.esVacia()) {
		estados.verTope()->alEntrar();
	}
}

void EstadosManager::cambiarEstado(Estado* nuevoEstado) {
	if (!estados.esVacia()) {
		Estado* actual = estados.desapilar();
		actual->alSalir();
		delete actual;
	}
	
	estados.apilar(nuevoEstado);
	nuevoEstado->alEntrar();
}

void EstadosManager::manejarEntrada(InputManager& entradas) {
	if(!estados.esVacia()) {
		estados.verTope()->manejarEntrada(entradas);
	}
}

void EstadosManager::actualizar(float deltaTime) {
	if(!estados.esVacia()) {
		estados.verTope()->actualizar(deltaTime);
	}
}

void EstadosManager::dibujar(Graficador& graficador) {
	if(!estados.esVacia()) {
		estados.verTope()->dibujar(graficador);
	}
}

bool EstadosManager::estaVacio() const {
	return estados.esVacia();
}
