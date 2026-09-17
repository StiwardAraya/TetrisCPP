/**
* @file Pieza.hpp
* @brief Esquema lógico de las piezas del juego
* @author Stiward Araya Calderón
* @date Creado el 27/08/2026
*/
#pragma once

#include <vector>			///< std::vector
#include <utility>			///< std::pair

/**
* @brief enum para el manejo de tipos de piezas, 7 tipos constantes
*/
enum class TipoPieza { I, O, T, S, Z, J, L };

/**
* @brief Objeto para representar de forma lógica las piezas del juego.
*/
class Pieza{
private:
	static const int FORMAS[7][4][4][2];			///< Tabla de posiciones precalculadas: [tipo][orientacion][bloque][fila,columna]
	TipoPieza tipo;									///< Indica que tipo de pieza es
	int filaPivote;									///< Punto de referencia fijo horizontal de la pieza
	int columnaPivote;								///< Punto de referencia fijo vertical de la pieza
	int orientacionActual;							///< Orientación actual de la pieza (0 a 3)
public:
	
	/**
	* @brief Constructor de la pieza.
	* @param tipoInicial: tipo de pieza que construirá la pieza instanciada.
	*/
	Pieza(TipoPieza tipoInicial);
	
	/**
	* @brief Decrementa columna pivote en 1
	*/
	void moverIzquierda();
	
	/**
	* @brief Incrementa columna pivote en 1
	*/
	void moverDerecha();
	
	/**
	* @brief Decrementa fila pivote en 1
	*/
	void moverAbajo();
	
	/**
	* @brief Avanza orientacion actual en 1
	* @pre Si se encuentra en 3 regresa a 0
	*/
	void rotar();
	
	/**
	* @brief Retorna una lista con las coordenadas de cada celda ocupada por la pieza.
	* @return Vector de pares, cada par representa la fila y columna de la celda ocupada por la pieza.
	*/
	std::vector<std::pair<int, int>> obtenerCeldasOcupadas() const;
	
	/**
	* @brief Calcula qué celdas ocuparía la pieza si estuviera en una posición/orientación hipotética.
	* @return Vector de pares, cada par representa la fila y columna que hipoteticamente ocuparia la pieza.
	*/
	std::vector<std::pair<int, int>> obtenerCeldasEn(int filaPivoteHipotetica, int columnaPivoteHipotetica, int orientacionHipotetica) const; 
	
	TipoPieza getTipoPieza() const;			///< GETTER TipoPieza
	int getFilaPivote() const; 				///< GETTER filaPivote
	int getColumnaPivote() const; 			///< GETTER columnaPivote
	int getOrientacion() const; 			///< GETTER orientacion
	
	/**
	* @brief Fuerza una pieza en una posicion especifica.
	* @param fila: posicion horizontal
	* @param columna: posicion vertical
	*/
	void establecerPosicion(int fila, int columna); 
	
	/**
	* @brief Necesario para saltar a la orientación necesaria, sin pasar
	* por todas las anteriores.
	* @param orientación, indica cual de las 4 orientaciones se le asignará
	* a la pieza.
	*/
	void establecerOrientacion(int orientacion);
};
