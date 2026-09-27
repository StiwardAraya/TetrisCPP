#include "InputManager.hpp"

AccionMotor InputManager::traducirTecla(sf::Keyboard::Key tecla) const {
	switch(tecla) {
		case sf::Keyboard::Left:
		case sf::Keyboard::A:
			return AccionMotor::IZQUIERDA;
		
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
			return AccionMotor::DERECHA;
		
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
			return AccionMotor::ARRIBA;
		
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			return AccionMotor::ABAJO;
		
		case sf::Keyboard::E:
			return AccionMotor::CONFIRMAR;
		
		case sf::Keyboard::Escape:
			return AccionMotor::CANCELAR;
		
		case sf::Keyboard::P:
			return AccionMotor::PAUSA;
		
		case sf::Keyboard::C:
			return AccionMotor::HOLD;
		
		case sf::Keyboard::Z:
			return AccionMotor::DESHACER;
		
		case sf::Keyboard::X:
			return AccionMotor::REHACER;
		
		default:
			return AccionMotor::NINGUNA;
	}
}

InputManager::InputManager() : solicitudCierre(false) {
	presionadoActual.fill(false);
	presionadoAnterior.fill(false);
}

void InputManager::actualizar(sf::RenderWindow& ventana) {
	presionadoAnterior = presionadoActual;
	
	sf::Event evento;
	while (ventana.pollEvent(evento)) {
		if (evento.type == sf::Event::Closed) {
			solicitudCierre = true;
			
		} else if (evento.type == sf::Event::KeyPressed) {
			AccionMotor accion = traducirTecla(evento.key.code);
			if (accion != AccionMotor::NINGUNA) {
				presionadoActual[static_cast<int>(accion)] = true;
			}
			
		} else if (evento.type == sf::Event::KeyReleased) {
			AccionMotor accion = traducirTecla(evento.key.code);
			if (accion != AccionMotor::NINGUNA) {
				presionadoActual[static_cast<int>(accion)] = false;
			}
			
		} else if (evento.type == sf::Event::TextEntered && capturandoTexto) {
			if (evento.text.unicode == 8) {
				if (!textoIngresado.empty()) {
					textoIngresado.pop_back();
				}
			} else if (evento.text.unicode >= 32 && evento.text.unicode < 128) {
				textoIngresado += static_cast<char>(evento.text.unicode);
			}
		}
	}
}
bool InputManager::estaPresionado(AccionMotor accion) const {
	return presionadoActual[static_cast<int>(accion)];
}

bool InputManager::fuePresionado(AccionMotor accion) const {
	int indice = static_cast<int>(accion);
	return presionadoActual[indice] && !presionadoAnterior[indice];
}

bool InputManager::seSolicitoCerrar() const {
	return solicitudCierre;
}

void InputManager::iniciarCapturaDeTexto() {
	capturandoTexto = true;
	textoIngresado.clear();
}

void InputManager::detenerCapturaDeTexto() {
	capturandoTexto = false;
}

const std::string& InputManager::obtenerTextoIngresado() const {
	return textoIngresado;
}

void InputManager::limpiarTextoIngresado() {
	textoIngresado.clear();
}
