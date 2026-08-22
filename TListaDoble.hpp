/**
* @file TListaDoble.hpp
* @brief Lista doblemente enlazada.
* @author Stiward Araya Calderón.
* @date Creado el 21/08/2026
*/
#pragma once

#include <stdexcept>		///< std::runtime_error

/**
* @brief Estructura de datos doblemente enlazada.
* @tparam T tipo de dato genérico que la cola va a almacenar.
*/
template <typename T>
class TListaDoble {
private:
	/**
	* @brief Nodo interno de la lista, tiene un objeto genérico, un puntero
	* al nodo siguiente y un puntero al anterior.
	*/
	struct Nodo{
		T obj;				///< Objeto genérico a almacenar en la lista.
		Nodo* anterior;		///< Puntero al nodo anterior del nodo.
		Nodo* siguiente;	///< Puntero al nodo siguiente del nodo.
	};
	
	Nodo* cabeza;			///< Puntero al inicio de la lista.
	Nodo* cola;				///< Puntero al final de la lista.
	Nodo* actual;			///< Puntero indice a una posición de la lista.
	int tamanno;			///< Cantidad de elementos en la lista.
	
public:
	
	/**
	* @brief Constructor genérico de la lista doblemente enlazada.
	*/
	TListaDoble() : cabeza(nullptr), cola(nullptr), actual(nullptr), tamanno(0) {}
	
	/**
	* @brief Destructor de la lista, libera la memoria de todos los nodos.
	* @post Reinicia todos los parámetros de la lista.
	*/
	~TListaDoble(){
		actual = cabeza;
		while(actual){
			Nodo* auxiliar = actual;
			actual = actual->siguiente;
			delete auxiliar;
		}
		cabeza = nullptr;
		cola = nullptr;
		actual = nullptr;
		tamanno = 0;
	}
	
	/**
	* @brief Retorna un valor booleano si la lista está vacía o no.
	*/
	bool esVacia() const {
		return cabeza == nullptr && cola == nullptr;
	}
		
	/**
	* @brief Inserta en la cabeza de la lista doble.
	* @pre El objeto a insertar no puede ser nulo.
	* @pre Si la lista está vacía inserta en cabeza y cola.
	* @throw std::runtime_error Si el objeto es nulo.
	* @param obj Objeto de tipo genérico a almacenar en la lista.
	* @post Tamanno incrementa en 1.
	*/
	void insertar(const T& obj){
		if (!obj) { 
			throw std::runtime_error("El objeto a insertar no es válido(nullptr)");
		}
		
		Nodo* nuevo = new Nodo{obj, nullptr, nullptr};
		if(esVacia()){
			cabeza = nuevo;
			cola = nuevo;
			actual = cabeza;
			tamanno++;
			return;
		}
		
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
		tamanno++;
	}
	
	/**
	* @brief Retorna un valor booleano si el anterior del indice
	* no es nulo.
	*/
	bool hayAnterior() const {
		return !esVacia() && actual->anterior != nullptr;
	}
	
	/**
	* @brief Retorna un valor booleano si el siguiente del indice 
	* no es nulo.
	*/
	bool haySiguiente() const {
		return !esVacia() && actual->siguiente != nullptr;
	}
	
	/**
	* @brief Mueve el indice al nodo anterior y retorna su objeto almacenado.
	* @pre El anterior del indice no puede ser nulo.
	* @throw std::runtime_error Si el anterior al indice es nulo.
	* @return Instancia del objeto almacenado en el nodo anterior al indice.
	*/
	T retroceder() {
		if(!hayAnterior()){
			throw std::runtime_error("No se puede retroceder más o la lista está vacía");
		}
		
		actual = actual->anterior;
		return actual->obj;
	}
	
	/**
	* @brief Mueve el indice al nodo siguiente y retorna su objeto almacenado.
	* @pre El siguiente del indice no puede ser nulo.
	* @throw std::runtime_error Si el siguiente al indice es nulo.
	* @return Instancia del objeto almacenado en el nodo siguiente al indice.
	*/
	T avanzar() {
		if(!haySiguiente()){
			throw std::runtime_error("No se puede avanzar más o la lista está vacía");
		}
		
		actual = actual->siguiente;
		return actual->obj;
	}
	
	/**
	* @brief Retorna el objeto que se encuentra actualmente en el indice
	* de la lista.
	* @pre La lista no debe estar vacía.
	* @throw std::runtime_error Si la lista está vacía.
	* @return Instancia del objeto correspondiente al indice de la lista.
	*/
	const T& verActual() const {
		if(esVacia()){
			throw std::runtime_error("La lista está vacía");
		}
		
		return actual->obj;
	}
	
	/**
	* @brief Reinicia el indice de la lista.
	* @pre La lista no puede estar vacía.
	* @throw std::runtime_error Si la lista está vacía.
	*/
	void reiniciarRecorrido() {
		if(esVacia()){
			throw std::runtime_error("La lista está vacía")
		}
		
		actual = cabeza;
	}
	
	/**
	* @brief Retorna el tamaño de la lista.
	* @return Valor entero que representa el tamaño de la lista.
	*/
	int obtenerTamanno const () {
		return tamanno;
	}
	
	// TEST
	void imprimir() {
		if(esVacia()){
			throw std::runtime_error("La lista está vacía");
		}
		
		actual = cabeza;
		while(actual){
			std::cout << "[ " << actual->obj << " ]->"; 
			actual = actual->siguiente;
		}
		std::cout << std::endl;
	}
};
