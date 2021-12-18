/*
**    Program Name: PokemonGo! Team Generator
**    Class Name: Pokemon_count
**    Purpose: The Pokemon_count class acts a definition for a pokemon object. The class provides a permutation and combination calculator and some functions for interacting with JSON formatted files. Together this help the main program interact with a 'Pokemon' object effectively. 
**              Things to be implemented in the class are more JSON accessing functions like get name get move count and getting and setting any other variables that may be useful to the overall functionallity of the entire program.
**    
**    Last Update: 12/18/2021 
*/

#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Pokemon_count {

    public:
    // 0-arg constructor.
    Pokemon_count(){
        if(ifile.is_open())
            ifile.close();
        //ifile.open("test.json");
        token = 0;
    }
    // 1-arg constructor.
    Pokemon_count(int findToken){
        if(ifile.is_open())
            ifile.close();
        //ifile.open("test.json");
        afile = "test.json";
        setNumberOfPokemon();
        if(findToken <= getNumberOfPokemon())
            token = findToken;
        else
            cout << "A token has been passed as larger than the number of pokemon available";
    }
    // find () opens the file titled afile set in the constructor and finds the pokemon whos token matches the index in afile.
    string find () {
        ifile.open(afile);
        bool openCase = false;
        bool closeCase = false;
        char currChar = ' ';
        char openQ = '"';
        char closeKey = '}';
        int kickStart;
        int kickEnd;
        int counter = 0;
        int findIndex = token;
        string container_2 = "";

        //mod ifile start position to be the first index of afile instead of the start of afile. Done so we can look for patterns in the data sheet rather than watching values.
        do {
            currChar = ifile.get();
        } while(currChar != '[');
            
        while(!ifile.eof()){
            currChar = ifile.get();
            //cout << currChar;
            if(currChar == openQ && !openCase){
                openCase = true;
                kickStart = ifile.tellg();
                //cout << "First";
            }
            else if(currChar == closeKey && openCase){
                closeCase = true;
                kickEnd = ifile.tellg();
                container_2 = copyMid(kickStart-1,kickEnd);
                counter++;
                if(counter == findIndex){
                    ifile.close();
                    return container_2;
                }
                openCase = closeCase = false;
            }
        }
        cout << counter;
        ifile.close();
        return "0";
    }// end find().

    // getNumberOfPokemon () returns the number of pokemon in the afile file.
    int getNumberOfPokemon ( ) const {
        return numberofpokemon;
    }//end getNumberOfPokemon().

    // setNumberOfPokemon () counts the number of pokemon in afile file and sets the private variable numberofpokemon to the value found.
    void setNumberOfPokemon ( ) {
        ifile.open(afile);
        bool dapokegon = false;
        char dapokegon_c = ',';
        bool openCase = false;
        bool closeCase = false;
        char currChar = ' ';
        char openQ = '"';
        char closeKey = '}';
        int kickStart;
        int kickEnd;
        int counter = 0;
        string container_2 = "";

        //mod ifile start position
        do {
            currChar = ifile.get();
        } while(currChar != '[');
            
        while(!ifile.eof()){
            currChar = ifile.get();
            //cout << currChar;
            if(currChar == openQ && !openCase){
                openCase = true;
                kickStart = ifile.tellg();
                //cout << "First";
            }
            else if(currChar == closeKey && openCase){
                closeCase = true;
                kickEnd = ifile.tellg();
                container_2 = copyMid(kickStart-1,kickEnd);
                counter++;
                //cout << counter;
                openCase = closeCase = false;
                currChar = ifile.get();
                //if(currChar != dapokegon_c){
                //    ifile.seekg(1,ifile.end);
                //}
            }
        }
        ifile.seekg(0);
        ifile.seekp(0);
        ifile.close();
        numberofpokemon = counter;
    }//end setNumberOfPokemon().

    //copy mid works as expected. Accepts the starting and ending point of a section of pokemon data and copies and returns the section as its own string variable. This basically returns a pokemon data entry.
    string copyMid(int mid_start, int mid_end){
        ifile.seekg(mid_start);
        string stringpass = " ";
        for(int i = 0; i < mid_end - mid_start; i++)
            stringpass += ifile.get();
        return stringpass;
    }//end copyMid().
    // permutation() is a permutation math function. It accepts the number of items in a set as arg-1 and the number to pick from the set to define a permutation as arg-2. Then it uses these to calculate the total number of permuations stored in the functions local variable top.
    int permutation ( int _number, int _pick ) const {
        int top = 1;
        if(_pick > _number){
            return top;
        }
        else{
            while(_number > _pick){
                top *= _number;
                _number--;
            }
        }
        return top;
    }//end permutation().
    // combination() is a combination math function. It accepts the number of items in a set as arg-1 and the number to pick from the set to define a combination as arg-2. Then it uses these to calculate the total number of combinations stored in the functions local variable top.
    const int combination ( int _number, int _pick ) const {
    int top = 1;
    int number_ = _number;
    int bottom = 1;
    if(_pick > _number){
        return top;
    }
    else{
        while(number_ > _number - _pick){
            top *= number_;
            number_--;
        }
        while(_pick != 0){
            bottom *= _pick;
            _pick--;
        }
    }
    return top/bottom;
}//end combination().

    private:
        string afile = ""; //private variable afile - stores the name of the file associate with a pokemon. Currently it either will store the name no file when a token is not assigned to the pokemon_count object or the default name of test.json when the pokemon token has been defined.
        fstream ifile; //private variable ifile - stores the file corresponding to afile. Usually this file is closed but when the object does open ifile it does so thru this variable. This is done to avoid changing memory too often.
        int token; //private variable token - store what is equivalent to the pokemons index in the afile file. When the find function is used the tokens value is referenced as the index of the pokemon.
        int numberofpokemon = 0; //private variable numberofpokemon. By default this is 0. When a valid token is set as the value of the private token variable then this variable is set to an appropriate value otherwise the value is 0.
};