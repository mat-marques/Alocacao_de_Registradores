#include "Graph.h"

Graph::Graph(int rows){
    graph.resize(rows);
};

/*
* Insere o id do nó, no qual father é o valor e row é a 
* posição que se inserirá na matrix
*/
bool Graph::InsertFather(int row, int father) {
    if(row >= 0 && row < this->graph.size()){
        this->graph[row].color = -1;
        this->graph[row].father = father;
        return true;
    }
    return false;
};

/*
* Insere uma aresta em um determinado nó, no qual children 
* é o valor e row é a posição que se inserirá na matrix
*/
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

/*
* Retorna a aresta de um nó, no qual row é a posição do nó e
* col é a posição da aresta na matrix
*/
int Graph::Get(int row, int col) {
    if(row >= 0 && row < this->graph.size()){
        if(col >= 0 && col < this->graph[row].childrens.size()) {
            return this->graph[row].childrens[col].value;
        }
    }
};


/*
* Remove uma aresta de um nó do grafo, no qual o nó da aresta removida será o valor
* representado por father. A remoção seta como false o valor active de uma aresta.
*/
void Graph::RemoveChildren(int father){
    for(int i = 0; i < this->graph.size(); i++) {
        for(int j = 0; j < this->graph[i].childrens.size(); j++) {
            if(this->graph[i].childrens[j].value == father) {
                this->graph[i].childrens[j].active = false;
            }
        }
    }
}

/*
* Retorna o grau de um nó.
*/
int Graph::ChildrenSize(int row) {
    int size = 0;
    for(int i = 0; i < this->graph[row].childrens.size(); i++) {
        if(this->graph[row].childrens[i].active) {
            size++;
        }
    }
    return size;
}

/*
* Ativa todas as arestas dos nós do grafo que foram definidas como removidas.
*/
void Graph::ActiveAllChildren(){
    for(int i = 0; i < this->graph.size(); i++) {
        this->graph[i].color = -1;
        for(int j = 0; j < this->graph[i].childrens.size(); j++) {
            this->graph[i].childrens[j].active = true;
        }
    }
}

/*
* Insere um nó no grafo. O nó é representado por node.
*/
void Graph::InsertNode(GraphNode node){
    this->graph.push_back(node);
}

/*
* Procura a cor de um nó no grafo, a procura buscará o nó com
* o valor representado por father. Se encontrar retorna o valor
* caso contrario retorna -1.
*/
int Graph::FindColorByFather(int father){
    for(int i = 0; i < this->graph.size(); i++) {
        if(this->graph[i].father == father) {
            return this->graph[i].color;
        }
    }
    return -1;
}

/*
* Printa o grafo na saída padrão.
*/
void Graph::PrintGraph() {
    for(int i = 0; i < this->graph.size(); i++) {
        cout << this->graph[i].father << " --> ";
        for(int j = 0; j < this->graph[i].childrens.size(); j++) {
            cout << this->graph[i].childrens[j].value << " ";
        }
        cout << endl;
    }
};