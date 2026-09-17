/**
* @file RegistroPuntaje.hpp
* @brief Objeto para almacenar los registros de puntajes.
* @author Stiward Araya Calderón
* @date Creado el 17/09/2026
*/
#pragma once

#include <string>					///< std::string

/**
* @brief Se almacena en la lista a ordenar de puntajes de los jugadores.
*/
class RegistroPuntaje {
private:
	std::string jugador;			///< Nombre del jugador
	int puntaje;					///< Puntaje del jugador
	
public:
	
	/**
	* @brief Constructor genérico con parámetros para iniciar el objeto.
	* @param jugador: Nombre del jugador
	* @param puntaje: Puntaje del jugador
	*/
	RegistroPuntaje(const std::string& jugador, int puntaje);
	
	const std::string& getNombre() const;	///< GETTER: nombre del jugador
	int getPuntaje() const;					///< GETTER: puntaje del jugador
};
