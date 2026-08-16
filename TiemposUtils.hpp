/**
* @file TiemposUtils.hpp
* @brief Utilidad para documentación de tiempos de ejecución.
* @author Stiward Araya Calderón
* @date Creado el 15/8/2026
*/
#pragma once

#include <vector> 		///< std::vector

/**
* @brief Conjunto de funciones estáticas para medir y documentar tiempos
* de ejecución.
*/
namespace TiemposUtils{
	
	/**
	* @brief Estructura para encapsular el resultado de un test.
	*/
	struct Resultado{
		int n;						///< Tamaño de la entrada
		double tiempoPromedioMS;	///< Tiempo promedio obtenido
	};
	
	/**
	* @brief Genera una progresión exponencial con base 10 aumentando su exponente dentro de un rango.
	* @return Vector con los valores resultado de las potencias
	*/
	inline std::vector<int> progresionExponencial(int potenciaInicial, int potenciaFinal, int base = 10){
		
	}
};
