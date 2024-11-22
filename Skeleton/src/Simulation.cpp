#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Auxiliary.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <Auxiliary.h>
#include "Facility.h"  // Make sure this is included where you need to use FacilityCategory
#include "Settlement.h"  // Include the header file
#include "Plan.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::runtime_error;
using std::string;

Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0), actionsLog(vector<BaseAction*>()), plans(vector<Plan>()), settlements(vector<Settlement>()), facilitiesOptions(vector<FacilityType>()) {




    std::ifstream configFile(configFilePath);

    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open file at " << configFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(configFile, line)) {  // Read file line by line
        std::vector<std::string> args = Auxiliary::parseArguments(line);
        if (args.empty()) continue;  // Skip empty lines

        const std::string& command = args[0];
        if (command == "settlement") {
            CreateSettlement(args);
        } else if (command == "facility") {
            CreateFacility(args);
        } else if (command == "plan") {
            CreatePlan(args);
        } else {
            std::cerr << "Error: Unknown command '" << command << "' in config file." << std::endl;
        }
    }

    configFile.close();
}



void start(){
    // set up
    //it needs to read the confic files and fill the setelments and facilitys options vectors

    //after that it starts the simulation loop and begans the first step
}



void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    int lastPlanId = plans.empty() ? 0 : plans.back().getPlanId();
    Plan p = Plan(lastPlanId,settlement,selectionPolicy,facilitiesOptions);
    // user action: add plan

    //recives info from use, and creates a plan. (chacks if a plan can be added to the setelment in menchen)
}

void addAction(BaseAction *action){
    // every tick, the user enters his action

    // action being logged

    // call the corresponding function 
}

bool Simulation::addSettlement(Settlement settlement){
    settlements.push_back(settlement);
}

bool Simulation:: addFacility(FacilityType facility){
    facilitiesOptions.push_back(facility);

    // user action: add facility

    // user adds facility to facility options

    //ligal iligal?
    
}

bool Simulation::isSettlementExists(const string &settlementName){
    // chacks if setelment exsists
    
    for(Settlement settlement : settlements){ /// check syntax
        if(settlement.getName() == settlementName){
            return true;
        }
    }
    return false;
    
}

Settlement &Simulation::getSettlement(const string &settlementName){
     for(Settlement setelment : settlements){ /// chack sintacs
        if(setelment.getName() == settlementName){
            return setelment;
        }
    }
    throw std::runtime_error("Settlement not found");
}


Plan &Simulation::getPlan(const int planID){
    for (Plan plan : plans)
    {
        if(plan.getPlanId() == planID)
            return plan;
    }
    throw std::runtime_error("Plan not found");

}

void Simulation::step(){
    // main step:

    // call for user to enter his play

    // acualize this plan and return the user the string resalt / error
    
}

void Simulation::close(){
    // delete everything. make sure no memory leaks
}

void Simulation::open(){
    // ??????????
    // maby read config files?
}

// Function to create a settlement
void Simulation::CreateSettlement(const vector<string>& args) {
    // Ensure args has at least 3 elements
    if (args.size() < 3) {
        // Handle error (for example, return or log an error message)
        return;
    }

    // Determine settlement type
    SettlementType s;
    if (args[2] == "0") {
        s = SettlementType::VILLAGE;
    }
    else if (args[2] == "1") {
        s = SettlementType::CITY;
    }
    else if (args[2] == "2") {
        s = SettlementType::METROPOLIS;
    }
    
    // Create and add settlement
    Settlement newSettlement(args[1], s); // Removed 'new' and fixed the constructor call
    addSettlement(newSettlement);
}

// Function to create a facility
void Simulation::CreateFacility(const vector<string>& args) {
    // Ensure args has enough elements
    if (args.size() < 7) {
        // Handle error
        return;
    }

    // Determine facility category
    FacilityCategory cat;
    if (args[2] == "0") {
        cat = FacilityCategory::LIFE_QUALITY;  // Correct usage
    }
    else if (args[2] == "1") {
        cat = FacilityCategory::ECONOMY;
    }
    else if (args[2] == "2") {
        cat = FacilityCategory::ENVIRONMENT;
    }

    // Convert arguments to integers for price and scores
    int price = std::stoi(args[3]);  
    int lifeQuality_score = std::stoi(args[4]);
    int economy_score = std::stoi(args[5]);
    int environment_score = std::stoi(args[6]);
    string settlementName=args[1];
    // Create and add facility
    Facility f(args[1], settlementName, cat, price, lifeQuality_score, economy_score, environment_score); 
    addFacility(f);
}
 SelectionPolicy Simulation::getSellectionPolicy(string policy){
        if (policy == "eco") {
        s1 = new EconomySelection();
    }
    else if (policy == "bal") {
        s1 = new BalancedSelection(0, 0, 0);  // Adjust parameters as needed
    }
    else if (policy == "nve") {
        s1 = new NaiveSelection();
    }
    else if (policy== "env") {
        s1 = new SustainabilitySelection();
    }
}



void Simulation::CreatePlan(const vector<string>& args) {
    // Ensure args has at least 3 elements
    if (args.size() < 3) {
        cout << "Error: Insufficient arguments to create a plan." << endl;
        return;
    }

    // Find the corresponding settlement
    Settlement* s = nullptr;  // Use a pointer to reference a settlement
    for (Settlement& b : settlements) {
        if (b.getName() == args[1]) {  // Assuming getName() returns the name of the settlement
            s = &b;
            break;
        }
    }

    // Handle case where settlement is not found
    if (s == nullptr) {
        cout << "Error: Settlement with name '" << args[1] << "' not found." << endl;
        return;
    }

    // Create selection policy
    SelectionPolicy* s1 = nullptr;
    if (args[2] == "eco") {
        s1 = new EconomySelection();
    }
    else if (args[2] == "bal") {
        s1 = new BalancedSelection(0, 0, 0);  // Adjust parameters as needed
    }
    else if (args[2] == "nve") {
        s1 = new NaiveSelection();
    }
    else if (args[2] == "env") {
        s1 = new SustainabilitySelection();
    }
    else {
        cout << "Error: Unknown selection policy '" << args[2] << "'." << endl;
        return;
    }

    // Delegate plan creation to addPlan
    addPlan(*s, s1);
}

