#include "GraphColoring.h"

GraphColoring::GraphColoring(vector<string> graph_input) {
    int n = 1;
    n = graph_input.size();
    this->g = new Graph(n-2);
    this->ReadInput(graph_input, n);
}

/*
* Função que realiza o split de um string input por um delimitador delimiter.
* A saida é retornada em um vetor de strings.
*/
vector<string> GraphColoring::SplitString(string input, string delimiter) {
	vector<string> l;
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        l.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    l.push_back(input);
	return l;
}

/*
* Leitura da entrada para a configuração do grafo. A entrada está
* em graph_input e n é o tamanho de grapf_input. O grafo é posta
* na variável this->g da classe.
*/
bool GraphColoring::ReadInput(vector<string> graph_input, int n){
    vector<string> split_row;
    //Leitura do nome do grafo
    split_row = SplitString(graph_input[0], " ");
    this->graph_name = split_row[1].substr(0, split_row[1].size() - 1);
    split_row.clear();
    
    //Leitura do número de registradores
    split_row = SplitString(graph_input[1], "=");
    this->K = stoi(split_row[1]);
    split_row.clear();

    //Leitura do grafo de entrada
    for(int i = 2; i < n; i++) {
        //Faz o split das linhas de entrada
        split_row = SplitString(graph_input[i], " ");
        this->g->InsertFather(i-2, stoi(split_row[0]));
        //insere no grafo os valores de entrada
        for(int j = 2; j < split_row.size(); j++) {
            this->g->InsertChildren(i-2, stoi(split_row[j]));
        }
        split_row.clear();
    }
    //this->g->PrintGraph();
    return true;
}

/*
* Realiza o Potencial Spill do processo de alocação de registradores.
*/
void GraphColoring::PotencialSpill(){
    int a, degreePosition = 0, degree;

    degree = this->g->ChildrenSize(0);
    degreePosition = 0;
    //Procura o menor grau
    for(int i = 0; i < this->g->graph.size(); i++) {
        a = this->g->ChildrenSize(i);
        if(a > degree) {
            degree = a;
            degreePosition = i;
        }
        else if(a == degree) {
            if(this->g->graph[i].father < this->g->graph[degreePosition].father) {
                degree = a;
                degreePosition = i;
            }
        }
    }

    this->g->RemoveChildren(this->g->graph[degreePosition].father);
    this->s.push(this->g->graph[degreePosition]);
    cout << "Push: " << this->g->graph[degreePosition].father << " *" << endl;
    this->g->graph.erase(this->g->graph.begin() + degreePosition);
}

/*
* Realiza o Simplify do processo de alocação de registradores.
*/
void GraphColoring::Simplify(){
    int a, degreePosition, degree;
    while(this->g->graph.size() > 0) {
        
        degree = this->g->ChildrenSize(0);

        if(degree < this->K) degreePosition = 0;
        else degreePosition = -1;
        //Procura o menor grau
        for(int i = 0; i < this->g->graph.size(); i++) {
            a = this->g->ChildrenSize(i);
            if(a < this->K){
                if(a < degree) {
                    degree = a;
                    degreePosition = i;
                }
                else if(a == degree) {
                    if(this->g->graph[i].father < this->g->graph[degreePosition].father) {
                        degree = a;
                        degreePosition = i;
                    }
                }
            }
        }

        if(degreePosition == -1) { //PotencialSpill
            this->PotencialSpill();
        }
        else { //Retirou o nó
            this->g->RemoveChildren(this->g->graph[degreePosition].father);
            this->s.push(this->g->graph[degreePosition]);
            cout << "Push: " << this->g->graph[degreePosition].father << endl;
            this->g->graph.erase(this->g->graph.begin() + degreePosition);
        }
    }
}

/*
* Função disponível ao usuário para a realização do processo total da alocação de registradores
* utilizando coloração de grafos.
*/
void GraphColoring::Coloring(){

    int k = this->K, a, b, space = 1;
    string intToString;
    vector<bool> results;
    cout << "Graph " << this->graph_name << " -> Physical Registers: " << this->K << endl;
    cout << "----------------------------------------" << endl;

    //Realiza o processo de alocação até K = 2
    while(this->K >= 2){
        cout << "----------------------------------------" << endl;
        cout << "K = " << this->K << endl;
        cout << endl;

        this->Simplify();
        results.push_back( this->Assign() );
        
        this->K = this->K - 1;
    }

    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------";
    intToString = std::to_string(k);
    a = intToString.size();
    for(int i = 0; i < results.size(); i++) {
        cout << endl;

        //Controle da quantidade de espaços para se printar na tela
        intToString = std::to_string(k - i);
        b = intToString.size();
        if(b < a) {
            space = space + 1;
            a = b;
        } 

        if(results[i]){
            cout << "Graph " << this->graph_name << " -> " << "K =";
            for(int j = 0; j < space; j++){
                cout << " ";
            }   
            cout << (k - i) << ": Successful Allocation";
        }
        else {
            cout << "Graph " << this->graph_name << " -> " << "K =" ;
            for(int j = 0; j < space; j++){
                cout << " ";
            }   
            cout << (k - i) << ": SPILL";
        }
    }
    delete this->g;
}

/*
* Retorna a menor cor para um determinado nó do grafo.
*/
int GraphColoring::SmallVA(GraphNode node) {
    int color;
    vector<int> colors;
    //Seta as cores com disponíveis
    for(int i = 0; i < this->K; i++){
        colors.push_back(1);
    }

    //Seta as cores que não estão disponíveis para coloração
    for(int i = 0; i < node.childrens.size(); i++) {
        // cout << node.childrens[i].value << " " << this->K << endl;
        if(node.childrens[i].value < this->K) { //Registrador físico
            colors[node.childrens[i].value] = 0;
        }
        else { //Registrador virtual
            color = this->g->FindColorByFather(node.childrens[i].value);
            if(color != -1 ) {
                colors[color] = 0;
            }
        }
    }

    // for(int i = 0; i < this->K; i++)
    //     cout << colors[i] << " ";
    // cout << endl;
    //Retorna a menor cor disponível
    for(int i = 0; i < this->K; i++){
        if(colors[i]) {
            return i;
        }
    }

    return -1;
}

/*
* Realiza o Assign do processo de alocação de registradores.
* Retorna true se o processo de coloração ocorreu com sucesso
* e falso caso contrário.
*/
bool GraphColoring::Assign(){
    GraphNode node;
    int color = -1;
    while(this->s.size() > 0) {
        node = this->s.top();
        this->s.pop();
        color = this->SmallVA(node);
        if(color != -1){ //Cor disponível
            node.color = color;
            cout << "Pop: " << node.father << " -> " << color <<endl;
        }
         else { //Cor indisponível
            cout << "Pop: " << node.father << " -> NO COLOR AVAILABLE" <<endl;
            this->g->InsertNode(node);
            //Reinsere no grafo
            while(this->s.size() > 0) {
                node = this->s.top();
                this->s.pop();
                this->g->InsertNode(node);
            }
            this->g->ActiveAllChildren();
            return false;
        }
        this->g->InsertNode(node);
    }
    this->g->ActiveAllChildren();
    return true;
}
