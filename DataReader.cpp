#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class DataReader {

private:

    fstream fin;

public:
    int number_of_vertexes;

    ~DataReader(){
        fin.close();
    }

    DataReader(string filename, string alg_name = "") {
        fin.open(filename, ios::in);

        unsigned long start = filename.find('_');
        unsigned long end = filename.find('_', start + 1);

        number_of_vertexes = stoi(filename.substr(start + 1, end - (start + 1)));

        cout << "Начинаю тест алгоритма " << alg_name << " на " << number_of_vertexes << " вершин.\n";
    }

    int bfs(int s, vector<int>& visited, vector<vector<int>>& flows, set<int>& sinks){

        queue<int> queue;

        visited[s] = true;
        queue.push(s);

        while(!queue.empty())
        {
            s = queue.front();
            queue.pop();

            for (int i = 0; i < number_of_vertexes; ++i)
            {
                if (!visited[i] && flows[s][i])
                {
                    visited[i] = 1;

                    if (sinks.count(i))
                        return i;

                    queue.push(i);
                }
            }
        }
    }

    void read(vector<vector<int>>& flows, vector<pair<int, int>>& source_sink)
    {
        if (!fin.is_open())
            throw ios_base::failure("file not open");

        string s;
        int cur;
        bool is_sink;
        set<int> sinks;
        set<int> sources;

        for (int i = 0; i < number_of_vertexes; ++i)
            sources.insert(i);

        for (int i = 0; i < number_of_vertexes; ++i)
        {
            vector<int>* vec = new vector<int>();

            is_sink = true;
            for (int j = 0; j < number_of_vertexes; ++j)
            {
                fin >> cur;
                if (cur != 0) {
                    is_sink = false;
                    sources.erase(j);
                }
                vec->push_back(cur);
            }

            if (is_sink)
                sinks.insert(i);

            flows.push_back(*vec);
        }

        vector<int> visited(number_of_vertexes);
        int cur_sink;
        for (int i = 0; i < number_of_vertexes; ++i)
        {
            if (sources.count(i))
            {
                cur_sink = bfs(i, visited, flows, sinks);
                source_sink.push_back(make_pair(i, cur_sink));
            }
        }
    }
};