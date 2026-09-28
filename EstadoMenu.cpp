#include "EstadoMenu.hpp"
#include "InputManager.hpp"
#include "Graficador.hpp"
#include "EstadosManager.hpp"
#include "EstadoJugando.hpp"
#include <cctype>

EstadoMenu::EstadoMenu(EstadosManager& estadosManager, const std::string& rutaArchivoPuntajes)
	: estadosManager(estadosManager),
	puntajesManager(rutaArchivoPuntajes),
	pantallaActual(PantallaMenu::PRINCIPAL),
	opcionSeleccionada(0) {
}

bool EstadoMenu::nombreEsValido(const std::string& nombre) const {
	if (nombre.empty() || static_cast<int>(nombre.size()) > LONGITUD_MAXIMA_NOMBRE) {
		return false;
	}
	
	for (char caracter : nombre) {
		if (!std::isalpha(static_cast<unsigned char>(caracter))) {
			return false;
		}
	}
	
	return true;
}

void EstadoMenu::manejarEntradaPrincipal(InputManager& entradas) {
	if (entradas.fuePresionado(AccionMotor::ABAJO)) {
		opcionSeleccionada = (opcionSeleccionada + 1) % CANTIDAD_OPCIONES_PRINCIPAL;
	}
	if (entradas.fuePresionado(AccionMotor::ARRIBA)) {
		opcionSeleccionada = (opcionSeleccionada - 1 + CANTIDAD_OPCIONES_PRINCIPAL) % CANTIDAD_OPCIONES_PRINCIPAL;
	}
	
	if (entradas.fuePresionado(AccionMotor::CONFIRMAR)) {
		if (opcionSeleccionada == 0) {
			mensajeError.clear();
			nombreJugador.clear();
			textoEnEdicion.clear();
			entradas.limpiarTextoIngresado();
			entradas.iniciarCapturaDeTexto();
			pantallaActual = PantallaMenu::INGRESO_NOMBRE;
			
		} else if (opcionSeleccionada == 1) {
			opcionSeleccionada = 0;
			pantallaActual = PantallaMenu::SELECCION_ORDEN;
			
		} else {
			estadosManager.desapilarEstado();
		}
	}
}

void EstadoMenu::manejarEntradaIngresoNombre(InputManager& entradas) {
	textoEnEdicion = entradas.obtenerTextoIngresado();
	
	if (entradas.fuePresionado(AccionMotor::CANCELAR)) {
		entradas.detenerCapturaDeTexto();
		entradas.limpiarTextoIngresado();
		pantallaActual = PantallaMenu::PRINCIPAL;
		return;
	}
	
	if (entradas.fuePresionado(AccionMotor::CONFIRMAR)) {
		if (nombreEsValido(textoEnEdicion)) {
			nombreJugador = textoEnEdicion;
			mensajeError.clear();
			entradas.detenerCapturaDeTexto();
			
			estadosManager.apilarEstado(new EstadoJugando(estadosManager, nombreJugador, puntajesManager));
			
		} else {
			mensajeError = "El nombre solo puede tener letras (max. "
				+ std::to_string(LONGITUD_MAXIMA_NOMBRE) + ").";
			entradas.limpiarTextoIngresado();
		}
	}
}

void EstadoMenu::manejarEntradaSeleccionOrden(InputManager& entradas) {
	const int CANTIDAD_OPCIONES_ORDEN = 2;
	
	if (entradas.fuePresionado(AccionMotor::ABAJO) || entradas.fuePresionado(AccionMotor::ARRIBA)) {
		opcionSeleccionada = (opcionSeleccionada + 1) % CANTIDAD_OPCIONES_ORDEN;
	}
	
	if (entradas.fuePresionado(AccionMotor::CONFIRMAR)) {
		TipoOrdenamiento tipoElegido = (opcionSeleccionada == 0)
			? TipoOrdenamiento::INSERCION
			: TipoOrdenamiento::QUICKSORT;
		
		tablaMostrada = puntajesManager.obtenerTop10(tipoElegido);
		pantallaActual = PantallaMenu::TABLA_PUNTAJES;
	}
	
	if (entradas.fuePresionado(AccionMotor::CANCELAR)) {
		opcionSeleccionada = 0;
		pantallaActual = PantallaMenu::PRINCIPAL;
	}
}

void EstadoMenu::manejarEntradaTablaPuntajes(InputManager& entradas) {
	if (entradas.fuePresionado(AccionMotor::CANCELAR)) {
		pantallaActual = PantallaMenu::PRINCIPAL;
	}
}

void EstadoMenu::dibujarPrincipal(Graficador& graficador) const {
	const std::string opciones[CANTIDAD_OPCIONES_PRINCIPAL] = {"Jugar", "Ver puntajes", "Salir"};
	
	const float CENTRO_X = graficador.getAnchoLogico() / 2.0f;
	const TipoPieza TIPOS_TITULO[] = {
		TipoPieza::T, TipoPieza::I, TipoPieza::Z, TipoPieza::L, TipoPieza::O, TipoPieza::S, TipoPieza::J
	};

	for (int i = 0; i < 7; i++) {
		graficador.dibujarVistaPreviaPieza(TIPOS_TITULO[i], CENTRO_X - 330.0f + i * 110.0f, 90.0f, 22.0f);
	}
	graficador.dibujarTextoCentrado("TETRIS", CENTRO_X, 150.0f, 96, sf::Color::White);

	graficador.dibujarPanel(CENTRO_X - 170.0f, 330.0f, 340.0f, 210.0f);
	for (int i = 0; i < CANTIDAD_OPCIONES_PRINCIPAL; i++) {
		bool seleccionada = (i == opcionSeleccionada);
		sf::Color color = seleccionada ? sf::Color(245, 215, 0) : sf::Color::White;
		std::string texto = seleccionada ? "> " + opciones[i] + " <" : opciones[i];
		graficador.dibujarTextoCentrado(texto, CENTRO_X, 360.0f + i * 55.0f, 34, color);
	}

	graficador.dibujarTextoCentrado("Flechas: elegir     E: confirmar", CENTRO_X, 620.0f, 18, sf::Color(150, 150, 190));
}

