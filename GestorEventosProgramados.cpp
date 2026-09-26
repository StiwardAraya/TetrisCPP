#include "GestorEventosProgramados.hpp"

GestorEventosProgramados::GestorEventosProgramados()
	: tiempoTranscurrido(0.0f) {
}

void GestorEventosProgramados::programarEvento(float momento, std::function<void()> efecto) {
	eventos.programarEvento(efecto, momento);
}

void GestorEventosProgramados::actualizar(float deltaTime) {
	tiempoTranscurrido += deltaTime;
	
	while (!eventos.esVacia() && eventos.verMomentoProximo() <= tiempoTranscurrido) {
		std::function<void()> efecto = eventos.extraerEvento();
		efecto();
	}
}
