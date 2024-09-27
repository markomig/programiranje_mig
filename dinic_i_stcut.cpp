#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int v;
    int flow;
    int C;
    int rev;
};


class Graph
{
    int V;
    int* level;
    vector<Edge>* adj;

public:
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }


    void addEdge(int u, int v, int C)
    {

        Edge a{ v, 0, C, (int)adj[v].size() };
        Edge b{ u, 0, 0, (int)adj[u].size() };

        adj[u].push_back(a);
        adj[v].push_back(b);
    }


    bool BFS(int s, int t)
    {
        for (int i = 0; i < V; i++)
            level[i] = -1;

        level[s] = 0;


        list<int> q;
        q.push_back(s);

        vector<Edge>::iterator i;
        while (!q.empty())
        {
            int u = q.front();
            q.pop_front();
            for (i = adj[u].begin(); i != adj[u].end(); i++)
            {
                Edge& e = *i;
                if (level[e.v] < 0 && e.flow < e.C)
                {

                    level[e.v] = level[u] + 1;

                    q.push_back(e.v);
                }
            }
        }

        if(level[t]<0)
            return false;
        else
            return true;

    }


    int sendFlow(int u, int flow, int t, int start[])
    {

        if (u == t)
            return flow;


        for (; start[u] < adj[u].size(); start[u]++)
        {

            Edge& e = adj[u][start[u]];

            if (level[e.v] == level[u] + 1 && e.flow < e.C)
            {
                int curr_flow = min(flow, e.C - e.flow);

                int temp_flow
                    = sendFlow(e.v, curr_flow, t, start);

                if (temp_flow > 0)
                {

                    e.flow += temp_flow;

                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }

        return 0;
    }


    int DinicMaxflow(int s, int t)
    {
        if (s == t)
            return -1;
        int total = 0;

        while (BFS(s, t) == true)
        {
            int* start = new int[V + 1] { 0 };
            while (int flow = sendFlow(s, INT_MAX, t, start))
            {
                total += flow;
            }
            delete[] start;
        }
        return total;
    }




    void minCut(int s, int t)
    {
        BFS(s, t);
        vector<int> reachable(V, false);
        dfs(s, reachable);

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                Edge& e = adj[i][j];
                if (reachable[i] && !reachable[e.v] && e.flow == e.C)
                {
                    cout << i << " - " << e.v << endl;
                }
            }
        }
    }


    void dfs(int u, vector<int>& reachable)
    {
        reachable[u] = true;
        for (int i = 0; i < adj[u].size(); i++)
        {
            Edge& e = adj[u][i];
            if (!reachable[e.v] && e.flow < e.C)
            {
                dfs(e.v, reachable);
            }
        }
    }
};




int main()
{
    Graph g(6);
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);



    cout << "Maximum flow so dinic e " << g.DinicMaxflow(0, 5);
    cout<<endl<<"s-t cut "<<endl;
    g.minCut(0,5);
    return 0;
}
