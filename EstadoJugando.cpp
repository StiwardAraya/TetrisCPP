#include "EstadoJugando.hpp"
#include "InputManager.hpp"
#include "Graficador.hpp"
#include "EstadosManager.hpp"
#include "PuntajesManager.hpp"
#include "EstadoPausa.hpp"
#include "EstadoGameOver.hpp"
#include <string>

const float EstadoJugando::RETRASO_INICIAL_DAS = 0.20f;
const float EstadoJugando::INTERVALO_REPETICION_DAS = 0.06f;

EstadoJugando::EstadoJugando(EstadosManager& estadosManager, const std::string& nombreJugador,
							 PuntajesManager& puntajesManager)
	: piezaActual(TipoPieza::I),
	puntaje(0),
	multiplicadorPuntaje(1),
	tiempoAcumulado(0.0f),
	intervaloCaida(1.0f),
	direccionHorizontalActiva(0),
	tiempoSostenidoHorizontal(0.0f),
	tiempoAcumuladoRepeticionH(0.0f),
	nombreJugador(nombreJugador),
	estadosManager(estadosManager),
	puntajesManager(puntajesManager) {
	
	piezaActual = colaPiezas.obtenerSiguiente();
	
	gestorEventos.programarEvento(20.0f, [this]() {
		if (intervaloCaida > 0.15f) {
			intervaloCaida *= 0.9f;
		}
		gestorEventos.programarEvento(gestorEventos.tiempoActual() + 20.0f, [this]() {
			if (intervaloCaida > 0.15f) {
				intervaloCaida *= 0.9f;
			}
		});
	});
	
	gestorEventos.programarEvento(15.0f, [this]() {
		multiplicadorPuntaje = 2;
	});
	gestorEventos.programarEvento(25.0f, [this]() {
		multiplicadorPuntaje = 1;
	});
	
	gestorEventos.programarEvento(45.0f, [this]() {
		if (tablero.getAlto() > 0) {
			std::vector<int> indiceInferior = { tablero.getAlto() - 1 };
			tablero.limpiarFilas(indiceInferior);
		}
	});
	
	verificarFinDeJuego();
}

bool EstadoJugando::intentarMover(int deltaFila, int deltaColumna) {
	int filaHipotetica = piezaActual.getFilaPivote() + deltaFila;
	int columnaHipotetica = piezaActual.getColumnaPivote() + deltaColumna;
	int orientacionActual = piezaActual.getOrientacion();
	
	if (tablero.hayColision(piezaActual, filaHipotetica, columnaHipotetica, orientacionActual)) {
		return false;
	}
	
	if (deltaColumna < 0) {
		piezaActual.moverIzquierda();
	} else if (deltaColumna > 0) {
		piezaActual.moverDerecha();
	}
	
	if (deltaFila > 0) {
		piezaActual.moverAbajo();
	}
	
	TipoMovimiento tipo;
	if (deltaColumna < 0) {
		tipo = TipoMovimiento::MOVER_IZQUIERDA;
	} else if (deltaColumna > 0) {
		tipo = TipoMovimiento::MOVER_DERECHA;
	} else {
		tipo = TipoMovimiento::BAJAR;
	}
	
	historial.registrarMovimiento(tipo, tablero, piezaActual, puntaje);
	
	return true;
}

bool EstadoJugando::intentarRotar() {
	int orientacionHipotetica = (piezaActual.getOrientacion() + 1) % 4;
	
	if (tablero.hayColision(piezaActual, piezaActual.getFilaPivote(),
							piezaActual.getColumnaPivote(), orientacionHipotetica)) {
		return false;
	}
	
	piezaActual.rotar();
	historial.registrarMovimiento(TipoMovimiento::ROTAR, tablero, piezaActual, puntaje);
	
	return true;
}

void EstadoJugando::fijarPiezaYContinuar() {
	tablero.fijarPieza(piezaActual);
	historial.registrarMovimiento(TipoMovimiento::COLOCAR, tablero, piezaActual, puntaje);
	
	limpiarLineasCompletas();
	generarNuevaPieza();
}

void EstadoJugando::limpiarLineasCompletas() {
	std::vector<int> filasCompletas = tablero.obtenerFilasCompletas();
	
	if (!filasCompletas.empty()) {
		puntaje += calcularPuntaje(static_cast<int>(filasCompletas.size()));
		tablero.limpiarFilas(filasCompletas);
	}
}

int EstadoJugando::calcularPuntaje(int cantidadLineas) const {
	const int PUNTOS_POR_LINEA = 100;
	int puntosBase = 0;
	
	switch (cantidadLineas) {
	case 1: puntosBase = PUNTOS_POR_LINEA; break;
	case 2: puntosBase = PUNTOS_POR_LINEA * 3; break;
	case 3: puntosBase = PUNTOS_POR_LINEA * 5; break;
	case 4: puntosBase = PUNTOS_POR_LINEA * 8; break;
	default: puntosBase = 0; break;
	}
	
	return puntosBase * multiplicadorPuntaje;
}

