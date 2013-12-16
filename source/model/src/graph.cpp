#include "graph.hpp"
#include "node.hpp"
#include <algorithm>


using namespace std;

Graph::Graph(){}

Graph::Graph(Graph *g) : counter(0) {
    vector<Node *> srcNodes = g->getNodes();
    for (int i = 0; i < srcNodes.size(); ++i) {
        addNode(srcNodes[i]->getId());
    }
    vector<Edge *> srcEdges = g->getEdges();
    for (int i = srcEdges.size()-1; i >= 0; --i) {
        addEdge(srcEdges[i]->first()->getId(), srcEdges[i]->second()->getId());
    }
}

Graph::Graph(int n) : counter(0) {
    for (int i = 0; i < n; ++i) {
        addNode();
    }
}

Graph::Graph(int n, int p) : counter(0) {
    p = p%101;
    for (int i = 0; i < n; ++i) {
        addNode();
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (rand()%101 <= p)
                addEdge(i, j);
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
    for (int i = 0; i < edges.size(); ++i) {
        delete edges[i];
    }
}

Node* Graph::addNode() {
    Node *n = new Node(counter);
    this->nodes.insert(make_pair(counter, n));
    ++counter;
    return n;
}

Node * Graph::addNode(int id) {
    Node *n = new Node(id);
    this->nodes.insert(make_pair(id, n));
    ++counter;
    return n;
}

void Graph::addEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];
    n1->addNeighbour(this->nodes[b]);
    n2->addNeighbour(this->nodes[a]);
    Edge* e= new Edge(n1,n2);
    edges.insert(make_pair(e->hash(),e));
}

bool Graph::hasEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];

    if (n1 && n2) {
        Node *from = n1;
        Node *to = n2;
        if (n1->getNeighbours().size() > n2->getNeighbours().size()) {
            from = n2;
            to = n1;
        }

        for (Node *neighbour : from->getNeighbours()) {
            if (neighbour->getId() == to->getId())
                return true;
        }
    }
    return false;
}

void Graph::removeEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];
    Edge *e = new Edge(n1, n2);
    unordered_map<int,Edge*>::iterator it = edges.find(e->hash());
    if (it != edges.cend()) {
        n1->removeNeighbour(this->nodes[b]);
        n2->removeNeighbour(this->nodes[a]);
        edges.erase(it);
    }
}

void Graph::removeEdges(int a) {
    Node *n = nodes[a];
    for (Node *node : n->getNeighbours()) {
        removeEdge(a, node->getId());
    }
}

Node* Graph::getRandomNode() {
    int select = rand() % nodes.size();
    map<int,Node*>::iterator it = nodes.begin();
    advance(it, select);
    return it->second;
}

Edge* Graph::getRandomEdge() {
    int select = rand() % nbEdges();
    unordered_map<int,Edge*>::iterator it = edges.begin();
    advance(it, select);
    return it->second;
}

void Graph::removeNode(int id) {
    removeEdges(id);
    nodes.erase(id);
}

void Graph::removeNode(Node *n) {
    removeNode(n->getId());
}

vector<Node*> Graph::getCover() {
    Graph *localGraph(this);
    vector<Node*> cover;

    while (localGraph->edges.size() > 0) {
        Edge *edge = localGraph->getRandomEdge();
        cover.push_back(edge->first());
        cover.push_back(edge->second());
        localGraph->removeNode(edge->first());
        localGraph->removeNode(edge->second());
    }
    return cover;
}

Node* Graph::getHighestDegreeNode() {
    Node *selectedNode;
    int highestDegree = -1;
    for (pair<int,Node*> pair : nodes) {
        Node *node = pair.second;
        if (highestDegree < node->degree()) {
            highestDegree = node->degree();
            selectedNode = node;
        }
    }
    return selectedNode;
}

vector<Node*> Graph::getCoverGlouton() {
    Graph *localGraph = new Graph(this);
    vector<int> cover;
    vector<int> degrees; //pour un acces direct au degré de chaque noeud;
    vector< list<int> > nodesByDegree; //pour trier les noeuds en fonction de leur degré
    for(int i = 0; i < nbNodes(); i++) {
        int degree = nodes[i]->degree();
        degrees.push_back(degree);
        while (nodesByDegree.size()<=degree){
            list<int> init;
            nodesByDegree.push_back(init);
        }
        nodesByDegree[degree].push_back(i);
    }

    while (localGraph->nbEdges() > 0) {
        while(nodesByDegree[nodesByDegree.size() - 1].size() == 0) {
            nodesByDegree.pop_back();
        }
        int node = nodesByDegree[nodesByDegree.size() - 1].front();
        nodesByDegree[nodesByDegree.size() - 1].pop_front();
        while (nodesByDegree[nodesByDegree.size() - 1].size() == 0) {
            nodesByDegree.pop_back();
        }
        cover.push_back(node);
        for (Node *n : localGraph->getNode(node)->getNeighbours()) {
            int id = n->getId();
            nodesByDegree[degrees[id]].remove(id);
            --degrees[id];
            nodesByDegree[degrees[id]].push_front(id);
        }
        localGraph->removeNode(node);
    }
    delete localGraph;
    vector<Node*> result;
    for(int i = 0; i < cover.size(); i++)
        result.push_back(nodes[cover[i]]);
    return result;
}

