#include "Grafo.h"




Grafo::Grafo()
{
}


Grafo::~Grafo()
{
}

bool compare_id(const Vertice* first, const Vertice* second)
{	
	return (first->get_id() < second->get_id());
}

bool compare_grau(const Vertice* first, const Vertice* second)
{
	return (first->get_grau() > second->get_grau());
}

bool compare_satur(const Vertice* first, const Vertice* second)
{
	return (first->get_satur_grau() > second->get_satur_grau());
}


void Grafo::build()
{
	string nome_arquivo;
	cout << " INSIRA O NOME DO SEU AQRUIVO .csv: ou Insira 1 se quiser abrir o arquivo padrao (grafo07.csv) " << endl;
	cin >> nome_arquivo;
	cout << endl;

	if (nome_arquivo == "1")
		nome_arquivo = "grafo07.csv";

	ifstream arquivo(nome_arquivo);

	string linha;

	int num_id;
	string  id;
	
	Vertice* vertex = NULL;
	Vertice* vertex_aux = NULL;

	if (arquivo.is_open()) {
		while (!arquivo.eof() && arquivo.good() && getline(arquivo,linha))
		{
			for (int i = 0; i <= (int)linha.length(); i++) {
				while ((linha[i] >= 48) && (linha[i] <= 57) && i <= (int)linha.length()) {//Separa os numeros de virgulas e espaços e constroi a represetação virtual do grafo
					id += linha[i];
					i++;
				}
				if (id != "") { 
					num_id = stoi(id); // STRING PARA INTEIRO
					if (vertex == NULL) {
						if (contem_vertice(num_id)) {
							vertex = get_instancia_de_vertice(num_id);
						}
						else {
							vertex = new Vertice(num_id);
							lista_vertices.push_back(vertex);
						}
					}
					else {
						if(contem_vertice(num_id) == false) { 
							vertex_aux = new Vertice(num_id);
							lista_vertices.push_back(vertex_aux);
						}
						else {
							vertex_aux = get_instancia_de_vertice(num_id);
						}
						vertex->add_adjacente(vertex_aux);
						vertex_aux->add_adjacente(vertex);
					}
					id = "";
				}
			

			}
			vertex = NULL;
		}
		arquivo.close();
	}
	else {
		cout << "FAILED TO OPEN THE FILE" << endl;
	}

}

void Grafo::DSATUR()
{
	Vertice* vertex = NULL;
	Vertice* vertex_aux = NULL;
	bool tem_cor_disponivel = false;
	int num_cor_disponivel = 0;

	//promeira iteração utiliza apenas o vetice com o maiur grau
	lista_vertices.sort(compare_grau); //ordena os vertices de acordo com o seu grau
	vertex = lista_vertices.front();//o primeiro elemento é o com o maior grau
	vertex->set_cor(0); //estabelece a primeira cor a ele
	color cor(0,true);
	cores.push_back(cor); //atualiza a lista de cores
	vertex->atualiza_adjacentes(0); //atualiza os vertices adjacentes
	computados_vertices.push_back(vertex); //o adiciona a lista de vertices ja computados (coloridos)
	lista_vertices.pop_front();  //o remove do grafo principal (agora o grafo é o subgrafo remanescente

	while (!lista_vertices.empty()) {
		//as itereções seguindes utilizam o vertice de mair grau de SATURAÇÃO
		lista_vertices.sort(compare_satur); //ordena os vertices de acordo com o grau de saturação
		int satAux = lista_vertices.front()->get_satur_grau(); //o primeiro elemento é o vertice de mair grau de saturaçãoe highest degree
		
		for (auto const&  v : lista_vertices) { //mas pode existir mais de um vertice com o mesmo grau de saturação
			if (v->get_satur_grau() == satAux)
				possiveis_vertices.push_back(v); // a lista de possiveis vertices(os empatados em maior grau de saturação) é criada
		}

		possiveis_vertices.sort(compare_grau); //ordena os vertices de acordo com o seu grau,assim o empate pode ser resolvido
		vertex = possiveis_vertices.front(); //podem existir vertices com mesmo grau, mas isso nao importa, podemos pegar qualquer um
		possiveis_vertices.clear(); //o vertice ja foi escolhido, a lista pode ser limpa

		for (auto const& v : vertex->get_lista_adjacentes()) { // olha as cores que os vertices adjacentes ja tem e as estabele como indisponiveis (false)
			if (v->get_tem_cor()) {
				cores.at( v->get_cor() ).set_ativo(false);
			}
		}
		
		tem_cor_disponivel = false; 
		num_cor_disponivel = 0;

		//procura pela cor minima que o vertice pode receber 
		for (int i = 0; i < (int)cores.size() ; i++) {
			if (cores.at(i).get_ativo() == true) {
				tem_cor_disponivel = true;
				num_cor_disponivel = i;
				break;
			}
		}

		if (!tem_cor_disponivel) { //se não tem nehuma cor disponivel, uma nova é cirada 
			vertex->set_cor(cores.size());
			num_cor_disponivel = cores.size();
			cor.set_ambos(num_cor_disponivel, true);
			cores.push_back(cor);
		}
		else
			vertex->set_cor(num_cor_disponivel); //se tem cor disponivel ele recebe a menor das cores

		vertex->atualiza_adjacentes(num_cor_disponivel);
		computados_vertices.push_back(vertex);
		lista_vertices.remove(vertex);

		for (int i = 0; i < (int)cores.size(); i++)
			cores.at(i).set_ativo(true);//assume que todas as cores estarão disponiveis para o proximo vertice;
	}

}

