/**
* @file TCola.hpp
* @brief Implementación de una estructura FIFO para el proyecto
* @author Stiward Araya Calderón
* @date creado el 15/08/2026
*/
#pragma once

/**
* @brief Estructura de datos genérica tipo FIFO.
* @tparam T tipo de dato genérico que la cola va a almacenar.
*/
template <typename T> 
class TCola{
private:
	
	/**
	* @brief Nodo interno de la cola, contiene un dato y un puntero al nodo siguiente.
	*/
	struct Nodo{
		T obj;				///< Objeto genérico.
		Nodo* siguiente;	///< Puntero al nodo siguiente de la cola.
	}
	
	Nodo* frente;			///< Puntero al nodo de enfrente de la cola.
	Nodo* fin;				///< Puntero al último nodo que ingresó a la cola.
	int tamanno;			///< Tamaño de la cola.
	
public:
	
	TCola() : frente(nullptr), fin(nullptr), tamanno(0){
	
};
