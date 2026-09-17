/**
* @file Tablero.hpp
* @brief Esquema lógico del tablero del juego
* @author Stiward Araya Calderón
* @date Creado el 28/08/2026
*/
#pragma once

#include "TLista.hpp"				///< TLista<T>
#include "Pieza.hpp"				///< Pieza
#include <vector>					///< std::vector

/**
* @brief Objeto para representar de forma lógica el tablero del juego.
*/
class Tablero {
private:
	static const int ALTO = 20;		///< Alto del tablero
	static const int ANCHO = 10;	///< Ancho del tablero
	
	/**
	* @brief Representa cada fila del tablero, cada celda guarda si está ocupada o no.
	*/
	struct Fila {
		bool celdas[ANCHO];			///< Arreglo de booleanos representando cada fila
		
		/**
		* @brief Revisa si la fila está completa.
		* @return Valor booleano indicando si la fila está completa.
		*/
		bool estaCompleta() const;
		
		/**
		* @brief Pasa todos los valores de la fila a false.
		*/
		void vaciar();
	};
	
	TLista<Fila> filas;				///< Representación estructural del tablero
	
	/**
	* @brief Chequeo interno de limites, revisa que una posición no esté
	* fuera de los limites del tablero.
	*/
	bool posicionValida(int fila, int columna) const;
	
public:
	
	/**
	* @brief Constructor del tablero, llena la lista con nodos Fila, todos
	* con sus celdas en false.
	*/
	Tablero();
	
	/**
	* @brief Revisa dada una pieza y una posición hipotetica si existe colisión con otras piezas al mover
	* esa pieza a la posición hipotética.
	* @param pieza: instancia de la pieza a posicionar en el tablero.
	* @param filaHipotetica: Fila pivote relacionada a la pieza a posicionar.
	* @param columnaHipotetica: Columna pivote relacionada a la pieza a posicionar.
	* @param orientacionHipotetica: orientación en la que se posicionará la pieza.
	* @return Valor booleano indicando si existe una colisión tras el posicionamiento.
	*/
	bool hayColision(const Pieza& pieza, int filaHipotetica, int columnaHipotetica, int orientacionHipotetica) const;
	
	/**
	* @brief Graba en el tablero una pieza cuando ya no puede seguir bajando
	* @param pieza: Pieza a fijar en el tablero.
	*/
	void fijarPieza(const Pieza& pieza);
	
	/**
	* @brief Recorre las 20 filas y retorna los indices de las filas que están
	* completas.
	* @return Arreglo de enteros con los indices de las filas que están completas.
	*/
	std::vector<int> obtenerFilasCompletas() const;
	
	/**
	* @brief Elimina los nodos de la lista correspondientes a los indices de filas
	* completas e inserta al inicio de la lista nodos con filas vacías.
	* @param indices: arreglo de indices de las filas completas.
	*/
	void limpiarFilas(const std::vector<int>& indices);
	
	/**
	* @brief Devuelve el valor de una celda en específico.
	* @param fila: Indice de la fila correspondiente a la celda.
	* @param columna: Indice de la columna correspondiente a la celda.
	* @return Valor booleano indicando si la celda está ocupada o no
	*/
	bool obtenerCelda(int fila, int columna) const;
	
	/**
	* @brief Carga en el tablero un snaptshot almacenado.
	* @param snapshot: Estructura de un tablero anterior o almacenado en el historial.
	*/
	void cargarSnapshot(const std::vector<std::vector<bool>>& snapshot);
	
	int getAncho() const;		///< GETTER Ancho
	int getAlto() const;		///< GETTER Alto
};
