#include "EstadoPausa.hpp"
#include "InputManager.hpp"
#include "Graficador.hpp"
#include "EstadosManager.hpp"

EstadoPausa::EstadoPausa(EstadosManager& estadosManager)
	: estadosManager(estadosManager), opcionSeleccionada(0) {
}

void EstadoPausa::manejarEntrada(InputManager& entradas) {
	if (entradas.fuePresionado(AccionMotor::ABAJO) || entradas.fuePresionado(AccionMotor::ARRIBA)) {
		opcionSeleccionada = (opcionSeleccionada + 1) % CANTIDAD_OPCIONES;
	}
	
	if (entradas.fuePresionado(AccionMotor::CONFIRMAR)) {
		if (opcionSeleccionada == 0) {
			estadosManager.desapilarEstado();
			
		} else {
			estadosManager.desapilarEstado();
			estadosManager.desapilarEstado();
		}
	}
}

void EstadoPausa::actualizar(float deltaTime) {
}

void EstadoPausa::dibujar(Graficador& graficador) {
	graficador.dibujarTexto("PAUSA", 250, 100, 32, sf::Color::White);
	
	sf::Color colorReanudar = (opcionSeleccionada == 0) ? sf::Color::Yellow : sf::Color::White;
	sf::Color colorSalir = (opcionSeleccionada == 1) ? sf::Color::Yellow : sf::Color::White;
	
	graficador.dibujarTexto("Reanudar", 240, 180, 22, colorReanudar);
	graficador.dibujarTexto("Salir al menu", 240, 220, 22, colorSalir);
}
