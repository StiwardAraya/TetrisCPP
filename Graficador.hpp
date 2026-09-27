/**
* @file Graficador.hpp
* @brief Sistema de renderizado en ventana
* @author Stiward Araya Calderón
* @date Creado el 11/09/2026
*/
#pragma once

#include <SFML/Graphics.hpp>		///< sf
#include <string> 					///< std::string

class Graficador {
private:
	sf::RenderWindow ventana;		///< Ventana de la App
	sf::Font fuente;				///< Fuente para los textos
	
public:
	/**
	* @brief Constructor del graficador, crea la ventana y carga la fuente
	* @param ancho: Ancho de la ventana en pixeles
	* @param alto: Alto de la ventana en pixeles
	* @param titulo: Titulo para la aventana
	*/
	Graficador(unsigned int ancho, unsigned int alto, const std::string& titulo);

	/**
	* @brief Se llama al inicio de cada frame, inicia la ventana principal 
	* antes de dibujar en ella.
	*/
	void iniciarFrame();

	/**
	* @brief Se llama al final de cada frame, limpia la ventana antes de iniciar
	* el siguiente frame.
	*/
	void finalizarFrame();

	/**
	* @brief Dibuja un rectangulo en la ventana principal empezando en las coordenadas x e y
	* indicadas hasta un ancho y un alto, usando el color también indicado.
	* @param x: Posición horizontal de inicio del rectangulo.
	* @param y: Posición vertical de inicio del rectangulo.
	* @param ancho: Posición horizontal de final del rectángulo.
	* @param alto: Posición vertical de final del rectángulo.
	* @param color: Color de relleno del rectángulo
	*/
	void dibujarRectangulo(float x, float y, float ancho, float alto, sf::Color color);

	/**
	* @brief Dibuja texto en la ventana principal iniciando en las posiciones x e y
	* usando el color también indicado.
	* @param texto: Texto a dibujar en la ventana
	* @param x: Posición horizontal de inicio del texto
	* @param y: Posición vertical de inicio del texto.
	* @param tamanno: Tamaño del texto en pixeles.
	* @param color: Color del texto.
	*/
	void dibujarTexto(const std::string& texto, float x, float y, unsigned int tamanno, sf::Color color);

	/**
	* @brief Dibuja una linea en la ventana principal desde las posiciones x1 e y1 hasta
	* las posiciones x2 e y2, usando el color indicado.
	* @param x1: Posición horizontal de inicio de la linea.
	* @param y1: Posición vertical de inicio de la linea.
	* @param x2: Posición horizontal de final de la linea.
	* @param y2: Posición vertical de final de la linea.
	* @param color: Color de la linea.
	*/
	void dibujarLinea(float x1, float y1, float x2, float y2, sf::Color color);

	/**
	* @brief Devuelve una referencia a la ventana principal, otras clases la necesitan
	* para detectar y operar sobre la misma.
	* @return Instancia de la ventana principal.
	*/
	sf::RenderWindow& obtenerVentana();

	/**
	* @brief Revisa si la ventana está abierta y disponible.
	* @return Valor booleano indicando si la ventana está abierta.
	*/
	bool estaAbierta() const;
};
