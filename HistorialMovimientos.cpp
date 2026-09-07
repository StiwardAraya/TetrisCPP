#include "HistorialMovimientos.hpp"

std::vector<std::vector<bool>> HistorialMovimientos::capturarSnapshot(const Tablero& tablero) const {
	int alto = tablero.getAlto();
	int ancho = tablero.getAncho();
	
	std::vector<std::vector<bool>> snapshot(alto, std::vector<bool>(ancho, false));
	
	for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			snapshot[i][j] = tablero.obtenerCelda(i, j);
		}
	}
	
	return snapshot;
}

HistorialMovimientos::HistorialMovimientos() {}

void HistorialMovimientos::registrarMovimiento(TipoMovimiento tipo, Tablero& tablero, Pieza& piezaActual, int puntaje) {
	EstadoMovimiento estado;
	estado.tipo = tipo;
	estado.snapshotTablero = capturarSnapshot(tablero);
	estado.tipoPiezaActual = piezaActual.getTipoPieza();
	estado.filaPivote = piezaActual.getFilaPivote();
	estado.columnaPivote = piezaActual.getColumnaPivote();
	estado.orientacion = piezaActual.getOrientacion();
	estado.puntaje = puntaje;
	historial.insertar(estado);
}

EstadoMovimiento HistorialMovimientos::deshacer() {
	return historial.retroceder();
}

EstadoMovimiento HistorialMovimientos::rehacer() {
	return historial.avanzar();
}

bool HistorialMovimientos::puedeDeshacer() const {
	return historial.hayAnterior();
}

bool HistorialMovimientos::puedeRehacer() const {
	return historial.haySiguiente();
}

const EstadoMovimiento& HistorialMovimientos::verEstadoActual() const {
	return historial.verActual();
}

void HistorialMovimientos::reiniciarReproduccion() {
	return historial.reiniciarRecorrido();
}

bool HistorialMovimientos::haySiguienteEnReproduccion() const {
	return historial.haySiguiente();
}

EstadoMovimiento HistorialMovimientos::avanzarReproduccion() {
	return historial.avanzar();
}

bool HistorialMovimientos::estaVacio() const {
	return historial.esVacia();
}
