/**
* @file TPila.hpp
* @brief Implementación de una estructura LIFO para el proyecto
* @author Stiward Araya Calderón
* @date Creado el 15/8/2026
*/
#pragma once

#include <functional>		///< std::function
#include <stdexcept>		///< std::runtime_error

/**
* @brief Estructura de datos genérica tipo LIFO.
* @tparam T tipo de dato genérico que la pila va a almacenar.
*/
template <typename T>
class TPila{
private:
	
	/**
	* @brief Nodo interno de la pila, contiene un objeto y un puntero al siguiente.
	*/
	struct Nodo{
		T obj;				///< Objéto genérico
		Nodo* siguiente; 	///< Puntero al siguiente nodo de la pila
	};
	
	Nodo* tope;				///< Puntero al nodo tope de la pila
	int tamanno;			///< Tamaño de la pila
	
public:
	
	/**
	* @brief Constructor genérico de la pila.
	*/
	TPila() : tope(nullptr), tamanno(0) {}
	
	/**
	* @brief Elimina todos los nodos de la pila y libera la memoria.
	* @post Reinicia todos los parámetros de la pila.
	*/
	~TPila(){
		Nodo* actual = tope;
		while(actual){
			Nodo* auxiliar = actual;
			actual = actual->siguiente;
			delete auxiliar;
		}
		tope = nullptr;
		tamanno = 0;
	}
	
	/**
	* @brief Retorna un valor booleano si la pila está vacía o no.
	* @return verificación de pila vacía.
	*/
	bool esVacia() const{
		return tope == nullptr;
	}
	
	/**
	* @brief Ingresa al tope de la pila un objeto nuevo.
	* @param obj Objeto genérico a almacenar en la pila.
	* @post El tamanno de la pila incrementa en 1.
	*/
	void apilar(const T& obj) {
		Nodo* nuevo = new Nodo{obj, nullptr};
		
		//Clausula guardian : Pila vacía
		if(esVacia()){
			tope = nuevo;
			tamanno++;
			return;
		}
		
		nuevo->siguiente = tope;
		tope = nuevo;
		tamanno++;
	}
	
	/**
	* @brief Elimina el nodo al tope de la pila y retorna su valor.
	* @pre La pila no debe estar vacía.
	* @return Valor que se encontraba en el nodo del tope.
	* @throw std::runtime_error si la pila está vacía.
	* @post El tamaño de la pila decrementa en 1.
	*/
	T desapilar(){
		//Clausula guardian: Pila vacía
		if(esVacia()){
			throw std::runtime_error("La pila se encuentra vacía");
		}
		
		T obj = tope->obj;
		Nodo* auxiliar = tope;
		tope = tope->siguiente;
		delete auxiliar;
		tamanno--;
		return obj;
	}
	
	/**
	* @brief Muestra una copia del objeto al tope de la pila.
	* @pre La pila no debe estar vacía.
	* @throw std::runtime_error si la pila está vacía.
	* @return Copia del objeto almacenado al tope de la pila.
	*/
	T& verTope() const {
		if(esVacia()){
			throw std::runtime_error("La pila se encuentra vacía");
		}
		
		return tope->obj;
	}
	
	/**
	* @brief Retorna el tamaño actual de la pila.
	* @return Entero que representa el tamaño de la pila.
	*/
	int obtenerTamanno() const {
		return tamanno;
	}
	
};
