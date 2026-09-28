#include "EstadoGameOver.hpp"
#include "InputManager.hpp"
#include "Graficador.hpp"
#include "EstadosManager.hpp"
#include "PuntajesManager.hpp"
#include "EstadoJugando.hpp"
#include "Pieza.hpp"

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
	const float TAMANO_CELDA = 25.0f;
	const int COLUMNAS = 10;
	const int FILAS = 20;
	const float CENTRO_X = graficador.getAnchoLogico() / 2.0f;
	const float ORIGEN_X = CENTRO_X - (COLUMNAS * TAMANO_CELDA) / 2.0f;
	const float ORIGEN_Y = 110.0f;
	const float ANCHO_PANEL = 170.0f;
	const float X_PANEL = ORIGEN_X + COLUMNAS * TAMANO_CELDA + 30.0f;
	const sf::Color COLOR_ETIQUETA(150, 150, 190);

	graficador.dibujarTextoCentrado("GAME OVER", CENTRO_X, 20.0f, 48, sf::Color(235, 55, 55));
	graficador.dibujarTextoCentrado(nombreJugador + "  -  " + std::to_string(puntajeFinal) + " pts",
									CENTRO_X, 72.0f, 22, sf::Color::White);

	graficador.dibujarFondoTablero(ORIGEN_X, ORIGEN_Y, COLUMNAS, FILAS, TAMANO_CELDA);

	if (historial.estaVacio()) {
		graficador.dibujarTextoCentrado("Sin movimientos", CENTRO_X, ORIGEN_Y + 230.0f, 20, sf::Color::White);
		graficador.dibujarTextoCentrado("que reproducir.", CENTRO_X, ORIGEN_Y + 258.0f, 20, sf::Color::White);

	} else {
		const EstadoMovimiento& estadoActual = historial.verEstadoActual();

		for (size_t fila = 0; fila < estadoActual.snapshotTablero.size(); fila++) {
			for (size_t columna = 0; columna < estadoActual.snapshotTablero[fila].size(); columna++) {
				if (estadoActual.snapshotTablero[fila][columna]) {
					graficador.dibujarBloque(ORIGEN_X + static_cast<float>(columna) * TAMANO_CELDA,
											 ORIGEN_Y + static_cast<float>(fila) * TAMANO_CELDA,
											 TAMANO_CELDA, Graficador::colorBloqueFijado());
				}
			}
		}

		Pieza piezaEnEsePaso(estadoActual.tipoPiezaActual);
		std::vector<std::pair<int, int>> celdasPieza = piezaEnEsePaso.obtenerCeldasEn(
			estadoActual.filaPivote, estadoActual.columnaPivote, estadoActual.orientacion);
		sf::Color colorPieza = Graficador::colorDePieza(estadoActual.tipoPiezaActual);
		for (const auto& celda : celdasPieza) {
			graficador.dibujarBloque(ORIGEN_X + static_cast<float>(celda.second) * TAMANO_CELDA,
									 ORIGEN_Y + static_cast<float>(celda.first) * TAMANO_CELDA,
									 TAMANO_CELDA, colorPieza);
		}

		graficador.dibujarPanel(X_PANEL, ORIGEN_Y, ANCHO_PANEL, 110.0f, "REPLAY");
		graficador.dibujarTextoCentrado(reproduccionPausada ? "Pausado" : "Reproduciendo",
										X_PANEL + ANCHO_PANEL / 2.0f, ORIGEN_Y + 45.0f, 18,
										reproduccionPausada ? sf::Color(245, 215, 0) : sf::Color(60, 205, 75));
		graficador.dibujarTextoCentrado(std::to_string(estadoActual.puntaje) + " pts",
										X_PANEL + ANCHO_PANEL / 2.0f, ORIGEN_Y + 72.0f, 18, sf::Color::White);
	}

	const float Y_CONTROLES = ORIGEN_Y + FILAS * TAMANO_CELDA + 22.0f;
	graficador.dibujarTextoCentrado("<- / ->  retroceder / avanzar     P  play / pausa",
									CENTRO_X, Y_CONTROLES, 17, COLOR_ETIQUETA);
	graficador.dibujarTextoCentrado("E  jugar de nuevo     Esc  volver al menu",
									CENTRO_X, Y_CONTROLES + 28.0f, 17, COLOR_ETIQUETA);
}
