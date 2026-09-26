/**
* @file GestorEventosProgramados.hpp
* @brief Gestor de la cola de eventos del juego
* @author Stiward Araya Calderón
* @date Creado el 24/09/2026
*/
#pragma once

#include <functional>		///< std::function
#include "TColaEventos.hpp"	///< TColaEventos<T>

/**
* @brief Gestiona la cola de eventos programados
*/
class GestorEventosProgramados {
private:
	TColaEventos<std::function<void()>> eventos;	///< Cola con los eventos del juego
	float tiempoTranscurrido;						///< Tiempo transcurrido actualmente
	
public:
	/**
	* @brief Constructor genérico del gestor de eventos.
	*/
	GestorEventosProgramados();
	
	/**
	* @brief Programa un evento en la cola de eventos.
	*/
	void programarEvento(float momento, std::function<void()> efecto);
	
	/**
	* @brief Actualiza el tiempo actual
	*/
	void actualizar(float deltaTime);
};
