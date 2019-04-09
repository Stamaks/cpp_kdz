#include <iostream>
#include <fstream>
#include <vector>

class DataReader {

private:

    std::fstream fin;

public:
    int number_of_vertexes;

    ~DataReader(){
        fin.close();
    }

    DataReader(std::string filename, std::string alg_name = "") {
        fin.open(filename, std::ios::in);

        unsigned long start = filename.find('_');
        unsigned long end = filename.find('_', start + 1);

        number_of_vertexes = std::stoi(filename.substr(start + 1, end - (start + 1)));

        std::cout << "Начинаю тест алгоритма " << alg_name << " на " << number_of_vertexes << " вершин.\n";
    }

    void read(std::vector<std::vector<int>>& flows)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::string s;
        int cur;
        for (int i = 0; i < number_of_vertexes; ++i)
        {
            std::vector<int>* vec = new std::vector<int>();

            for (int j = 0; j < number_of_vertexes; ++j)
            {
                fin >> cur;
                vec->push_back(cur);
            }

            flows.push_back(*vec);
        }
    }
};