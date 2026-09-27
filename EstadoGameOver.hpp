/**
* @file EstadoGameOver.hpp
* @brief Esquema lógico del estado de fin de partida, con reproducción
* automática del historial de movimientos.
* @author Stiward Araya Calderón
* @date Creado el 24/09/2026
*/
#pragma once

#include <string>					///< std::string
#include "Estado.hpp"				///< Estado (clase base)
#include "HistorialMovimientos.hpp"	///< HistorialMovimientos, EstadoMovimiento

class EstadosManager;			
class InputManager;			
class Graficador;				
class PuntajesManager;			

/**
* @brief Estado que se apila sobre EstadoJugando al terminar la partida.
* Guarda el puntaje si califica al top 10, y reproduce automáticamente
* el historial completo de movimientos, con controles para pausar,
* retroceder, avanzar, reiniciar la partida o volver al menú.
*/
class EstadoGameOver : public Estado {
private:
	static const float TIEMPO_ENTRE_PASOS;			///< Segundos entre cada paso automático del replay
	
	EstadosManager& estadosManager;					///< Referencia al manejador de estados
	PuntajesManager& puntajesManager;				///< Referencia al manejador de puntajes, compartido con EstadoMenu
	HistorialMovimientos& historial;				///< Referencia al historial de la partida ya jugada (no se copia)
	
	std::string nombreJugador;						///< Nombre capturado en EstadoMenu, reutilizado al reiniciar
	int puntajeFinal;								///< Puntaje con el que terminó la partida
	
	bool reproduccionPausada;						///< true si el jugador pausó el auto-play del replay
	float tiempoAcumulado;							///< Acumulador de tiempo para el avance automático
	
	/**
	* @brief Avanza un paso del replay si hay uno disponible; si no,
	* deja la reproducción pausada en el último frame.
	*/
	void avanzarUnPaso();
	
	/**
	* @brief Descarta este EstadoGameOver y el EstadoJugando que quedó
	* debajo en la pila, y apila una partida nueva con el mismo jugador.
	*/
	void reiniciarPartida();
	
	/**
	* @brief Descarta este EstadoGameOver y el EstadoJugando debajo en
	* la pila, revelando el EstadoMenu original sin reconstruirlo.
	*/
	void volverAlMenu();
	
public:
	
	/**
	* @brief Constructor del estado de fin de partida. Registra el
	* puntaje en PuntajesManager si corresponde, y reinicia el recorrido
	* del historial para empezar la reproducción desde el principio.
	* @param estadosManager: referencia al manejador de estados de la aplicación.
	* @param puntajesManager: referencia al manejador de puntajes compartido.
	* @param historial: referencia al historial de movimientos de la partida.
	* @param nombreJugador: nombre capturado al iniciar la partida.
	* @param puntajeFinal: puntaje obtenido al terminar la partida.
	*/
	EstadoGameOver(EstadosManager& estadosManager, PuntajesManager& puntajesManager,
				   HistorialMovimientos& historial, const std::string& nombreJugador,
				   int puntajeFinal);
	
	/**
	* @brief Procesa pausa/reanudación del replay, retroceso y avance
	* manual, reinicio de partida y vuelta al menú.
	* @param entradas: manejador de entradas del motor, ya actualizado.
	*/
	void manejarEntrada(InputManager& entradas) override;
	
	/**
	* @brief Avanza automáticamente el replay mientras no esté pausado.
	* @param deltaTime: tiempo transcurrido, en segundos, desde la
	* última actualización.
	*/
	void actualizar(float deltaTime) override;
	
	/**
	* @brief Dibuja el mensaje de fin de partida, el puntaje, el estado
	* actual del replay, y las instrucciones de control.
	* @param graficador: encargado de dibujar las primitivas en pantalla.
	*/
	void dibujar(Graficador& graficador) override;
};
