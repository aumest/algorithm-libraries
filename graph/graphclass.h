#ifndef __GRAPHCLASS__
#define __GRAPHCLASS__
#include <vector>
#include <stdexcept>
namespace stdalg {	
	template<typename _Ty = int>
	class edge {
		int fromVertex;
		int toVertex;		
		_Ty cost;
		_Ty capacity;
		_Ty flow = 0;
		edge<_Ty>* dual = nullptr;
	public:
		edge() { }
		edge(int fVertexIdx, int sVertexIdx) : fromVertex(fVertexIdx), toVertex(sVertexIdx) { }
		_Ty getCost() { return cost; }
		void setCost(_Ty v) { cost = v; }
		_Ty getEdgeCapacity() { return capacity; }
		void setEdgeCapacity(_Ty capa) { capacity = capa; }
		_Ty getFlow() { return flow; }
		void setFlow(_Ty f) { flow = f; }
		_Ty getRemainFlow() { return capacity - flow; }
		int getFromVertex() { return fromVertex; }
		int getToVertex() { return toVertex; }
		void setFromVertex(int fromVertex) { this->fromVertex = fromVertex; }
		void setToVertex(int toVertex) { this->toVertex = toVertex; }
		void setDual(edge<_Ty>* e) { dual = e; e->dual = this; }
		edge<_Ty>* getDual() { return dual; }
	};
	template<typename _Ty = int>
	class graph {
		std::vector<edge<_Ty>>* connections;
		int size;
	public:
		graph() {
			connections = new std::vector<edge<_Ty>>[10000];
			size = 10000;
		}
		graph(int vCnt) {
			connections = new std::vector<edge<_Ty>>[vCnt + 10];
			size = vCnt + 10;
		}
		graph(const graph& copy) : size(copy.size) {
			connections = new std::vector<edge<_Ty>>[copy.size];
			for (int i = 0; i < copy.size; i++)
				connections[i] = copy.connections[i];
		}
		void connect(int fromVertex, int toVertex) {
			edge<_Ty> tmp(fromVertex, toVertex);			
			connections[fromVertex].push_back(tmp);
		}
		void connect(int fromVertex, int toVertex, _Ty cost) {
			edge<_Ty> tmp(fromVertex, toVertex);
			tmp.setCost(cost);
			connections[fromVertex].push_back(tmp);
		}
		void connect(int fromVertex, int toVertex, _Ty cost, _Ty capacity) {
			edge<_Ty> tmp(fromVertex, toVertex);
			tmp.setCost(cost);
			tmp.setEdgeCapacity(capacity);
			connections[fromVertex].push_back(tmp);
		}
		void dualConnect(int fromVertex, int toVertex) {
			connections[fromVertex].push_back({ fromVertex, toVertex });
			connections[toVertex].push_back({ toVertex, fromVertex });
		}
		void dualConnect(int fromVertex, int toVertex, _Ty cost) {
			edge<_Ty> tmp1(fromVertex, toVertex);
			tmp1.setCost(cost);
			edge<_Ty> tmp2(toVertex, fromVertex);
			tmp2.setCost(cost);
			connections[fromVertex].push_back(tmp1);
			connections[toVertex].push_back(tmp2);
		}
		void dualConnect(int fromVertex, int toVertex, _Ty cost, _Ty capacity) {
			edge<_Ty> tmp1(fromVertex, toVertex);
			tmp1.setCost(cost);
			tmp1.setEdgeCapacity(capacity);
			edge<_Ty> tmp2(toVertex, fromVertex);
			tmp2.setCost(cost);
			tmp2.setEdgeCapacity(capacity);
			connections[fromVertex].push_back(tmp1);
			connections[toVertex].push_back(tmp2);
		}
		bool isConnected(int fromVertex, int toVertex) {
			for (edge<_Ty> e : connections[fromVertex]) {
				if (e.getToVertex() == toVertex)
					return true;
			}
			return false;
		}
		std::vector<edge<_Ty>>* getConnectionRef() {
			return connections;
		}
		int getCapacity() {
			return size;
		}
		~graph() {
			delete[] connections;
		}
	};
}
#endif
