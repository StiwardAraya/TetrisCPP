/**
* @file EstadosManager.hpp
* @brief Sistema de control de estados
* @author Stiward Araya Calderón
* @date Creado el 15/09/2026
*/
#pragma once

#include "TPila.hpp" 			///< TPila<T>
#include "Estado.hpp"			///< Estados[interface]

class EstadosManager {
private:
	TPila<Estado*> estados;		///< Pila de estados
	
public:
	
	/**
	* @brief Constructor genérico del objeto, arranca vacío.
	*/
	EstadosManager();
	
	/**
	* @brief Destructor genérico del objeto, vacía la pila de estados.
	*/
	~EstadosManager();
	
	/**
	* @brief Recibe un estado nuevo para apilar.
	* @param nuevoEstado: puntero del estado nuevo a apilar.
	*/
	void apilarEstado(Estado* nuevoEstado);
	
	/**
	* @brief Remueve el estado al tope de la pila para recuperar
	* el estado anterior.
	*/
	void desapilarEstado();
	
	/**
	* @brief En lugar de agregar un estado nuevo, intercambia el 
	* tope de la pila con el estado nuevo.
	*/
	void cambiarEstado(Estado* nuevoEstado);
	
	/**
	* @brief Consulta el estado al tope de la pila y delega
	* el manejo de entradas.
	*/
	void manejarEntrada(InputManager& entradas);
	
	/**
	* @brief Consulta el estado al tope de la pila y delega
	* la actualización de datos.
	*/
	void actualizar(float deltaTime);
	
	/**
	* @brief Consulta el estado al tope de la pila y delega
	* la graficación.
	*/
	void dibujar(Graficador& graficador);
	
	/**
	* @brief Consulta si la pila de estados se encuentra vacía.
	*/
	bool estaVacio() const;
};
