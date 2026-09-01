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
	bool esVacia() const {
		return cabeza == nullptr;
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
	
	/**
	* @brief Elimina un nodo según su posición.
	* @pre La lista no puede estar vacía.
	* @pre El indice no puede estar fuera de rango.
	* @pre Si el indice es 0, elimina cabeza.
	* @throw std::runtime_error Si la lista está vacía.
	* @throw std::out_of_range Si el indice está fuera de rango.
	* @param indice: Posición a eliminar.
	* @return Objeto genérico que se encontraba en el nodo eliminado.
	* @post Tamanno decrementa en 1.
	*/
	T eliminar(int indice) {
		if(esVacia()){
			throw std::runtime_error("La lista esta vacia");
		}
		
		if(indice < 0 || indice >= tamanno){
			throw std::out_of_range("Indice fuera de rango");
		}
		
		if(indice == 0){
			T obj = cabeza->obj;
			Nodo* aux = cabeza;
			cabeza = cabeza->siguiente;
			delete aux;
			return obj;
		}
		
		Nodo* anterior = cabeza;
		for(int i = 0; i < indice - 1; i++){
			anterior = anterior->siguiente;
		}
		
		Nodo* actual = anterior->siguiente;
		T obj = actual->obj;
		anterior->siguiente = actual->siguiente;
		delete actual;
		tamanno--;
		return obj;
	}
	
	/**
	* @brief Obtiene el valor de un nodo según su posición.
	* @pre La lista no puede estar vacía.
	* @pre El indice no puede estar fuera de rango.
	* @pre Si el indice es 0, retorna el valor de la cabeza.
	* @throw std::runtime_error Si la lista está vacía.
	* @throw std::out_of_range Si el indice está fuera de rango.
	* @param indice: Posición a retornar.
	* @return Puntero del objeto genérico que se encontraba en el nodo a retornar.
	*/
	T& obtener(int indice) {
		if(esVacia()){
			throw std::runtime_error("La lista esta vacia");
		}
		
		if(indice < 0 || indice >= tamanno){
			throw std::out_of_range("Indice fuera de rango");
		}
		
		if(indice == 0){
			T* obj = &cabeza->obj;
			return *obj;
		}
		
		Nodo* actual = cabeza;
		for(int i = 0; i <= indice - 1; i++){
			actual = actual->siguiente;
		}
		
		T* obj = &actual->obj;
		return *obj;
	}
	
	/**
	* @brief Sobrecarga const para obtener, parche.
	*/
	const T& obtener(int indice) const {
		if(esVacia()){
			throw std::runtime_error("La lista esta vacia");
		}
		
		if(indice < 0 || indice >= tamanno){
			throw std::out_of_range("Indice fuera de rango");
		}
		
		if(indice == 0){
			T* obj = &cabeza->obj;
			return *obj;
		}
		
		Nodo* actual = cabeza;
		for(int i = 0; i <= indice - 1; i++){
			actual = actual->siguiente;
		}
		
		T* obj = &actual->obj;
		return *obj;
	}
	
	/**
	* @brief Retorna el tamaño de la lista.
	* @return Valor entero que representa el tamaño de la lista.
	*/
	int obtenerTamanno() const {
		return tamanno;
	}
};
