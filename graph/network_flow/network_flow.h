#ifndef __NETFLOW_H__
#define __NETFLOW_H__
#include <queue>
#include <vector>

class network_flow {
	int** capacity;
	int** flow;
	int** cost;
	int maxSize;
	std::vector<std::vector<int>> connection;
	int remain_flow(int start, int end) {
		return capacity[start][end] - flow[start][end];
	}
public:	
	network_flow(int vMax) {
		maxSize = vMax + 1;
		capacity = new int* [vMax + 1];
		flow = new int* [vMax + 1];
		cost = new int* [vMax + 1];
		for (int i = 0; i < vMax + 1; i++) {
			capacity[i] = new int[vMax + 1];
			flow[i] = new int[vMax + 1];
			cost[i] = new int[vMax + 1];
			for (int j = 0; j < vMax + 1; j++) {
				capacity[i][j] = 0;
				flow[i][j] = 0;
				cost[i][j] = 1;
			}
		}
		connection.resize(vMax + 1);
	}
	network_flow(int vMax, std::vector<std::vector<int>> connectionTable){
		maxSize = vMax;
		capacity = new int* [vMax];
		flow = new int* [vMax];
		cost = new int* [vMax];
		for (int i = 0; i < vMax; i++) {
			capacity[i] = new int[vMax];
			flow[i] = new int[vMax];
			cost[i] = new int[vMax];
		}
		connection = connectionTable;
	}
	void connect(int start, int end, int capacity) {		
		this->capacity[start][end] += capacity;		
		connection[start].push_back(end);
		connection[end].push_back(start);
	}
	void connect(int start, int end, int capacity, int cost) {
		this->capacity[start][end] += capacity;
		this->cost[start][end] += cost;
		connection[start].push_back(end);
		connection[end].push_back(start);
	}
	int edmonds_karp(int start, int end) {
		int* prev = new int[maxSize];
		int cur;
		int resFlow;
		int res = 0;
		while (true) {
			for (int i = 0; i < maxSize; i++)
				prev[i] = -1;
			std::queue<int> q;
			q.push(start);
			while (!q.empty() && prev[end] == -1) {
				cur = q.front();
				q.pop();
				for (int nxt : connection[cur]) {
					if (remain_flow(cur, nxt) > 0 && prev[nxt] == -1) {
						q.push(nxt);
						prev[nxt] = cur;
						if (nxt == end)
							break;
					}
				}
			}
			if (prev[end] == -1)
				break;
			resFlow = 2 << 20;
			for (int i = end; i != start; i = prev[i])
				resFlow = resFlow < remain_flow(prev[i], i) ? resFlow : remain_flow(prev[i], i);
			for (int i = end; i != start; i = prev[i]) {
				flow[prev[i]][i] += resFlow;
				flow[i][prev[i]] -= resFlow;				
			}
			res += resFlow;
		}
		delete[] prev;
		return res;
	}
	std::pair<int, int> spfa(int start, int end) {
		int totalFlow = 0;
		int totalCost = 0;
		int resFlow = 0;
		int* pre = new int[maxSize];
		int* dist = new int[maxSize];
		bool* inQueue = new bool[maxSize];
		for (int i = 0; i < maxSize; i++)
			inQueue[i] = false;
		int cur;
		while (true) {
			std::queue<int> q;
			for (int i = 0; i < maxSize; i++)
				pre[i] = -1;
			for (int i = 0; i < maxSize; i++)
				dist[i] = 10000000;
			dist[start] = 0;
			inQueue[start] = true;
			q.push(start);
			while (!q.empty()) {
				cur = q.front();
				q.pop();
				inQueue[cur] = false;
				for (int nxt : connection[cur]) {
					if (remain_flow(cur, nxt) > 0 && dist[nxt] > dist[cur] + cost[cur][nxt]) {
						dist[nxt] = dist[cur] + cost[cur][nxt];
						pre[nxt] = cur;
						if (!inQueue[nxt]) {
							inQueue[nxt] = true;
							q.push(nxt);
						}
					}
				}
			}
			if (pre[end] == -1)
				break;
			resFlow = 10000000;
			for (int i = end; i != start; i = pre[i])
				resFlow = resFlow < remain_flow(pre[i], i) ? resFlow : remain_flow(pre[i], i);
			for (int i = end; i != start; i = pre[i]) {
				totalCost += resFlow * cost[pre[i]][i];
				flow[pre[i]][i] += resFlow;
				flow[i][pre[i]] -= resFlow;
			}
			totalFlow += resFlow;
		}
		return std::make_pair(totalFlow, totalCost);
	}
	int dinic() {

	}
	~network_flow() {
		for (int i = 0; i < maxSize; i++) {
			delete[] capacity[i];
			delete[] flow[i];
			delete[] cost[i];
		}
		delete[] cost;
		delete[] capacity;
		delete[] flow;
	}
};
#endif
