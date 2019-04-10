#include <iostream>
#include <fstream>
#include <ctime>
#include "DataReader.cpp"

using namespace std;

vector<vector<int>> cur_flows;
vector<bool> visited;

int dfs(int current, int sink, int flow)
{
    if (current == sink)
        return flow;

    visited[current] = true;
    for (int i = 0; i < cur_flows[current].size(); ++i)
    {
        if (!visited[i] and cur_flows[current][i] > 0)
        {
            int delta = dfs(i, sink, min(flow, cur_flows[current][i]));
            if (delta > 0)
            {
                cur_flows[current][i] -= delta;
                cur_flows[i][current] += delta;
                return delta;
            }
        }
    }

    return 0;
}

int maxFlow(vector<bool>& visited, int source, int sink) {
    int flow = 0;
    int delta = dfs(source, sink, INT32_MAX);
    while (delta > 0) {
        flow += delta;

        for (int i = 0; i < cur_flows.size(); ++i) {
            visited[i] = false;
        }

        delta = dfs(source, sink, INT32_MAX);
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

        res += maxFlow(visited, cur_source, cur_sink);
    }

    double end_time = clock();
    double res_time = ((end_time - start_time) / CLOCKS_PER_SEC);

    cout << "Время работы: " << res_time << " s; ответ: " << res;

}