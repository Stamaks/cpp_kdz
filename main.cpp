#include <iostream>
#include <fstream>
#include "FlowNetwork.cpp"
#include "DataReader.cpp"

using namespace std;

int dft(int u, int Cmin)
{

}

int main() {
    DataReader* dr = new DataReader("../../kdzdata/input_10_0.0.txt");

    vector<vector<int>> v;
    dr->read(v);

    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
        {
            cout << v[i][j] << " ";
        }

        cout << "\n";
    }
}