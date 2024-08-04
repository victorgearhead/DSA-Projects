#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;
class Vehicle;
// class BinarySearchTree;


class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};
class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class BinaryTree {
protected:
    

public:
    BinaryTreeNode* root;
    BinaryTree() : root(nullptr) {}

    //  friend class TransportService;
     int getHeight() const {
        // Implement this function to return the height of the tree
        int height = 0;
        if(this->root == nullptr){
            return 0;
        }
        else{
            std :: queue<BinaryTreeNode*> q;
            q.push(this->root);
            while(!q.empty()){
                int nodes_at_cur_level= q.size();

                while(nodes_at_cur_level>0){
                   BinaryTreeNode* btn;
                   btn = q.front();
                   q.pop();

                 if(btn->getLeftPtr()){
                    q.push(btn->getLeftPtr());  //if it is not nullptr then push it thats what it is doing
                 }
                 if(btn->getRightPtr()){
                    q.push(btn->getRightPtr());
                 }
                 nodes_at_cur_level--;
                }
            height++;
            }
        }
        return height;
        // return 0; // Placeholder
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        // return 0; // Placeholder
        int total_no_of_nodes=1;
        if(this->root == nullptr){
            return 0;
        }
        else{
            std :: queue<BinaryTreeNode*> q;
            q.push(this->root);
            while(!q.empty()){
                
                int nodes_at_cur_level= q.size();

                while(nodes_at_cur_level>0){
                   BinaryTreeNode* btn;
                   btn = q.front();
                   q.pop();

                 if(btn->getLeftPtr()){
                    total_no_of_nodes++;
                    q.push(btn->getLeftPtr());  //if it is not nullptr then push it thats what it is doing
                 }
                 if(btn->getRightPtr()){
                    total_no_of_nodes++;
                    q.push(btn->getRightPtr());
                 }
                //  total_no_of_nodes+=nodes_at_cur_level
                 nodes_at_cur_level--;
                }
            
            }
        }
        return total_no_of_nodes;

    }
};


class BinarySearchTree : public BinaryTree {
    private:

    public:
    BinaryTreeNode* root;

    BinarySearchTree() :  root(nullptr) {}
    friend class TransportService;
    
    void setbstroot(BinaryTreeNode* btn){
        this->root = btn;
    }
    BinaryTreeNode* getroot(){
        return this->root;
    }

    void insert(BinaryTreeNode* node){
        BinaryTreeNode* current;
        // if(this->root == nullptr){
        //     this->root = node;
        //     this->root->setParentPtr(nullptr);
        //     cout<<"Root setted"<<endl;
        // }
        // else{
        current = this->root;
        while(current!= nullptr){
            if(node->getDepartureTime() < current->getDepartureTime() ){
                if(current->getLeftPtr() == nullptr){
                   current->setLeftPtr(node);
                   node->setParentPtr(current);
                   cout<<"left setted"<<endl;
                   break;
                }
                current = current->getLeftPtr();
            } 
            else if(node->getDepartureTime() >= current->getDepartureTime()){
                if(current->getRightPtr() == nullptr){
                   current->setRightPtr(node);
                   node->setParentPtr(current);
                   cout<<"Right setted"<<endl;
                   break;
                }
                current = current->getRightPtr();
            }
        }

    // }
        
    }

    BinaryTreeNode* deletenodebst(BinaryTreeNode* node){
        // if 1 child exist
        BinaryTreeNode* parent = node->getParentPtr();
        if(node->getLeftPtr() == nullptr && node->getRightPtr() != nullptr){
            
        }
        else if(node->getRightPtr() == nullptr && node->getLeftPtr() != nullptr){

        }

    }

