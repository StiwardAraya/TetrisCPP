#include "Ordenamiento.hpp"
#include <utility>

void Ordenamiento::ordenInsercion(std::vector<RegistroPuntaje>& puntajes) {
	for (size_t i = 1; i < puntajes.size(); i++) {
		RegistroPuntaje actual = puntajes[i];
		size_t j = i;

		while (j > 0 && puntajes[j - 1].getPuntaje() < actual.getPuntaje()) {
			puntajes[j] = puntajes[j - 1];
			j--;
		}
		
		puntajes[j] = actual;
	}
}

static int particionar(std::vector<RegistroPuntaje>& puntajes, int bajo, int alto) {
	RegistroPuntaje pivote = puntajes[alto];
	int i = bajo - 1;
	
	for (int j = bajo; j < alto; j++) {
		if (puntajes[j].getPuntaje() > pivote.getPuntaje()) {
			i++;
			std::swap(puntajes[i], puntajes[j]);
		}
	}
	
	std::swap(puntajes[i + 1], puntajes[alto]);
	return i + 1;
}

static void quickSort(std::vector<RegistroPuntaje>& puntajes, int bajo, int alto) {
	if (bajo < alto) {
		int pivote = particionar(puntajes, bajo, alto);
		
		quickSort(puntajes, bajo, pivote - 1);
		quickSort(puntajes, pivote + 1, alto);
	}
}

void Ordenamiento::ordenQuickSort(std::vector<RegistroPuntaje>& puntajes) {
	if (!puntajes.empty()) {
		quickSort(puntajes, 0, static_cast<int>(puntajes.size()) - 1);
	}
}
