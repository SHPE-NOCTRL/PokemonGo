#include "pokeQueueNode.h"
class pokeQueue {
    pokeQueue(){
        length = 0;
        root = new pokeQueueNode();
    };

    void enQueue(int _value){
        if(length == 0)
             (*root).setValue(_value);
        else
            root->addValue(_value);
        length++;
    };

    int deQueue(){
        int return_val = length;
        --length;
        pokeQueueNode temp;
        temp.setValue(root->getValue());
        (*root).~pokeQueueNode();
        root = root->getNext();
        return return_val;

    }
    
    private:
        int length;
        pokeQueueNode* root;
};