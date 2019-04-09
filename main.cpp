#include <iostream>
#include <fstream>
#include <ctime>
#include "FlowNetwork.cpp"
#include "DataReader.cpp"

using namespace std;

int dft(int current, int flow, vector<vector<int>>& flows, vector<vector<int>>& cur_flows,
        vector<bool>& visited, const int& source, const int& sink)
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

}

int main() {
    DataReader* dr = new DataReader("../../kdzdata/input_10_0.0.txt");

    vector<vector<int>> flows;
    int source, sink;
    dr->read(flows, source, sink);

    cout << source << sink;

    vector<vector<int>> current_flows(flows.size(), vector<int>(flows.size()));

    double start_time = clock();

//    dft();

    double end_time = clock();
    double res_time = ((end_time - start_time) / CLOCKS_PER_SEC);

}