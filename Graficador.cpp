#include "Graficador.hpp"
#include <iostream>

Graficador::Graficador(unsigned int ancho, unsigned int alto, const std::string& titulo) {
	ventana.create(sf::VideoMode(ancho, alto), titulo);
	if(!fuente.loadFromFile("assets/fonts/departure.otf")) {
		std::cerr << "Advertencia: no se pudo cargar la fuente. El texto no se mostrará correctamente." << std::endl;
	}
}

void Graficador::iniciarFrame() {
    ventana.clear(sf::Color::Black);
}
 
void Graficador::finalizarFrame() {
    ventana.display();
}

void Graficador::dibujarRectangulo(float x, float y, float ancho, float alto, sf::Color color) {
	sf::RectangleShape rectangulo(sf::Vector2f(ancho, alto));
	rectangulo.setPosition(x, y);
	rectangulo.setFillColor(color);
	
	ventana.draw(rectangulo);
}

void Graficador::dibujarTexto(const std::string& texto, float x, float y, unsigned int tamanno, sf::Color color) {
	sf::Text textoSFML;
	textoSFML.setFont(fuente);
	textoSFML.setString(texto);
	textoSFML.setCharacterSize(tamanno);
	textoSFML.setFillColor(color);
	textoSFML.setPosition(x, y);
	
	ventana.draw(textoSFML);
}

void Graficador::dibujarLinea(float x1, float y1, float x2, float y2, sf::Color color) {
	sf::Vertex linea[] = {
		sf::Vertex(sf::Vector2f(x1, y1), color),
		sf::Vertex(sf::Vector2f(x2, y2), color)
	};
	
	ventana.draw(linea, 2, sf::Lines);
}

sf::RenderWindow& Graficador::obtenerVentana() {
	return ventana;
}

bool Graficador::estaAbierta() const {
	return ventana.isOpen();
}
