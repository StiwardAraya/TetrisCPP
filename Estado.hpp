/**
* @file Estado.hpp
* @brief Interfaz para los estados del juego
* @author Stiward Araya Calderón
* @date Creado el 15/09/2026
*/
#pragma once

class InputManager;
class Graficador;

/**
* @brief Interfaz que deben implementar todos los estados del juego
* para poder ser tratados de forma uniforme.
*/
class Estado {
public:
	virtual ~Estado() = default;
	
	/**
	* @brief Procesa el input del frame actual, según la lógica propia
	* de cada estado concreto.
	* @param entradas instancia del Sistema de control de entradas
	*/
	virtual void manejarEntrada(InputManager& entradas) = 0;
	
	/**
	* @brief Actualiza la lógica del estado un paso de tiempo fijo.
	* @param deltaTime Tiempo transcurrido, en segundos, desde la
	* última actualización.
	*/
	virtual void actualizar(float deltaTime) = 0;
	
	/**
	* @brief Dibuja el estado actual usando las primitivas de Graficador.
	* @param graficador Instancia del sistema de graficación.
	*/
	virtual void dibujar(Graficador& graficador) = 0;
	
	/**
	* @brief Se llama cuando este estado pasa a ser el tope de la pila
	* de EstadosManager. Implementación vacía por defecto: la mayoría
	* de los estados no necesitan hacer nada especial acá.
	*/
	virtual void alEntrar() {}
	
	/**
	* @brief Se llama cuando este estado deja de ser el tope de la pila. 
	* Implementación vacía por defecto.
	*/
	virtual void alSalir() {}
};
