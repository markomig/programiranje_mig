#include <bits/stdc++.h>

using namespace std;

const int inf = 1000000000;

class PushRelabel {
public:
int n;
vector<vector<int>> capacity, flow;
vector<int> height, excess, seen;
queue<int> excess_vertices;

PushRelabel(int vertices) : n(vertices), capacity(vertices, vector<int>(vertices, 0)), flow(vertices, vector<int>(vertices, 0)), height(vertices, 0), excess(vertices, 0), seen(vertices, 0)
{}

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v);
            else
                seen[u]++;
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}

int max_flow(int s, int t) {
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }
    seen.assign(n, 0);

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}
};

int main()
{
    int n = 6;
    PushRelabel pr(n);


    pr.capacity.resize(n, vector<int>(n, 0));


    pr.capacity[0][1] = 16;
    pr.capacity[0][2] = 13;
    pr.capacity[1][2] = 10;
    pr.capacity[1][3] = 12;
    pr.capacity[2][1] = 4;
    pr.capacity[2][4] = 14;
    pr.capacity[3][2] = 9;
    pr.capacity[3][5] = 20;
    pr.capacity[4][3] = 7;
    pr.capacity[4][5] = 4;
    int source = 0;
    int sink = 5;


    cout << "Max Flow: " << pr.max_flow(source, sink) << endl;

    return 0;
}
