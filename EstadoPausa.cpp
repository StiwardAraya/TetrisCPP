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
	const float CENTRO_X = graficador.getAnchoLogico() / 2.0f;
	const std::string opciones[CANTIDAD_OPCIONES] = {"Reanudar", "Salir al menu"};

	graficador.dibujarTextoCentrado("PAUSA", CENTRO_X, 200.0f, 72, sf::Color::White);

	graficador.dibujarPanel(CENTRO_X - 190.0f, 320.0f, 380.0f, 150.0f);
	for (int i = 0; i < CANTIDAD_OPCIONES; i++) {
		bool seleccionada = (i == opcionSeleccionada);
		sf::Color color = seleccionada ? sf::Color(245, 215, 0) : sf::Color::White;
		std::string texto = seleccionada ? "> " + opciones[i] + " <" : opciones[i];
		graficador.dibujarTextoCentrado(texto, CENTRO_X, 350.0f + i * 55.0f, 32, color);
	}

	graficador.dibujarTextoCentrado("Flechas: elegir     E: confirmar", CENTRO_X, 620.0f, 18, sf::Color(150, 150, 190));
}
