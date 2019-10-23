#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include <iostream>
#include <vector>
#include <stack>
#include "Graph.h"

using namespace std;

class GraphColoring 
{
    private:
        int K;
        string graph_name;
        Graph *g;
        stack <GraphNode> s;
        vector<string> SplitString(string input, string delimiter);
        bool ReadInput(vector<string> graph_input, int n);
        void PotencialSpill();
        void Simplify();
        bool Assign();
        int SmallVA(GraphNode node);

    public:
        GraphColoring(vector<string> graph_input);
        void Coloring();
};

#endif