    BinaryTreeNode* getElementWithMinimumKey() const {
        // Implement this function to return the element with the minimum key
        // return nullptr; // Placeholder
        BinaryTreeNode* btn =this->root;
        if(this->root->getLeftPtr() == nullptr){
            return this->root;
        }
        while(btn->getLeftPtr()!= nullptr){
            btn = btn->getLeftPtr();
        }
        return btn;

    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        // Implement this function to return the element with the maximum key
        // return nullptr; // Placeholder
        BinaryTreeNode* btn =this->root;
        if(this->root->getRightPtr() == nullptr){
            return this->root;
        }
        while(btn->getRightPtr()!= nullptr){   //2exceptions are left where if root === nullptr thenn.
            btn = btn->getRightPtr();
        }
        return btn;

    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        // Implement this function to search for a node with the given key or the next larger key
        // return nullptr; // Placeholder
        BinaryTreeNode* parent; 
        BinaryTreeNode* btn =this->root;
        while(btn != nullptr){
            parent =btn;
            if(btn->getDepartureTime() == key){
                return btn;
            }
            else if(key < btn->getDepartureTime()){
                btn =btn->getLeftPtr();
            }
            else if(key > btn->getDepartureTime()){
                btn = btn->getRightPtr();
            }
            else{
                return parent;
            }

        }
        return parent;
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the successor node of the given node
        // return nullptr; // Placeholder
        BinaryTreeNode* btn =node;
        BinaryTreeNode* parent = btn->getParentPtr();
        if(btn->getRightPtr() != nullptr){
            btn = btn->getRightPtr();
            while(btn->getLeftPtr() != nullptr){
                btn = btn->getLeftPtr();
            }
            return btn;
        }
        else if(btn->getRightPtr() == nullptr){
            while(parent != nullptr){
                if(btn->getDepartureTime() <parent->getDepartureTime()){
                   return parent;
                }
    
                parent = parent->getParentPtr();
            }

        }
        return nullptr;

    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        // return nullptr; // Placeholder
        BinaryTreeNode*btn =searchNodeWithKey(key);
        BinaryTreeNode* successor = getSuccessorNode(btn);
        return successor;
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        // return nullptr; // Placeholder
        BinaryTreeNode* btn = node;
        BinaryTreeNode* parent = btn->getParentPtr();
        if(btn->getLeftPtr() != nullptr){
            btn = btn->getLeftPtr();
            while(btn->getRightPtr() != nullptr){
                btn = btn->getRightPtr();
            }
            return btn;
        }
        else if(btn->getLeftPtr() == nullptr){
            while(parent != nullptr){
                if(btn->getDepartureTime() > parent->getDepartureTime()){
                   return parent;
                }
                parent = parent->getParentPtr();
            }

        }
        return nullptr;
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
        // return nullptr; // Placeholder
        BinaryTreeNode* btn = searchNodeWithKey(key);
        BinaryTreeNode* predecessor = getPredecessorNode(btn);
        return predecessor;
    }
};

class TransportService {
private:
    BinarySearchTree* bst = new BinarySearchTree();
    string name;
    BinaryTreeNode* BSThead   ;
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinarySearchTree* getbst(){
        return bst;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip){
        cout<<"into add trip"<<endl;
        BinaryTreeNode*  node = new BinaryTreeNode(key,trip,nullptr);
        node->setLeftPtr(nullptr);
        node->setRightPtr(nullptr);
        if(this->BSThead == nullptr){
            this->bst->setbstroot(node);
            setBSTHead(node);
        }
        else{
        this->bst->insert(node);
        }
    }

    BinaryTreeNode* getbstroot(){
        return bst->getroot();
    }

    void deletenode(BinaryTreeNode* node){
        bst->deletenodebst(node);

    }

};

class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    vector<Trip *> getTrips(){
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}
    friend class TravelDesk;
    // Getter functions
    std::string getName() const {
        return name;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }
    
     vector<TransportService*> getserviceptrs(){
        return serviceptrs;
    }

    void setServicePtr(std::string droplocation) {
        TransportService*ts = new TransportService(droplocation);
        serviceptrs.push_back(ts);
        // return ts;
    }

   TransportService* getServicePtr(const string& droplocation) {
    for (int i = 0; i < serviceptrs.size(); i++) {
        if (droplocation == serviceptrs[i]->getName()) {
            return serviceptrs[i];
        }
    }
    // return nullptr; 
}


    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<Trip*> getTrips(){
        return trips;
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};



