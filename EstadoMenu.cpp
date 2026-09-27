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
	
	graficador.dibujarTexto("TETRIS", 220, 40, 32, sf::Color::White);
	
	for (int i = 0; i < CANTIDAD_OPCIONES_PRINCIPAL; i++) {
		sf::Color color = (i == opcionSeleccionada) ? sf::Color::Yellow : sf::Color::White;
		graficador.dibujarTexto(opciones[i], 240, 150 + i * 40, 22, color);
	}
}

void EstadoMenu::dibujarIngresoNombre(Graficador& graficador) const {
	graficador.dibujarTexto("Ingresa tu nombre:", 180, 100, 22, sf::Color::White);
	graficador.dibujarTexto(textoEnEdicion, 180, 140, 22, sf::Color::Yellow);
	
	if (!mensajeError.empty()) {
		graficador.dibujarTexto(mensajeError, 100, 200, 16, sf::Color::Red);
	}
}

void EstadoMenu::dibujarSeleccionOrden(Graficador& graficador) const {
	graficador.dibujarTexto("Elegi el algoritmo de ordenamiento:", 100, 100, 20, sf::Color::White);
	
	sf::Color colorInsercion = (opcionSeleccionada == 0) ? sf::Color::Yellow : sf::Color::White;
	sf::Color colorQuickSort = (opcionSeleccionada == 1) ? sf::Color::Yellow : sf::Color::White;
	
	graficador.dibujarTexto("Insercion  O(n^2)", 240, 160, 20, colorInsercion);
	graficador.dibujarTexto("QuickSort  O(n log n)", 240, 200, 20, colorQuickSort);
}

void EstadoMenu::dibujarTablaPuntajes(Graficador& graficador) const {
	graficador.dibujarTexto("Mejores puntajes:", 200, 30, 24, sf::Color::White);
	
	for (size_t i = 0; i < tablaMostrada.size(); i++) {
		std::string linea = std::to_string(i + 1) + ". " + tablaMostrada[i].getNombre()
			+ " - " + std::to_string(tablaMostrada[i].getPuntaje());
		graficador.dibujarTexto(linea, 150, 80 + static_cast<float>(i) * 30, 18, sf::Color::White);
	}
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
