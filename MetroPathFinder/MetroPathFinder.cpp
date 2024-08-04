#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstdlib>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

int stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}
// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int total_stops= 0;
    MetroStop* stops = getNode();
    while(stops!= nullptr){
        total_stops++;
        stops = stops->getNextStop();
    }
    return total_stops;

}

void MetroLine::populateLine(std::string filename) {
    // Read the file and populate the line
    string linename = filename.substr(0, filename.length() - 4);
    MetroLine* metroline = new MetroLine(linename);
    MetroStop* prev;
    ifstream in(filename);
    while(!in.eof()){
        string st;
        getline(in,st);
        while(st[st.size()-1] == ','){
            st.pop_back();
        }
        string stpname;
        int fare;
        size_t lastspacepos = st.find_last_of(' ');
        stpname =st.substr(0,lastspacepos);
        fare =stoi(st.substr(lastspacepos+1));  // seperated out 
        cout<<stpname<<endl;
        cout<<fare<<endl;

        // Now we need to create a doubly linked list
        MetroStop* ms;
        if(this->node == nullptr){
            ms = new MetroStop(stpname,metroline,fare);
            this->node =ms;
            prev = ms;
        }
        else{
            ms = new MetroStop(stpname,metroline,fare);
            prev->setNextStop(ms);
            ms->setPrevStop(prev);
            prev = ms;
        }


    }

}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void rotateLeftRight(AVLNode* node);
    void rotateRightLeft(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    AVLNode* find_unbal_node(AVLNode* node);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
    int isjunction(AVLNode* node);

};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node == nullptr){
        return 0;
    }
    int a =height(node->getLeft());
    int b =height(node->getRight());
    return max(a,b) + 1;
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if(node == nullptr){
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight()) ;
}

void AVLTree::rotateLeft(AVLNode* node) {
    AVLNode* nodel =node->getLeft();
    AVLNode* nodelr =node->getLeft()->getRight();
    AVLNode* parentnode = node->getParent();
    nodel->setRight(node);
    node->setParent(nodel);
    node->setLeft(nodelr);
    nodel->setParent(parentnode);
    if(nodelr!=nullptr){
        nodelr->setParent(node);
    }
    if(this->root == node){
        this->root = nodel;
    }
    else{
        if(stringCompare(parentnode->getStopName(),nodel->getStopName())>0){
           parentnode->setLeft(nodel);
        }
        else{
           parentnode->setRight(nodel);
        }
    }

}

void AVLTree::rotateRight(AVLNode* node) {
    AVLNode* noder = node->getRight();
    AVLNode* noderl = node->getRight()->getLeft();
    AVLNode* parentnode = node->getParent();
    noder->setLeft(node);
    node->setParent(noder);
    node->setRight(noderl);
    noder->setParent(parentnode);
    if(noderl!=nullptr){
        noderl->setParent(node);
    }
    if(this->root == node){
        this->root = noder;
    }
    else{
        if(stringCompare(parentnode->getStopName(),noder->getStopName())>0){
           parentnode->setLeft(noder);
        }
        else{
           parentnode->setRight(noder);
        }
    }

}

void  AVLTree :: rotateLeftRight(AVLNode* node){
    rotateRight(node->getLeft());
    rotateLeft(node);
    
}

void  AVLTree :: rotateRightLeft(AVLNode* node){
    rotateLeft(node->getRight());
    rotateRight(node);

}

void AVLTree::balance(AVLNode* node) {
    if(balanceFactor(node) == 2 && balanceFactor(node->getLeft()) ==1){
        rotateLeft(node);
    }
    if(balanceFactor(node) == 2 && balanceFactor(node->getLeft()) == -1){
        rotateLeftRight(node);
    }
    if(balanceFactor(node) == -2 && balanceFactor(node->getRight()) == -1){
        rotateRight(node);
    }
    if(balanceFactor(node) == -2 && balanceFactor(node->getRight()) == 1 ){
        rotateRightLeft(node);
    }
}

