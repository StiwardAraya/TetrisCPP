/**
* @file Aplicacion.hpp
* @brief Punto de entrada del motor: crea la ventana, arranca en
* EstadoMenu, y ejecuta el game loop principal de timestep fijo.
* @author Stiward Araya Calderón
* @date Creado el 27/09/2026
*/
#pragma once

#include <string>				///< std::string
#include "Graficador.hpp"		///< Graficador (atributo por valor)
#include "InputManager.hpp"		///< InputManager (atributo por valor)
#include "EstadosManager.hpp"	///< EstadosManager (atributo por valor)

/**
* @brief Dueña de la ventana, el manejador de entradas y la pila de
* estados. Ejecuta el ciclo principal: procesar entrada, actualizar en
* pasos fijos, y dibujar, hasta que se cierre la ventana o la pila de
* estados quede vacía.
*/
class Aplicacion {
private:
	static const float PASO_FIJO;		///< Paso de tiempo fijo para actualizar(), en segundos
	
	Graficador graficador;				///< Ventana y primitivas de dibujo
	InputManager entradas;				///< Traduce eventos de teclado a AccionMotor
	EstadosManager estadosManager;		///< Pila de estados del juego
	
public:
	
	/**
	* @brief Constructor de la aplicación. Crea la ventana y apila
	* EstadoMenu como primer estado.
	* @param ancho: ancho de la ventana, en píxeles.
	* @param alto: alto de la ventana, en píxeles.
	* @param titulo: título de la ventana.
	* @param rutaArchivoPuntajes: ruta al archivo de persistencia de
	* mejores puntajes, propagada a EstadoMenu.
	*/
	Aplicacion(unsigned int ancho, unsigned int alto, const std::string& titulo,
			   const std::string& rutaArchivoPuntajes);
	
	/**
	* @brief Ejecuta el game loop principal hasta que se cierre la
	* ventana o la pila de estados quede vacía.
	*/
	void ejecutar();
};
