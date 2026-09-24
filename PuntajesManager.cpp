#include "PuntajesManager.hpp"
#include "Ordenamiento.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

PuntajesManager::PuntajesManager(const std::string& rutaArchivo) : rutaArchivo(rutaArchivo){
	cargarDesdeArchivo();
}

void PuntajesManager::cargarDesdeArchivo() {
	std::ifstream archivo(rutaArchivo);
	
	if (!archivo.is_open()) {
		return;
	}
	
	std::string linea;
	while (std::getline(archivo, linea)) {
		std::stringstream flujoLinea(linea);
		std::string nombreLeido;
		std::string puntajeTexto;
		
		if (std::getline(flujoLinea, nombreLeido, ',') && std::getline(flujoLinea, puntajeTexto)) {
			try {
				int puntajeLeido = std::stoi(puntajeTexto);
				registros.push_back(RegistroPuntaje(nombreLeido, puntajeLeido));
			} catch (const std::exception& error) {
				std::cout << "Advertencia: línea de puntajes ignorada " << "(formato inválido): " << linea << std::endl;
			}
		}
	}
}

void PuntajesManager::guardarEnArchivo() const {
	std::ofstream archivo(rutaArchivo);
	
	if (!archivo.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo de puntajes: " + rutaArchivo);
	}
	
	for (const auto& registro : registros) {
		archivo << registro.getNombre() << "," << registro.getPuntaje() << "\n";
	}
}

bool PuntajesManager::calificaParaTop10(int puntaje) const {
	if (registros.size() < 10) {
		return true;
	}
	
	int puntajeMinimo = registros[0].getPuntaje();
	for (const auto& registro : registros) {
		if (registro.getPuntaje() < puntajeMinimo) {
			puntajeMinimo = registro.getPuntaje();
		}
	}
	
	return puntaje > puntajeMinimo;
}

void PuntajesManager::agregarPuntaje(const std::string& nombre, int puntaje) {
	registros.push_back(RegistroPuntaje(nombre, puntaje));
	
	if (registros.size() > 10) {
		Ordenamiento::ordenQuickSort(registros);
		registros.erase(registros.begin() + 10, registros.end());
	}
	
	guardarEnArchivo();
}

const std::vector<RegistroPuntaje>& PuntajesManager::obtenerTop10(TipoOrdenamiento tipo) {
	if (tipo == TipoOrdenamiento::INSERCION) {
		Ordenamiento::ordenInsercion(registros);
	} else {
		Ordenamiento::ordenQuickSort(registros);
	}
	
	return registros;
}
