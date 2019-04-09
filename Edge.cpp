class Edge {
    int max_flow;
    int current_flow;
    int from;
    int to;

public:
    Edge(int from, int to, int max_flow) {
        this->from = from;
        this->to = to;
        this->max_flow = max_flow;
        current_flow = 0;
    }
};