Node* Graph::getNode(int id) {
    return nodes[id];
}

vector<Node*> Graph::getNodes() const {
    vector<Node*> dup;
    for (pair<int,Node*> pair : nodes) {
        dup.push_back(pair.second);
    }
    return dup;
}

vector<int> getKCoverRec(Graph *localGraph, int K, vector<int>cover) {
    if (localGraph->nbEdges() > 0) {
        if (localGraph->nbEdges() >= K*localGraph->nbNodes()) {
            delete localGraph;
            cover.clear();
            return cover;
        } else {
            Edge *e = localGraph->getRandomEdge();
            Graph *localGraph1 = new Graph(localGraph);
            Graph *localGraph2 = new Graph(localGraph);
            int node1 = e->first()->getId();
            int node2 = e->second()->getId();
            delete localGraph;
            vector<int> cover1(cover);
            vector<int> cover2(cover);
            cover1.push_back(node1);
            localGraph1->removeNode(node1);
            cover2.push_back(node2);
            localGraph2->removeNode(node2);
            cover1 = getKCoverRec(localGraph1,K-1, cover1);
            cover2 = getKCoverRec(localGraph2,K-1, cover2);
            if (cover2.size() == 0)
                cover2 = cover1;
            if (cover1.size() == 0)
                cover1 = cover2;
            return cover1.size()>cover2.size() ? cover2 : cover1;
        }
    } else {
        delete localGraph;
        return cover;
    }
}

int Graph::kernelize(int k, vector<int> *cover) {
    cout << "kernelize(" << k << ") : k' = ";
    int Kprime = k;
    Node *highestDegreeNode;
    while ((Kprime > 0) && ((highestDegreeNode = getHighestDegreeNode())->degree() > Kprime)) {
        cover->push_back(highestDegreeNode->getId());
        this->removeNode(highestDegreeNode->getId());
        --Kprime;
    }
    cout << Kprime << endl;
    return Kprime;
}

vector<Node*> Graph::getKCover(int k) {
    Graph *localGraph = new Graph(this);
    vector<int> cover;
    vector<Node*>result;

    int Kprime = localGraph->kernelize(k, &cover);
    if (localGraph->nbEdges() > Kprime*localGraph->nbNodes()){
        cout << "nbEdges : " << localGraph->nbEdges() << endl << "Kprime*K : " << Kprime*k << endl;
        delete localGraph;
        return result;
    } else {
        cover = getKCoverRec(localGraph, Kprime, cover);
        for (int nodeId : cover) {
            result.push_back(nodes[nodeId]);
        }
        return result;
    }
}

int Graph::nbEdges() {
    return edges.size();
}

int Graph::nbNodes() {
    return nodes.size();
}

vector<Edge*> Graph::getEdges() const {
    vector<Edge*> vec;
    for (pair<int,Edge*> pair : edges) {
        vec.push_back(pair.second);
    }
    return vec;
}

void Graph::coverToMinisat(string outputfile) {
    ofstream myFile;
    myFile.open(DEFAULT_DIRECTORY + outputfile);

    if(myFile.is_open()) {
        int graphSize = this->getNodes().size();
        myFile << "p cnf " << graphSize << " " << graphSize << endl;

        int literals = 0;
        for(Node* node : this->getNodes()) {
            for(Node* neighbour : node->getNeighbours()) {
                myFile << node->getId()+1 << " " << neighbour->getId()+1 << " 0" << endl;
                ++literals;
            }
        }

    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
}

vector<Node*> Graph::minisatToCover(string inputFile) {
    ifstream input;
    input.open(DEFAULT_DIRECTORY + inputFile);
    vector<Node*> nodes;

    if(input.is_open()) {
        string line("");
        getline(input, line);
        getline(input, line); // read second line from file
        istringstream ss(line);
        string buffer;
        while(ss >> buffer) {
            int id = stoi(buffer);
            if(id > 0) {
                nodes.push_back(new Node(id-1));
            }
        }
    } else {
        cout << "Unable to read file, exiting" << endl;
        exit(1);
    }

    return nodes;
}

Graph* Graph::edgeComplementGraph(){
    Graph *comp = new Graph(nbNodes(),100);
    for(Edge* e : this->getEdges()){
        comp->removeEdge(e->first()->getId(),e->second()->getId());
    }
    return comp;
}

Graph* Graph::edgeComplementGraph2(){
    Graph * comp = new Graph(this);
    Graph * local = new Graph(this);
    for(Node * compNode : comp->getNodes()){
        for(Node * compNodeNeighbour : comp->getNodes()){
            if(!(compNodeNeighbour==compNode)){
                int id1 = compNode->getId();
                int id2 = compNodeNeighbour->getId();
                if(local->hasEdge(id1,id2)){
                    local->removeEdge(id1,id2);
                    comp->removeEdge(id1,id2);
                }
                else if(!comp->hasEdge(id1,id2)){
                    comp->addEdge(id1,id2);
                }
            }
        }
    }
    return comp;
}
