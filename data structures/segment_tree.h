#ifndef __SEGTREE__
#define __SEGTREE__
#include <vector>
#include <cmath>
#include <functional>

namespace exalg {
	template<typename _Ty, typename _QOper = std::plus<_Ty>, typename _OOper = std::plus<_Ty>>
	class SegmentTree {
		std::vector<_Ty> segArr;
		std::vector<_Ty> lazy;
		int treeHeight;
		int treeSize;
		_QOper qOp;
		_OOper oOp;
		int (*bConPtr)() = breakCondition; //For Segment Tree Beats
		int (*tConPtr)() = tagCondition; //For Segment Tree Beats
		bool isLeaf(int node) {
			return node >= treeSize / 2;
		}
		bool breakCondition(int s, int e, int node, int ns, int ne) {
			if (e <= ns || ne <= s)
				return true;
			return false;
		}
		bool tagCondition(int s, int e, int node, int ns, int ne) {
			if (s <= ns && ne <= e)
				return true;
			return false;
		}
		void propagate(int node, int s, int e) {
			if (lazy[node] != 0) {
				if (!isLeaf(node)) {
					lazy[node * 2] += lazy[node];
					lazy[node * 2 + 1] += lazy[node];
				}
				segArr[node] = oOp(segArr[node], lazy[node] * (e - s));
				lazy[node] = 0;
			}
		}
		std::pair<_Ty, bool> query(int s, int e, int node, int ns, int ne) {
			propagate(node, ns, ne);
			if (e <= ns || s >= ne)
				return { 0, false };
			if (s <= ns && ne <= e)
				return { segArr[node], true };
			int mid = (ns + ne) / 2;
			std::pair<_Ty, bool> ret1 = query(s, e, node * 2, ns, mid), ret2 = query(s, e, node * 2 + 1, mid, ne);
			if (ret1.second && ret2.second)
				return { qOp(ret1.first, ret2.first), true };
			if (ret1.second)
				return ret1;
			if (ret2.second)
				return ret2;
			return { 0, false };
		}
		void operate(int s, int e, _Ty val, int node, int ns, int ne) {
			propagate(node, ns, ne);
			if (bConPtr(s, e, node, ns, ne))
				return;
			if (tConPtr(s, e, node, ns, ne)) {
				lazy[node] += val;
				propagate(node, ns, ne);
				return;
			}
			int mid = (ns + ne) / 2;
			operate(s, e, val, node * 2, ns, mid);
			operate(s, e, val, node * 2 + 1, mid, ne);
			segArr[node] = oOp(segArr[node * 2], segArr[node * 2 + 1]);
		}
	public:
		SegmentTree() { treeHeight = 0; treeSize = 0; }
		SegmentTree(std::vector<_Ty> arr) { adapt(arr); }
		SegmentTree(_Ty* arr, int size) { adapt(arr, size); }
		void adapt(std::vector<_Ty> arr) {
			treeHeight = ceil(log2(arr.size()));
			treeSize = 1 << (treeHeight + 1);
			segArr.resize(treeSize);
			lazy.resize(treeSize);
			for (int i = 0; i < arr.size(); i++)
				segArr[i + treeSize / 2] = arr[i];
			for (int i = arr.size(); i < treeSize / 2; i++)
				segArr[i + treeSize / 2] = 0;
			for (int i = treeSize / 2 - 1; i > 0; i--)
				segArr[i] = op(segArr[i * 2], segArr[i * 2 + 1]);
			for (int i = 0; i < lazy.size(); i++)
				lazy[i] = 0;
		}		
		void adapt(_Ty* arr, int size) {
			treeHeight = ceil(log2(arr.size()));
			treeSize = 1 << (treeHeight + 1);
			segArr.resize(treeSize);
			lazy.resize(treeSize);
			for (int i = 0; i < size; i++)
				segArr[i + treeSize / 2] = arr[i];
			for (int i = size; i < treeSize / 2; i++)
				segArr[i + treeSize / 2] = 0;
			for (int i = treeSize / 2 - 1; i > 0; i--)
				segArr[i] = op(segArr[i * 2], segArr[i * 2 + 1]);
			for (int i = 0; i < lazy.size(); i++)
				lazy[i] = 0;
		}
		_Ty query(int start, int end) {
			return query(start - 1, end, 1, 0, treeSize / 2).first;
		}
		void operate(int idx, _Ty val) {
			operate(idx, idx, val);
		}
		void operate(int start, int end, _Ty val) {
			operate(start - 1, end, val, 1, 0, treeSize / 2);
		}
		void setBreakCondition(bool (*_breakCondition)(int start, int end, int node, int ns, int ne)) {
			bConPtr = _breakCondition;
		}
		void setTagCondition(bool (*_tagCondition)(int start, int end, int node, int ns, int ne)) {
			tConPtr = _tagCondition;
		}
	};
}
#endif
