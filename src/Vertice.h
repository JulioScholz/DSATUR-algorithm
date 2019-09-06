#pragma once
#include "Cabeçalho.h"
class Vertice
{
private:
	int id; /*Identificador do vértice armazenado no nó. */
	int cor;
	int satur_grau;
	int grau;
	bool tem_cor;
	list <Vertice*> adjacentes;
	list <int> cores_adjacentes;
public:
	Vertice();
	Vertice(int id);
	~Vertice();

	const int get_id()const { return id; }
	void set_cor(const int cor) { this->cor = cor; tem_cor = true;
	}
	const int get_cor()const { return cor; }
	//when an adjacent vertex receives a color, the saturation of this.vertex increases 
	void atualiza_satur_grau() {satur_grau++;}
	const int get_satur_grau() const {return satur_grau;}

	/*TRUE para incrementar o grau, FALSE para reduzir o grau*/
	void atualiza_grau(bool op);

	const int get_grau() const {return grau;}
	const bool get_tem_cor() const {return tem_cor;}
	void add_adjacente(Vertice* v);

	void atualiza_adjacentes(int color);
	list <Vertice*> get_lista_adjacentes() {
		return adjacentes;
	}
	list <int> get_lista_cores_adjacentes() {
		return cores_adjacentes;
	}
};

 
