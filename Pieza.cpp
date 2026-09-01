#include "Pieza.hpp"

const int Pieza::FORMAS[7][4][4][2] = {
	{
		// Pieza I
		{{0,-1},{0,0},{0,1},{0,2}},
		{{-1,0},{0,0},{1,0},{2,0}},
		{{0,-1},{0,0},{0,1},{0,2}},
		{{-1,0},{0,0},{1,0},{2,0}},
	},
	{
		// Pieza O
		{{0,0},{0,1},{1,0},{1,1}},
		{{0,0},{0,1},{1,0},{1,1}},
		{{0,0},{0,1},{1,0},{1,1}},
		{{0,0},{0,1},{1,0},{1,1}}
	},
	{
		// Pieza T
		{{0,-1},{0,0},{0,1},{1,0}},
		{{-1,0},{0,0},{1,0},{0,1}},
		{{0,-1},{0,0},{0,1},{-1,0}},
		{{-1,0},{0,0},{1,0},{0,-1}},
	},
	{
		// Pieza S
		{{0,0},{0,1},{1,-1},{1,0}},
		{{-1,0},{0,0},{0,1},{1,1}},
		{{0,0},{0,1},{1,-1},{1,0}},
		{{-1,0},{0,0},{0,1},{1,1}}
	},
	{
		// Pieza Z
		{{0,-1},{0,0},{1,0},{1,1}},
		{{-1,1},{0,0},{0,1},{1,0}},
		{{0,-1},{0,0},{1,0},{1,1}},
		{{-1,1},{0,0},{0,1},{1,0}}
	},
	{
		// Pieza J
		{{-1,-1},{0,-1},{0,0},{0,1}},
		{{-1,0},{-1,1},{0,0},{1,0}},
		{{0,-1},{0,0},{0,1},{1,1}},
		{{-1,0},{0,0},{1,0},{1,-1}}
	},
	{
		// Pieza L
		{{-1,1},{0,-1},{0,0},{0,1}},
		{{-1,0},{0,0},{1,0},{1,1}},
		{{0,-1},{0,0},{0,1},{1,-1}},
		{{-1,-1},{-1,0},{0,0},{1,0}}
	}
};

Pieza::Pieza(TipoPieza tipoInicial) : tipo(tipoInicial), filaPivote(0), columnaPivote(4), orientacionActual(0){}

void Pieza::moverIzquierda() {
	columnaPivote--;
}

void Pieza::moverDerecha() {
	columnaPivote++;
}

void Pieza::moverAbajo() {
	filaPivote++;
}

void Pieza::rotar() {
	if(orientacionActual == 3){
		orientacionActual = 0;
		return;
	}
	
	orientacionActual++;
}

std::vector<std::pair<int, int>> Pieza::obtenerCeldasOcupadas() const {
	return obtenerCeldasEn(filaPivote, columnaPivote, orientacionActual);
}

std::vector<std::pair<int, int>> Pieza::obtenerCeldasEn(int filaPivoteHipotetica, int columnaPivoteHipotetica, int orientacionHipotetica) const {
	std::vector<std::pair<int, int>> celdas;
	int indiceTipo = static_cast<int>(tipo);
	
	for(int i = 0; i < 4; i++){
		int desplazamientoFila = FORMAS[indiceTipo][orientacionHipotetica][i][0];
		int desplazamientoColumna = FORMAS[indiceTipo][orientacionHipotetica][i][1];
		
		int filaAbsoluta = filaPivoteHipotetica + desplazamientoFila;
		int columnaAbsoluta = columnaPivoteHipotetica + desplazamientoColumna;
		
		celdas.push_back({filaAbsoluta, columnaAbsoluta});
	}
	
	return celdas;
}

TipoPieza Pieza::getTipoPieza() const {
	return this->tipo;
}

int Pieza::getFilaPivote() const {
	return this->filaPivote;
}

int Pieza::getColumnaPivote() const {
	return this->columnaPivote;
}

int Pieza::getOrientacion() const {
	return this->orientacionActual;
}

void Pieza::establecerPosicion(int fila, int columna){
	filaPivote = fila;
	columnaPivote = columna;
}
