class TravelDesk {
public:

    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
     // Add the trip to the TransportService's BST
        int flag =0;
        int i;
        Vehicle* vehicle;
        for(i=0;i<vehicles.size();i++){
            if(vehicle_number == vehicles[i]->getVehicleNumber()){
                flag =1;
                vehicle = vehicles[i];
                break;
            }
        }
        if(flag ==0){
            vehicle = new Vehicle (vehicle_number,seating_capacity);
            vehicles.push_back(vehicle);
        }
        Trip* trp =new Trip(vehicle,pick_up_location,drop_location,departure_time);
        vehicle->addTrip(trp);
        Location* loc;
        int j,m;
        int flg=0;
        Location* l;
        for(j=0;j<locations.size();j++){
            if(locations[j]->getName() == pick_up_location){
                locations[j]->addTrip(trp);
                flg = 2;
                l = locations[j];
              for(int k=0;k<locations[j]->getserviceptrs().size();k++){
                if(locations[j]->getserviceptrs()[k]->getName() == drop_location){
                    flg = 1;
                    cout<<"flag=1"<<endl;
                    locations[j]->getserviceptrs()[k]->addTrip(departure_time,trp);
                    break;
                }
              }
            }
        }
        if (flg ==0){
            //from here error occurs
            cout<<"flag=0"<<endl;
            loc= new Location(pick_up_location);
            loc->setServicePtr(drop_location);
            loc->addTrip(trp);
            loc->getServicePtr(drop_location)->addTrip(departure_time,trp);
            locations.push_back(loc);

        }
        else if(flg ==2){
            cout<<"flag=2"<<endl;
            cout<<j<<endl;
            l->setServicePtr(drop_location);
            l->getServicePtr(drop_location)->addTrip(departure_time,trp);
        }

    }
    
    vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
     // Implement this function to retrieve trips within a specified time range
        if(after_time > before_time){
            int temp;
            temp =after_time;
            after_time =before_time;
            before_time =temp;
        }
        int i,j;
        Location* l;
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                l =locations[i];
                break;
            }
        }
        std :: vector<Trip*>shtrips;
        l->getName();
        std ::vector<TransportService*> Tr_se = l->getserviceptrs();
        cout<<Tr_se[0]->getName()<<endl;
        BinaryTreeNode* btnode =Tr_se[0]->getBSTHead();
        cout<<"hi"<<endl;
        for(j=0;j<Tr_se.size();j++){
            BinaryTreeNode* node;
            node = Tr_se[j]->getbst()->searchNodeWithKey(after_time);
            while(node!=nullptr){
                int flag=0;
                BinaryTreeNode* successor;
                cout<<"of successor"<<endl;
                cout<<node->getDepartureTime()<<endl;
                if(node== nullptr){
                    break;
                }
                if(node->getDepartureTime() < before_time && node->getDepartureTime() >after_time){
                    shtrips.push_back(node->getTripNodePtr());
                    cout<<shtrips.size()<<endl;
                    node = Tr_se[j]->getbst()->getSuccessorNode(node);
                    flag=1;
                }
                else if(flag==0){
                    break;
                }
            cout<<"hi"<<endl;
            }
            cout<<"hi"<<endl;
        }
        return shtrips;
    }

    vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        
        if(after_time>before_time){
            int temp;
            temp =after_time;
            after_time =before_time;
            before_time =temp;
        }
        int i,j;
        cout<<"hi"<<endl;
        Location* loc;
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                loc = locations[i];
                cout<<locations[i]->getName()<<endl;
                break;
            }
        }
        std::vector<Trip*> s_trip_dest;
        cout<<"hi"<<endl;
        std::vector<Trip*> show_tripp =loc->trips;
        cout<<"hi"<<endl;
        for(j=0;j<show_tripp.size();j++){
            if(show_tripp[j]->getDropLocation() == destination){
                int dept_time =show_tripp[j]->getDepartureTime();
                if(dept_time >after_time && dept_time < before_time){
                   s_trip_dest.push_back(show_tripp[j]);
                }
            }
        }
        return s_trip_dest;

    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
     Vehicle* vehicle;
        int i;
        int flag =0;
         for(i=0;i<vehicles.size();i++){
            if(vehicle_number == vehicles[i]->getVehicleNumber()){
                flag =1;
                break;
            }
        }
        std:: vector<Trip*> trip_vec = vehicles[i]->getTrips();
        for(int j=0;j<trip_vec.size();j++){
            if(trip_vec[j]->getDropLocation() ==drop_location && trip_vec[j]->getPickUpLocation() == pick_up_location
               && trip_vec[j]->getDepartureTime() == departure_time ){
                 if(trip_vec[j]->getBookedSeats() <vehicles[i]->getSeatingCapacity()){
                    int booked_seats =trip_vec[j]->getBookedSeats();
                    trip_vec[j]->setBookedSeats(booked_seats+1);
                    return trip_vec[j];
                 }
                 else{
                    // need to perform deletion
                    

                 }
             }
        }
        return nullptr;
    }
    
    Location* getLocation(std::string location){
        for (Location* loc : locations) {
            if (loc->getName() == location) {
                return loc;
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
    vector<TransportService*> transportServices;
};

////////***   search error and why 2 times nodes are being adding like 1100 1100 1200 1200 ***////////// 


// void read_input_file(string file_path){
//     ifstream in(file_path);
//         if (!in.is_open()) {
//         cerr << "Failed to open the file " <<file_path<< endl;
//         return;
//         }
    
//     string line;
//     while (getline(in, line)) {
//             stringstream ss(line);
//             string a;
//             vector<string> row;
//             while (getline(ss, a, ' ')) {
//                 row.push_back(a);
//             }
//             if(row[0]=="ADDTRIP"){
//                 TravelDesk x;
//                 x.addTrip(row[1],stoi(row[2]),row[3],row[4],stoi(row[5]));
//             }

//             else if(row[0]=="SHOWTRIPS"){
//                 TravelDesk b;
//                 b.showTrips(row[1],stoi(row[2]),stoi(row[3]));
//             }
//             else if(row[0]=="BOOKTRIP"){
//                 TravelDesk c;
//                 c.bookTrip(row[1],row[2],row[3],stoi(row[4]));
//             }
//         }     
// }
// int main(){
//     BinarySearchTree* bst;
//     TransportService* tss;
//     vector<Trip*> trp;
//     Trip *t,*t1,*t2,*t3;
//     t->setDepartureTime(12);
//     t1->setDepartureTime(10);
//     t2->setDepartureTime(14);
//     t3->setDepartureTime(13);
//     trp.push_back(t);trp.push_back(t1);trp.push_back(t2);trp.push_back(t3);
//     for(int i=0;i<4;i++){
//         tss->addTrip(10,trp[i]);
//     }
//     cout<<bst->getHeight();
    
    
//     return 0;
// }