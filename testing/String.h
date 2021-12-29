#include <iostream>
#include <fstream>
using namespace std;
class String {
    private:
        char* array;
        int height;
    public:
        String() {
            array = (char*) malloc(128*sizeof(char));
            for(int i = 0; i < 128; i++) {
                array[i] = '\0';
            }
            height = 0;
        }
        String(char* value, int height) {
            array = (char*) malloc(128*sizeof(char));
            for(int i = 0; i < 128; i++) {
                array[i] = '\0';
            }
            for(int i = 0; i < height; i++) {
                array[i] = value[i];
            }
            this->height = height;
        }
        String(char value, int height) {
            array = (char*) malloc(128*sizeof(char));
            for(int i = 0; i < 128; i++) {
                array[i] = '\0';
            }
            for(int i = 0; i < height; i++) {
                array[i] = value;
            }
            this->height = height;
        }

        char* c_str(){
            return this->array;
        }

        String operator+ (const String& anotherString){
            String* theString;
            int total_new_height = this->height + anotherString.height;
            char* theArray = (char*) malloc((total_new_height+1)*sizeof(char));
            for(int i = 0; i < total_new_height + 1; i++){
                theArray[i] = '\0';
            }
            int ctr = 0;
            for(ctr; ctr < this->height; ctr++){
                theArray[ctr] = this->array[ctr];
            }
            for(ctr; total_new_height - ctr > 0; ctr++){
                theArray[ctr] = anotherString.array[ctr - this->height];
            }
            //theString->height = total_new_height;
            //theString->array = theArray;
            theString = new String(theArray,total_new_height);
            return *theString;
        }

        String operator- (const int height) {
            String theString;
            int total_new_height = this->height - height;
            if(total_new_height < 0){
                total_new_height = 0;
            }
            char* theArray = (char*) malloc((total_new_height+1)*sizeof(char));
            if(total_new_height != 0)
                for(int i = 0; i < total_new_height; i++){
                    theArray[i] = this->array[i];
                }
            theArray[total_new_height] = '\0';
            theString.array = theArray;
            theString.height = total_new_height;
            return theString;
        }
        
        friend ostream& operator<<(ostream& thestream, const String& thestring);
        friend istream& operator>>(istream& thestream, String& thestring);
        friend String& operator>>(String& thestream, String& thestring);
};

ostream& operator<<(ostream& thestream, const String& thestring){
    for(int i = 0; thestring.array[i] != '\0'; i++){
        thestream << thestring.array[i];
    }
    thestream << '\0';
    return thestream;
}

String& operator>>(String& thestream, String& thestring){
    for(int i = 0; i < 128; i++){
        thestring = thestring + thestream;
    }
    return thestream;
}

istream& operator>>(istream& thestream, String& thestring){
    cout << thestream.gcount();
    return thestream;
}