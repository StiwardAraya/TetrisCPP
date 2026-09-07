/**
* @file HistorialMovimientos.hpp
* @brief Historial de movimientos de la partida
* @author Stiward Araya Calderón.
* @date Creado el 01/09/2026
*/
#pragma once

#include <vector>			///< std::vector
#include "Pieza.hpp"		///< Pieza<T>
#include "TListaDoble.hpp"	///< TListaDoble<T>
#include "Tablero.hpp"		///< Tablero

/**
* @brief Enum para el control del tipo de movimiento realizado por el jugador
*/
enum class TipoMovimiento {
	MOVER_IZQUIERDA,
	MOVER_DERECHA,
	ROTAR,
	BAJAR,
	COLOCAR
};

/**
* @brief Fotografia de un estado de la partida en un momento.
*/
struct EstadoMovimiento {
	TipoMovimiento tipo;								///< Tipo de movimiento realizado
	std::vector<std::vector<bool>> snapshotTablero;		///< Fotografia del estado del tablero
	TipoPieza tipoPiezaActual;							///< Tipo de pieza en el movimiento actual
	int filaPivote;										///< Fila pivote de la pieza actual
	int columnaPivote;									///< Columna pivote de la pieza actual
	int orientacion;									///< Orientacion de la pieza actual
	int puntaje;										///< Puntaje hasta el momento del jugador
};

/**
* @brief Objeto logico para el control de movimientos(undo, redo)
* y la reproduccion de la prtida al finalizar.
*/
class HistorialMovimientos {
private:
	TListaDoble<EstadoMovimiento> historial;			///< Lista doble usada como historial de movimientos
	
	/**
	* @brief Convierte el estado actual del tablero en su representacion plana.
	* @param tablero: Tablero de la partida a capturar
	* @return Arreglo bidimensional con la snapshot del tablero de juego
	*/
	std::vector<std::vector<bool>> capturarSnapshot(const Tablero& tablero) const;
public:
	
	/**
	* @brief Constructor genérico del historial.
	*/
	HistorialMovimientos();
	
	/**
	* @brief Registra un movimiento en el historial.
	* @param tipo: Tipo de movimiento a registrar.
	* @param tablero: Tablero de la partida a copiar como snapshot.
	* @param piezaActual: Pieza correspondiente al movimiento actual.
	* @param puntaje: Puntaje del jugador al momento de realizar el movimiento.
	*/
	void registrarMovimiento(
		TipoMovimiento tipo,
		Tablero& tablero,
		Pieza& piezaActual,
		int puntaje
	);
	
	/**
	* @brief Retrocede en la lista enviando el estado de movimiento anterior.
	* @return Estado de movimiento anterior al actual.
	*/
	EstadoMovimiento deshacer();
	
	/**
	* @brief Se adelanta en el historial al movimiento siguiente.
	* @return Estado de movimiento siguiente al actual.
	*/
	EstadoMovimiento rehacer();
	
	/**
	* @brief Revisa si hay movimiento anterior para deshacer el actual.
	* @return Valor booleano indicando si el movimiento se puede deshacer.
	*/
	bool puedeDeshacer() const;
	
	/**
	* @brief Revisa si hay movimiento siguiente para rehacer un movimiento.
	* @return Valor booleano indicando si el movimiento se puede rehacer.
	*/
	bool puedeRehacer() const;
	
	/**
	* @brief Muestra sin modificar el historial el movimiento actual.
	* @return Estado de movimiento actualmente en el historial
	*/
	const EstadoMovimiento& verEstadoActual() const;
	
	/**
	* @brief Envia el nodo actual al inicio del historial.
	*/
	void reiniciarReproduccion();
	
	/**
	* @brief Revisa si hay un movimiento siguiente al reproducir la partida.
	* Limita cuando la reproduccion de un partida debe detenerse.
	* @return Valor booleano indicando si se puede seguir reproduciendo.
	*/
	bool haySiguienteEnReproduccion() const;
	
	/**
	* @brief Avanza la reproduccion de una prtida con un loop.
	* @return El estado de movimiento a mostrar en la reproducción.
	*/
	EstadoMovimiento avanzarReproduccion();
	
	/**
	* @brief Revisa si el historial está vacío.
	* @return Valor booleano indicando si el historial esta vacio.
	*/
	bool estaVacio() const;
};
