#include <iostream>
class pokeQueueNode {
    private:
        int value;
        pokeQueueNode* next;
    
    public:
        pokeQueueNode() {
            value = -1;
            next = NULL;
        }

        int getValue() const {
            return value;
        }
        pokeQueueNode& getNext() const {
            return *next;
        }

        void addValue(int _value) {
            value = _value;
        }

        void setValue(int _value) {
            value = _value;
        }
        void setNext(pokeQueueNode& address){
            next = &address;
        }

        ~pokeQueueNode() {
            value = 0;
            if(next != NULL)
                (*next).~pokeQueueNode();
            next = NULL;
        }
};