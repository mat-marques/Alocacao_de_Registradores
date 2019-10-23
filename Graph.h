#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

struct GraphNodeChild {
    int value;
    bool active;
};

struct GraphNode {
    int father;
    int color;
    vector<GraphNodeChild> childrens;
};

class Graph
{
    public:
        vector<GraphNode> graph;
        
        Graph(int rows);

        bool InsertFather(int row, int father);

        bool InsertChildren(int row, int children);

        int Get(int row, int col);

        int FindColorByFather(int father);
        
        void RemoveChildren(int father);

        void ActiveAllChildren();

        int ChildrenSize(int row);

        void InsertNode(GraphNode node);

        void PrintGraph();
};

#endif