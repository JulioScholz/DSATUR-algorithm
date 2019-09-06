#include "Vertice.h"



Vertice::Vertice()
{
	id = -1;
	cor = -1;
	satur_grau = -1;
	grau = -1;
	tem_cor = false;
}

Vertice::Vertice(int id)
{
	this->id = id;
	cor = -1;
	satur_grau = 0;
	grau = 0;
	tem_cor = false;
}


Vertice::~Vertice()
{
}

void Vertice::atualiza_grau(bool op)
{
		if (op)
			grau++;
		else
			grau--;
}

void Vertice::add_adjacente(Vertice* v)
{

	for (list<Vertice*>::iterator it_adj = adjacentes.begin(); it_adj != adjacentes.end(); ++it_adj) {
		if ((*it_adj)->get_id() == v->get_id()) {
			return;
		}//Se o adjacente a tiver cor ele nao precisa mais ser computado
	}
	adjacentes.push_back(v);
	//checa se existem vertices duplicados, caso exista um deles é removido;
	atualiza_grau(true);
}

void Vertice::atualiza_adjacentes(int cor) {
		//saturation degree is equal the number of >different< colors of the adjacent vertexes
		//checks if this vertex already has an adjacent vertex with @color
	bool adj_tem_a_cor = false;
	for (list<Vertice*>::iterator it_adj = adjacentes.begin(); it_adj != adjacentes.end(); ++it_adj) {
		if (!(*it_adj)->get_tem_cor()) {//Se o adjacente a tiver cor ele nao precisa mais ser computado

			adj_tem_a_cor = false;
			//Pesquisa na lista de cores adjacentes dos vertices adjacentes se a cor a ser inserida ja esta contando para seu grau de saturação
			for (list<int>::iterator it_cor = (*it_adj)->cores_adjacentes.begin(); it_cor != (*it_adj)->cores_adjacentes.end(); ++it_cor) {
				if (*it_cor == cor) { //se o adjacente ja tiver a cor na sua lista o grau de saturação permanece igual
					adj_tem_a_cor = true;
					break;
				}
			}
			if (adj_tem_a_cor == false) {// se ele nao tiver a cor na lista o grau de saturação aumenta
				(*it_adj)->atualiza_satur_grau();
			}
			(*it_adj)->atualiza_grau(false);
		}
		
	}

	
}


