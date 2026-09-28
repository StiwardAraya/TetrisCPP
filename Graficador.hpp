/**
* @file Graficador.hpp
* @brief Sistema de renderizado en ventana
* @author Stiward Araya Calderón
* @date Creado el 11/09/2026
*/
#pragma once

#include <SFML/Graphics.hpp>		///< sf
#include <string> 					///< std::string
#include "Pieza.hpp"				///< TipoPieza, Pieza

/**
* @brief Encargado de la ventana y de todas las primitivas de dibujo.
* Todo se dibuja sobre una resolución lógica fija (anchoLogico x altoLogico)
* que se escala y centra automáticamente sobre la ventana real, sin importar
* su tamaño, dejando franjas negras si la proporción no coincide.
*/
class Graficador {
private:
	sf::RenderWindow ventana;		///< Ventana de la App
	sf::Font fuente;				///< Fuente para los textos
	float anchoLogico;				///< Ancho del área de dibujo lógica, en pixeles lógicos
	float altoLogico;				///< Alto del área de dibujo lógica, en pixeles lógicos

	/**
	* @brief Ajusta la vista para que el área lógica ocupe el mayor espacio
	* posible de la ventana, centrada y conservando su proporción.
	*/
	void ajustarVista();

public:
	/**
	* @brief Constructor del graficador, crea la ventana y carga la fuente.
	* La ventana se crea con el mayor tamaño que quepa en el escritorio
	* conservando la proporción ancho/alto indicada.
	* @param ancho: Ancho lógico del área de dibujo, en pixeles
	* @param alto: Alto lógico del área de dibujo, en pixeles
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
	* @brief Dibuja un panel: rectángulo con relleno y borde, con un título
	* opcional centrado en su parte superior.
	* @param x: Posición horizontal de inicio del panel.
	* @param y: Posición vertical de inicio del panel.
	* @param ancho: Ancho del panel.
	* @param alto: Alto del panel.
	* @param titulo: Texto del encabezado (vacío para no dibujar título).
	*/
	void dibujarPanel(float x, float y, float ancho, float alto, const std::string& titulo = "");

	/**
	* @brief Dibuja un bloque (celda) de pieza con borde y relieve, para que
	* no se vea plano.
	* @param x: Posición horizontal de la esquina superior izquierda.
	* @param y: Posición vertical de la esquina superior izquierda.
	* @param tamanno: Lado del bloque, en pixeles.
	* @param color: Color base del bloque.
	*/
	void dibujarBloque(float x, float y, float tamanno, sf::Color color);

	/**
	* @brief Dibuja el fondo, la cuadrícula y el marco de un tablero.
	* @param x: Posición horizontal de la esquina superior izquierda.
	* @param y: Posición vertical de la esquina superior izquierda.
	* @param columnas: Cantidad de columnas del tablero.
	* @param filas: Cantidad de filas del tablero.
	* @param tamannoCelda: Lado de cada celda, en pixeles.
	*/
	void dibujarFondoTablero(float x, float y, int columnas, int filas, float tamannoCelda);

	/**
	* @brief Dibuja una pieza en su orientación inicial, centrada en el punto
	* indicado. Se usa para las vistas previas de la cola y el hold.
	* @param tipo: Tipo de pieza a dibujar.
	* @param centroX: Posición horizontal del centro de la pieza.
	* @param centroY: Posición vertical del centro de la pieza.
	* @param tamannoCelda: Lado de cada bloque, en pixeles.
	*/
	void dibujarVistaPreviaPieza(TipoPieza tipo, float centroX, float centroY, float tamannoCelda);

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
	* @brief Dibuja texto centrado horizontalmente alrededor de centroX.
	* @param texto: Texto a dibujar en la ventana
	* @param centroX: Posición horizontal del centro del texto
	* @param y: Posición vertical de inicio del texto.
	* @param tamanno: Tamaño del texto en pixeles.
	* @param color: Color del texto.
	*/
	void dibujarTextoCentrado(const std::string& texto, float centroX, float y, unsigned int tamanno, sf::Color color);

	/**
	* @brief Dibuja texto alineado a la derecha, terminando en xDerecha.
	* @param texto: Texto a dibujar en la ventana
	* @param xDerecha: Posición horizontal donde termina el texto
	* @param y: Posición vertical de inicio del texto.
	* @param tamanno: Tamaño del texto en pixeles.
	* @param color: Color del texto.
	*/
	void dibujarTextoDerecha(const std::string& texto, float xDerecha, float y, unsigned int tamanno, sf::Color color);

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
	* @brief Devuelve el color propio de cada tipo de pieza.
	* @param tipo: Tipo de pieza.
	* @return Color asociado al tipo de pieza.
	*/
	static sf::Color colorDePieza(TipoPieza tipo);

	/**
	* @brief Color de los bloques ya fijados en el tablero.
	* @return Color de los bloques fijados.
	*/
	static sf::Color colorBloqueFijado();

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

	float getAnchoLogico() const;		///< GETTER anchoLogico
	float getAltoLogico() const;		///< GETTER altoLogico
};
