#include <graph/graph.h>
#include <iostream>

//using namespace std;

int main() {
	Graph<int> graph;
	graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	graph.add_vertex(4);

	graph.add_edge(1, 2, 5);
	graph.add_edge(2, 1, 6);
	graph.add_edge(3, 2, 2);
	graph.add_edge(1, 3, 9);
	graph.add_edge(2, 3, 7);

	cout << graph.degree(5);
	/*for (auto i : graph.edges()) {
		cout << i;
	}*/
	//cout << graph.remove_vertex(1);
	/*graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	graph.add_vertex(4);
	for (auto i : graph.vertices()) {
		cout << i << " ";
	}
	graph.add_edge(1, 2, 1.2f);
	graph.add_edge(1, 3, 1.3f);
	graph.add_edge(1, 4, 1.4f);
	graph.add_edge(2, 1, 2.1f);
	graph.add_edge(2, 3, 2.3f);
	graph.add_edge(3, 4, 3.4f);*/
	//cout << graph.has_vertex(2);
	//cout << graph.remove_vertex(2);
	//cout << graph.remove_vertex(2);
	return 0;
}