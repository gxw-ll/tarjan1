// tarjan.cpp : 算法求无向图的桥
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int SIZE = 100010;
int head[SIZE], ver[SIZE * 2], Next[SIZE * 2];
int dfn[SIZE], low[SIZE];
int n, m, tot, num;
bool bridge[SIZE * 2];

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x];
}
// x 代表当前搜索树的根节点，in_edge代表其对应的序号(tot)
void tarjan(int x, int in_edge) {
	// 在搜索之前，先初始化节点x的时间戳与追溯值
	dfn[x] = low[x] = ++num;
	//通过head变量获取节点x的直接连接的第一个相邻节点的序号
	//通过next变量，迭代获取剩下的与节点x直接的节点的序号
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
			if (!dfn[y]) {
				tarjan(y, i);
				low[x] = min(low[x], low[y]);
				if (low[y] > dfn[x])
					bridge[i] = bridge[i ^ 1] = true;
			}
			else if (i != (in_edge ^ 1))
				low[x] = min(low[x], dfn[y]);
	}
}
	

int main()
{
	// [[0,1],[1,2],[2,0],[1,3]]
	cin >> n >> m;
	tot = 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf_s("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i, 0);
	for (int i = 2; i < tot; i += 2)
		if (bridge[i])
			printf("%d %d\n", ver[i ^ 1], ver[i]);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