void EstadoJugando::generarNuevaPieza() {
	piezaActual = colaPiezas.obtenerSiguiente();
	verificarFinDeJuego();
}

void EstadoJugando::ejecutarHold() {
	if (hold.hayPiezaGuardada()) {
		Pieza piezaGuardada = hold.obtenerGuardada();
		hold.guardar(Pieza(piezaActual.getTipoPieza()));
		piezaActual = piezaGuardada;
	} else {
		hold.guardar(Pieza(piezaActual.getTipoPieza()));
		piezaActual = colaPiezas.obtenerSiguiente();
	}
	
	historial.registrarMovimiento(TipoMovimiento::HOLD, tablero, piezaActual, puntaje);
}

void EstadoJugando::aplicarEstadoDelHistorial(const EstadoMovimiento& estado) {
	tablero.cargarSnapshot(estado.snapshotTablero);
	
	piezaActual = Pieza(estado.tipoPiezaActual);
	piezaActual.establecerPosicion(estado.filaPivote, estado.columnaPivote);
	piezaActual.establecerOrientacion(estado.orientacion);
	
	puntaje = estado.puntaje;
}

void EstadoJugando::verificarFinDeJuego() {
	bool hayColisionAlAparecer = tablero.hayColision(
													 piezaActual, piezaActual.getFilaPivote(),
													 piezaActual.getColumnaPivote(), piezaActual.getOrientacion());
	
	if (hayColisionAlAparecer) {
		estadosManager.apilarEstado(
									new EstadoGameOver(estadosManager, puntajesManager, historial, nombreJugador, puntaje));
	}
}

void EstadoJugando::manejarEntrada(InputManager& entradas) {
	if (entradas.fuePresionado(AccionMotor::IZQUIERDA)) {
		intentarMover(0, -1);
		direccionHorizontalActiva = -1;
		tiempoSostenidoHorizontal = 0.0f;
		tiempoAcumuladoRepeticionH = 0.0f;
	} else if (entradas.fuePresionado(AccionMotor::DERECHA)) {
		intentarMover(0, 1);
		direccionHorizontalActiva = 1;
		tiempoSostenidoHorizontal = 0.0f;
		tiempoAcumuladoRepeticionH = 0.0f;
	} else if (!entradas.estaPresionado(AccionMotor::IZQUIERDA) &&
			   !entradas.estaPresionado(AccionMotor::DERECHA)) {
		direccionHorizontalActiva = 0;
	}
	if (entradas.estaPresionado(AccionMotor::ABAJO)) {
		intentarMover(1, 0);
	}
	
	if (entradas.fuePresionado(AccionMotor::ARRIBA)) {
		intentarRotar();
	}
	
	if (entradas.fuePresionado(AccionMotor::HOLD)) {
		ejecutarHold();
	}
	
	if (entradas.fuePresionado(AccionMotor::DESHACER) && historial.puedeDeshacer()) {
		aplicarEstadoDelHistorial(historial.deshacer());
	}
	
	if (entradas.fuePresionado(AccionMotor::REHACER) && historial.puedeRehacer()) {
		aplicarEstadoDelHistorial(historial.rehacer());
	}
	
	if (entradas.fuePresionado(AccionMotor::PAUSA)) {
		estadosManager.apilarEstado(new EstadoPausa(estadosManager));
	}
}

void EstadoJugando::actualizar(float deltaTime) {
	gestorEventos.actualizar(deltaTime);
	
	if (direccionHorizontalActiva != 0) {
		tiempoSostenidoHorizontal += deltaTime;
		if (tiempoSostenidoHorizontal >= RETRASO_INICIAL_DAS) {
			tiempoAcumuladoRepeticionH += deltaTime;
			while (tiempoAcumuladoRepeticionH >= INTERVALO_REPETICION_DAS) {
				tiempoAcumuladoRepeticionH -= INTERVALO_REPETICION_DAS;
				intentarMover(0, direccionHorizontalActiva);
			}
		}
	}
	
	tiempoAcumulado += deltaTime;
	
	if (tiempoAcumulado >= intervaloCaida) {
		tiempoAcumulado -= intervaloCaida;
		
		if (!intentarMover(1, 0)) {
			fijarPiezaYContinuar();
		}
	}
}