void Grafo::save()
{
	ofstream file;
	file.open("out.csv", std::ofstream::out | std::ofstream::trunc); // Lmpa os dados ja existentes em out.csv
	computados_vertices.sort(compare_id);

	for (const auto& G : computados_vertices) {
		file << G->get_id() << ", " << G->get_cor() << "\n";
	}
	file.close();

}

bool Grafo::contem_vertice(int id)
{
	for (list<Vertice*>::iterator it_adj = lista_vertices.begin(); it_adj != lista_vertices.end(); ++it_adj) {
		if ((*it_adj)->get_id() == id) {
			return true;
		}
	}
	return false;
}

Vertice* Grafo::get_instancia_de_vertice(int id)
{
	for (list<Vertice*>::iterator it_adj = lista_vertices.begin(); it_adj != lista_vertices.end(); ++it_adj) {
		if ((*it_adj)->get_id() == id) {
			return (*it_adj);
		}
	}
	return NULL;
}

void Grafo::print_grafo()
{
	for (list<Vertice*>::iterator it_adj = lista_vertices.begin(); it_adj != lista_vertices.end(); ++it_adj) {
		cout << "Vertice[" << (*it_adj)->get_id() << "] -> ";
		list <Vertice*> lista = (*it_adj)->get_lista_adjacentes();
		for (list<Vertice*>::iterator it = lista.begin(); it != lista.end(); ++it) {
			cout <<  (*it)->get_id() << " ";

		}
		cout << endl;
	}

	//for (list<Vertice*>::iterator it_adj = computados_vertices.begin(); it_adj != computados_vertices.end(); ++it_adj) {
	//	cout << "Vertice[" << (*it_adj)->get_id() << "] -> " << (*it_adj)->get_cor() << " -> "; 
	//cout << endl;
	//}

}

void Grafo::print_final_result()
{
	int nVertexes, nEdges = 0, maxSatDegree = 0, minSatDegree = 10, nColors;
	float averageSatDegree = 0, standardDeviationSatDegree = 0;

	nVertexes = computados_vertices.size();
	nColors = cores.size();
	for (const auto&  v1 : computados_vertices) {
		averageSatDegree += v1->get_satur_grau();
		if (v1->get_satur_grau() > maxSatDegree)
			maxSatDegree = v1->get_satur_grau();
		if (v1->get_satur_grau() < minSatDegree)
			minSatDegree = v1->get_satur_grau();
		for (const auto& v2 : v1->get_lista_adjacentes()) {
			if (v2->get_id() > v1->get_id())
				nEdges++;
		}
	}
	averageSatDegree = averageSatDegree / (float)nVertexes;
	//calculo da variancia
	for (const auto& v1 : computados_vertices)
		standardDeviationSatDegree += pow(v1->get_satur_grau() - averageSatDegree, 2);  

	standardDeviationSatDegree = (float)sqrt(standardDeviationSatDegree); //raiz da variancia nos da o desvio padrão

	cout << "No. Vertexes: " << nVertexes <<
			"\nNo. Edges: " << nEdges <<
			"\nMin Sat Degree: " << minSatDegree <<
			"\nMax Sat Degree: " << maxSatDegree <<
			"\nSat Degree Average: " << averageSatDegree <<
			"\nSat Degree Standard Deviation: " << standardDeviationSatDegree <<
			"\nNo. Colors: " << nColors << endl;
	return;
}
