#include <iostream>
#include <vector>
#include "GraphColoring.h"

using namespace std;


int main(int argc, char* argv[]) {
    int k, n;
    GraphColoring *gc;
    string input;
    vector<string> graph_input;

    //Leitura da entrada
    while(getline(cin, input)) {
        graph_input.push_back(input);
    }
    
    gc = new GraphColoring(graph_input);
    gc->Coloring();
    delete gc;
}