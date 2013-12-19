#include <algorithm>
#include "graphutils.hpp"
#include "graph.hpp"
#include "node.hpp"
#include "tree.hpp"

using namespace std;

Graph::Graph():counter(0){}

Graph::Graph(IGraph *g) : counter(0) {
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

Node* Graph::addNode(int id) {
    map<int, Node*>::iterator it = nodes.find(id);
    if (it != nodes.end()) {
        return it->second;
    }
    Node *n = new Node(id);
    this->nodes.insert(make_pair(id, n));
    ++counter;
    return n;
}

void Graph::addEdge(int a, int b) {
    map<int, Node*>::iterator it = nodes.find(a);
    if (it != nodes.end()) {
        it = nodes.find(b);
        if (it != nodes.end()) {
            Node *n1 = this->nodes[a];
            Node *n2 = this->nodes[b];
            n1->addNeighbour(this->nodes[b]);
            n2->addNeighbour(this->nodes[a]);
            Edge* e= new Edge(n1,n2);
            edges.insert(make_pair(e->hash(),e));
        } else {
            cerr << "Node " << b << " does not exist" << endl;
        }
    } else {
        cout << "Node " << a << " does not exist" << endl;
    }
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
    map<int, Node*>::iterator it = nodes.find(a);
    if (it != nodes.end()){
        Node *n = nodes[a];
        for (Node *node : n->getNeighbours()) {
            removeEdge(a, node->getId());
        }
    }
}

Node* Graph::getRandomNode() {
    if (nodes.size() == 0)
        return 0;
    int select = rand() % nodes.size();
    map<int,Node*>::iterator it = nodes.begin();
    advance(it, select);
    return it->second;
}

Edge* Graph::getRandomEdge() {
    if (edges.size() == 0)
        return 0;
    int select = rand() % nbEdges();
    unordered_map<int,Edge*>::iterator it = edges.begin();
    advance(it, select);
    return it->second;
}

Edge* Graph::getEdge(int a, int b) {
    Edge tmp(nodes[a], nodes[b]);
    return edges[tmp.hash()];
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

vector<Node*> Graph::getCoverGreedy() {
    Graph *localGraph = new Graph(this);
    localGraph->supressIsolatedNode();
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

int Graph::kernelize(int k, vector<int> *cover) {
    supressIsolatedNode();
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

/*void Graph::coverToMinisat(string outputfile) {
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
        cout << "Unable to open file " << outputfile << endl;
        exit(1);
    }
}*/


vector<Node*> Graph::getKCoverWithMinisat(int k) {
    if(k >= (this->getNodes()).size())
        return this->getNodes();
    vector<Node*> cover;
    vector<int> nodeIds = this->getIndependentSet(this->getNodes().size() - k);
    if(nodeIds.size() > 0) {
        for(Node* node : this->getNodes()) {
            if(find(nodeIds.begin(), nodeIds.end(), node->getId()) == nodeIds.end())
                cover.push_back(node);
        }
    }
    return cover;
}

vector<int> Graph::getIndependentSet(int size){
    Graph * g = edgeComplementGraph();
    vector<int> result =  g->getClique(size);

    delete g;
    return result;
}


vector<int> Graph::getClique(int size) {
    Graph *clique = new Graph(size, 100);
    vector<int> result = this->getIsomorphicSubgraph(clique);
    delete clique;
    return result;
}

vector<int> Graph::getIsomorphicSubgraph(Graph* subgraph) {
    unordered_map<int, int> vars, reverse_vars, hashes;
    ofstream myFile;
    stringstream total, tmp;

    int numSubNodes = subgraph->getNodes().size();
    int numNodes = this->getNodes().size();

    myFile.open(DEFAULT_INPUT_DIR + "g.cnf");

    if(myFile.is_open()) {
        int numClauses = 0;
        int numLits = 0;

        for(Node* k : subgraph->getNodes()) {
            for(Node* i : this->getNodes()) {
                int ki = GraphUtils::hashPair(k->getId()+1, i->getId()+1);
                hashes.insert(make_pair(ki, i->getId()));

                if(vars.find(ki) == vars.end()) {
                    reverse_vars.insert(make_pair(vars.size()+1, ki));
                    vars.insert(make_pair(ki, vars.size()+1));
                }

                for(Node* j : this->getNodes()) {
                    if(i->getId() != j->getId()) {
                        int kj = GraphUtils::hashPair(k->getId()+1, j->getId()+1);
                        hashes.insert(make_pair(kj, j->getId()));

                        if(vars.find(kj) == vars.end()) {
                            reverse_vars.insert(make_pair(vars.size()+1, kj));
                            vars.insert(make_pair(kj, vars.size()+1));
                        }
                        tmp << "-" <<  vars[ki] << " -" << vars[kj] << " 0" << endl;
                        ++numClauses;
                        numLits += 2;
                    }
                }

                // function is total
                total << vars[ki] << " ";
                ++numLits;

                for(Node* k2 : subgraph->getNodes()) {
                    if(k->getId() != k2->getId()) {

                        int k2i = GraphUtils::hashPair(k2->getId()+1, i->getId()+1);
                        hashes.insert(make_pair(k2i, i->getId()));
                        if(vars.find(k2i) == vars.end()) {
                            reverse_vars.insert(make_pair(vars.size()+1, k2i));
                            vars.insert(make_pair(k2i, vars.size()+1));
                        }

                        // function is injective
                        tmp << "-" << vars[ki] << " -" << vars[k2i] << " 0" << endl;
                        ++numClauses;
                        numLits += 2;
                        for(Node* i2 : this->getNodes()) {
                            if(i->getId() != i2->getId()) {

                                // in our case, subgraph is a clique, so whichever pair of vertices we chose, there will always be an edge to join them
                                // Therefore we can remove the conditions stating that the edge must not be in the subgraph.
                                if(!this->hasEdge(i->getId(), i2->getId())) {
                                    int k2i2 = GraphUtils::hashPair(k2->getId()+1, i2->getId()+1);
                                    hashes.insert(make_pair(k2i2, i2->getId()));
                                    if(vars.find(k2i2) == vars.end()) {
                                        reverse_vars.insert(make_pair(vars.size()+1, k2i2));
                                        vars.insert(make_pair(k2i2, vars.size()+1));
                                    }
                                    // function is isomorphique
                                    tmp << "-" << vars[ki] << " -" << vars[k2i2] << " 0" << endl;
                                    ++numClauses;
                                    numLits += 2;
                                }
                            }
                        }
                    }
                }
            }

            total << "0" << endl;
            tmp << total.rdbuf();
            ++numClauses;
            total.flush();
        }

        // Useful information for minisat
        myFile << "c" <<endl;
        myFile << "c #vars:" << numNodes*numSubNodes << "    #clauses:" << numClauses << "    #lits:" << numLits << endl;
        myFile << "c" << endl;

        // append all clauses to myFile
        myFile << tmp.rdbuf();
        tmp.flush();
        myFile.close();

        vector<int> result = getSatCover(reverse_vars, hashes);
        return result;
    }
}

vector<int> getSatCover(unordered_map<int, int> reverse_vars, unordered_map<int, int> hashes) {
    vector<int> result;
    stringstream cmd;
    cmd << DEFAULT_MINISAT_DIR << " " << DEFAULT_INPUT_DIR << "g.cnf " << DEFAULT_OUTPUT_DIR << "g_res";
    string cmdString = cmd.str();
    system(cmdString.c_str());
    ifstream satResult;
    stringstream fileRes;
    fileRes << DEFAULT_OUTPUT_DIR << "g_res";
    satResult.open(fileRes.str());

    if(satResult.is_open()) {
        string line("");
        getline(satResult, line);
        if(line == "SAT") {
            getline(satResult, line);
            istringstream iss(line);
            string buffer;
            while(iss >> buffer) {
                int val = stoi(buffer);
                if(val > 0) {
                    result.push_back(hashes.find(reverse_vars.find(val)->second)->second);
                }
            }
        }
    }
    return result;
}

vector<Node*> Graph::minisatToCover(string inputFile) {
    ifstream input;
    input.open(DEFAULT_INPUT_DIR + inputFile);
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

Graph* Graph::edgeComplementGraph() {
    Graph *comp = new Graph(nbNodes(),100);
    for(Edge* e : this->getEdges()){
        comp->removeEdge(e->first()->getId(),e->second()->getId());
    }
    return comp;
}

Graph* Graph::edgeComplementGraph2() {
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
                } else if(!comp->hasEdge(id1,id2)){
                    comp->addEdge(id1,id2);
                }
            }
        }
    }
    return comp;
}

string Graph::getType() {
    return "graph";
}

Tree* Graph::DepthFirstSearch(){
    Graph * localGraph = new Graph(this);
    Tree * result = new Tree();
    list<Node*> stack;
    vector<bool> done;
    for (Node* n : getNodes()){
        while(done.size() <= n->getId()){
            done.push_back(false);
        }
    }
    Node * current = localGraph->getHighestDegreeNode();
    stack.push_front(current);
    result->addNode(current->getId());
    while(stack.size() > 0){
        current = stack.front();
        int id = current->getId();
        stack.pop_front();
        if(!done[id]){
            done[id] = true;
            for(Node* neighbour : current->getNeighbours()){
                int nId =neighbour->getId();
                if(!done[nId]){
                    result->removeEdges(nId);
                    result->addNode(nId);
                    result->addEdge(nId, id);
                    stack.push_front(neighbour);
                }
            }
        }
    }
    return result;
}


vector<Node*> Graph::getCoverDFS(){
    supressIsolatedNode();
    Tree * t = DepthFirstSearch();
    return t->getCover();
}

void Graph::supressIsolatedNode(){
    for (Node*n : getNodes()){
        if (n->degree() == 0)
            removeNode(n);
    }
}
