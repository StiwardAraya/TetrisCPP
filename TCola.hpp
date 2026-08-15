/**
* @file TCola.hpp
* @brief Implementación de una estructura FIFO para el proyecto
* @author Stiward Araya Calderón
* @date creado el 15/08/2026
*/
#pragma once

#include <functional>		///< std::funcion
#include <stdexcept>		///< std::runtime_error

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
	};
	
	Nodo* frente;			///< Puntero al nodo de enfrente de la cola.
	Nodo* fin;				///< Puntero al último nodo que ingresó a la cola.
	int tamanno;			///< Tamaño de la cola.
	
public:
	
	/**
	* @brief Constructor genérico de la cola.
	*/
	TCola() : frente(nullptr), fin(nullptr), tamanno(0){}
	
	/**
	* @brief Destructor de la cola, libera la memoria de todos los nodos.
	* @post reinicia todos los parámetros de la cola.
	*/
	~TCola(){
		Nodo* actual = frente;
		while(actual){
			Nodo* auxiliar = actual;
			actual = actual->siguiente;
			delete auxiliar;
		}
		frente = nullptr;
		fin = nullptr;
		tamanno = 0;
	}
	
	/**
	* @brief Retorna un valor booleano si la cola está vacía o no.
	*/
	bool esVacia() const{
		return !frente && !fin;
	}
	
	/**
	* @brief Agrega al frente de la cola un nodo con el objeto
	* recibido.
	* 
	* @param obj objeto a almacenar en la cola.
	* @post Tamanno incrementa en 1.
	*/
	void encolar(const T& obj){
		Nodo* nuevo = new Nodo{obj, nullptr};
		
		// Clausula Guardian: Caso de cola vacía.
		if(esVacia()) { 
			frente = nuevo;
			fin = nuevo;
			tamanno++;
			return;
		}
		
		fin->siguiente = nuevo;
		fin = nuevo;
		tamanno++;
	}
	
	/**
	* @brief Elimina el elemento de enfrente y lo retorna.
	* @pre La cola no debe estar vacía
	* @return Instancia del objeto que se encontraba al frente.
	* @throw std::runtime_error Si la cola está vacía.
	* @post Tamanno decrementa en 1.
	*/
	T desencolar(){
		// Clausula Guardian: Caso de cola vacía.
		if(esVacia()){
			throw std::runtime_error("La cola está vacía");
		}
		
		T obj = frente->obj;
		Nodo* auxiliar = frente;
		frente = frente->siguiente;
		delete auxiliar;
		tamanno--;
		
		if(!frente){
			fin = nullptr;
		}
		
		return obj;
	}
	
	/**
	* @brief Devuelve el elemento al frente de la cola.
	* @pre La cola no debe estar vacía.
	* @return Objeto genérico al frente de la cola.
	*/
	T& verFrente() const{
		if(esVacia()){
			throw std::runtime_error("La cola está vacía");
		}
		
		return frente->obj;
	}
	
	/**
	* @brief Retorna el tamaño de la cola.
	* @return Valor entero que representa el tamaño de la cola.
	*/
	int obtenerTamanno() const {
		return tamanno;
	}
	
	/**
	* @brief Metodo solo para testing, recorre la lista y ejecuta una acción
	* sobre cada elemento de la cola.
	*
	* @return accion, función lambda a ejecutar en cada elemento.
	*/
	void recorrer(std::function<void(const T&)> accion) const {
		Nodo* actual = frente;
		while(actual){
			accion(actual->obj);
			actual = actual->siguiente;
		}
	}
};
