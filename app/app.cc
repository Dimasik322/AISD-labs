#include <graph/graph.h>
#include <iostream>
#include <memory>

using namespace std;

int main() {
	cout << "Graph initialization:" << endl;
	Graph<char> graph;
	graph.add_vertex('a');
	graph.add_vertex('b');
	graph.add_vertex('c');
	graph.add_vertex('d');

	graph.add_edge('a', 'b', 1);
	graph.add_edge('b', 'a', 1);
	graph.add_edge('a', 'c', 2);
	graph.add_edge('c', 'a', 2);
	graph.add_edge('b', 'd', 3);
	graph.add_edge('d', 'b', 3);
	graph.add_edge('c', 'd', 4);
	graph.add_edge('d', 'c', 4);

	graph.print();

	cout << endl << endl << "Edges and vertices remove:" << endl;

	graph.remove_edge('a', 'b');
	graph.remove_vertex('c');

	graph.print();

	cout << endl << endl << "Edges and vertices availability:" << endl;

	cout << graph.has_vertex('a');
	cout << graph.has_vertex('c');
	cout << graph.has_edge('a', 'b');
	cout << graph.has_edge(Graph<char>::Edge('d', 'c', 4));

	cout << endl << endl << "Edges and vertices list:" << endl;

	for (auto i : graph.vertices()) {
		cout << *i;
	}
	cout << endl;
	for (auto i : graph.edges('b')) {
		cout << i;
	}

	cout << endl << endl << "Order and Degree:" << endl;
	cout << graph.order();
	cout << graph.degree('a');
	cout << graph.degree('d');

	cout << endl << endl << "Dijkstra algorithm shortest path:" << endl;
	
	Graph<int, float> graph1;
	graph1.add_vertex(1);
	graph1.add_vertex(2);
	graph1.add_vertex(3);
	graph1.add_vertex(4);
	graph1.add_vertex(5);
	graph1.add_vertex(6);
	graph1.add_edge(1, 2, 4.0f);
	graph1.add_edge(1, 3, 1.0f);
	graph1.add_edge(2, 4, 2.0f);
	graph1.add_edge(3, 4, 6.0f);
	graph1.add_edge(4, 5, 3.0f);
	graph1.add_edge(4, 6, 2.0f);
	graph1.add_edge(5, 6, 6.0f);
	graph1.print();

	for (auto v : graph1.shortest_path(1, 6)) {
		cout << v << " -> ";
	}

	cout << endl << endl << "Walk:" << endl;

	graph1.add_vertex(7);
	graph1.add_edge(7, 1, 1.0f);
	graph1.walk(1, print_exc);

	cout << endl << endl << "Task, best location for storage:" << endl;

	Graph<char> graph2;
	graph2.add_vertex('a');
	graph2.add_vertex('b');
	graph2.add_vertex('c');
	graph2.add_vertex('d');
	graph2.add_vertex('e');
	graph2.add_edge('a', 'b', 1);
	graph2.add_edge('b', 'a', 1);
	graph2.add_edge('a', 'c', 2);
	graph2.add_edge('c', 'a', 2);
	graph2.add_edge('b', 'd', 3);
	graph2.add_edge('d', 'b', 3);
	graph2.add_edge('c', 'd', 4);
	graph2.add_edge('d', 'c', 4);
	graph2.add_edge('d', 'e', 5);
	graph2.add_edge('e', 'd', 5);

	cout <<"By eccentricity and radius: " << graph2.center() << endl;
	cout << "By minimum lenghts of paths: " << graph2.best_place() << endl;

	return 0;
}