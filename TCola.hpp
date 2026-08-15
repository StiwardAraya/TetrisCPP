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
	
	/**
	* @brief Constructor genérico de la cola.
	*/
	TCola() : frente(nullptr), fin(nullptr), tamanno(0){}
	
	/**
	* @brief Destructor de la cola, libera la memoria de todos los nodos.
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
	
	// TODO: revisar la eficiencia de este metodo, 
	T peak(int index){
		if(esVacia()){
			throw std::runtime_error("La cola está vacía")
		}
		
		int posicion = 0;
	}
};
