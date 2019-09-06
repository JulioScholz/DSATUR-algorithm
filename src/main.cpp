/* Developed by Júlio Scholz*/
#include "Grafo.h"
int main() {

	Grafo graph;
	long time;

	graph.build();

	clock_t Ticks[2];
	Ticks[0] = clock();

	graph.DSATUR();
	
	Ticks[1] = clock();
	time = (long)((Ticks[1] - Ticks[0]) * 1000.0)/ CLOCKS_PER_SEC;
	
	graph.save(); // salva em out.csv

	graph.print_final_result();

	cout << "Runtime: " << time << " ms.\n" << endl;

	system("pause");
	return 0;
}
