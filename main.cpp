#include <iostream>
#include <fstream>
#include <ctime>
#include "DataReader.cpp"

using namespace std;

vector<vector<int>> flows;
vector<vector<int>> cur_flows;
queue<pair <int, pair <int, int>>> block;
vector<vector<int>> lay;

bool bfs(vector<int>& q, vector<int>& dest, int source, int sink) {
    int qh = 0, qt = 0;
    q[qt++] = source;
    for (int i = 0; i < dest.size(); ++i)
        dest[i] = -1;
    dest[source] = 0;
    while (qh < qt) {
        int v = q[qh++];
        for (int to=0; to<flows.size(); ++to)
            if (dest[to] == -1 && cur_flows[v][to] < flows[v][to]) {
                q[qt++] = to;
                dest[to] = dest[v] + 1;
            }
    }
    return dest[sink] != -1;
}

int dfs (int v, int flow, vector<int>& dest, vector<int>& ptr, int sink) {
    if (!flow)  return 0;
    if (v == sink)  return flow;
    for (int & to=ptr[v]; to<flows.size(); ++to) {
        if (dest[to] != dest[v] + 1)  continue;
        int pushed = dfs (to, min (flow, flows[v][to] - cur_flows[v][to]), dest, ptr, sink);
        if (pushed) {
            cur_flows[v][to] += pushed;
            cur_flows[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}

int maxFlow(vector<int>& ptr, int source, vector<int>& q, vector<int>& dest, int sink) {
    int flow = 0;
    cout << flows.size() << "PO";
    for (;;) {
        if (!bfs(q, dest, source, sink))  break;
        for (int i = 0; i < ptr.size(); ++i)
            ptr[i] = 0;
        while (int pushed = dfs(source, INT32_MAX, dest, ptr, sink))
            flow += pushed;
    }
    return flow;
}

int main() {
    DataReader* dr = new DataReader("../../kdzdata/input_910_0.0.txt", "Форда-Фалкерсона");

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
//        vector<int> v(flows.size());
//        lay.push_back(v);

        vector<int> a(flows.size());

//        for (int j = 0; j < flows.size(); ++j)
//            a[j] = flows[i][j];

        cur_flows.push_back(a);
    }

    vector<int> dest(flows.size());
    vector<int> ptr(flows.size());
    vector<int> q(flows.size());

//    first_not_del_edge.reserve(flows.size());
//    dest.reserve(flows.size());

    double start_time = clock();

    int res = 0, cur_source, cur_sink;
    for (int i = 0; i < source_sink.size(); ++i) {
        cur_source = source_sink[i].first;
        cur_sink = source_sink[i].second;

        res += maxFlow(ptr, cur_source, q, dest, cur_sink);
    }

    double end_time = clock();
    double res_time = ((end_time - start_time) / CLOCKS_PER_SEC);

    cout << "Время работы: " << res_time << " s; ответ: " << res;
}