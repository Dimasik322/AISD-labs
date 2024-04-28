#pragma once

#include <memory>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;


template<typename Vertex, typename Distance = double>
class Graph {
private:
	struct Edge {
		Vertex to;
		Distance d;
		Edge(const Vertex& to, const Distance& d) : to(to), d(d) {};
		bool operator==(const Edge& other) {
			return (to == other.to && d == other.d);
		}
	};
	unordered_map<Vertex, list<Edge>> graph;

public:
	Graph() {};
	~Graph() {
		cout << "Destructor" << endl;
	}

	bool has_vertex(const Vertex& v) const {
		return graph.contains(v);
	}
	void add_vertex(const Vertex& v) {
		if (!has_vertex(v)) {
			graph[v] = list<Edge>();
		}
		else {
			cout << "Vertex already in graph" << endl;
		}
	}
	bool remove_vertex(const Vertex& v) {
		return graph.erase(v);
	}
	vector<Vertex> vertices() const {
		vector<Vertex> vec;
		for (auto i : graph) {
			vec.push_back(i.first);
		}
		return vec;
	}

	void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
		if (has_vertex(from) && has_vertex(to)) {
			graph[from].push_back(Edge(to, d));
		}
		else {
			throw invalid_argument("Vertex is not exist");
		}
	}
	bool remove_edge(const Vertex& from, const Vertex& to) {
		for (Edge edge : graph[from]) {
			edge.print();
			if (edge.is_equal(to)) {
				graph[from].remove(Edge(edge.to, edge.d));
				return true;
			}
		}
		return false;
	}
};