void EstadoJugando::dibujar(Graficador& graficador) {
	const float TAMANO_CELDA = 30.0f;
	const float TAMANO_CELDA_PREVIA = 22.0f;
	const float ANCHO_TABLERO_PX = tablero.getAncho() * TAMANO_CELDA;
	const float ALTO_TABLERO_PX = tablero.getAlto() * TAMANO_CELDA;
	const float ORIGEN_X = (graficador.getAnchoLogico() - ANCHO_TABLERO_PX) / 2.0f;
	const float ORIGEN_Y = (graficador.getAltoLogico() - ALTO_TABLERO_PX) / 2.0f;
	const float SEPARACION = 30.0f;
	const float ANCHO_PANEL = 170.0f;
	const float X_PANEL_IZQ = ORIGEN_X - SEPARACION - ANCHO_PANEL;
	const float X_PANEL_DER = ORIGEN_X + ANCHO_TABLERO_PX + SEPARACION;
	const sf::Color COLOR_ETIQUETA(150, 150, 190);

	// Tablero
	graficador.dibujarFondoTablero(ORIGEN_X, ORIGEN_Y, tablero.getAncho(), tablero.getAlto(), TAMANO_CELDA);

	for (int fila = 0; fila < tablero.getAlto(); fila++) {
		for (int columna = 0; columna < tablero.getAncho(); columna++) {
			if (tablero.obtenerCelda(fila, columna)) {
				graficador.dibujarBloque(ORIGEN_X + columna * TAMANO_CELDA, ORIGEN_Y + fila * TAMANO_CELDA,
										 TAMANO_CELDA, Graficador::colorBloqueFijado());
			}
		}
	}

	sf::Color colorPieza = Graficador::colorDePieza(piezaActual.getTipoPieza());
	std::vector<std::pair<int, int>> celdasPieza = piezaActual.obtenerCeldasOcupadas();
	for (const auto& celda : celdasPieza) {
		graficador.dibujarBloque(ORIGEN_X + celda.second * TAMANO_CELDA, ORIGEN_Y + celda.first * TAMANO_CELDA,
								 TAMANO_CELDA, colorPieza);
	}

	// Panel izquierdo: hold, jugador y controles
	const float ALTO_PANEL_HOLD = 140.0f;
	graficador.dibujarPanel(X_PANEL_IZQ, ORIGEN_Y, ANCHO_PANEL, ALTO_PANEL_HOLD, "HOLD");
	if (hold.hayPiezaGuardada()) {
		graficador.dibujarVistaPreviaPieza(hold.verGuardada().getTipoPieza(),
										   X_PANEL_IZQ + ANCHO_PANEL / 2.0f, ORIGEN_Y + 85.0f, TAMANO_CELDA_PREVIA);
	}

	const float Y_PANEL_JUGADOR = ORIGEN_Y + ALTO_PANEL_HOLD + SEPARACION;
	graficador.dibujarPanel(X_PANEL_IZQ, Y_PANEL_JUGADOR, ANCHO_PANEL, 80.0f, "JUGADOR");
	graficador.dibujarTextoCentrado(nombreJugador, X_PANEL_IZQ + ANCHO_PANEL / 2.0f,
									Y_PANEL_JUGADOR + 42.0f, 20, sf::Color::White);

	const float Y_PANEL_CONTROLES = Y_PANEL_JUGADOR + 80.0f + SEPARACION;
	const int CANTIDAD_CONTROLES = 7;
	const std::string CONTROLES[CANTIDAD_CONTROLES] = {
		"<- ->  Mover", "Arriba Rotar", "Abajo  Bajar", "C      Hold", "Z      Deshacer", "X      Rehacer", "P      Pausa"
	};
	graficador.dibujarPanel(X_PANEL_IZQ, Y_PANEL_CONTROLES, ANCHO_PANEL, 230.0f, "CONTROLES");
	for (int i = 0; i < CANTIDAD_CONTROLES; i++) {
		graficador.dibujarTexto(CONTROLES[i], X_PANEL_IZQ + 14.0f, Y_PANEL_CONTROLES + 45.0f + i * 25.0f,
								16, COLOR_ETIQUETA);
	}

	// Panel derecho: siguientes piezas y puntaje
	const int CANTIDAD_PROXIMAS = 3;
	const float ALTO_PANEL_SIGUIENTES = 330.0f;
	graficador.dibujarPanel(X_PANEL_DER, ORIGEN_Y, ANCHO_PANEL, ALTO_PANEL_SIGUIENTES, "SIGUIENTES");
	std::vector<Pieza> proximas = colaPiezas.verProximas(CANTIDAD_PROXIMAS);
	for (size_t i = 0; i < proximas.size(); i++) {
		graficador.dibujarVistaPreviaPieza(proximas[i].getTipoPieza(), X_PANEL_DER + ANCHO_PANEL / 2.0f,
										   ORIGEN_Y + 95.0f + static_cast<float>(i) * 90.0f, TAMANO_CELDA_PREVIA);
	}

	const float Y_PANEL_PUNTAJE = ORIGEN_Y + ALTO_PANEL_SIGUIENTES + SEPARACION;
	graficador.dibujarPanel(X_PANEL_DER, Y_PANEL_PUNTAJE, ANCHO_PANEL, 110.0f, "PUNTAJE");
	graficador.dibujarTextoCentrado(std::to_string(puntaje), X_PANEL_DER + ANCHO_PANEL / 2.0f,
									Y_PANEL_PUNTAJE + 42.0f, 32, sf::Color::White);
	if (multiplicadorPuntaje > 1) {
		graficador.dibujarTextoCentrado("PUNTOS x" + std::to_string(multiplicadorPuntaje),
										X_PANEL_DER + ANCHO_PANEL / 2.0f, Y_PANEL_PUNTAJE + 82.0f,
										16, sf::Color(245, 215, 0));
	}
}
