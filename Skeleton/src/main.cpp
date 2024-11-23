#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation* backup = nullptr;

int main(int argc, char* argv[]) {

    cout << "argc: " << argc << endl;

    for(int i=0; i<argc; i++){
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }

    cout << "Let's Begine: " << endl;

    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }

    string configurationFile = argv[1];
    cout << "create Simulation: " << configurationFile << endl;
    Simulation simulation(configurationFile);
    cout << "Simulation created" << endl;
    simulation.start();
    cout << "Simulation started" << endl;
    //if(backup!=nullptr){
    //	delete backup;
    //	backup = nullptr;
    //}
    
    return 0;
}
