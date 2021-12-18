/*
    Program Name: PokemonGo! Team Generator

    Purpose: The purpose of the program is to inform the reader of the best possible team they can have for Pokemon GO! PvP battles. The program is a work in a progess and intends to use machine learning algorithm to produce appropriate output.
                Presently only the exact result of any team is generated but ideally the program will be developed to include a locally stored neural network that will generate values as weights to estimate team results. Once the neural network part is developed the real machine learning can begin.
                Things to implement are a way to keep track of neural network training results, a way to track test results, a way to track gowth training, a way to track prediction variables, a definition for the training and testing functions, a way to get user input from the cmd rather than from opening the real file, a way to parallel compute the training data set, a comfy user-interface, preferable in C++, the optimization of the test.js file (idealliy converting its work into a C++ program), a complete JSON API in/for Pokemon_count.h
    
    Last Update: 12/17/2021 
*/

#include <string>
#include <iostream>
#include <fstream>
#include "pokemon_count.h"
#include <thread>

using namespace std;

// templated functions. Used so the compiler knows to note compile w/out ensuring these functions are implemented. Also for the assembler to know these functions will be implemented.
string getName(string);
string getFastMoveCount(string);
string getChargeMoveCount(string);
//end of templated functions.



// A Thread function. The only thread function in the program. This is used on all threads activated in the program. I like to think of it as the real 'main' function that gets called from the main function for all threads.
void thread_func ( string b , int thread_number , bool *complete ) {
    //The instruction below takes arg[0] and arg[1] and pieces them together in a way that makes sense to the OS as used in the program. The program currently pieces an instruction to the cmd to start node.js with program of test.js and a set of pokemon to run on the javascript code and includes the thread number for output.
    system ( (b + " " + to_string(thread_number)).c_str() );
    //the below commented code has not been deleted yet because eventually output will happen from the C++ code and this will serve as a guide to thread tracking.
    //string filename = "Threads/thread_output_"+to_string(thread_number)+".txt";
    //fstream file ( filename );
    //file << thread_number;
    //setting arg[2] to the opposite value so the main program hears about the thread function completing its functionality.
    *complete = !*complete;
    //file.close();
}//end thread_func().

