/**
* @file EstadoMenu.hpp
* @brief Estado del menu principal
* @author Stiward Araya Calderón
* @date Creado el 24/09/2026
*/
#pragma once

class EstadosManager;
class InputManager;
class GraficadorManager;
class EstadoJugando;

#include "PuntajesManager.hpp"
#include "Estado.hpp"

/**
* @brief enum para el control de la pantalla mostrada.
*/
enum class PantallaMenu {
	PRINCIPAL,
	INGRESO_NOMBRE,
	SELECCION_ORDEN,
	TABLA_PUNTAJES
};

/**
* @brief Logica del sistema a ejecutarse mientras el jugador se encuentre
* en el menú principal, hereda de "Estado".
*/
class EstadoMenu : public Estado {
private:
	static const int CANTIDAD_OPCIONES_PRINCIPAL = 3;		///< Cantidad de opciones del menú principal
	static const int LONGITUD_MAXIMA_NOMBRE = 15;			///< Maximo de caracteres del nombre
	
	EstadosManager& estadosManager;							///< Controlador de la maquina de estados del juego
	PuntajesManager puntajesManager;						///< Controlador de puntajes
	PantallaMenu pantallaActual;							///< Pantalla del menu actualmente visible
	int opcionSeleccionada; 								///< Control de la opcion del menu seleccionada
	std::string nombreJugador;								///< Nombre del jugador ingreso previo a jugar
	std::string mensajeError;								///< Mensaje de error a mostrar en casos de fallo
	std::string textoEnEdicion;								///< Texto actualmente siendo editado
	std::vector<RegistroPuntaje> tablaMostrada;				///< Tabla de puntajes
	
	/**
	* @brief Verifica si el nombre ingresado por el jugador es valido.
	* @param nombre: Nombre ingresado por el jugador.
	* @return Valor booleano indicando si el nombre es valido
	*/
	bool nombreEsValido(const std::string& nombre) const;
	
	/**
	* @brief Maneja las entradas del jugador en el menu principal
	*/
	void manejarEntradaPrincipal(InputManager& entradas);
	
	/**
	* @brief Maneja las entradas del jugador en el ingreso de nombres
	*/
	void manejarEntradaIngresoNombre(InputManager& entradas);
	
	/**
	* @brief Maneja las entradas del jugador en la seleccion de ordenamiento
	*/
	void manejarEntradaSeleccionOrden(InputManager& entradas);
	
	/**
	* @brief Maneja las entradas del jugador en la tabla de puntajes
	*/
	void manejarEntradaTablaPuntajes(InputManager& entradas);
	
	/**
	* @brief Grafica el menu principal.
	*/
	void dibujarPrincipal(Graficador& graficador) const;
	
	/**
	* @brief Grafica el ingreso del nombre del jugador.
	*/
	void dibujarIngresoNombre(Graficador& graficador) const;
	
	/**
	* @brief Grafica la vista de seleccion de ordenamiento
	*/
	void dibujarSeleccionOrden(Graficador& graficador) const;
	
	/**
	* @brief Grafica la tabla de puntajes
	*/
	void dibujarTablaPuntajes(Graficador& graficador) const;
	
public:
	/**
	* @brief Constructor del estado, recibe el manager de estados y la ruta
	* al archivo de puntajes.
	*/
	EstadoMenu(EstadosManager& estadosManager, const std::string& rutaArchivoPuntajes);
	
	/**
	* @brief Sobreescritura del método de Estado, maneja las entradas del jugador
	* en el estado actual.
	*/
	void manejarEntrada(InputManager& entradas) override;
	
	/**
	* @brief Sobreescritura del método de Estado, actualiza la información
	* correspondiente al menú.
	*/
	void actualizar(float deltaTime) override;
	
	/**
	* @brief Sobreescritura del método de Estado, grafica en la ventana
	* el estado actual según la ventana actual.
	*/
	void dibujar(Graficador& graficador) override;
};
