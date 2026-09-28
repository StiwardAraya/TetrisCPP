#include "Tablero.hpp"
#include <utility>

bool Tablero::Fila::estaCompleta() const {
	for(int i = 0; i < ANCHO; i++){
		if(!celdas[i]){
			return false;
		}
	}
	return true;
}

void Tablero::Fila::vaciar() {
	for(int i = 0; i < ANCHO; i++){
		celdas[i] = false;
	}
}

Tablero::Tablero() {
	for(int i = 0; i < ALTO; i++){
		Fila filaVacia;
		filaVacia.vaciar();
		filas.insertar(filaVacia);
	}
}

bool Tablero::posicionValida(int fila, int columna) const {
	return fila >= 0 && fila < ALTO && columna >= 0 && columna < ANCHO;
}

bool Tablero::hayColision(const Pieza& pieza, int filaHipotetica, int columnaHipotetica, int orientacionHipotetica) const {
	std::vector<std::pair<int, int>> celdasHipoteticas = pieza.obtenerCeldasEn(filaHipotetica, columnaHipotetica, orientacionHipotetica);
	
	for(const auto& celda : celdasHipoteticas){
		int fila = celda.first;
		int columna = celda.second;
		
		if(!posicionValida(fila, columna)){
			return true;
		}
		
		if(obtenerCelda(fila, columna)){
			return true;
		}
	}
	
	return false;
}

void Tablero::fijarPieza(const Pieza& pieza) {
	std::vector<std::pair<int, int>> celdasOcupadas = pieza.obtenerCeldasOcupadas();
	
	for(const auto& celda : celdasOcupadas){
		int fila = celda.first;
		int columna = celda.second;
		
		Fila& filaObjetivo = filas.obtener(fila);
		filaObjetivo.celdas[columna] = true;
	}
}

std::vector<int> Tablero::obtenerFilasCompletas() const {
	std::vector<int> indices;
	
	for(int i = 0; i < ALTO; i++) {
		const Fila& filaActual = filas.obtener(i);
		if(filaActual.estaCompleta()) {
			indices.push_back(i);
		}
	}
	
	return indices;
}

void Tablero::limpiarFilas(const std::vector<int>& indices) {
	std::vector<int> indicesDescendente = indices;
	
	for(size_t i = 0; i < indicesDescendente.size(); i++) {
		for(size_t j = i+1; j < indicesDescendente.size(); j++) {
			if(indicesDescendente[j] > indicesDescendente[i]){
				std::swap(indicesDescendente[j], indicesDescendente[i]);
			}
		}
	}
	
	for(int indice : indicesDescendente) {
		filas.eliminar(indice);
	}
	
	int cantidadEliminadas = static_cast<int>(indicesDescendente.size());
	for(int i = 0; i < cantidadEliminadas; i++){
		Fila filaVacia;
		filaVacia.vaciar();
		filas.insertar(filaVacia);
	}
}

bool Tablero::obtenerCelda(int fila, int columna) const{
	const Fila& filaObjetivo = filas.obtener(fila);
	return filaObjetivo.celdas[columna];
}

void Tablero::cargarSnapshot(const std::vector<std::vector<bool>>& snapshot) {
	for (int fila = 0; fila < ALTO; fila++) {
		Fila& filaObjetivo = filas.obtener(fila);
		for (int columna = 0; columna < ANCHO; columna++) {
			filaObjetivo.celdas[columna] = snapshot[fila][columna];
		}
	}
}

int Tablero::getAncho() const {
	return ANCHO;
}
int Tablero::getAlto() const {
	return ALTO;
}













