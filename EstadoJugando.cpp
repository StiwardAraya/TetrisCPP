#include "EstadoJugando.hpp"
#include "InputManager.hpp"
#include "Graficador.hpp"
#include "EstadosManager.hpp"
#include "PuntajesManager.hpp"
#include "EstadoPausa.hpp"
#include "EstadoGameOver.hpp"
#include <string>

EstadoJugando::EstadoJugando(EstadosManager& estadosManager, const std::string& nombreJugador,
							 PuntajesManager& puntajesManager)
	: piezaActual(TipoPieza::I), // placeholder, se reemplaza abajo
	puntaje(0),
	multiplicadorPuntaje(1),
	tiempoAcumulado(0.0f),
	intervaloCaida(1.0f),
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
		hold.guardar(piezaActual);
		piezaActual = piezaGuardada;
	} else {
		hold.guardar(piezaActual);
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
	if (entradas.estaPresionado(AccionMotor::IZQUIERDA)) {
		intentarMover(0, -1);
	}
	if (entradas.estaPresionado(AccionMotor::DERECHA)) {
		intentarMover(0, 1);
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
	
	tiempoAcumulado += deltaTime;
	
	if (tiempoAcumulado >= intervaloCaida) {
		tiempoAcumulado -= intervaloCaida;
		
		if (!intentarMover(1, 0)) {
			fijarPiezaYContinuar();
		}
	}
}

void EstadoJugando::dibujar(Graficador& graficador) {
	const float TAMANO_CELDA = 20.0f;
	
	for (int fila = 0; fila < tablero.getAlto(); fila++) {
		for (int columna = 0; columna < tablero.getAncho(); columna++) {
			if (tablero.obtenerCelda(fila, columna)) {
				graficador.dibujarRectangulo(
											 columna * TAMANO_CELDA, fila * TAMANO_CELDA,
											 TAMANO_CELDA, TAMANO_CELDA, sf::Color::Cyan);
			}
		}
	}
	
	std::vector<std::pair<int, int>> celdasPieza = piezaActual.obtenerCeldasOcupadas();
	for (const auto& celda : celdasPieza) {
		graficador.dibujarRectangulo(
									 celda.second * TAMANO_CELDA, celda.first * TAMANO_CELDA,
									 TAMANO_CELDA, TAMANO_CELDA, sf::Color::Yellow);
	}
	
	graficador.dibujarTexto("Puntaje: " + std::to_string(puntaje), 220, 10, 18, sf::Color::White);
}
