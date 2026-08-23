/**
* @file TLista.hpp
* @brief Lista simple enlazada.
* @author Stiward Araya Calderón.
* @date Creado el 22/08/2026
*/
#pragma once

#include <stdexcept>		///< std::runtime_error

/**
* @brief Estructura de datos simplemente enlazada.
* @tparam T tipo de dato genérico que la cola va a almacenar.
*/
template <typename T>
class TLista {
private:
	
	/**
	* @brief Nodo interno de la estructura, guarda el objeto y
	* un puntero al nodo siguiente.
	*/
	struct Nodo{
		T obj;				///< Objeto genérico a almacenar en la lista
		Nodo* siguiente;	///< Puntero al nodo siguiente
	};
	
	Nodo* cabeza;			///< Puntero al primer nodo de la lista
	int tamanno;			///< Tamaño de la lista
	
	// TODO: Junto con revisar eliminar por indice, revisar si se puede prescindir de este helper.
	/**
	* @brief Método helper, borra el nodo que está en cabeza.
	* @post Tamanno decrementa en 1.
	*/
	void eliminarCabeza(){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
		tamanno--;
	}
	
public:
	
	/**
	* @brief Constructor genérico de la lista simplemente enlazada.
	*/
	TLista() : cabeza(nullptr), tamanno(0) {}
	
	/**
	* @brief Destructor de la lista, libera la memoria de todos los nodos.
	* @post Reinicia todos los parámetros de la lista.
	*/
	~TLista() {
		Nodo* actual = cabeza;
		while(actual){
			Nodo* aux = actual;
			actual = actual->siguiente;
			delete aux;
		}
		cabeza = nullptr;
		tamanno = 0;
	}
	
	/**
	* @brief Retorna un valor booleano si la lista está vacía o no.
	*/
	bool esVacia() {
		return cabeza == null;
	}
	
	/**
	* @brief Inserta un nuevo nodo a la cabeza de la lista.
	* @param obj Objeto genérico a guardar en la lista.
	* @post Tamanno incrementa en 1
	*/
	void insertar(const T& obj) {
		Nodo* nuevo = new Nodo{obj, nullptr};
		if(esVacia()){
			cabeza = nuevo;
			tamanno++;
			return;
		}
		
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
		tamanno++;
	}
	
	// TODO: hacer pruebas y refactorizar codigo, algo tiene mal, aun no se que es.
	T eliminar(int indice) {
		if(esVacia()){
			throw std::runtime_error("La lista esta vacia");
		}
		
		T obj;
		
		if(indice == 0 && tamanno > 1){
			obj = cabeza->obj;
			eliminarCabeza();
			return obj;
		}
		
		if(tamanno == 1 && indice == 0){
			obj = cabeza->obj;
			~TLista();
			return obj;
		}
		
		Nodo* actual = cabeza;
		Nodo* anterior = nullptr;
		for(int i = 0; i < indice; i++){
			anterior = actual;
			actual = actual->siguiente;
		}
		
		obj = actual->obj;
		anterior->siguiente = actual->siguiente;
		actual->siguiente = nullptr;
		delete actual;
		return obj;
	}
};
