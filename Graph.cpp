#include "Graph.h"

Graph::Graph(int rows){
    graph.resize(rows);
};

bool Graph::InsertFather(int row, int father) {
    if(row >= 0 && row < this->graph.size()){
        this->graph[row].color = -1;
        this->graph[row].father = father;
        return true;
    }
    return false;
};

bool Graph::InsertChildren(int row, int children) {
    GraphNodeChild c;
    c.value = children;
    c.active = true;
    if(row >= 0 && row < this->graph.size()){
        this->graph[row].childrens.push_back(c);
        return true;
    }
    return false;
};

int Graph::Get(int row, int col) {
    if(row >= 0 && row < this->graph.size()){
        if(col >= 0 && col < this->graph[row].childrens.size()) {
            return this->graph[row].childrens[col].value;
        }
    }
};

void Graph::RemoveChildren(int father){
    for(int i = 0; i < this->graph.size(); i++) {
        for(int j = 0; j < this->graph[i].childrens.size(); j++) {
            if(this->graph[i].childrens[j].value == father) {
                this->graph[i].childrens[j].active = false;
            }
        }
    }
}

int Graph::ChildrenSize(int row) {
    int size = 0;
    for(int i = 0; i < this->graph[row].childrens.size(); i++) {
        if(this->graph[row].childrens[i].active) {
            size++;
        }
    }
    return size;
}

void Graph::ActiveAllChildren(){
    for(int i = 0; i < this->graph.size(); i++) {
        this->graph[i].color = -1;
        for(int j = 0; j < this->graph[i].childrens.size(); j++) {
            this->graph[i].childrens[j].active = true;
        }
    }
}

void Graph::InsertNode(GraphNode node){
    this->graph.push_back(node);
}

int Graph::FindColorByFather(int father){
    for(int i = 0; i < this->graph.size(); i++) {
        if(this->graph[i].father == father) {
            return this->graph[i].color;
        }
    }
    return -1;
}

void Graph::PrintGraph() {
    for(int i = 0; i < this->graph.size(); i++) {
        cout << this->graph[i].father << " --> ";
        for(int j = 0; j < this->graph[i].childrens.size(); j++) {
            cout << this->graph[i].childrens[j].value << " ";
        }
        cout << endl;
    }
};