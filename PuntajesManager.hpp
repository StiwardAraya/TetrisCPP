/**
* @file PuntajesManager.hpp
* @brief Manejador del sistema de puntajes
* @author Stiward Araya Calderón
* @date Creado el 19/09/2026
*/
#pragma once

#include <vector> 				///< std::vector
#include <string>				///< std::string
#include "RegistroPuntaje.hpp"	///< RegistroPuntaje

/**
* @brief enum class para clasificar los tipos de ordenamientos disponibles
*/
enum class TipoOrdenamiento {
	INSERCION,
	QUICKSORT
};

/**
* @brief Objeto manejador de los puntajes de los jugadores.
*/
class PuntajesManager {
private:
	std::vector<RegistroPuntaje> registros;			///< Arreglo con los registros de los puntajes
	std::string rutaArchivo;						///< Ruta al archivo de registros
	
	/**
	* @brief Carga en el arreglo de registros los registros guardados
	* en el archivo ubicado en la ruta correspondiente.
	*/
	void cargarDesdeArchivo();
	
	/**
	* @brief Actualiza el archivo de persistencia con el estado actual
	* de los registros de puntajes.
	*/
	void guardarEnArchivo() const;
	
public:
	
	/**
	* @brief Constructor genérico, almacena la ruta del archivo.
	* @param rutaArchivo: ruta del archivo correspondiente.
	*/
	PuntajesManager(const std::string& rutaArchivo);
	
	/**
	* @brief Revisa si un puntaje se encuentra entre los 10 más altos.
	* @param puntaje: Puntaje a calificar para el top 10.
	* @return Valor booleano indicando si el puntaje califica o no.
	*/
	bool calificaParaTop10(int puntaje) const;
	
	/**
	* @brief Agrega al arreglo de puntajes un regitro nuevo.
	* @param nombre: Nombre del jugador con el puntaje nuevo.
	* @param puntaje: Puntaje nuevo a guardar.
	*/
	void agregarPuntaje(const std::string& nombre, int puntaje);
	
	/**
	* @brief Retorna el top 10 del arreglo de puntajes.
	* @param tipo: Tipo de ordenamiento a utilizar para ordenar los puntajes.
	* @return Arreglo ordenado con los 10 mejores puntajes.
	*/
	const std::vector<RegistroPuntaje>& obtenerTop10(TipoOrdenamiento tipo);
	
};
