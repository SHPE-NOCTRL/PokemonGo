#include <string>
using namespace std;

class pokeNode {
    public:
    pokeNode(){
        next = NULL;
    }
    void insert(string value){
        if(!search(value)){
            if(entry == "")
                entry = value;
            else if(next == NULL){
                next = new pokeNode();
                (*next).insert(value);
            }
            else
                (*next).insert(value);
        }
    }
    bool search(string value){
        if(entry == value)
            return true;
        if(next == NULL)
            return false;
        return (*next).search(value);
    }
    string getEntry(){
        return entry;
    }
    pokeNode getNext() {
        return *next;
    }
    private:
    string entry = "";
    pokeNode *next;
};