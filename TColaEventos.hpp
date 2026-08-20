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
	}
	
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
	* @pre Inserta directamente al frente si la cola está vacía.
	* @param obj Evento a insertar en la cola.
	* @param momento Tiempo de la partida en la ocurrirá el evento.
	* @post incrementa tamanno en 1
	*/
	void programarEvento(const T& obj, float momento) {
		if(!obj){ throw std::runtime_error("El evento no es válido(nullptr)"); }
		
		Nodo* nuevo = new Nodo{obj, momento, nullptr};
		if(esVacia()){
			frente = nuevo;
			tamanno++;
			return;
		}
		
		Nodo* actual = frente;
		Nodo* anterior = frente;
		while(!actual){
			
			//TODO: Completar logica de insertar en orden.
			if(nuevo->momento < actual->momento){}
			
			anterior = actual;
			actual = actual->siguiente;
		}
	}
};
