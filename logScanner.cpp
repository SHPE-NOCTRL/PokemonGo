

#include <string>
#include <fstream>
#include <iostream>
#include "pokeNode.h"
using namespace std;
class logScanner {
    private:
        string* OS;
        string* USER;
        char* PATHTOLOGGER;
        int start;
        int end;
        fstream ifile;
        pokeNode* myPokeNode;
    public:
        logScanner(){
            PATHTOLOGGER = new char(sizeof("C:/Users/mpidi/AppData/Local/Google/Chrome/User Data/Default/Local Storage/leveldb/\0"));
            PATHTOLOGGER = "C:\\Users\\mpidi\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Local Storage\\leveldb\\\0";
            string PATHTOLOGGER_C = "\"C:\\Users\\mpidi\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Local Storage\\leveldb\\\"";
            std::system(("del /Q " + PATHTOLOGGER_C + "*").c_str());
            start = end = 0;
            myPokeNode = new pokeNode();
        }
        void scan(){
            int newstart;
            int newend;
            char input;
            ofstream afile("logfile.txt", ofstream::out | ofstream::trunc);
            fstream thefile;
            char **output = (char**) malloc(256*sizeof(char*));
            for( int i = 0; i < 256; i++){
                output[i] = (char*) malloc(16*sizeof(char));
            }
            for( int r = 0; r < 256; r++){
                for( int c = 0; c < 16; c++)
                    output[r][c] = '\0';
            }
            char* ifilename = (char*) malloc(128*sizeof(char));
            string filename = "000003.log";
            int i = 0;
            for(i = 0; PATHTOLOGGER[i] != '\0'; i++){
                ifilename[i] = PATHTOLOGGER[i];
            }
            int q = 0;
            for(q = 0; q < filename.size(); q++){
                ifilename[i+q] = filename[q];
            }
            
            //ifilename[i+q] = '\0';
            ifilename = (char*) malloc((i+q+1)*sizeof(char));
            for(i = 0; PATHTOLOGGER[i] != '\0'; i++){
                ifilename[i] = PATHTOLOGGER[i];
            }
            for(q = 0; q < filename.size(); q++){
                ifilename[i+q] = filename[q];
            }
            
          
            
            while(1){

                    ifile.open((string)ifilename);
                    
                    if(ifile.is_open()){
                    
                        while(!ifile.eof()){
                            ifile.get(input);
                            afile << input;
                        }
                        
                        ifile.close();
                        afile << std::endl;
                        afile.close();
                        thefile.open("logfile.txt");
                        if(findNewPokemon(thefile,output)){
                            for(int r = 0; output[r][0] != '\0'; r++)
                                (*myPokeNode).insert(output[r]);
                            pokeNode temp = *myPokeNode;
                            while(&temp != NULL){
                                //cout << temp.getEntry();
                                temp = (temp.getNext());
                            }
                            
                        }
                        //cout << "Got here" << endl;
                        //end = newend;
                        thefile.close();
                        afile.open("logfile.txt", ofstream::out | ofstream::trunc);
                    }
                    else
                        cout << "not open\n";
                    ofstream inputfile("pokemon_input2.json",ofstream::out | ofstream::trunc);
                    inputfile << (*myPokeNode).toString();
                    inputfile << endl;
                    inputfile.close();
            }
        }
        bool findNewPokemon(fstream& afile, char **output){
            afile.seekg(afile.beg);
            afile.seekp(afile.beg);
            char finder[4] = {'\0'};
            int counter = 0;
            int entry = 0;
            while(!afile.eof()){
                for(int i = 0; i < 4; i++){
                    if(i != 3)
                        finder[i] = finder[i+1];
                    else
                        finder[i] = afile.get();
                }
                if(finder[0] == 'n' && finder[1] == 'a' && finder[2] == 'm'){
                    afile.seekg((std::streamoff)1,afile.cur);
                    afile.seekp((std::streamoff)1,afile.cur);
                    afile.get();
                    while(afile.peek() != '"'){
                        output[entry][counter] = afile.get();
                        counter++;
                    }
                    output[entry][counter] = '\0';
                    counter = 0;
                    entry++;
                }
            }
            if(entry != 0)
                return true;
            return false;
        }
};

int main(){
    logScanner* scanner = new logScanner();
    std::cout << "Calling scanner\n";
    scanner->scan();
    return 1;
}