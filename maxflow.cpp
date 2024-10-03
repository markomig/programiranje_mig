#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int to; //do koe teme e nasoceno rebroto
    int capacity; //kolku flow moze da tece niz nego
    int flow; //kolku flow vsusnost tece

};

class GraphAdjList
{
public:
    int V; //broj na teminja
    vector<vector<Edge>> adj;
    vector<int> parent;


    GraphAdjList(int V)
    {
        this->V = V;
        adj.resize(V);
        parent.resize(V);
    }

    void addEdge(int u, int v, int capacity)
    {
        Edge e1 = {v, capacity, 0};
        Edge e2 = {u, 0, 0};
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }

    bool bfs(int s, int t)
    {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(s);
        parent[s] = -2;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (Edge &e : adj[u])
            {
                int v = e.to;
                if (parent[v] == -1 && e.capacity - e.flow > 0)
                {
                    parent[v] = u;
                    q.push(v);
                    if (v == t)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    int fordFulkerson(int s, int t)
    {
        int max_flow = 0;
        while (dfs(s, t))
        {
            int path_flow = INT_MAX;
            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                for (Edge &e : adj[u])
                {
                    if (e.to == v)
                    {
                        path_flow = min(path_flow, e.capacity - e.flow);
                    }
                }
            }

            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                for (Edge &e : adj[u])
                {
                    if (e.to == v)
                    {
                        e.flow += path_flow;
                    }
                }
                for (Edge &e : adj[v])
                {
                    if (e.to == u)
                    {
                        e.flow -= path_flow;
                    }
                }
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

   bool dfs(int u, int t)
    {
        if (u == t) return true;

        for (int v = 0; v < V; v++)
        {

            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0)
            {
                parent[v] = u;
                if (dfs(v, t))
                {
                    return true;
                }
            }
        }
        return false;
    }



    int edmondKarps(int s, int t)
    {
        int max_flow = 0;
        while (bfs(s, t))
        {
            int path_flow = INT_MAX;
            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                for (Edge &e : adj[u])
                {
                    if (e.to == v)
                    {
                        path_flow = min(path_flow, e.capacity - e.flow);
                    }
                }
            }

            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                for (Edge &e : adj[u])
                {
                    if (e.to == v)
                    {
                        e.flow += path_flow;
                    }
                }
                for (Edge &e : adj[v])
                {
                    if (e.to == u)
                    {
                        e.flow -= path_flow;
                    }
                }
            }
            max_flow += path_flow;
        }
        return max_flow;
    }




};





class GraphAdjMatrix
{
public:
    int **capacity;
    int **flow;
    int V;
    vector<int> parent;

    GraphAdjMatrix(int V)
    {
        this->V = V;
        capacity = new int*[V];
        flow = new int*[V];
        for (int i = 0; i < V; i++)
        {
            capacity[i] = new int[V]();
            flow[i] = new int[V]();
        }
        parent.resize(V);
    }



    void addEdge(int u, int v, int cap)
    {
        capacity[u][v] = cap;
    }

    bool bfs(int s, int t)
    {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(s);
        parent[s] = -2;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; v++)
            {
                if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0)
                {
                    parent[v] = u;
                    q.push(v);
                    if (v == t)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    int fordFulkerson(int s, int t)
    {
        int max_flow = 0;
        while (dfs(s, t))
        {
            int path_flow = INT_MAX;
            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
            }

            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                flow[u][v] += path_flow;
                flow[v][u] -= path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

    bool dfs(int u, int t)
    {
        if (u == t) return true;

        for (int v = 0; v < V; v++)
        {

            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0)
            {
                parent[v] = u;
                if (dfs(v, t))
                {
                    return true;
                }
            }
        }
        return false;
    }


    int edmondKarps(int s, int t)
    {
        int max_flow = 0;

        while (true)
        {
            fill(parent.begin(), parent.end(), -1);
            parent[s] = -2;


            if (!bfs(s, t)) break;

            int path_flow = INT_MAX;

            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
            }


            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                flow[u][v] += path_flow;
                flow[v][u] -= path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }


};


int main()
{
    GraphAdjList g1(6);
    g1.addEdge(0, 1, 10);
    g1.addEdge(0, 2, 5);
    g1.addEdge(1, 2, 15);
    g1.addEdge(1, 3, 10);
    g1.addEdge(2, 4, 10);
    g1.addEdge(3, 5, 10);
    g1.addEdge(4, 5, 10);

    int maxi = g1.fordFulkerson(0, 5);
    cout << "ford fulkerson so adjList: " << maxi << endl;


    GraphAdjList g2(6);
    g2.addEdge(0, 1, 10);
    g2.addEdge(0, 2, 5);
    g2.addEdge(1, 2, 15);
    g2.addEdge(1, 3, 10);
    g2.addEdge(2, 4, 10);
    g2.addEdge(3, 5, 10);
    g2.addEdge(4, 5, 10);

    maxi = g2.edmondKarps(0, 5);
    cout << "edmond karps so adjList: " << maxi << endl;

    GraphAdjMatrix g3(6);
    g3.addEdge(0, 1, 16);
    g3.addEdge(0, 2, 13);
    g3.addEdge(1, 2, 10);
    g3.addEdge(1, 3, 12);
    g3.addEdge(2, 1, 4);
    g3.addEdge(2, 4, 14);
    g3.addEdge(3, 2, 9);
    g3.addEdge(3, 5, 20);
    g3.addEdge(4, 3, 7);
    g3.addEdge(4, 5, 4);

    maxi = g3.fordFulkerson(0, 5);
    cout << "ford fulkerson so adjMatrix: " << maxi << endl;

    GraphAdjMatrix g4(6);
    g4.addEdge(0, 1, 16);
    g4.addEdge(0, 2, 13);
    g4.addEdge(1, 2, 10);
    g4.addEdge(1, 3, 12);
    g4.addEdge(2, 1, 4);
    g4.addEdge(2, 4, 14);
    g4.addEdge(3, 2, 9);
    g4.addEdge(3, 5, 20);
    g4.addEdge(4, 3, 7);
    g4.addEdge(4, 5, 4);

    maxi = g4.edmondKarps(0, 5);
    cout << "edmond karps so adjMatrix: " << maxi << endl;


    return 0;
}