AVLNode* AVLTree::find_unbal_node(AVLNode* node) {
        //finding unbalanced node here
        AVLNode* unbalnode =node;
        while(unbalnode!= nullptr){
            // if(balanceFactor(unbalnode) !=0 || balanceFactor(unbalnode) !=1 || balanceFactor(unbalnode) !=-1){
            if(balanceFactor(unbalnode) >1 || balanceFactor(unbalnode) <-1){
               return unbalnode;
            }
            unbalnode =unbalnode->getParent();
        }
        return nullptr;
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    AVLNode* current;
    if(this->root == nullptr){
        this->root =node;
        this->root->setParent(nullptr);
        this->root->addMetroStop(metroStop);
        cout<<"into root"<<endl;
    }
    else{
    current = this->root;
    while(current!= nullptr){
       if(stringCompare(node->getStopName(),current->getStopName()) <0){
        if(current->getLeft() == nullptr){
            current->setLeft(node);
            node->addMetroStop(metroStop);
            node->setParent(current);
            cout<<node->getStopName()<<" left setted"<<endl;
            break;
        }
        current = current->getLeft();
       }
       else if(stringCompare(node->getStopName(),current->getStopName()) >0){
         if(current->getRight() == nullptr){
            current->setRight(node);
            node->addMetroStop(metroStop);
            node->setParent(current);
            cout<<node->getStopName()<<" right setted"<<endl;
            break;
         }
         current= current->getRight();
       }
       else if(stringCompare(node->getStopName(),current->getStopName())==0){
            // cout<<node->getStopName();
            current->addMetroStop(metroStop);
            break;
        }
    }
    AVLNode* newnode = find_unbal_node(node);
    if(newnode!= nullptr){
        balance(newnode);
    }
    }

}

void AVLTree::populateTree(MetroLine* metroLine) {
    MetroStop* met_stp = metroLine->getNode();
    while(met_stp != nullptr){
        AVLNode* node_to_insert = new AVLNode(met_stp->getStopName());
        insert(node_to_insert,met_stp);
        // cout<<"|||||||"<<getRoot()->getStopName()<<"|||||||| of root value"<<endl;
        // printf("%d\n",height(getRoot()));
        met_stp = met_stp->getNextStop();
        
    }

}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* current = this->root;
    while(current != nullptr){
       int res = stringCompare(stopName,current->getStopName());
       if(res < 0){
          current = current->getLeft();
       }
       else if(res > 0){
          current = current->getRight();
       }
       else if(res == 0){
          return current;
       }
    }
    return nullptr;

}