int main () {
    // process to implement
    /*
        create array of sets
        call new thread func in its own loop
    */
    // consider each pokemon_count object as an actual pokemon. Pokemon_count accesses the test.json file and uses it to create the thread function pokemon arguments. Essentially a JSON API w/ specific functions for Pokemon Data.
    Pokemon_count finder1, finder2, finder3;
    // used to keep track of the pokemon in the test.json file that the pokemon_count objects point to.
    int a, b, c;
    // create array of bools to keep track of when a thread number is available
    bool * threadtracker = new bool[6];

    // Used to keep track of the max number of moves a pokemon may have. Only used in the else conditional as argument to the cmd thread function. 
    int fast_moves_1 = 0;
    int fast_moves_2 = 0;
    int fast_moves_3 = 0;
    int charge_moves_1 = 0;
    int charge_moves_2 = 0;
    int charge_moves_3 = 0;

    //For loop to set all bools that track threads to false so we know they 'are' in use.
    for(int i = 0; i < 6; i++){
        threadtracker[i] = false;
    }
    // Initialize our actual array of threads.
    thread threads [6];
    // Not utilized yet. Will be implemented in a way for the code to be more readable.
    string string_arg [6];

    // begin verifying size of pokemon user input list.
    finder1 = Pokemon_count(1);
    int lengthofpokemonlist = finder1.getNumberOfPokemon();
    //end verifying pokemon list length. This works because all pokemon_count objects will use the same test.json file.
    cout << "Length of Pokemon list: " << lengthofpokemonlist;
    // SIZEOFPROGRAM saves the value that is essentially the size of the program. The larger this number is the longer the program can be expected to take to complete.
    int SIZEOFPROGRAM = finder1.combination(lengthofpokemonlist,3);
    // Here the next instruction will set the size of printline to the program size. This is done so when the if conditional is met the program will store the every node.js instance to complete into an array to they give as an argument to a thread with the thread function.
    string * printline = new string[SIZEOFPROGRAM];//is equal to statment : string blob
    cout << "Size of program: " << SIZEOFPROGRAM;
    a = 0; b = a+1; c = b+1;
    int counter = 0;

    // the below if is the if of the program. If the if condition is true this means the number of pokemon a user has submitted is greater than three and the appropriate code is ran for what is considered a LARGE list.
    if(lengthofpokemonlist != 3){
        // The below while() will generate our array of thread function arguments printline.
        while(a + 2 < lengthofpokemonlist) {
            finder1 = Pokemon_count(a+1);
            finder2 = Pokemon_count(b+1);
            finder3 = Pokemon_count(c+1);
            printline[counter] = "node test.js " + getName(finder1.find()) + " " + getName(finder2.find()) + " " + getName(finder3.find()) ;//+ " " + to_string((counter%6)+1);
            if(c+1<lengthofpokemonlist){
                c++;
            }
            else if(b+1 < lengthofpokemonlist-1){
                b++;
                c = b+1;
            }
            else {
                a++;
                b = a + 1;
                c = b + 1;
            }
            counter++;
        }//end while() to generate thread function arguments.

        // The counter integer will be used to keep track of the number of thread functions we have ran.
        counter = 0;
        // The below for-loop runs the first 6 thread_func() instances.
        for(int i = 0; i < 6; i++){
            // Assign thread[i] to a thread with thread function thread_func() to run, and arguments of a node.js instances and the bool to track its present activity.
            threads[i].swap(thread(&thread_func, printline[counter], (i+1), &threadtracker[i]));
            counter++;
        }//end for(run first 6 threads).
        // The below while-loop is the final stage of the program if the if conditional was met. From this main thread the threadtracker boolean variables are monitored and new instances of thread functions are ran on appropriate threads.
        while(counter < SIZEOFPROGRAM){
            // For-loop to monitor thread tracking bools.
            for(int i = 0; i < 6; i++){
                // Check if thread[i] is available.
                if(threadtracker[i]){
                    // Close thread process.
                    threads[i].join();
                    threads[i].~thread();
                    //end close thread process.
                    // Reset thread tracking variable.
                    threadtracker[i] = !threadtracker[i];
                    // Assign thread[i] to a thread with valid thread function arguments.
                    threads[i].swap(thread(&thread_func, printline[counter], (i+1), &threadtracker[i]));
                    // Increment thread_func counter variable.
                    counter++;
                    // Done for no reason other than buble sort like flow. Will update for performance as needed.
                    i=6;
                }
            }//end thread monitoring pass.
        }
    }//end if ( LARGE list ).
    // The else below is the else that is ran when a list is 3 pokemon in length. If the length is less than three the program will break in here.
    else {
        // The instruction below is done in both the if and the else. It sets our pokemon object to a valid pokemon.
        finder1 = Pokemon_count(a+1);
        finder2 = Pokemon_count(b+1);
        finder3 = Pokemon_count(c+1);
        //end setting pokemon.
        // Below instructions can be removed but I use them to gage the eth of the program in runtime.
        cout << "Ho-Oh fast move count from pokemon_count obj: " + getFastMoveCount(finder1.find()) << endl;
        
        cout << "Ho-Oh charge move count from pokemon_count obj: " << getChargeMoveCount(finder1.find()) << endl;
        //end run-time time gage.

        // Setting the move counts for each pokemon. This is done in only the else conditional. The thread function in the else conditional varies from the thread function of the if conditional in the argument passed to the thread function thru the printline variable. The point is the if conditional only passes the pokemon name arguments and the else conditional passes the complete address.
        fast_moves_1 = stoi(getFastMoveCount(finder1.find()));
        fast_moves_2 = stoi(getFastMoveCount(finder2.find()));
        fast_moves_3 = stoi(getFastMoveCount(finder3.find()));
        charge_moves_1 = stoi(getChargeMoveCount(finder1.find()));
        charge_moves_2 = stoi(getChargeMoveCount(finder2.find()));
        charge_moves_3 = stoi(getChargeMoveCount(finder3.find()));
        //end setting the move counts.
        // Recalculating the size of program variable utilizing the pokemon_count combination() function. The formula: Total#pokecombinations = product(pokeIfastmovescombination*pokeIchargemovescombination, for 0 < I < 4, or for each pokemon). This is the same as counting pokemon. For more details about why this works check out https://en.wikipedia.org/wiki/Counting 
        lengthofpokemonlist = finder1.combination(fast_moves_1,1) * finder1.combination(fast_moves_2,1) * finder1.combination(fast_moves_3,1) * finder1.combination(charge_moves_1,2) * finder1.combination(charge_moves_2,2) * finder1.combination(charge_moves_3,2);
        SIZEOFPROGRAM = lengthofpokemonlist;
        cout << "\nResized program size: " << SIZEOFPROGRAM << endl;
        delete [] printline;
        printline = new string[SIZEOFPROGRAM];
        //end sizing program size and printline.
        // The below for() will generate our array of thread function arguments printline.
        for(int d = 0; d < fast_moves_1; d++){
            for(int e = 1; e < charge_moves_1; e++){
                for(int f = e+1; f < charge_moves_1+1; f++){
                    for(int g = 0; g < fast_moves_2; g++){
                        for(int h = 1; h < charge_moves_2; h++){
                            for(int i = h+1; i < charge_moves_2+1; i++){
                                for(int j = 0; j < fast_moves_3; j++){
                                    for(int k = 1; k < charge_moves_3; k++){
                                        for(int l = k+1; l < charge_moves_3+1; l++){
                                            printline[counter] = "node test.js premierclassic/10000-40/"+getName(finder1.find())+"-m-"+to_string(d)+"-"+to_string(e)+"-"+to_string(f)+"%2C"+getName(finder2.find())+"-m-"+to_string(g)+"-"+to_string(h)+"-"+to_string(i)+"%2C"+getName(finder3.find())+"-m-"+to_string(j)+"-"+to_string(k)+"-"+to_string(l) + " " + "-1" + " " + "-1";                                            
                                            counter++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }//end for() to generate thread function arguments.
        // The counter integer will be used to keep track of the number of thread functions we have ran.
        counter = 0;
        // The below for-loop runs the first 6 thread_func() instances.
        for(int z = 0; z < 6; z++){
            // Assign thread[z] to a thread with thread function thread_func() to run, and arguments of a node.js instances and the bool to track its present activity.
            threads[z].swap(thread(&thread_func, printline[counter], (z+1), &threadtracker[z]));
            counter++;
        }//end for(run first 6 threads).
        // The below while-loop is the final stage of the program if the if conditional was met. From this main thread the threadtracker boolean variables are monitored and new instances of thread functions are ran on appropriate threads.
        while(counter < SIZEOFPROGRAM){
            // For-loop to monitor thread tracking bools.
            for(int i = 0; i < 6; i++){
                // Check if thread[i] is available.
                if(threadtracker[i]){
                    // Close thread process.
                    threads[i].join();
                    threads[i].~thread();
                    //end close thread process.
                    // Reset thread tracking variable.
                    threadtracker[i] = !threadtracker[i];
                    // Assign thread[i] to a thread with valid thread function arguments.
                    threads[i].swap(thread(&thread_func, printline[counter], (i+1), &threadtracker[i]));
                    // Increment thread_func counter variable.
                    counter++;
                    // Done for no reason other than buble sort like flow. Will update for performance as needed.
                    i=6;
                }
            }//end thread monitoring pass.
        }
    }//end else ( SMALL list )

    delete [] threadtracker;
    delete [] printline;
    
    return 0;
}//end main().

// The getName function looks thru a pokemons data passed as the argument and finds its name and returns the name of the pokemon as a string variable return_value. This can be moved in to the pokemon_count page.
string getName(string input) {
    int tracker = 0, startPoint = 0, endPoint = 0;
    string return_value = "";
    for(int i = 0; i < input.length(); i++) {
        if(input[i] == '"')
            tracker++;
        if(tracker == 3 && startPoint == 0) {
            startPoint = i + 1;
        }
        if(tracker == 4 && endPoint == 0) {
            endPoint = i;
        }
    }
    while(startPoint < endPoint) {
        return_value += input[startPoint];
        startPoint++;
    }
    return return_value;
}//end getName.

// The getFastMoveCount function looks thru a pokemons data passed as the argument and finds its fast move amount number and returns the fast move amount of the pokemon as a string variable return_value. This can be moved in to the pokemon_count page.
string getFastMoveCount(string input) {
    int tracker = 0, startPoint = 0, endPoint = 0, item_number = 2, current_item = 1;
    string return_value = "";
    int i = 0;
    while(current_item < item_number){
        for(i; i < input.length(); i++) {
            if(input[i] == '"')
                tracker++;
            if(tracker == 6 && startPoint == 0) {
                startPoint = i + 2;
            }
            if(input[i] == ',' && startPoint != 0 && endPoint == 0) {
                endPoint = i;
                break;
            }
        }
        while(startPoint < endPoint) {
            return_value += input[startPoint];
            startPoint++;
        }
        current_item++;
    }

    return return_value;
}//end getFastMoveCount.

// The getChargeMoveCount function looks thru a pokemons data passed as the argument and finds its charge move amount number and returns the charge move amount of the pokemon as a string variable return_value. This can be moved in to the pokemon_count page.
string getChargeMoveCount(string input) {
    int tracker = 0, startPoint = 0, endPoint = 0, item_number = 2, current_item = 1;
    string return_value = "";
    int i = 0;
    //while(current_item < item_number){
        for(i; i < input.length(); i++) {
            if(input[i] == '"')
                tracker++;
            if(tracker == 8 && startPoint == 0) {
                startPoint = i + 2;
            }
            if(input[i] == ',' && startPoint != 0 && endPoint == 0) {
                endPoint = i;
                break;
            }
        }
        while(startPoint < endPoint) {
            return_value += input[startPoint];
            startPoint++;
        }
        current_item++;
    //}

    return return_value;
}//end getChargeMoveCount.