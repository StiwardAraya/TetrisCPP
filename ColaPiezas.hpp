/**
* @file ColaPiezas.hpp
* @brief Esquema lógico de la cola de piezas del juego
* @author Stiward Araya Calderón
* @date Creado el 29/08/2026
*/
#pragma once

#include "TCola.hpp"		///< TCola
#include "Pieza.hpp"		///< Pieza
#include <vector>			///< std::vector

/**
* @brief Sistema logico para la cola de piezas del juego que genera
* y gestiona la bolsa de 7 piezas.
*/
class ColaPiezas {
private:
	TCola<Pieza> cola;		///< Cola de piezas aleatorias
	
	/**
	* @brief Genera un orden aleatorio para los 7 tipos de piezas.
	* @return Arreglo de tipos de pieza, generado aleatoriamente.
	*/
	std::vector<TipoPieza> generarOrdenAleatorio() const;
	
	/**
	* @brief Genera una bolsa nueva y la encola.
	*/
	void generarBolsa();
	
	/**
	* @brief Si la cantidad de piezas disponibles baja de cierto umbral,
	* genera una bolsa nueva para que el jugador siempre tenga piezas
	* futuras que ver y jugar.
	*/
	void asegurarSuficientesPiezas();
	
public:
	
	/**
	* @brief Constructor de la Cola de Piezas, inicializa la clase
	*/
	ColaPiezas();
	
	/**
	* @brief Desencola y retorna la pieza al frente de la cola.
	*/
	Pieza obtenerSiguiente();
	
	/**
	* @brief Muestra las proximas 3 piezas en la cola sin desencolarlas.
	* @param cantidad: Cantidad de piezas que se requieran ver.
	* @return Arreglo con las piezas a mostrar.
	*/
	std::vector<Pieza> verProximas(int cantidad) const;
	
	/**
	* @brief Verifica si la cola está vacía.
	* @return Valor booleano indicando si la cola está vacía
	*/
	bool estaVacia() const;
};
