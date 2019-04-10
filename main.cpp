#include <iostream>
#include <fstream>
#include <ctime>
#include "FlowNetwork.cpp"
#include "DataReader.cpp"

using namespace std;

vector<vector<int>> flows;
vector<vector<int>> cur_flows;
vector<bool> visited;
int source, sink;

int dft(int current, int flow)
{
    if (current == sink)
        return flow;

    visited[current] = true;
    for (int i = 0; i < flows[current].size(); ++i)
    {
        if (!flows[current][i])
            continue;

        if (!visited[i] and cur_flows[current][i] < flows[current][i])
        {
            int delta = dft(i, min(flow, flows[current][i] - cur_flows[current][i]));
            if (delta > 0)
            {
                cur_flows[current][i] += delta;
                cur_flows[i][current] -= delta;
                return delta;
            }
        }
    }

    return 0;

}

int main() {
    DataReader* dr = new DataReader("../../kdzdata/input_10_disco.txt");

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
        cur_flows.push_back(v);
    }

    for (int i = 0; i < flows.size(); ++i)
    {
        visited.push_back(false);
    }

    double start_time = clock();


    int res = 0, cur_source, cur_sink, cur;
    for (int i = 0; i < source_sink.size(); ++i) {
        cur_source = source_sink[i].first;
        cur_sink = source_sink[i].second;
//        cur = dft(source, INT32_MAX);
//        while (cur > 0) {
//            res += cur;
//
//            for (int i = 0; i < flows.size(); ++i) {
//                visited[i] = false;
//            }
//
//            cur = dft(source, INT32_MAX);
//        }
    }

    double end_time = clock();
    double res_time = ((end_time - start_time) / CLOCKS_PER_SEC);

    cout << "Время работы: " << res_time << " s; ответ: " << res;

}