int AVLTree::isjunction(AVLNode* node){
    vector<MetroStop*> stops_vec = node->getStops();
    return stops_vec.size();
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;
    int direction;
    MetroStop* prevtriplastnode;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
    void setdirection(int g);
    int getdirection();
    void setprevtriplastnode(MetroStop* metrostop);
    MetroStop* getprevtriplastnode();
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
    prevtriplastnode=nullptr;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

void Trip::setdirection(int g){
    direction = g;
}

int Trip::getdirection(){
    return direction ;
}

void  Trip::setprevtriplastnode(MetroStop* metrostop){
       prevtriplastnode = metrostop;
}

MetroStop* Trip::getprevtriplastnode(){
    return prevtriplastnode;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void setstops(vector<MetroStop*> vec ){
        stops = vec;
    }
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    for(int i=0;i<lines.size();i++){
       tree->populateTree(lines[i]);
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    int n; Trip* trp; MetroStop* origin_stop; MetroStop* met_stop;  AVLNode* avlnode;
    Trip* backtrip; MetroStop* backstop;
    AVLNode* node = tree->searchStop(origin);
    cout<<node->getStops().size()<<endl;
    origin_stop = node->getStops()[0];
    Trip* trp_f1 = new Trip(origin_stop,nullptr);
    trp_f1->setdirection(1);
    Trip* trp_b1 = new Trip(origin_stop,nullptr);
    trp_b1->setdirection(-1);
    cout<<"HI"<<endl;
    Exploration* explore = new Exploration();
    explore->enqueue(trp_f1);
    explore->enqueue(trp_b1);
    while(!explore->isEmpty()){ 
        cout<<"into while loop"<<endl;
        trp = explore->dequeue();
        met_stop = trp->getNode();
        int j = 0;
        cout<<"hi"<<endl;
       while(met_stop != nullptr){
        cout<<"into"<<endl;
        std :: vector<MetroStop*> stops_vec;
        if(j==0){
        cout<<node->getStopName()<<endl;
        cout<<node->getStops().size()<<"requires size"<<endl;
        n = tree->isjunction(node);
        cout<<n<<endl;
        j++;
        }
        else if(j!=0){
          avlnode = tree->searchStop(met_stop->getStopName());
          stops_vec = avlnode->getStops();
          n = tree->isjunction(avlnode);
          cout<<n<<endl;
        }
        if(n>1){   
            cout<<"junction is being there"<<endl;    //there is a junction
            MetroStop* m = met_stop;
            for(int i=0;i<n;i++){
                if(stringCompare(stops_vec[i]->getLine()->getLineName(),origin_stop->getLine()->getLineName())==0){
                    stops_vec.erase(stops_vec.begin()+i);
                }
                else{
                    MetroStop* mst;
                    mst = stops_vec[i];
                    origin_stop = mst;
                    Trip* tripforward = new Trip(mst,trp_f1);
                    tripforward->setdirection(1);
                    tripforward->setprevtriplastnode(m);
                    Trip* tripbackward = new Trip(mst,trp_b1);
                    tripbackward->setdirection(-1);
                    tripbackward->setprevtriplastnode(m);
                    explore->enqueue(tripforward);
                    explore->enqueue(tripbackward);
                }
            }
        }
        
        if(stringCompare(met_stop->getStopName(),destination)==0){
            cout<<"we get destination "<<met_stop->getStopName()<<endl;
            backstop=met_stop;
            backtrip=trp;
            break;
        }
        if(trp->getdirection() == 1){
          met_stop = met_stop->getNextStop();
        }
        if(trp->getdirection() == -1){
          met_stop = met_stop->getPrevStop();
        }
        j++;
       }

    }

    cout <<"hehe"<<endl;
    int faretotal=0,finalfare;
    int initialfare=backtrip->getNode()->getFare();
    finalfare = backstop->getFare();

    cout<<backtrip->getdirection()<<endl;
    cout<<backtrip->getNode()->getStopName()<<endl;
    cout<<backstop->getStopName()<<endl;
    cout<<"hehehe"<<endl;
    Path* path =new Path();
    int i=0; int flag=0;
    while(backtrip != nullptr){
        cout<<"into"<<endl;
        if(i!=0){
            cout<<"into"<<endl;
            backstop = trp->getprevtriplastnode();
            backtrip = trp->getPrev();
            finalfare = backstop->getFare();
            initialfare=backtrip->getNode()->getFare();
        }
        if(backtrip->getdirection() == 1){
            //moving in forward direction
            cout<<"inside this when direction is 1"<<endl;
            while(stringCompare(backstop->getStopName(),backtrip->getNode()->getStopName())!=0){
                path->addStop(backstop);

                if(stringCompare(backstop->getStopName(),origin)==0){
                    initialfare=backstop->getFare();
                    flag=1;
                    break;
                }
                cout<<"while loop into"<<endl;
                cout<<backstop->getStopName()<<endl;
                backstop = backstop->getPrevStop();
            }
            cout<<"out of while"<<endl;
        }
        else if(backtrip->getdirection() == -1){
            //moving in backward direction
            cout<<"into this when direction is -1"<<endl;
            while(stringCompare(backstop->getStopName(),backtrip->getNode()->getStopName())!=0){
                path->addStop(backstop);
                if(stringCompare(backstop->getStopName(),origin)==0){
                    initialfare=backstop->getFare();
                    flag=1;
                    break;
                }
                backstop = backstop->getNextStop();
            }
        }
        
        if(stringCompare(origin,backtrip->getNode()->getStopName())==0){
            flag=1;
            path->addStop(backstop);
            cout<<"we get dest"<<endl;
        }
        faretotal += max(initialfare,finalfare) - min(initialfare,finalfare) ;
        if(flag==1){
            break;
        }
        
        i++;
    }
    cout<<"path finder done"<<endl;
    vector<MetroStop*> path_vec = path->getStops();
    cout<<path_vec.size()<<endl;
    path->setstops(path_vec);
    for(int i=0;i<path_vec.size();i++){
        cout<<path_vec[i]->getStopName()<<" "<<path_vec[i]->getFare()<<endl;
    }
    //***************Now we need to compute the FARE    ***********//
    path->setTotalFare(faretotal);
    cout<<"*************************************************"<<endl;
    cout<<"printing totalfare"<<faretotal<<endl;
    cout<<"*************************************************"<<endl;
    return path;
}
    
vector<MetroLine*> lines;