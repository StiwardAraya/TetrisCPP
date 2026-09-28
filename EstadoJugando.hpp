/**
* @file EstadoJugando.hpp
* @brief Esquema lógico del estado de partida activa: orquesta Tablero,
* Pieza, ColaPiezas, PiezaHold, HistorialMovimientos y
* GestorEventosProgramados.
* @author Stiward Araya Calderón
* @date Creado el 26/09/2026
*/
#pragma once

#include <string>						///< std::string
#include "Estado.hpp"					///< Estado (clase base)
#include "Tablero.hpp"					///< Tablero (atributo por valor)
#include "Pieza.hpp"					///< Pieza (atributo por valor)
#include "ColaPiezas.hpp"				///< ColaPiezas (atributo por valor)
#include "PiezaHold.hpp"				///< PiezaHold (atributo por valor)
#include "HistorialMovimientos.hpp"		///< HistorialMovimientos, EstadoMovimiento
#include "GestorEventosProgramados.hpp"	///< GestorEventosProgramados (atributo por valor)

class EstadosManager;			
class InputManager;			
class Graficador;				
class PuntajesManager;			

/**
* @brief Acciones internas del jugador durante la partida, traducidas
* desde AccionMotor por manejarEntrada().
*/
enum class AccionJugador {
	IZQUIERDA, DERECHA, ROTAR, BAJAR_SUAVE, BAJAR_FORZADO,
	HOLD, DESHACER, REHACER, PAUSA
};

/**
* @brief Estado que orquesta la partida activa de Tetris: caída,
* colisión, rotación, hold, deshacer/rehacer, eventos programados y
* condición de fin de juego.
*/
class EstadoJugando : public Estado {
private:
	static const float RETRASO_INICIAL_DAS;			///< Segundos sosteniendo antes de repetir el movimiento
	static const float INTERVALO_REPETICION_DAS;	///< Segundos entre repeticiones tras el retraso inicial
	int direccionHorizontalActiva;					///< -1 izquierda, 0 ninguna, 1 derecha
	float tiempoSostenidoHorizontal;				///< Tiempo que lleva sostenida la dirección activa
	float tiempoAcumuladoRepeticionH;				///< Acumulador para las repeticiones tras el retraso
	
	Tablero tablero;								///< Tablero de 20x10 celdas
	Pieza piezaActual;								///< Pieza que está cayendo actualmente
	ColaPiezas colaPiezas;							///< Bolsa de 7 piezas futuras
	PiezaHold hold;									///< Casilla de pieza en espera
	HistorialMovimientos historial;					///< Historial para deshacer/rehacer y replay
	GestorEventosProgramados gestorEventos;			///< Eventos programados de la partida
	
	int puntaje;									///< Puntaje acumulado de la partida
	int multiplicadorPuntaje;						///< Multiplicador activo (eventos de puntos dobles)
	float tiempoAcumulado;							///< Acumulador de tiempo para la caída automática
	float intervaloCaida;							///< Segundos entre cada caída automática (modificable por eventos)
	
	std::string nombreJugador;						///< Nombre capturado en EstadoMenu
	
	EstadosManager& estadosManager;					///< Referencia al manejador de estados
	PuntajesManager& puntajesManager;				///< Referencia al manejador de puntajes, compartido
	
	/**
	* @brief Intenta mover la pieza actual el desplazamiento dado,
	* validando colisión antes de aplicar el movimiento.
	* @return true si el movimiento se aplicó, false si había colisión.
	*/
	bool intentarMover(int deltaFila, int deltaColumna);
	
	/**
	* @brief Intenta avanzar a la siguiente orientación, validando
	* colisión (sin wall kick).
	* @return true si la rotación se aplicó, false si no había espacio.
	*/
	bool intentarRotar();
	
	/**
	* @brief Fija la pieza actual en el tablero, limpia líneas completas
	* y genera la siguiente pieza.
	*/
	void fijarPiezaYContinuar();
	
	/**
	* @brief Detecta filas completas, suma el puntaje correspondiente y
	* las limpia del tablero.
	*/
	void limpiarLineasCompletas();
	
	/**
	* @brief Calcula los puntos a otorgar según la cantidad de líneas
	* limpiadas simultáneamente, aplicando el multiplicador activo.
	*/
	int calcularPuntaje(int cantidadLineas) const;
	
	/**
	* @brief Pide la siguiente pieza a colaPiezas y verifica fin de juego.
	*/
	void generarNuevaPieza();
	
	/**
	* @brief Intercambia la pieza actual con la guardada en hold, o la
	* guarda si la casilla estaba vacía.
	*/
	void ejecutarHold();
	
	/**
	* @brief Reconstruye tablero y piezaActual a partir de un snapshot
	* del historial (usado al deshacer/rehacer).
	*/
	void aplicarEstadoDelHistorial(const EstadoMovimiento& estado);
	
	/**
	* @brief Revisa si la pieza actual colisiona en su posición inicial;
	* si es así, transiciona a EstadoGameOver.
	*/
	void verificarFinDeJuego();
	
public:
	
	/**
	* @brief Constructor del estado de partida. Genera la primera pieza,
	* programa los eventos iniciales y verifica que haya espacio para
	* empezar.
	* @param estadosManager: referencia al manejador de estados de la aplicación.
	* @param nombreJugador: nombre capturado en EstadoMenu.
	* @param puntajesManager: referencia al manejador de puntajes compartido.
	*/
	EstadoJugando(EstadosManager& estadosManager, const std::string& nombreJugador,
				  PuntajesManager& puntajesManager);
	
	/**
	* @brief Traduce AccionMotor a AccionJugador y ejecuta la acción
	* correspondiente.
	* @param entradas: manejador de entradas del motor, ya actualizado.
	*/
	void manejarEntrada(InputManager& entradas) override;
	
	/**
	* @brief Actualiza eventos programados y aplica la caída automática
	* según intervaloCaida.
	* @param deltaTime: tiempo transcurrido, en segundos, desde la
	* última actualización.
	*/
	void actualizar(float deltaTime) override;
	
	/**
	* @brief Dibuja el tablero, la pieza actual y el puntaje.
	* @param graficador: encargado de dibujar las primitivas en pantalla.
	*/
	void dibujar(Graficador& graficador) override;
};
