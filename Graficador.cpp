#include "Graficador.hpp"
#include <iostream>
#include <algorithm>
#include <climits>

namespace {
	const sf::Color COLOR_FONDO(12, 12, 24);				///< Fondo general de la ventana
	const sf::Color COLOR_FONDO_PANEL(24, 24, 44);			///< Relleno de los paneles
	const sf::Color COLOR_BORDE_PANEL(90, 90, 140);			///< Borde de los paneles y tablero
	const sf::Color COLOR_FONDO_TABLERO(6, 6, 14);			///< Fondo del tablero
	const sf::Color COLOR_CUADRICULA(32, 32, 52);			///< Líneas de la cuadrícula

	/**
	* @brief Multiplica cada canal del color por un factor, limitando a 255.
	*/
	sf::Color escalarColor(sf::Color color, float factor) {
		auto canal = [factor](sf::Uint8 valor) {
			return static_cast<sf::Uint8>(std::min(255.0f, valor * factor));
		};
		return sf::Color(canal(color.r), canal(color.g), canal(color.b), color.a);
	}

	/**
	* @brief Mezcla el color con blanco en la proporción indicada.
	*/
	sf::Color aclararColor(sf::Color color, float proporcion) {
		auto canal = [proporcion](sf::Uint8 valor) {
			return static_cast<sf::Uint8>(valor + (255 - valor) * proporcion);
		};
		return sf::Color(canal(color.r), canal(color.g), canal(color.b), color.a);
	}
}

Graficador::Graficador(unsigned int ancho, unsigned int alto, const std::string& titulo)
	: anchoLogico(static_cast<float>(ancho)), altoLogico(static_cast<float>(alto)) {

	sf::VideoMode escritorio = sf::VideoMode::getDesktopMode();
	float escala = std::min(escritorio.width * 0.90f / anchoLogico,
							escritorio.height * 0.85f / altoLogico);
	escala = std::max(escala, 0.5f);

	unsigned int anchoVentana = static_cast<unsigned int>(anchoLogico * escala);
	unsigned int altoVentana = static_cast<unsigned int>(altoLogico * escala);

	ventana.create(sf::VideoMode(anchoVentana, altoVentana), titulo);
	ventana.setPosition(sf::Vector2i(
		(static_cast<int>(escritorio.width) - static_cast<int>(anchoVentana)) / 2,
		(static_cast<int>(escritorio.height) - static_cast<int>(altoVentana)) / 2 - 20));
	ajustarVista();

	if(!fuente.loadFromFile("assets/fonts/departure.otf")) {
		std::cerr << "Advertencia: no se pudo cargar la fuente. El texto no se mostrará correctamente." << std::endl;
	}
}

void Graficador::ajustarVista() {
	sf::Vector2u tamannoVentana = ventana.getSize();
	if (tamannoVentana.x == 0 || tamannoVentana.y == 0) {
		return;
	}

	float proporcionVentana = static_cast<float>(tamannoVentana.x) / tamannoVentana.y;
	float proporcionLogica = anchoLogico / altoLogico;

	sf::FloatRect areaVisible(0.0f, 0.0f, 1.0f, 1.0f);
	if (proporcionVentana > proporcionLogica) {
		areaVisible.width = proporcionLogica / proporcionVentana;
		areaVisible.left = (1.0f - areaVisible.width) / 2.0f;
	} else {
		areaVisible.height = proporcionVentana / proporcionLogica;
		areaVisible.top = (1.0f - areaVisible.height) / 2.0f;
	}

	sf::View vista(sf::FloatRect(0.0f, 0.0f, anchoLogico, altoLogico));
	vista.setViewport(areaVisible);
	ventana.setView(vista);
}