void EstadoMenu::dibujarIngresoNombre(Graficador& graficador) const {
	const float CENTRO_X = graficador.getAnchoLogico() / 2.0f;

	graficador.dibujarTextoCentrado("Ingresa tu nombre", CENTRO_X, 220.0f, 40, sf::Color::White);
	graficador.dibujarPanel(CENTRO_X - 220.0f, 300.0f, 440.0f, 70.0f);
	graficador.dibujarTextoCentrado(textoEnEdicion + "_", CENTRO_X, 314.0f, 36, sf::Color(245, 215, 0));

	if (!mensajeError.empty()) {
		graficador.dibujarTextoCentrado(mensajeError, CENTRO_X, 400.0f, 20, sf::Color(235, 55, 55));
	}

	graficador.dibujarTextoCentrado("E: comenzar     Esc: volver", CENTRO_X, 620.0f, 18, sf::Color(150, 150, 190));
}

void EstadoMenu::dibujarSeleccionOrden(Graficador& graficador) const {
	const float CENTRO_X = graficador.getAnchoLogico() / 2.0f;

	graficador.dibujarTextoCentrado("Algoritmo de ordenamiento", CENTRO_X, 200.0f, 40, sf::Color::White);

	const std::string opciones[] = {"Insercion  O(n^2)", "QuickSort  O(n log n)"};
	graficador.dibujarPanel(CENTRO_X - 230.0f, 290.0f, 460.0f, 150.0f);
	for (int i = 0; i < 2; i++) {
		bool seleccionada = (i == opcionSeleccionada);
		sf::Color color = seleccionada ? sf::Color(245, 215, 0) : sf::Color::White;
		std::string texto = seleccionada ? "> " + opciones[i] + " <" : opciones[i];
		graficador.dibujarTextoCentrado(texto, CENTRO_X, 320.0f + i * 55.0f, 30, color);
	}

	graficador.dibujarTextoCentrado("Flechas: elegir     E: confirmar     Esc: volver", CENTRO_X, 620.0f, 18,
									sf::Color(150, 150, 190));
}

void EstadoMenu::dibujarTablaPuntajes(Graficador& graficador) const {
	const float CENTRO_X = graficador.getAnchoLogico() / 2.0f;
	const float ANCHO_PANEL = 480.0f;
	const float X_PANEL = CENTRO_X - ANCHO_PANEL / 2.0f;

	graficador.dibujarTextoCentrado("Mejores puntajes", CENTRO_X, 40.0f, 44, sf::Color::White);
	graficador.dibujarPanel(X_PANEL, 120.0f, ANCHO_PANEL, 460.0f);

	if (tablaMostrada.empty()) {
		graficador.dibujarTextoCentrado("Aun no hay puntajes", CENTRO_X, 320.0f, 24, sf::Color(150, 150, 190));
	}

	for (size_t i = 0; i < tablaMostrada.size(); i++) {
		float y = 140.0f + static_cast<float>(i) * 43.0f;
		sf::Color color = (i == 0) ? sf::Color(245, 215, 0) : sf::Color::White;
		graficador.dibujarTextoDerecha(std::to_string(i + 1) + ".", X_PANEL + 70.0f, y, 26, color);
		graficador.dibujarTexto(tablaMostrada[i].getNombre(), X_PANEL + 90.0f, y, 26, color);
		graficador.dibujarTextoDerecha(std::to_string(tablaMostrada[i].getPuntaje()), X_PANEL + ANCHO_PANEL - 30.0f,
									   y, 26, color);
	}

	graficador.dibujarTextoCentrado("Esc: volver", CENTRO_X, 620.0f, 18, sf::Color(150, 150, 190));
}

void EstadoMenu::alEntrar() {
	pantallaActual = PantallaMenu::PRINCIPAL;
	opcionSeleccionada = 0;
	mensajeError.clear();
	textoEnEdicion.clear();
}

void EstadoMenu::manejarEntrada(InputManager& entradas) {
	switch (pantallaActual) {
	case PantallaMenu::PRINCIPAL:
		manejarEntradaPrincipal(entradas);
	break;
	case PantallaMenu::INGRESO_NOMBRE:
		manejarEntradaIngresoNombre(entradas);
	break;
	case PantallaMenu::SELECCION_ORDEN:
		manejarEntradaSeleccionOrden(entradas);
	break;
	case PantallaMenu::TABLA_PUNTAJES:
		manejarEntradaTablaPuntajes(entradas);
	break;
	}
}

void EstadoMenu::actualizar(float deltaTime) {
}

void EstadoMenu::dibujar(Graficador& graficador) {
	switch (pantallaActual) {
	case PantallaMenu::PRINCIPAL:
		dibujarPrincipal(graficador);
	break;
	case PantallaMenu::INGRESO_NOMBRE:
		dibujarIngresoNombre(graficador);
	break;
	case PantallaMenu::SELECCION_ORDEN:
		dibujarSeleccionOrden(graficador);
	break;
	case PantallaMenu::TABLA_PUNTAJES:
		dibujarTablaPuntajes(graficador);
	break;
	}
}
