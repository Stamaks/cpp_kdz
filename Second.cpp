#include <iostream>
#include <fstream>
#include <ctime>
#include "DataReader.cpp"

using namespace std;

vector<vector<int>> cur_flows;
vector<bool> visited;

bool bfs(int source, int sink, vector<int>& parent)
{
    for (int i = 0; i < visited.size(); ++i)
        visited[i] = false;

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int i = 0; i < cur_flows.size(); ++i)
        {
            if (!visited[i] && cur_flows[current][i] > 0)
            {
                q.push(i);
                parent[i] = current;
                visited[i] = true;
            }
        }
    }

    return visited[sink];
}

int maxFlow(int source, int sink)
{
    int current, i;

    vector<int> parent(cur_flows.size());

    int flow = 0;

    while (bfs(source, sink, parent))
    {
        int current_flow = INT32_MAX;
        for (i = sink; i != source; i = parent[i])
        {
            current = parent[i];
            current_flow = min(current_flow, cur_flows[current][i]);
        }

        for (i = sink; i != source; i = parent[i])
        {
            current = parent[i];
            cur_flows[current][i] -= current_flow;
            cur_flows[i][current] += current_flow;
        }

        flow += current_flow;
    }

    return flow;
}

int main() {
    DataReader* dr = new DataReader("../../kdzdata/input_910_0.0.txt", "Форда-Фалкерсона");

    vector<vector<int>> flows;
    vector<pair<int, int>> source_sink;
    dr->read(flows, source_sink);

//    for (auto p : source_sink)
//        cout << p.first << " " << p.second << "\n";

//    cout << source << sink;
//
//    for (int i = 0; i < flows.size(); ++i)
//    {
//        for (int j = 0; j < flows.size(); ++j)
//            cout << flows[i][j] << " ";
//
//        cout << "\n";
//    }

    for (int i = 0; i < flows.size(); ++i)
    {
        vector<int> v(flows.size());
        for (int j = 0; j < flows.size(); ++j)
            v[j] = flows[i][j];

        cur_flows.push_back(v);
    }

    for (int i = 0; i < flows.size(); ++i)
        visited.push_back(false);

    double start_time = clock();

    int res = 0, cur_source, cur_sink;
    for (int i = 0; i < source_sink.size(); ++i) {
        cur_source = source_sink[i].first;
        cur_sink = source_sink[i].second;

        res += maxFlow(cur_source, cur_sink);
    }

    double end_time = clock();
    double res_time = ((end_time - start_time) / CLOCKS_PER_SEC);

    cout << "Время работы: " << res_time << " s; ответ: " << res;
}