void Graficador::iniciarFrame() {
	ajustarVista();
	ventana.clear(sf::Color::Black);
	dibujarRectangulo(0.0f, 0.0f, anchoLogico, altoLogico, COLOR_FONDO);
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

void Graficador::dibujarPanel(float x, float y, float ancho, float alto, const std::string& titulo) {
	sf::RectangleShape panel(sf::Vector2f(ancho, alto));
	panel.setPosition(x, y);
	panel.setFillColor(COLOR_FONDO_PANEL);
	panel.setOutlineColor(COLOR_BORDE_PANEL);
	panel.setOutlineThickness(3.0f);
	ventana.draw(panel);

	if (!titulo.empty()) {
		dibujarTextoCentrado(titulo, x + ancho / 2.0f, y + 10.0f, 22, sf::Color(200, 200, 230));
	}
}

void Graficador::dibujarBloque(float x, float y, float tamanno, sf::Color color) {
	const float BORDE = std::max(1.0f, tamanno * 0.07f);
	const float RELIEVE = tamanno * 0.14f;

	// Borde oscuro exterior
	dibujarRectangulo(x, y, tamanno, tamanno, escalarColor(color, 0.35f));

	// Cuerpo, con sombra abajo/derecha y brillo arriba/izquierda
	float xi = x + BORDE;
	float yi = y + BORDE;
	float lado = tamanno - 2.0f * BORDE;
	dibujarRectangulo(xi, yi, lado, lado, escalarColor(color, 0.70f));
	dibujarRectangulo(xi, yi, lado - RELIEVE, lado - RELIEVE, aclararColor(color, 0.45f));
	dibujarRectangulo(xi + RELIEVE, yi + RELIEVE, lado - 2.0f * RELIEVE, lado - 2.0f * RELIEVE, color);
}

void Graficador::dibujarFondoTablero(float x, float y, int columnas, int filas, float tamannoCelda) {
	const float ANCHO = columnas * tamannoCelda;
	const float ALTO = filas * tamannoCelda;

	sf::RectangleShape marco(sf::Vector2f(ANCHO, ALTO));
	marco.setPosition(x, y);
	marco.setFillColor(COLOR_FONDO_TABLERO);
	marco.setOutlineColor(COLOR_BORDE_PANEL);
	marco.setOutlineThickness(4.0f);
	ventana.draw(marco);

	for (int columna = 1; columna < columnas; columna++) {
		float xLinea = x + columna * tamannoCelda;
		dibujarLinea(xLinea, y, xLinea, y + ALTO, COLOR_CUADRICULA);
	}
	for (int fila = 1; fila < filas; fila++) {
		float yLinea = y + fila * tamannoCelda;
		dibujarLinea(x, yLinea, x + ANCHO, yLinea, COLOR_CUADRICULA);
	}
}

void Graficador::dibujarVistaPreviaPieza(TipoPieza tipo, float centroX, float centroY, float tamannoCelda) {
	Pieza pieza(tipo);
	std::vector<std::pair<int, int>> celdas = pieza.obtenerCeldasEn(0, 0, 0);

	int filaMin = INT_MAX, filaMax = INT_MIN, columnaMin = INT_MAX, columnaMax = INT_MIN;
	for (const auto& celda : celdas) {
		filaMin = std::min(filaMin, celda.first);
		filaMax = std::max(filaMax, celda.first);
		columnaMin = std::min(columnaMin, celda.second);
		columnaMax = std::max(columnaMax, celda.second);
	}

	float anchoPieza = (columnaMax - columnaMin + 1) * tamannoCelda;
	float altoPieza = (filaMax - filaMin + 1) * tamannoCelda;
	float origenX = centroX - anchoPieza / 2.0f;
	float origenY = centroY - altoPieza / 2.0f;

	sf::Color color = colorDePieza(tipo);
	for (const auto& celda : celdas) {
		dibujarBloque(origenX + (celda.second - columnaMin) * tamannoCelda,
					  origenY + (celda.first - filaMin) * tamannoCelda,
					  tamannoCelda, color);
	}
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

void Graficador::dibujarTextoCentrado(const std::string& texto, float centroX, float y, unsigned int tamanno, sf::Color color) {
	sf::Text textoSFML;
	textoSFML.setFont(fuente);
	textoSFML.setString(texto);
	textoSFML.setCharacterSize(tamanno);
	textoSFML.setFillColor(color);

	sf::FloatRect limites = textoSFML.getLocalBounds();
	textoSFML.setPosition(static_cast<float>(static_cast<int>(centroX - limites.left - limites.width / 2.0f)), y);

	ventana.draw(textoSFML);
}

void Graficador::dibujarTextoDerecha(const std::string& texto, float xDerecha, float y, unsigned int tamanno, sf::Color color) {
	sf::Text textoSFML;
	textoSFML.setFont(fuente);
	textoSFML.setString(texto);
	textoSFML.setCharacterSize(tamanno);
	textoSFML.setFillColor(color);

	sf::FloatRect limites = textoSFML.getLocalBounds();
	textoSFML.setPosition(static_cast<float>(static_cast<int>(xDerecha - limites.left - limites.width)), y);

	ventana.draw(textoSFML);
}

void Graficador::dibujarLinea(float x1, float y1, float x2, float y2, sf::Color color) {
	sf::Vertex linea[] = {
		sf::Vertex(sf::Vector2f(x1, y1), color),
		sf::Vertex(sf::Vector2f(x2, y2), color)
	};

	ventana.draw(linea, 2, sf::Lines);
}

sf::Color Graficador::colorDePieza(TipoPieza tipo) {
	switch (tipo) {
	case TipoPieza::I: return sf::Color(0, 220, 235);		// Cian
	case TipoPieza::O: return sf::Color(245, 215, 0);		// Amarillo
	case TipoPieza::T: return sf::Color(170, 70, 225);		// Morado
	case TipoPieza::S: return sf::Color(60, 205, 75);		// Verde
	case TipoPieza::Z: return sf::Color(235, 55, 55);		// Rojo
	case TipoPieza::J: return sf::Color(235, 90, 190);		// Rosa
	case TipoPieza::L: return sf::Color(250, 145, 25);		// Naranja
	}
	return sf::Color::White;
}

sf::Color Graficador::colorBloqueFijado() {
	return sf::Color(55, 95, 210);							// Azul
}

sf::RenderWindow& Graficador::obtenerVentana() {
	return ventana;
}

bool Graficador::estaAbierta() const {
	return ventana.isOpen();
}

float Graficador::getAnchoLogico() const {
	return anchoLogico;
}

float Graficador::getAltoLogico() const {
	return altoLogico;
}
