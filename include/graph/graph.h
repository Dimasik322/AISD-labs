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

	pair<unordered_map<Vertex, Distance>, unordered_map<Vertex, Vertex>> dijkstra(const Vertex& from) const {
		unordered_map<Vertex, Distance> d;
		unordered_map<Vertex, Vertex> prev;
		for (auto v : vertices()) {
			d[*v] = numeric_limits<Distance>::max();
			prev[*v] = NULL;
		}
		d[from] = 0;
		vector<Vertex> q;
		q.push_back(from);
		while (!q.empty()) {
			sort(q.begin(), q.end());
			auto u = q.front();
			q.erase(q.begin());
			for (auto e : graph.at(u)) {
				auto v = e.to;
				auto weight = e.d;
				if (d[v] > d[u] + weight) {
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
		cout << "Vertices:" << endl;
		for (auto v : graph) {
			cout << v.first << " ";
		}
		cout << endl << "Edges:" << endl;
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
	const vector<std::shared_ptr<Vertex>> vertices() const {
		vector<shared_ptr<Vertex>> vec;
		for (auto i : graph) {
			vec.push_back(std::make_shared<Vertex>(i.first));
		}
		return vec;
	}

	void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
		if (has_vertex(from) && has_vertex(to)) {
			graph.at(from).push_back(Edge(from, to, d));
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
		if (iter == graph.end()) {
			return false;
		}
		auto list = (*iter).second;
		for (auto iter_e = list.begin(); iter_e != list.end(); ++iter_e) {
			if ((*iter_e).to == to) {
				return true;
			}
		}
		return false;
	}
	bool has_edge(const Edge& edge) const {
		auto iter = graph.find(edge.from);
		if (iter == graph.end()) {
			return false;
		}
		auto list = (*iter).second;
		for (auto iter_e = list.begin(); iter_e != list.end(); ++iter_e) {
			if ((*iter_e) == edge) {
				return true;
			}
		}
		return false;
	}
	const list<Edge>& edges(const Vertex& from) const {
		return graph.at(from);
	}

	size_t order() const {
		return graph.size();
	}
	size_t degree(const Vertex& v) const {
		return graph.at(v).size();
	}

	void walk(const Vertex& start_vertex, function<void(const Vertex&)> action) const {
		queue<Vertex> q;
		auto visited = unordered_map<Vertex, float>();
		q.push(start_vertex);
		action(start_vertex);
		visited[start_vertex] = 0;
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (auto e : graph.at(u)) {
				auto v = e.to;
				if (visited[v] == 0) {
					visited[v] = visited[u] + 1;
					q.push(v);
					action(v);
				}
			}
		}
	}

	vector<Vertex> shortest_path(const Vertex& from, const Vertex& to) {
		auto prev = dijkstra(from).second;
		vector<Vertex> path;
		path.push_back(to);
		for (auto v = prev[to]; v != from; v = prev[v]) {
			path.push_back(v);
		}
		path.push_back(from);
		reverse(path.begin(), path.end());
		return path;
	}

	const Distance& eccentricity(const Vertex& v) const {
		Distance max_dist = 0;
		auto d = dijkstra(v).first;
		for (auto dist_v : d) {
			if (dist_v.first != v && dist_v.second > max_dist) {
				max_dist = dist_v.second;
			}
		}
		return max_dist;
	}

	vector<Vertex> center() const {
		vector<Vertex> center;
		Distance min_e = NULL;
		for (auto v : vertices()) {
			auto ecc_v = eccentricity(*v);
			if (min_e == NULL || ecc_v <= min_e) {
				if (ecc_v < min_e) {
					center.clear();
				}
				min_e = ecc_v;
				center.push_back(*v);
			}
		}
		return center;
	}

	vector<Vertex> best_place() const {
		vector<Vertex> center;
		Distance min_sum = NULL;
		for (auto v : vertices()) {
			auto d = dijkstra(*v).first;
			Distance summa = 0;
			for (auto d_v : d) {
				summa += d_v.second;
			}
			if (min_sum == NULL || summa <= min_sum) {
				if (summa < min_sum) {
					center.clear();
				}
				min_sum = summa;
				center.push_back(*v);
			}
		}
		return center;
	}
};

auto print_exc = [](const auto& v) { cout << v << endl; };

template<typename Vertex>
ostream& operator<<(ostream& os, const vector<Vertex>& vec) {
	os << "Vertices:";
	for (auto v : vec) {
		os << ' ' << v;
	}
	return os;
}