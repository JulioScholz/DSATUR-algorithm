#pragma once
#include "Vertice.h"
#include "color.h"

class Grafo
{
private:
	list<Vertice*> lista_vertices;
	list<Vertice*> possiveis_vertices;
	list<Vertice*> computados_vertices;
	 vector <color> cores;
public:
	Grafo();
	~Grafo();
	void build();
	void DSATUR();
	void save();
	bool contem_vertice(int id);
	Vertice* get_instancia_de_vertice(int id);
	void print_grafo();
	void print_final_result();
	
};

