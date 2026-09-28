#include <SFML/Graphics.hpp>
#include "Graficador.hpp"
#include "Aplicacion.hpp"

using namespace sf;

int main(int argc, char *argv[]){
	Aplicacion aplicacion(960, 720, "Tetris", "puntajes.txt");
	aplicacion.ejecutar();
	return 0;
}

