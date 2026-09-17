#include "RegistroPuntaje.hpp"

RegistroPuntaje::RegistroPuntaje(const std::string& jugador, int puntaje) {
	this->jugador = jugador;
	this->puntaje = puntaje;
}

const std::string& RegistroPuntaje::getNombre() const {
	return jugador;
}

int RegistroPuntaje::getPuntaje() const {
	return puntaje;
}
