#include <SFML/Graphics.hpp>
#include "Graficador.hpp"

using namespace sf;

int main(int argc, char *argv[]){
	Graficador graficador(600, 400, "Pruebas");
	while (graficador.estaAbierta()) {
		sf::Event evento;
		while (graficador.obtenerVentana().pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				graficador.obtenerVentana().close();
			}
		}
		
		graficador.iniciarFrame();
		graficador.dibujarRectangulo(50, 50, 100, 100, sf::Color::Green);
		graficador.dibujarTexto("Prueba Graficador", 50, 170, 24, sf::Color::White);
		graficador.dibujarLinea(50, 220, 550, 220, sf::Color::Red);
		graficador.finalizarFrame();
	}
	return 0;
}

