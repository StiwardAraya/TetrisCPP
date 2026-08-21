/**
* @file TColaEventos.hpp
* @brief Implementación de una cola de prioridad para l
* os eventos de partida.
* @author Stiward Araya Calderón
* @date Creado el 20/08/2026
*/
#pragma once

#include <stdexcept>		///< std::runtime_error

/**
* @brief Estructura de datos genérica tipo FIFO con prioridades.
* @tparam T tipo de dato genérico que la cola va a almacenar.
*/
template <typename T>
class TColaEventos {
private:
	/**
	* @brief Nodo interno de la cola, contiene un dato genérico, un valor de
	* prioridad y un puntero al nodo siguiente.
	*/
	struct Nodo{
		T obj;				///< Dato genérico almacenado en el nodo.
		float momento;		///< Momento en el que ocurre el evento(prioridad).
		Nodo* siguiente;	///< Puntero al nodo siguiente.
	};
	
	Nodo* frente;			///< Puntero al frente de la cola.
	int tamanno;			///< Tamaño de la cola(cantidad de eventos).
	
public:
	
	/**
	* @brief Constructor genérico de la cola de prioridad.
	*/
	TColaEventos() : frente(nullptr), tamanno(0) {}
	
	/**
	* @brief Destructor de la cola, libera la memoria de todos los nodos.
	* @post Reinicia todos los parametros de la cola de prioridad.
	*/
	~TColaEventos(){
		Nodo* actual = frente;
		while(actual){
			Nodo* auxiliar = actual;
			actual = actual->siguiente;
			delete auxiliar;
		}
		frente = nullptr;
		tamanno = 0;
	}
		
	/**
	* @brief Retorna un valor booleano si la cola está vacía o no.
	*/
	bool esVacia() const{
		return !frente;
	}
	
	/**
	* @brief Programa un evento en la cola según su prioridad.
	* @throw std::runtime_error Si el evento es nulo.
	* @pre El evento no puede ser nulo.
	* @pre Inserta directamente al frente si la cola está vacía.
	* @pre Inserta al frente si el momento es menor al nodo de enfrente.
	* @param obj Evento a insertar en la cola.
	* @param momento Tiempo de la partida en la ocurrirá el evento.
	* @post incrementa tamanno en 1.
	*/
	void programarEvento(const T& obj, float momento) {
		if(!obj){ throw std::runtime_error("El evento no es válido(null)"); }
		
		Nodo* nuevo = new Nodo{obj, momento, nullptr};
		if(esVacia()){
			frente = nuevo;
			tamanno++;
			return;
		}
		
		if(nuevo->momento < frente->momento) {
			nuevo->siguiente = frente;
			frente = nuevo;
			tamanno++;
			return;
		}
				   
		Nodo* actual = frente;
		Nodo* anterior = nullptr;
		
		while(actual){
			
			if(actual->siguiente == nullptr && nuevo->momento >= actual->momento){
				actual->siguiente = nuevo;
				tamanno++;
				break;
			}
			
			if(actual->momento >= nuevo->momento){
				nuevo->siguiente = actual;
				anterior->siguiente = nuevo;
				tamanno++;
				break;
			}
			
			anterior = actual;
			actual = actual->siguiente;
		}
	}
	
	/**
	* @brief Elimina el elemento de enfrente y lo retorna.
	* @pre La cola no debe estar vacía
	* @return Instancia del evento que se encontraba al frente.
	* @throw std::runtime_error Si la cola está vacía.
	* @post Tamanno decrementa en 1.
	*/
	T extraerEvento() {
		if(esVacia()){
			throw std::runtime_error("La cola de eventos está vacía");
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
	* @return Evento al frente de la cola.
	*/
	T verProximo() const {
		if(esVacia()){
			throw std::runtime_error("La cola está vacía");
		}
		
		return frente->obj;
	}
	
	/**
	* @brief Devuelve el elemento al frente de la cola.
	* @pre La cola no debe estar vacía.
	* @return Evento al frente de la cola.
	*/
	float verMomentoProximo() const {
		if(esVacia()){
			throw std::runtime_error("La cola está vacía");
		}
		
		return frente->momento;
	}
	
	/**
	* @brief Retorna el tamaño de la cola.
	* @return Valor entero que representa el tamaño de la cola.
	*/
	int obtenerTamanno() const {
		return tamanno;
	}
	
};
