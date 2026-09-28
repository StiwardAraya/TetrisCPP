#include "Aplicacion.hpp"
#include "EstadoMenu.hpp"
#include <SFML/System.hpp>

const float Aplicacion::PASO_FIJO = 1.0f / 60.0f;

Aplicacion::Aplicacion(unsigned int ancho, unsigned int alto, const std::string& titulo,
					   const std::string& rutaArchivoPuntajes)
	: graficador(ancho, alto, titulo) {
	
	estadosManager.apilarEstado(new EstadoMenu(estadosManager, rutaArchivoPuntajes));
}

void Aplicacion::ejecutar() {
	sf::Clock reloj;
	float tiempoAcumulado = 0.0f;
	
	while (graficador.estaAbierta() && !estadosManager.estaVacio()) {
		float deltaTime = reloj.restart().asSeconds();
		tiempoAcumulado += deltaTime;
		
		entradas.actualizar(graficador.obtenerVentana());
		if (entradas.seSolicitoCerrar()) {
			graficador.obtenerVentana().close();
		}
		
		estadosManager.manejarEntrada(entradas);
		
		while (tiempoAcumulado >= PASO_FIJO) {
			estadosManager.actualizar(PASO_FIJO);
			tiempoAcumulado -= PASO_FIJO;
		}
		
		graficador.iniciarFrame();
		estadosManager.dibujar(graficador);
		graficador.finalizarFrame();
	}
}
