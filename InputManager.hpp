/**
* @file InputManager.hpp
* @brief [MOTOR]Gestionador de eventos del jugador
* @author Stiward Araya Calderón.
* @date Creado el 07/09/2026
*/
#pragma once

#include <array>					///< std::array
#include <SFML/Graphics.hpp>		///< sf namespace

/**
* @brief Clase enum para representar todos los posibles
* eventos del jugador.
*/
enum class AccionMotor {
	IZQUIERDA,
	DERECHA,
	ARRIBA,
	ABAJO,
	CONFIRMAR,
	CANCELAR,
	PAUSA,
	HOLD,
	DESHACER,
	REHACER,
	NINGUNA
};

/**
* @brief Conoce los eventos de entrada de SFML para
* gestionar las entradas del jugador durante los distintos
* estados del juego.
*/
class InputManager {
	
private:
	static const int CANTIDAD_ACCIONES = 10;				///< Total de acciones disponibles(no se cuenta "NINGUNA")
	std::array<bool, CANTIDAD_ACCIONES> presionadoActual;	///< Acciones presionadas en el momento
	std::array<bool, CANTIDAD_ACCIONES> presionadoAnterior; ///< Acciones presionadas anteriormente
	bool solicitudCierre;									///< Flag para detectar el cierre del programa
	std::string textoIngresado; 							///< Input de texto para capturar el nombre del jugador
	bool capturandoTexto;									///< Bandera para identificar si se está ingresando texto
	
	/**
	* @brief Traduce la tecla de entrada a una acción del motor.
	* @param tecla: Tecla presionada
	* @return Accion de motor traducida
	*/
	AccionMotor traducirTecla(sf::Keyboard::Key tecla) const;
	
public:
	/**
	* @brief Constructor genérico del gestionador de entradas,
	* inicializa ambos arreglos en false y la solicitudCierre en false.
	*/
	InputManager();
	
	/**
	* @brief Copia el presionadoActual al anterior y recorre la
	* cola de eventos para actualizar el presionadoActual por las
	* entradas nuevas.
	* @param ventana: contiene la cola de eventos a recorrer.
	*/
	void actualizar(sf::RenderWindow& ventana);
	
	/**
	* @brief Revisa si una accion está actualmente presionada.
	* @return Valor booleano indicando si la acción está presionada.
	*/
	bool estaPresionado(AccionMotor accion) const;
	
	/**
	* @brief Revisa si una accion fué presionada anteriormente.
	* @return Valor booleano indicando si la acción fué presionada.
	*/
	bool fuePresionado(AccionMotor accion) const;
	
	/**
	* @brief Revisa si se solicitó el cierre de la aplicación.
	* @return Valor booleano indicando si se solicitó el cierre.
	*/
	bool seSolicitoCerrar() const;
	
	/**
	* @brief Inicia la captura de texto ingresado por el usuario.
	*/
	void iniciarCapturaDeTexto();
	
	/**
	* @brief Captura el texto ingresado por el usuario
	*/
	void detenerCapturaDeTexto();
	
	/**
	* @brief retorna el texto ingresado por el usuario
	*/
	const std::string& obtenerTextoIngresado() const;
	
	/**
	* @brief Reinicia el input de texto
	*/
	void limpiarTextoIngresado();
	
};
