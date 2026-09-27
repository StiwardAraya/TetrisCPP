#include "EstadoGameOver.hpp"
#include "InputManager.hpp"
#include "Graficador.hpp"
#include "EstadosManager.hpp"
#include "PuntajesManager.hpp"
#include "EstadoJugando.hpp"

const float EstadoGameOver::TIEMPO_ENTRE_PASOS = 0.5f;

EstadoGameOver::EstadoGameOver(EstadosManager& estadosManager, PuntajesManager& puntajesManager,
							   HistorialMovimientos& historial, const std::string& nombreJugador,
							   int puntajeFinal)
	: estadosManager(estadosManager),
	puntajesManager(puntajesManager),
	historial(historial),
	nombreJugador(nombreJugador),
	puntajeFinal(puntajeFinal),
	reproduccionPausada(false),
	tiempoAcumulado(0.0f) {
	
	if (puntajesManager.calificaParaTop10(puntajeFinal)) {
		puntajesManager.agregarPuntaje(nombreJugador, puntajeFinal);
	}
	
	if (!historial.estaVacio()) {
		historial.reiniciarReproduccion();
	}
}

void EstadoGameOver::avanzarUnPaso() {
	if (historial.haySiguienteEnReproduccion()) {
		historial.avanzarReproduccion();
	} else {
		reproduccionPausada = true; 
	}
}

void EstadoGameOver::reiniciarPartida() {
	estadosManager.desapilarEstado(); 
	estadosManager.desapilarEstado();
	estadosManager.apilarEstado(new EstadoJugando(estadosManager, nombreJugador, puntajesManager));
}

void EstadoGameOver::volverAlMenu() {
	estadosManager.desapilarEstado(); 
	estadosManager.desapilarEstado(); 
}

void EstadoGameOver::manejarEntrada(InputManager& entradas) {
	if (entradas.fuePresionado(AccionMotor::PAUSA)) {
		reproduccionPausada = !reproduccionPausada;
	}
	
	if (entradas.fuePresionado(AccionMotor::IZQUIERDA) && historial.puedeDeshacer()) {
		historial.deshacer();
		reproduccionPausada = true;
	}
	
	if (entradas.fuePresionado(AccionMotor::DERECHA) && historial.haySiguienteEnReproduccion()) {
		historial.avanzarReproduccion();
		reproduccionPausada = true;
	}
	
	if (entradas.fuePresionado(AccionMotor::CONFIRMAR)) {
		reiniciarPartida();
		return;
	}
	
	if (entradas.fuePresionado(AccionMotor::CANCELAR)) {
		volverAlMenu();
		return;
	}
}

void EstadoGameOver::actualizar(float deltaTime) {
	if (reproduccionPausada || historial.estaVacio()) {
		return;
	}
	
	tiempoAcumulado += deltaTime;
	
	if (tiempoAcumulado >= TIEMPO_ENTRE_PASOS) {
		tiempoAcumulado -= TIEMPO_ENTRE_PASOS;
		avanzarUnPaso();
	}
}

void EstadoGameOver::dibujar(Graficador& graficador) {
	const float TAMANO_CELDA = 15.0f;
	
	graficador.dibujarTexto("GAME OVER", 220, 20, 28, sf::Color::Red);
	graficador.dibujarTexto("Puntaje: " + std::to_string(puntajeFinal), 230, 60, 20, sf::Color::White);
	
	if (historial.estaVacio()) {
		graficador.dibujarTexto("Sin movimientos que reproducir.", 150, 150, 18, sf::Color::White);
		
	} else {
		const EstadoMovimiento& estadoActual = historial.verEstadoActual();
		
		for (size_t fila = 0; fila < estadoActual.snapshotTablero.size(); fila++) {
			for (size_t columna = 0; columna < estadoActual.snapshotTablero[fila].size(); columna++) {
				if (estadoActual.snapshotTablero[fila][columna]) {
					graficador.dibujarRectangulo(
												 static_cast<float>(columna) * TAMANO_CELDA,
												 100.0f + static_cast<float>(fila) * TAMANO_CELDA,
												 TAMANO_CELDA, TAMANO_CELDA, sf::Color::Cyan);
				}
			}
		}
	}
	
	graficador.dibujarTexto("Izq/Der: retroceder/avanzar   Pausa: play/pausa", 30, 450, 14, sf::Color::White);
	graficador.dibujarTexto("Confirmar: jugar de nuevo   Cancelar: menu", 30, 470, 14, sf::Color::White);
}
