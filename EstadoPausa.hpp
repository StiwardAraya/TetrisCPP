/**
* @file EstadoPausa.hpp
* @brief Esquema lógico del estado de pausa del juego
* @author Stiward Araya Calderón
* @date Creado el 26/09/2026
*/
#pragma once

#include "Estado.hpp"			///< Estado (clase base)

class EstadosManager;	
class InputManager;			
class Graficador;				

/**
* @brief Estado que se apila sobre EstadoJugando cuando el jugador pausa
* la partida. Ofrece reanudar o salir al menú, sin dibujar el tablero
* de fondo.
*/
class EstadoPausa : public Estado {
private:
	static const int CANTIDAD_OPCIONES = 2;		///< Cantidad de opciones del menú de pausa
	
	EstadosManager& estadosManager;				///< Referencia al manejador de estados, para desapilar
	int opcionSeleccionada;						///< Indice de la opción resaltada (0 a 1)
	
public:
	
	/**
	* @brief Constructor del estado de pausa.
	* @param estadosManager: referencia al manejador de estados de la aplicación.
	*/
	EstadoPausa(EstadosManager& estadosManager);
	
	/**
	* @brief Procesa la navegación entre opciones y la confirmación.
	* @param entradas: manejador de entradas del motor, ya actualizado.
	*/
	void manejarEntrada(InputManager& entradas) override;
	
	/**
	* @brief Sin lógica dependiente del tiempo: la pausa no actualiza nada.
	* @param deltaTime: tiempo transcurrido, en segundos, desde la
	* última actualización.
	*/
	void actualizar(float deltaTime) override;
	
	/**
	* @brief Dibuja únicamente el mensaje de pausa y sus opciones, sin
	* el tablero de fondo.
	* @param graficador: encargado de dibujar las primitivas en pantalla.
	*/
	void dibujar(Graficador& graficador) override;
};
