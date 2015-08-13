//Purpose: Comparing depth first search implemented recursively (using an implicit stack)
//to depth first search implemented iteratively (using an explicit stack)
#include <iostream>
using namespace std;

#define MAX_V 100

bool discovered[MAX_V + 1];
bool processed[MAX_V + 1];

class Node{
    public:
        int key;
        Node *next;
        Node(int key);
};

Node::Node(int key){
    this->key = key;
    this->next = NULL;
}

class Stack{
    public:
        Node *top;
        Stack();
        ~Stack();
        void push(int);
        int pop();
        bool empty();
};

Stack::Stack(){
    this->top = NULL;
}

Stack::~Stack(){
    Node *curr = this->top;
    while(curr != NULL){
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void Stack::push(int key){
    Node *node = new Node(key);
    if(this->top == NULL){
       this->top = node; 
    }
    else{
        node->next = this->top;
        this->top = node;
    }
}

int Stack::pop(){
    int key = -99999;
    if(this->top != NULL){
        Node *temp = this->top;
        key = temp->key;
        this->top = temp->next;
        delete temp;
    }
    return key;
}

bool Stack::empty(){
    bool result = false;
    if(this->top == NULL){
        result = true;
    }
    return result;
}

class EdgeNode{
    public:
        int key;
        EdgeNode *next;
        EdgeNode(int);
};

EdgeNode::EdgeNode(int key){
    this->key = key;
    this->next = NULL;
}

class Graph{
    public:
        EdgeNode *edges[MAX_V + 1];
        Graph();
        ~Graph();
        void insert_edge(int, int, bool);
        void print();
};

Graph::Graph(){
    for(int i = 1; i < (MAX_V + 1); i ++){
        this->edges[i] = NULL;
    }
}

Graph::~Graph(){
    for(int i = 1; i < (MAX_V + 1); i ++){
        EdgeNode *curr = this->edges[i];
        while(curr != NULL){
            EdgeNode *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
}

void Graph::insert_edge(int source_vertex, int neighbor_vertex, bool directed){
    EdgeNode *edge = new EdgeNode(neighbor_vertex);
    edge->next = this->edges[source_vertex];
    this->edges[source_vertex] = edge;

    if(!directed){
        insert_edge(neighbor_vertex, source_vertex, true);
    }
}

void Graph::print(){
    for(int i = 1; i < (MAX_V + 1); i ++){
        if(this->edges[i] != NULL){
            cout << "Vertex " << i << " has Edges: " << endl;
            EdgeNode *curr = this->edges[i];
            while(curr != NULL){
                cout << curr->key << endl;
                curr = curr->next;
            }
        }
    }
}

void init_traversal_vars(){
    for(int i = 1; i < (MAX_V + 1); i ++){
        discovered[i] = false;
        processed[i] = false;
    }
}

//depth first search using an implicit stack (recursive)
void depth_first_search_v1(Graph *g, int root){

    discovered[root] = true;

    EdgeNode *curr = g->edges[root];
    while(curr != NULL){
        int neighbor_vertex = curr->key;
        if(!discovered[neighbor_vertex]){
            discovered[neighbor_vertex] = true;
            depth_first_search_v1(g, neighbor_vertex);
        }
        curr = curr->next;
    }
    cout << "Processed " << root << endl;
    processed[root] = true;
}

//depth first search using an explicit stack (non-recursive)
void depth_first_search_v2(Graph *g, int root){

    discovered[root] = true;
    Stack *stack = new Stack();
    stack->push(root);

    while(!stack->empty()){
        int parent_vertex = stack->pop();
        EdgeNode *curr = g->edges[parent_vertex];
        while(curr != NULL){
            int neighbor_vertex = curr->key;
            if(!discovered[neighbor_vertex]){
                discovered[neighbor_vertex] = true;
                stack->push(neighbor_vertex);
            }
            curr = curr->next;
        }
        cout << "Processed " << parent_vertex << endl;
        processed[parent_vertex] = true;
    }
    delete stack;
}

int main(){
    init_traversal_vars();
    Graph *g = new Graph();
    g->insert_edge(1, 5, false);
    g->insert_edge(1, 2, false);
    g->insert_edge(2, 5, false);
    g->insert_edge(4, 5, false);
    g->insert_edge(2, 4, false);
    g->insert_edge(2, 3, false);
    g->insert_edge(3, 4, false);
    cout << "Depth First Search recursive" << endl;
    depth_first_search_v1(g, 1);
    init_traversal_vars();
    cout << "Depth First Search iterative" << endl;
    depth_first_search_v2(g, 1);
    delete g;
    return 0;
}
