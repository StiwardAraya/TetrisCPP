/**
* @file PiezaHold.hpp
* @brief Esquema lógico de la pila de piezas en espera
* @author Stiward Araya Calderón
* @date Creado el 01/09/2026
*/
#pragma once

#include "TPila.hpp"		///< TPila<T>
#include "Pieza.hpp"		///< Pieza

/**
* @brief Sistema logico para la pila de piezas en espera.
*/
class PiezaHold {
private:
	TPila<Pieza> pila;		///< Pila de piezas en espera
	
public:
	
	/**
	* @brief Constructor base de la clase.
	*/
	PiezaHold();
	
	/**
	* @brief Revisa si hay piezas guardadas en la pila.
	* @return Valor booleano indicando si hay piezas guardadas o no.
	*/
	bool hayPiezaGuardada() const;
	
	/**
	* @brief Desapila la ultima pieza guardada.
	* @return Devuelve una instancia de pieza desde la pila
	*/
	Pieza obtenerGuardada();
	
	/**
	* @brief Apila una pieza en la pila.
	* @param pieza: Pieza a guardar en la pila.
	*/
	void guardar(const Pieza& pieza);
};
