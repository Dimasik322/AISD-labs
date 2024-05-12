#include <graph/graph.h>
#include <iostream>

//using namespace std;

int main() {
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

	cout << graph.center();

	//graph.eccentricity('a');

	//graph.walk('a', print_exc);
	/*for (auto v : graph.shortest_path('a', 'g')) {
		cout << v << "->";
	}*/
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