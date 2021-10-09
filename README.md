# algorithm libraries
C++에서 직접 사용하기위해 구현해둔 알고리즘 라이브러리입니다.

✔ - 구현됨
❌ - 미구현
❔ - 구현 결정 안됨

주요기능
=======
Graph 관련 기능
---------------
> * DFS, BFS ❌ - 기본적인 그래프 탐색
> * Dijkstra's algorithm, Floyd-Warshall algorithm, Bellman-Ford algorithm ❌ - 최단경로 알고리즘
> * Network Flow ✔ - 최대유량 알고리즘
> * Flow Tracking ❌ - 유량이 어떻게 흘러야 최대유량이 되는지 추적
> * Connected Components(SCC, BCC, Block-Cut Tree) ❌ - 그래프 묶기
> * Bipartite Matching ❌ - 이분 매칭
> * Heavy-Light Decomposistion ❌ - Heavy-Light 분할
> * Centroid Decomposition ❌ - 센트로이드 분할

Data Structures 관련 기능
-----------------------
> * Graph, Edge ✔ - 그래프 자료구조(정점이 아니라 간선을 저장, 공간복잡도 효율성 증가)
> * Segment Tree ❌ - 세그먼트 트리(Lazy Propagation 적용)
> * Union-Find ❌ - Disjoint set을 위한 자료구조
> * Tree ❌ - 트리를 더 쉽게 다루기 위한 자료구조(LCA같은 부가기능 적용)
> * Persistent Segment Tree ❌ - 각 시점에서 자료구조 상태를 알 수 있는 segment tree
> * BigInteger in C++ ❌ - C++에서 큰 수 다루기(string으로 구현)
> * Merge Sort Tree ❌ - 머지 소트 트리
> * Binary Search Tree - 이분 탐색 트리
> * Splay Tree ❌ - BST의 한 종류, Red-Black Tree나 AVL트리보다 구현이 쉬움
> * Red-Black Tree ❔ - map과 같은 자료구조 구현에 사용되는 레드블랙 트리

String 관련 기능
----------------
> * KMP algorithm ❌ - 문자열 탐색 알고리즘
> * Trie ❌ - 트라이
> * Aho-Corasick ❌ - 아호-코라식
> * Suffix Array ❌ - 접미사 배열
> * Rabin-Karp algorithm ❌ - 라빈-카프 알고리즘

Geometry 관련 기능
------------------
> * Convex hull ❌ - 볼록 껍질
> * CCW ❌ - 벡터의 외적
> * Line Crossing ❌ - 선분 교차

Math 관련 기능
--------------
> * Fast Fourier Transform ❌ - 고속 푸리에 변환
> * Chinese Remainder Theorem ❌ - 중국인의 나머지 정리
> * Euclid Algorithm ❌ - 유클리드 호제법 (확장됨)
> * Miller-Rabin test ❌ - 밀러-라빈 소수 판정법
> * Pollard's Rho ❌ - 폴라드 로 알고리즘(소인수분해)
