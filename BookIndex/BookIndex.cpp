#include <bits/stdc++.h>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cctype>
using namespace std;

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child; // Right child node
    HybridNode* uncle;  
    HybridNode* next_node;  // Next node in the linked list
    string color;    // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr),color("red"),uncle(nullptr) {}
};

class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }

    int stringCompare(string s1, string s2) {

      char *c1 = new char[s1.length() + 1];
      strcpy(c1, s1.c_str());
      char *c2 = new char[s2.length() + 1];
      strcpy(c2, s2.c_str());
      int result = strcmp(c1, c2);
      return result;
    }

    HybridNode* rotateleft(HybridNode* node){
        HybridNode* nodel =node->left_child;
        HybridNode* nodelr = nodel->right_child;
        HybridNode* parentnode =node->parent;
        nodel->right_child =node;
        node->left_child = nodelr;
        node->parent = nodel;
        nodel->parent = parentnode;
        if(nodelr!=nullptr){
           nodelr->parent = node;
        }
        if(stringCompare(this->root->key,node->key) ==0){
           this->root = nodel;

        }
        else{
        if(stringCompare(nodel->key,parentnode->key )>0 ){
            parentnode->right_child= nodel;
        }
        else if(stringCompare(nodel->key ,parentnode->key) <=0){
            parentnode->left_child = nodel;  //keep mind of equalto sign
        }
        }
        // nodel->colour =1;
        // node->colour= 0;
        
        return nodel; 

    }

    HybridNode* rotateright(HybridNode* node){
        HybridNode* noder =node->right_child;
        HybridNode* noderl = noder->left_child;
        HybridNode* parentnode =node->parent;
        noder->left_child =node;
        node->right_child = noderl;
        node->parent = noder;
        noder->parent = parentnode;
        if(noderl!=nullptr){
           noderl->parent = node;
        }
        if(this->root == node){
           this->root = noder;
        }
        else{
        if(stringCompare(noder->key,parentnode->key) >0){
            parentnode->right_child= noder;
        }
        else if(stringCompare(noder->key, parentnode->key) <=0){
            parentnode->left_child = noder;  //keep mind of equalto sign
        }
        }
        // noder->colour =1;
        // node->colour =0;

        return noder;

    }

    HybridNode* rotateleftright(HybridNode* node){
        HybridNode* newnode =node->left_child->right_child;
        rotateright(node->left_child);
        rotateleft(node);
        return newnode;

    }

    HybridNode* rotaterightleft(HybridNode* node){
        HybridNode* newnode = node->right_child->left_child;
        rotateleft(node->right_child);
        rotateright(node);
        return newnode;

    }

    HybridNode* find_uncle(HybridNode* node){
        HybridNode* p =node->parent;
        if(p != nullptr){
          HybridNode* grandparent = node->parent->parent;
            if(grandparent != nullptr){
                if(grandparent->left_child != nullptr && grandparent->right_child != nullptr){
                  if(stringCompare(grandparent->left_child->key , node->parent->key) !=0){
                    node->uncle =grandparent->left_child;
                  }
                  else if(stringCompare(grandparent->right_child->key,node->parent->key) !=0){
                    node->uncle =grandparent->right_child;
                  }
                }
                else{
                    node->uncle = nullptr;
                }
            }
            else{
                return nullptr;
            }
        return node->uncle; 
        }
        else{
            return nullptr;
        }

    }

    HybridNode* findpredecessor(HybridNode* node){
        HybridNode* par = node->parent;
        if(node->left_child != nullptr){
            node = node->left_child;
            while(node->right_child != nullptr){
                node = node->right_child;
            }
            return node;
        }
        else{
            while(par != nullptr){
                if(stringCompare(node->key , par->key) >0){
                   return par;
                }
                par = par->parent;
            }

        }
        return nullptr;

    }

    HybridNode* insert(string key, string element) {
        // Implement Red-Black Tree insertion
        HybridNode* node = new HybridNode(key , element);
        if(this->root == nullptr){
            this->root = node;
            this->root->color = "black";
            setRoot(this->root);
            return this->root;
        }
        else{
            HybridNode* current = this->root;
            while(current != nullptr){
               if(stringCompare(node->key , current->key) <0) {
                if(current->left_child == nullptr){
                    current->left_child =node;
                    node->parent= current;
                    break;
                }
                current= current->left_child;
               }
               else if(stringCompare(node->key , current->key) >0){
                if(current->right_child == nullptr){
                    current->right_child = node;
                    node->parent = current;
                    break;
                }
                current = current->right_child;
               }
               else{
                return nullptr;
               }
            }
            //setting uncle
            HybridNode* grandparent;
            //now only insertion process done now need to check rr conflict 
            HybridNode* hn =node;
            while(hn->parent != nullptr && hn->parent->parent != nullptr){
                grandparent =hn->parent->parent;
                hn->uncle = find_uncle(hn);
                if(hn->parent->color == "red"){
                    if(hn->uncle!= nullptr && hn->uncle->color == "red"){
                       //case 1:
                       //we need to do recolouring
                       hn->uncle->color= "black";
                       hn->parent->color= "black";
                       if(stringCompare(grandparent->key ,this->root->key) != 0){
                        grandparent->color ="red";
                       }
                       hn = grandparent;
                    }
                    else {
                    // we need to do rotations
                    // Case 2:
                    if(grandparent->right_child){
                        if(grandparent->right_child->right_child){
                            if(stringCompare(grandparent->right_child->right_child->key , hn->key) ==0){
                               HybridNode* newnode = rotateright(grandparent);
                               newnode->color ="black";
                               newnode->left_child->color= "red";
                               break;
                            }
                        }
                        if(grandparent->right_child->left_child){
                            if(stringCompare(grandparent->right_child->left_child->key , hn->key) ==0){
                                HybridNode* newnode = rotaterightleft(grandparent);
                                newnode->color="black";
                                newnode->left_child->color="red";
                                break;
                            }
                        }
                    }
                    if(grandparent->left_child){
                        if(grandparent->left_child->left_child){
                            if(stringCompare(grandparent->left_child->left_child->key , hn->key) ==0){
                               HybridNode* newnode = rotateleft(grandparent);
                               newnode->color="black";
                               newnode->right_child->color="red";
                               break;

                            }
                        }
                        if(grandparent->left_child->right_child){
                            if(stringCompare(grandparent->left_child->right_child->key , hn->key) ==0){
                               HybridNode* newnode = rotateleftright(grandparent);
                               newnode->color="black";
                               newnode->right_child->color="red";
                               break;
                            }
                        }
                    }
                    

                  }
                }
            else{
                break;
            }
              
            }
            return node;
            
        }

    }

    int totalnodes(HybridNode* node){
        if(node == NULL){
            return 0;
        }
        int a = totalnodes(node->left_child);
        int b = totalnodes(node->right_child);
        return 1+a+b ;
    }

     void swap_values(HybridNode* node1,HybridNode* node2){
        string temp;
        temp = node1->key;
        node1->key = node2->key;
        node2->key = temp;
    }

    HybridNode* find_sibling(HybridNode* node){
        HybridNode* par =node->parent;
        if(par!= nullptr){
            if(par->left_child !=nullptr && par->right_child!=nullptr){
              if(stringCompare(par->left_child->key,node->key) != 0){
                return par->left_child;
              }
              if(stringCompare(par->right_child->key,node->key) !=0){
                return par->right_child;
              }
            }
            else{
                return nullptr; 
            }
        }
        return nullptr;
    }

    string sibling_parent_relation(HybridNode* sib){
        HybridNode* par = sib->parent;
        if(par->right_child != nullptr){
           if(stringCompare(par->right_child->key,sib->key) ==0){
            return "right";
           }
        }
        if(par->left_child){
           if(stringCompare(par->left_child->key,sib->key) ==0){
            return "left";
           }
        }
    }
    
    void delete_black_node(HybridNode* node){
        if(node->left_child == nullptr && node->right_child ==nullptr){
            HybridNode* par =node->parent;
            if(stringCompare(par->right_child->key,node->key) ==0){
                delete node;
                par->right_child =nullptr;
            }
            else{
                delete node;
                par->left_child = nullptr;
            }
        }
        else if(node->left_child != nullptr && node->right_child ==nullptr){
            HybridNode* lnode = node->left_child;
            HybridNode* p =node->parent;
            string st = sibling_parent_relation(node);
            if(st =="left"){
                delete node;
                p->left_child =lnode;
                lnode->parent =p;
            }
            else{
                delete node;
                p->right_child =lnode;
                lnode->parent =p;
            }
        }
        else if(node->left_child == nullptr && node->right_child !=nullptr){
            HybridNode* rnode = node->right_child;
            HybridNode* p =node->parent;
            string st = sibling_parent_relation(node);
            if(st =="left"){
                delete node;
                p->left_child =rnode;
                rnode->parent =p;
            }
            else{
                delete node;
                p->right_child =rnode;
                rnode->parent =p;
            }
        }
    }

    void fixing_rr_conflict(HybridNode* node){
        if(node->left_child == nullptr && node->right_child == nullptr){
            //no child so no rr conflict
        }
        else if(node->left_child != nullptr && node->right_child == nullptr){
            if(node->left_child->color =="red"){
                //conflict occurs
                string st =sibling_parent_relation(node);
                if(st =="left"){
                    HybridNode* newnode =rotateleft(node->parent);
                    newnode->color="black";
                    newnode->right_child->color="red";
                    // fixing_rr_conflict(newnode->right_child);
                    //now here 1 more rr conflict chances??????
                }
                else{
                    HybridNode* newnode =rotaterightleft(node->parent);
                    newnode->color="black";
                    newnode->left_child->color="red";
                    // fixing_rr_conflict(newnode->right_child);
                    //now here 1 more rr conflict chances??????
                }
            }
            else if(node->left_child->color=="black"){
                // no conflict as its child is black
            }
        }
        else if(node->left_child == nullptr && node->right_child != nullptr){
            if(node->right_child->color =="red"){
                //conflict occurs
                string st =sibling_parent_relation(node);
                // cout<<"here node rchild not null and lchild is null"<<endl;
                if(st =="left"){
                    HybridNode* newnode =rotateleftright(node->parent);
                    newnode->color="black";
                    newnode->right_child->color="red";
                    // fixing_rr_conflict(newnode->right_child);
                    //now here 1 more rr conflict chances??????
                }
                else{
                    HybridNode* newnode =rotateright(node->parent);
                    newnode->color="black";
                    newnode->left_child->color="red";
                    //now here 1 more rr conflict chances??????
                }

            }
            else if(node->right_child->color=="black"){
                // no conflict as its child is black
                cout<<"no rr conflict"<<endl;
            }
        }
        else if(node->left_child != nullptr && node->right_child != nullptr){
            if(node->left_child->color=="red" && node->right_child->color=="red"){
                string st =sibling_parent_relation(node);
                if(st =="left"){
                    HybridNode* newnode =rotateleftright(node->parent);
                    newnode->color="red";
                    newnode->left_child->color="black";
                    newnode->right_child->color="black";
                    // fixing_rr_conflict(newnode->right_child);
                    //now here 1 more rr conflict chances??????
                }
                else{
                    HybridNode* newnode =rotaterightleft(node->parent);
                    newnode->color="red";
                    newnode->left_child->color="black";
                    newnode->right_child->color="black";
                    //now here 1 more rr conflict chances??????
                }
            }
            else if(node->left_child->color=="black" && node->right_child->color=="red"){
                string st =sibling_parent_relation(node);
                if(st =="left"){
                    HybridNode* newnode = rotateleftright(node->parent);
                    newnode->color="red";
                    newnode->left_child->color="black";
                    newnode->right_child->color="black";
                    // fixing_rr_conflict(newnode->right_child);
                    //now here 1 more rr conflict chances??????
                }
                else{
                    HybridNode* newnode =rotateright(node->parent);
                    newnode->color="black";
                    newnode->left_child->color="red";
                    //now here 1 more rr conflict chances??????
                }
            }
            else if(node->left_child->color=="red" && node->right_child->color=="black"){
                string st =sibling_parent_relation(node);
                if(st =="right"){
                    HybridNode* newnode =rotaterightleft(node->parent);
                    newnode->color="red";
                    newnode->left_child->color="black";
                    newnode->right_child->color="black";
                    // fixing_rr_conflict(newnode->right_child);
                    //now here 1 more rr conflict chances??????
                }
                else{
                    HybridNode* newnode =rotateleft(node->parent);
                    newnode->color="black";
                    newnode->right_child->color="red";
                    // newnode->left_child->colour=1;
                    //now here 1 more rr conflict chances??????
                }
            }
            else if(node->left_child->color=="black" && node->right_child->color=="black"){
                //hence no rr conflict as both child are black
            }
        }
    }

    void fixing_doubleblackness(HybridNode* node){
        HybridNode* par = node->parent; 
        HybridNode* sibling = find_sibling(node);

        if(sibling != nullptr){
            if(sibling->color == "red"){
                //sibling is red so its child will be black 2 different colours so we will do rotations
                if(stringCompare(par->left_child->key,sibling->key) ==0){
                    delete_black_node(node);
                    HybridNode* newnode = rotateleft(par);
                    newnode->color="black";
                    if(newnode->right_child->left_child){
                    newnode->right_child->left_child->color="red";
                    HybridNode* noderl =newnode->right_child->left_child;
                    //if noderl child colour red so again conflict
                    cout<<"fixing rr conflict"<<endl;
                    fixing_rr_conflict(noderl);
                    }
                    // newnode->right_child->colour is being already 1
                    //doing this for rr conflict
                }
                else if(stringCompare(par->right_child->key,sibling->key) ==0){
                    delete_black_node(node);
                    HybridNode* newnode = rotateright(par);
                    newnode->color="black";
                    if(newnode->left_child->right_child){
                    newnode->left_child->right_child->color="red";
                    HybridNode* nodelr =newnode->left_child->right_child;
                    //if nodelr child colour red so again conflict
                    fixing_rr_conflict(nodelr);
                    }
                    //newnode->left_child and right_child colour is being 1 already
                    // doing this for rr conflict
                    
                }
            }
            else if(sibling->color =="black"){
                //here the sibling is black so what we need to do is being depends on sibling child
                if(sibling->left_child == nullptr && sibling->right_child == nullptr){
                    //recolouring need to be done here
                    if(par->color =="red"){
                        delete_black_node(node);
                        par->color ="black";
                        sibling->color ="red";
                        //as parent becomes black so now no chances of rr conflict here
                    }
                    else if(par->color =="black"){
                        //now here parent colour is already black so no need to change
                        delete_black_node(node);
                        sibling->color="red";
                    }

                }
                else if(sibling->left_child ==nullptr && sibling->right_child !=nullptr){
                    //sibling will have 1 child
                    if(sibling->right_child->color =="black"){
                        //again recolouring need  to be done
                        if(par->color =="red"){
                            delete_black_node(node);
                            par->color ="black";
                            sibling->color ="red";
                        }
                        else if(par->color =="black"){
                            // parent black its child and sibling black now sibling rchild black andother nullptr
                            delete_black_node(node);
                            sibling->color="red";
                            
                        }
                    }
                    else if(sibling->right_child->color=="red"){
                        //rotations
                        string st = sibling_parent_relation(sibling);
                        if(st =="right"){
                            delete_black_node(node);
                            HybridNode* newnode = rotateright(par);
                            if(par->color=="black"){
                                newnode->right_child->color="black";
                            }
                            else if(par->color =="red"){
                                newnode->color="red";
                                newnode->left_child->color="black";
                                newnode->right_child->color="black";
                            }
                            // newnode->left_child->colour
                        }
                        else{
                            delete_black_node(node);
                            HybridNode* newnode = rotateleftright(par);
                            if(par->color =="black"){
                                newnode->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->color="red";
                                newnode->right_child->color="black";
                            }

                        }
                    }
                }    
                else if(sibling->left_child !=nullptr && sibling->right_child ==nullptr){
                    //sibling will have 1 child
                    if(sibling->left_child->color =="black"){
                        //again recolouring need  to be done
                        if(par->color =="red"){
                            delete_black_node(node);
                            par->color ="black";
                            sibling->color ="red";
                        }
                        else if(par->color =="black"){
                            // parent black its child and sibling black now sibling lchild black andother nullptr
                            delete_black_node(node);
                            sibling->color="red";
                        }
                    }
                    else if(sibling->left_child->color =="red"){
                        //rotations
                        string st = sibling_parent_relation(sibling);

                        if(st =="left"){
                            delete_black_node(node);
                            HybridNode* newnode = rotateleft(par);
                            if(par->color=="black"){
                                newnode->left_child->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->color="red";
                                newnode->left_child->color="black";
                                newnode->right_child->color="black";
                            }
                            // newnode->right_child->colour
                        }
                        else{
                            delete_black_node(node);
                            HybridNode* newnode = rotaterightleft(par);
                            if(par->color=="black"){
                                newnode->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->color="red";
                                newnode->left_child->color="black";
                            }
                            // newnode->left_child->colour
                        }
                    }
                }
                else{
                    //sibling will have 2 child
                    if(sibling->left_child->color =="black" && sibling->right_child->color =="black"){
                        //black sibling with 2 black child recolouring
                        if(par->color =="red"){
                            delete_black_node(node);
                            par->color ="black";
                            sibling->color ="red";
                        }
                        else if(par->color =="black"){
                            // parent black its child and sibling black now sibling rchild black andother nullptr
                            delete_black_node(node);
                            sibling->color="red";
                             
                        }
                        
                    }
                    else if(sibling->left_child->color =="red" && sibling->right_child->color =="red"){
                        string st = sibling_parent_relation(sibling);
                        if(st == "right"){
                            delete_black_node(node);
                            HybridNode* newnode = rotateright(par);
                            if(par->color=="black"){
                                newnode->right_child->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->left_child->color="black";
                                newnode->right_child->color="black";
                                newnode->color="red";
                            }
                        }
                        else{
                            delete_black_node(node);
                            HybridNode* newnode = rotateleft(par);
                            if(par->color=="black"){
                                newnode->left_child->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->left_child->color="black";
                                newnode->right_child->color="black";
                                newnode->color="red";
                            }
                        }
                    }
                    else if(sibling->left_child->color =="red" && sibling->right_child->color =="black"){
                        string st = sibling_parent_relation(sibling);
                        if(st == "right"){
                            delete_black_node(node);
                            HybridNode* newnode = rotaterightleft(par);
                            if(par->color=="black"){
                                newnode->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->left_child->color="black";
                                newnode->color="red";
                            }   
                        }
                        else{
                            delete_black_node(node);
                            HybridNode* newnode = rotateleft(par);
                            if(par->color=="black"){
                                newnode->left_child->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->left_child->color="black";
                                newnode->right_child->color="black";
                                newnode->color="red";
                            }
                        }
                    }
                    else if(sibling->left_child->color =="black" && sibling->right_child->color =="red"){
                        string st = sibling_parent_relation(sibling);
                        if(st == "left"){
                            delete_black_node(node);
                            HybridNode* newnode = rotateleftright(par);
                            if(par->color =="black"){
                                newnode->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->color="red";
                                newnode->right_child->color="black";
                            }
                        }
                        else{
                            delete_black_node(node);
                            HybridNode* newnode = rotateright(par);
                            if(par->color=="black"){
                                newnode->right_child->color="black";
                            }
                            else if(par->color=="red"){
                                newnode->left_child->color="black";
                                newnode->right_child->color="black";
                                newnode->color="red";
                            }
                        }
                    }
                }
                
            }

        }
        else{
            //here sibling is nullptr so it is possible only when the node we delete is being red 
            // o.w. black height issue occurs and here we are deleting the black node 
            // so this case is not possible
        }

    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
        HybridNode* current = this->root;
        while(current!= nullptr){
            if(stringCompare(key,current->key) <0){
                current = current->left_child;
            }
            if(stringCompare(key,current->key) >0){
                current = current->right_child;
            }
            if(stringCompare(key,current->key) == 0){
                break;
            }
        }
        HybridNode* node = current;
        if(node == nullptr){
            return false;
        }
        else{
            // we need to write different deletions cases according to the conditions.
            // HybridNode* node_replace =replace_node(node); 
            if(node->left_child == nullptr && node->right_child==nullptr){
                //henc acc to my code node is leaf node
                if(node == this->root){
                    this->root = nullptr;
                    return true;
                }
                else{
                    if(node->color == "red"){
                        HybridNode* p =node->parent;
                        string st = sibling_parent_relation(node);
                        if(st =="left"){
                            delete node;
                            p->left_child =nullptr;
                        }
                        else{
                            delete node;
                            p->right_child = nullptr;
                        }
                        return true;
                    }
                    else if(node->color =="black"){
                        //black leaf node or due to deletion of black node double blackness comes
                        // cout<<"this case"<<endl;
                        fixing_doubleblackness(node);
                        return true;
                    }
                }
            }

            else if(node->left_child != nullptr && node->right_child==nullptr){
                //node with 1 child and is left 
                HybridNode* par =node->parent;
                HybridNode* lnode =node->left_child;
                if(node == this->root){
                    delete node;
                    this->root =lnode;
                    this->root->color="black";
                    return true;
                }
                else{
                    if(node->color =="red"){
                        string st = sibling_parent_relation(node);
                        delete node;
                        lnode->parent =par;
                        if(st =="left"){
                            par->left_child =lnode;
                        }
                        else{
                            par->right_child =lnode;
                        }
                        return true;
                    }
                    else{
                        fixing_doubleblackness(node);
                        return true;
                    }
                }
            }

            else if(node->right_child != nullptr && node->left_child==nullptr){
                //node with 1 child and is right
                HybridNode* par =node->parent;
                HybridNode* rnode =node->right_child;
                if(node == this->root){
                    delete node;
                    this->root =rnode;
                    this->root->color="black";
                    return true;
                }
                else{
                    if(node->color =="red"){
                        string st = sibling_parent_relation(node);
                        delete node;
                        rnode->parent =par;
                        if(st =="left"){
                            par->left_child =rnode;
                        }
                        else{
                            par->right_child =rnode;
                        }
                        return true;
                    }
                    else{
                        fixing_doubleblackness(node);
                        return true;
                    }
                }
            }

            else{
                //node with 2 child
                HybridNode* replaced_node =findpredecessor(node);
                swap_values(node,replaced_node);
                //now we know that the replaced node will have 1/0 child
                if(replaced_node->color=="red"){
                    //red node
                    if(replaced_node->left_child ==nullptr && replaced_node->right_child ==nullptr){
                        HybridNode* p =replaced_node->parent;
                        string st = sibling_parent_relation(replaced_node);
                        if(st =="left"){
                            delete replaced_node;
                            p->left_child =nullptr;
                        }
                        else{
                            delete replaced_node;
                            p->right_child = nullptr;
                        }
                        return true;
                    }
                    else if(replaced_node->left_child !=nullptr && replaced_node->right_child ==nullptr){
                        HybridNode* par =replaced_node->parent;
                        HybridNode* lnode =replaced_node->left_child;
                        string st = sibling_parent_relation(replaced_node);
                        delete replaced_node;
                        lnode->parent =par;
                        if(st =="left"){
                            par->left_child =lnode;
                        }
                        else{
                            par->right_child =lnode;
                        }
                        return true;

                    }
                    else if(replaced_node->left_child ==nullptr && replaced_node->right_child !=nullptr){
                        HybridNode* par =replaced_node->parent;
                        HybridNode* rnode =replaced_node->right_child;
                        string st = sibling_parent_relation(replaced_node);
                        delete replaced_node;
                        rnode->parent =par;
                        if(st =="left"){
                            par->left_child =rnode;
                        }
                        else{
                            par->right_child =rnode;
                        }
                        return true;
                    }
                }
                else{
                    //black node
                    fixing_doubleblackness(replaced_node);
                    return true;
                }

            }

        }

    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
        vector<HybridNode*> vec;
        while(node!= nullptr){
            vec.push_back(node);
            node = node->parent;
        }
        return vec;

    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
        int i=0;
        vector<HybridNode*> vec;
        while(node != nullptr){
            vec.push_back(node);
            if(bit_sequence[i] == '1'){
                node = node->left_child;
            }
            else if(bit_sequence[i] == '0'){
                node = node->right_child;
            }
            i++;
        }
        return vec;

    }

    vector<HybridNode*>result;
    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        // Perform pre-order traversal staying within specified depth
        // if(node == nullptr || depth<0){
        //     return ;
        // }
        if(node ==nullptr){
            return result;
        }
        // cout<<"into preorder"<<endl;
        result.push_back(node);
        preOrderTraversal(node->left_child,depth-1);
        preOrderTraversal(node->right_child , depth-1);
        return result;
    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
        HybridNode* node = this->root;
        while(node!= nullptr){
            if(stringCompare(key,node->key) <0){
                node= node->left_child;
            }
            else if(stringCompare(key,node->key) >0){
                node = node->right_child;
            }
            else if(stringCompare(key,node->key) ==0){
                return node;
            }
        }
        return nullptr;
    }
    
    int blackheight(HybridNode* node){
        // Implement blackheight
        int height = -1;
        while(node!=nullptr){
           if(node->color =="black"){
             height++;
           }
           node= node->right_child;
        }
        return height+1;
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;
      // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}
    
    // chapter_word_counts.push_back(make_pair("Chapter1",0));

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;  // Red-Black Tree
    vector<IndexEntry*> index_entries;
    vector<IndexEntry*> pruned_index_entries;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }
    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        int no_of_chapters =chapter_names.size();
        int count=0,aa=0;
        for(auto it: chapter_names){
            string chaptername =it.substr(0,it.size()-4);
            ifstream file(it);
            if(file.is_open()){
                string line;
                transform(line.begin(), line.end(), line.begin(), ::tolower);
                while(getline(file,line)){
                    string word;
                    for(char c: line){
                        if(c == ' ' || c == ','){
                            if(!word.empty()){
                                transform(word.begin(), word.end(), word.begin(), ::tolower);    // Convert to lowercase
                                HybridNode* newnode = red_black_tree.search(word);
                                vector<pair<string, int>> chapter_word_count;
                                chapter_word_count.push_back(make_pair("Chapter1",0));
                                chapter_word_count.push_back(make_pair("Chapter2",0));
                                chapter_word_count.push_back(make_pair("Chapter3",0));
                                if(newnode == nullptr){
                                    red_black_tree.insert(word,chaptername);
                                    aa++;
                                    IndexEntry* entry = new IndexEntry(word);
                                    index_entries.push_back(entry);
                                    cout<<word<<" pushed"<<endl;
                                    for(int i=0;i<chapter_word_count.size();i++){
                                        if(chapter_word_count[i].first ==chaptername){
                                            chapter_word_count[i].second +=1;
                                            break;
                                        }
                                    }
                                    entry->setChapterWordCounts(chapter_word_count);    
                                }
                                else{
                                    // that means here word is being already present
                                    for(auto id_entry:index_entries){
                                        if(id_entry->getWord() == word){
                                            int flag =0,i;
                                            vector<pair<string, int>> word_count = id_entry->getChapterWordCounts();
                                            for(int j=0;j<3;j++){
                                                if(word_count[j].first == chaptername){
                                                    word_count[j].second +=1;
                                                    id_entry->setChapterWordCounts(word_count);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                word.clear();
                            }
                        }
                        else{
                            word += c;
                        }
                    }
                    HybridNode* nnode =red_black_tree.search(word);
                    vector<pair<string, int>> chapterwordcount;
                    chapterwordcount.push_back(make_pair("Chapter1",0));
                    chapterwordcount.push_back(make_pair("Chapter2",0));
                    chapterwordcount.push_back(make_pair("Chapter3",0));
                    if(nnode == nullptr && word.size()>0){            
                        red_black_tree.insert(word,chaptername);
                        IndexEntry* entr = new IndexEntry(word);
                        index_entries.push_back(entr);
                        cout<<word<<" pushed"<<endl;
                        for(int i=0;i<chapterwordcount.size();i++){
                            if(chapterwordcount[i].first ==chaptername){
                                chapterwordcount[i].second +=1;
                                break;
                            }
                        }
                        entr->setChapterWordCounts(chapterwordcount); 
                    }
                    else{
                        if(word.size() >0){
                        for(auto identry:index_entries){
                            if(identry->getWord() == word){
                                int flag =0,i;
                                vector<pair<string, int>> wordcount = identry->getChapterWordCounts();
                                for(int j=0;j<3;j++){
                                    if(wordcount[j].first == chaptername){
                                        wordcount[j].second +=1;
                                        identry->setChapterWordCounts(wordcount);
                                        break;
                                    }
                                }
                            }
                        }
                        }
                    }
                }
            }
            else{
                cout<<"Unable to open the file"<<endl;
            }
            
        }
        //now pruning starts from here
        int c=0;
        for(auto i_entry : index_entries){
            cout<<i_entry->getWord()<<" "<<i_entry->getChapterWordCounts()[0].first<<endl;
            cout<<i_entry->getWord()<<" "<<i_entry->getChapterWordCounts()[0].second<<endl;
            if(i_entry->getChapterWordCounts()[0].second>=1 &&
                i_entry->getChapterWordCounts()[1].second>=1 &&
                i_entry->getChapterWordCounts()[2].second>=1 ){
    
                cout<<"deleted word : "<<i_entry->getWord()<<endl;

                red_black_tree.deleteNode(i_entry->getWord());
                HybridNode* nnode = red_black_tree.search(i_entry->getWord());
                if(nnode==nullptr){
                    cout<<"\\\\\\\\ deleted\\\\\\"<<endl;
                }
            }
        }
        cout<<aa<<endl;
        cout<<c<<endl;
        cout<<"size of pruned index entry"<<endl;
        cout<<pruned_index_entries.size()<<endl;
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
        // IndexEntry
        vector<IndexEntry> idx_en;
        for(auto indexentry : index_entries){
            idx_en.push_back(*indexentry);
        }
        
        sort(idx_en.begin(),idx_en.end(),[]( IndexEntry& a,IndexEntry& b){
            return a.getWord() < b.getWord();
            }
        );

        return idx_en;

    }
};

