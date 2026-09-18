/**
* @file Ordenamiento.hpp
* @brief Namespace con los algoritmos de ordenamiento.
* @author Stiward Araya Calderón
* @date Creado el 17/09/2026
*/
#pragma once

#include <vector>				///< std::vector
#include "RegistroPuntaje.hpp"	///< RegistroPuntaje

/**
* @brief Contiene los algoritmos de ordenamiento para los 
* registros de puntaje de los jugadores.
*/
namespace Ordenamiento {
	
	/**
	* @brief ordena los puntajes con insertion sort.
	* @param puntajes: Lista de puntajes a ordenar.
	*/
	void ordenInsercion(std::vector<RegistroPuntaje>& puntajes);
	
	/**
	* @brief ordena los puntajes con quicksort.
	* @param puntajes: Lista de puntajes a ordenar.
	*/
	void ordenQuickSort(std::vector<RegistroPuntaje>& puntajes);
};
