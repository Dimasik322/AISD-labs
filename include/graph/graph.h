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
#include <queue>

using namespace std;


template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from;
		Vertex to;
		Distance d;
		Edge(const Vertex& from, const Vertex& to, const Distance& d) : from(from), to(to), d(d) {};
		bool operator==(const Edge& other) const {
			return (from == other.from && to == other.to && d == other.d);
		}
		friend ostream& operator<<(ostream& os, const Edge& e) {
			os << e.from << " -> " << e.to << " : " << e.d << endl;
			return os;
		}
	};

private:
	unordered_map<Vertex, list<Edge>> graph;

	pair<unordered_map<Vertex, Distance>, unordered_map<Vertex, Vertex>> dijkstra(const Vertex& from) {
		unordered_map<Vertex, Distance> d;
		unordered_map<Vertex, Vertex> prev;
		for (auto v : vertices()) {
			d[v] = numeric_limits<Distance>::max();
			prev[v] = NULL;
		}
		d[from] = 0;
		vector<Vertex> q;
		q.push_back(from);
		while (!q.empty()) {
			sort(q.begin(), q.end());
			auto u = q.front();
			q.erase(q.begin());
			for (auto e : graph[u]) {
				auto v = e.to;
				auto weight = e.d;
				if (d[v] > d[u] + weight && d[v] != -1) {
					d[v] = d[u] + weight;
					prev[v] = u;
					q.push_back(v);
				}
			}
		}
		return pair(d, prev);
	}

public:
	Graph() = default;
	~Graph() = default;
	void print() const {
		for (const auto& v : graph) {
			for (const auto& e : v.second) {
				cout << e;
			}
		}
	}

	bool has_vertex(const Vertex& v) const {
		return graph.contains(v);
	}
	void add_vertex(const Vertex& v) {
		if (!has_vertex(v)) {
			graph[v] = list<Edge>();
		}
		else {
			cout << "Vertex already exists" << endl;
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
			graph[from].push_back(Edge(from, to, d));
		}
		else {
			throw invalid_argument("Vertex is not exist");
		}
	}
	bool remove_edge(const Vertex& from, const Vertex& to) {
		auto iter = graph.find(from);
		if (iter != graph.end()) {
			for (auto iter_e = (*iter).second.begin(); iter_e != (*iter).second.end(); ++iter_e) {
				if ((*iter_e).to == to) {
					graph[from].erase(iter_e);
					return true;
				}
			}
		}
		return false;
	}
	bool remove_edge(const Edge& edge) {
		auto iter = graph.find(edge.from);
		if (iter != graph.end()) {
			for (auto iter_e = (*iter).second.begin(); iter_e != (*iter).second.end(); ++iter_e) {
				if ((*iter_e) == edge) {
					graph[edge.from].erase(iter_e);
					return true;
				}
			}
		}
		return false;
	}
	bool has_edge(const Vertex& from, const Vertex& to) const {
		auto iter = graph.find(from);
		if (iter != graph.end()) {
			for (auto iter_e = (*iter).second.begin(); iter_e != (*iter).second.end(); ++iter_e) {
				if ((*iter_e).to == to) {
					return true;
				}
			}
		}
		return false;
	}
	bool has_edge(const Edge& edge) const {
		auto iter = graph.find(edge.from);
		if (iter != graph.end()) {
			for (auto iter_e = (*iter).second.begin(); iter_e != (*iter).second.end(); ++iter_e) {
				if ((*iter_e) == edge) {
					return true;
				}
			}
		}
		return false;
	}
	vector<Edge> edges() const {
		vector<Edge> edges;
		for (auto i : graph) {
			for (auto j : i.second) {
				edges.push_back(j);
			}
		}
		return edges;
	}

	size_t order() const {
		return graph.size();
	}
	size_t degree(const Vertex& v) {
		if (has_vertex(v)) {
			return graph[v].size();
		}
		throw invalid_argument("Vertex is not exists");
	}

	void walk(const Vertex& start_vertex, function<void(const Vertex&)> action) {
		queue<Vertex> q;
		auto visited = unordered_map<Vertex, float>();
		q.push(start_vertex);
		//action(start_vertex);
		visited[start_vertex] = 0;
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (auto e : graph[u]) {
				auto v = e.to;
				if (visited[v] == 0) {
					visited[v] = visited[u] + 1;
					q.push(v);
					//action(v);
				}
			}
		}
		for (auto v : visited) {
			cout << v.first << ':' << v.second << endl;
			//action(v.first);
		}
	}

	vector<Vertex> shortest_path(const Vertex& from, const Vertex& to) {
		auto prev = dijkstra(from).second;
		vector<Vertex> path;
		if (prev[to] == -1) {
			return path;
		}
		path.push_back(to);
		for (auto v = prev[to]; v != from; v = prev[v]) {
			path.push_back(v);
		}
		path.push_back(from);
		reverse(path.begin(), path.end());
		return path;
	}

	Distance eccentricity(const Vertex& v) {
		
	}

	//Task 1
	Vertex radius() {
		
	}
};

auto print_exc = [](const auto& v) { cout << v << endl; };