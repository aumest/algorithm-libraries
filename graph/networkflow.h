#ifndef __NETWORKFLOW__
#define __NETWORKFLOW__
#include "graphclass.h"
#include <climits>
#include <queue>
#include <iostream>

namespace stdalg {
	template<typename _Ty = int>
	class NetworkFlowAdapter {
		graph<_Ty> gp;
		int* level;
		int* work;
		_Ty min(_Ty a, _Ty b) {
			return a < b ? a : b;
		}		
		bool dinic_bfs(int start, int end) {
			for (int i = 0; i < gp.getCapacity(); i++)
				level[i] = -1;			
			level[start] = 0;
			std::queue<int> q;
			q.push(start);
			int cur;
			while (!q.empty()) {
				cur = q.front();
				q.pop();
				for (edge<_Ty> edg : gp.getConnectionRef()[cur]) {
					if (level[edg.getToVertex()] == -1 && edg.getRemainFlow() > 0) {
						level[edg.getToVertex()] = level[edg.getFromVertex()] + 1;
						q.push(edg.getToVertex());
					}
				}
			}
			return level[end] != -1;
		}
		_Ty dinic_dfs(int cur, int destination, int flow) {
			int nxt;
			_Ty dfsRes;			
			if (cur == destination)
				return flow;
			for (int& i = work[cur]; i < gp.getConnectionRef()[cur].size(); i++) {
				edge<_Ty>& edg = gp.getConnectionRef()[cur][i];				
				nxt = edg.getToVertex();
				if (level[nxt] == level[cur] + 1 && edg.getRemainFlow() > 0) {
					dfsRes = dinic_dfs(nxt, destination, min(edg.getRemainFlow(), flow));					
					if (dfsRes > 0) {
						edg.setFlow(edg.getFlow() + dfsRes);						
						edg.getDual()->setFlow(edg.getDual()->getFlow() - dfsRes);						
						return dfsRes;
					}
				}
			}
			return 0;
		}
		void reset() {
			std::vector<edge<_Ty>>* gpVec = gp.getConnectionRef();			
			for (int i = 0; i < gp.getCapacity(); i++) {
				for (int j = 0; j < gpVec[i].size(); j++) {
					gpVec[i][j].setFlow(0);
					gpVec[i][j].getDual()->setFlow(0);
				}
			}
		}
	public:
		NetworkFlowAdapter() { };
		NetworkFlowAdapter(graph<_Ty> g, bool isDualConnected = false) : gp(g) {						
			if (!isDualConnected) {
				std::vector<edge<_Ty>>* tempVec;
				tempVec = g.getConnectionRef();
				std::vector<edge<_Ty>>* gpVec;
				gpVec = gp.getConnectionRef();
				int size = g.getCapacity();				
				edge<_Ty> tmp;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < tempVec[i].size(); j++) {
						gp.connect(gpVec[i][j].getToVertex(), gpVec[i][j].getFromVertex(), -gpVec[i][j].getCost(), 0);
						gpVec[i][j].setDual(&gpVec[gpVec[i][j].getToVertex()].back());
						gpVec[i][j].getDual()->setFlow(0);
					}					
				}
			}
			level = new int[gp.getCapacity()];
			work = new int[gp.getCapacity()];
		}
		void adapt(graph<_Ty> g, bool isDualConnected = false) {
			gp = g;
			if (!isDualConnected) {
				std::vector<edge<_Ty>>* tempVec;
				tempVec = g.getConnectionRef();
				std::vector<edge<_Ty>>* gpVec;
				gpVec = gp.getConnectionRef();
				int size = g.getCapacity();
				edge<_Ty> tmp;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < tempVec[i].size(); j++) {
						gp.connect(gpVec[i][j].getToVertex(), gpVec[i][j].getFromVertex(), -gpVec[i][j].getCost(), 0);
						gpVec[i][j].setDual(&gpVec[gpVec[i][j].getToVertex()].back());
						gpVec[i][j].getDual()->setFlow(0);
					}
				}
			}
			delete[] level;
			delete[] work;
			level = new int[gp.getCapacity()];
			work = new int[gp.getCapacity()];
		}
		_Ty getMaximumFlow(int start, int end) { //Works with Dinic's algorithm
			_Ty res = 0;
			_Ty flow;
			while (dinic_bfs(start, end)) {
				for (int i = 0; i < gp.getCapacity(); i++)
					work[i] = 0;				
				while (true) {
					flow = dinic_dfs(start, end, INT_MAX);
					if (flow == 0)
						break;
					res += flow;
				}
			}
			reset();
			return res;
		}
		std::pair<_Ty, _Ty> getMCMF(int start, int end) { //based on spfa;
			std::pair<_Ty, _Ty> res = { 0, 0 };
			int maxSize = gp.getCapacity();
			int tempResFlow = 0;
			edge<_Ty>** pre = new edge<_Ty>*[maxSize];
			_Ty* dist = new _Ty[maxSize];
			bool* inQueue = new bool[maxSize];
			for (int i = 0; i < maxSize; i++)
				inQueue[i] = false;
			int cur;
			int nxt;
			while (true) {
				std::queue<int> q;	
				for (int i = 0; i < maxSize; i++)
					dist[i] = INT_MAX;
				for (int i = 0; i < maxSize; i++) {					
					pre[i] = nullptr;
				}
				dist[start] = 0;
				q.push(start);
				inQueue[start] = true;
				while (!q.empty()) {
					cur = q.front();
					q.pop();
					inQueue[cur] = false;
					for (edge<_Ty>& edg : gp.getConnectionRef()[cur]) {
						nxt = edg.getToVertex();
						if (edg.getRemainFlow() > 0 && dist[nxt] > dist[cur] + edg.getCost()) {
							dist[nxt] = dist[cur] + edg.getCost();
							pre[nxt] = &edg;
							if (!inQueue[nxt]) {
								inQueue[nxt] = true;
								q.push(nxt);
							}							
						}
					}
				}				
				if (pre[end] == nullptr)
					break;
				tempResFlow = INT_MAX;
				for (edge<_Ty>* i = pre[end]; ; i = pre[i->getFromVertex()]) {
					tempResFlow = min(tempResFlow, i->getRemainFlow());					
					if (i->getFromVertex() == start)
						break;
				}				
				
				for (edge<_Ty>* i = pre[end]; ; i = pre[i->getFromVertex()]) {
					res.second += tempResFlow * i->getCost();
					i->setFlow(i->getFlow() + tempResFlow);
					i->getDual()->setFlow(i->getDual()->getFlow() - tempResFlow);
					if (i->getFromVertex() == start)
						break;
				}
				res.first += tempResFlow;
			}
			delete[] inQueue;
			delete[] dist;
			delete[] pre;
			reset();
			return res;
		}
		~NetworkFlowAdapter() {
			delete[] level;
			delete[] work;
		}
	};
}
#endif
