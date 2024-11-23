#include "Simulation.h"
#include "Auxiliary.h"
#include "Action.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <Auxiliary.h>
#include <string>


using std::cout;
using std::endl;
using std::ifstream;
using std::runtime_error;
using std::string;

Simulation::Simulation(const string &configFilePath) : isRunning(true), planCounter(0), actionsLog(vector<BaseAction*>()), plans(vector<Plan>()), settlements(vector<Settlement>()), facilitiesOptions(vector<FacilityType>()) {


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



void Simulation::start(){
    string fullLine = "";
    cout << "The simulation has started" << endl; // Outputs the message

    while (isRunning)
    {
        cout << "Please enter your action:" << endl; // Outputs the message
        std::getline(std::cin, fullLine);
        std::vector<std::string> args = Auxiliary::parseArguments(fullLine);

        if (args[0] == "settlement") {
            CreateSettlement(args);
        } else if (args[0] == "facility") {
            CreateFacility(args);
        } else if (args[0] == "plan") {
            CreatePlan(args);
        }
        else if(args[0]=="planStatus"){
            int id = std::stoi(args[1]);  

            BaseAction* base = new PrintPlanStatus(id);
            base->act(*this);
            addAction(base);
        }
        else if (args[0]=="changePolicy"){
            cout << "in change policy" << endl;
            int id = std::stoi(args[1]);  
            BaseAction* base = new ChangePlanPolicy(id,args[2]);
            cout << "base created" << endl;
            base->act(*this); // Error here
            cout << "base act" << endl;
            addAction(base);
            cout << "base added" << endl;
        }
        else if (args[0]=="log"){
            BaseAction* base = new PrintActionsLog();
            base->act(*this);
            addAction(base);
        }

    }
    
    // set up
    //it needs to read the confic files and fill the setelments and facilitys options vectors

    //after that it starts the simulation loop and begans the first step
}



void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){

    int lastPlanId = plans.empty() ? 0 : (plans.back().getPlanId()+1);
    cout << lastPlanId << endl;

    Plan p = Plan(lastPlanId,settlement,selectionPolicy,facilitiesOptions);
    plans.push_back(p);
    // user action: add plan

    //recives info from use, and creates a plan. (chacks if a plan can be added to the setelment in menchen)
}

void Simulation::addAction(BaseAction *action){
    // every tick, the user enters his action
    actionsLog.push_back(action);

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
std::vector<BaseAction*>& Simulation::getAction() {
    return actionsLog;
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


Plan& Simulation::getPlan(const int planID) {
    if (plans.empty()) {
        throw std::runtime_error("No plans available.");
    }

    for (auto plan : plans) {
        if (plan.getPlanId() == planID) {
            return plan;
        }
    }

    throw std::runtime_error("Plan not found.");
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
    BaseAction* base = new AddSettlement(args[1],getSettlementType(args[2]));
    base->act(*this);
            addAction(base);


}

// Function to create a facility
void Simulation::CreateFacility(const vector<string>& args) {
    // Ensure args has enough elements
    if (args.size() < 7) {
        // Handle error
        return;
    }
    int price = std::stoi(args[3]);  
    int lifeQuality_score = std::stoi(args[4]);
    int economy_score = std::stoi(args[5]);
    int environment_score = std::stoi(args[6]);
    string settlementName=args[1];
    BaseAction* base =new AddFacility(args[1],getFacitlityType(args[2]),price, lifeQuality_score, economy_score, environment_score);
    base->act(*this);
            addAction(base);
}
SelectionPolicy* Simulation::getSellectionPolicy(const string &policy) {
    if (policy == "eco") {
        return new EconomySelection();
    } else if (policy == "bal") {
        return new BalancedSelection(0, 0, 0);  // Adjust parameters if needed
    } else if (policy == "nve") {
        return new NaiveSelection();
    } else if (policy == "env") {
        return new SustainabilitySelection();
    } else {
        throw std::invalid_argument("Unknown selection policy: " + policy);
    }
}
SettlementType Simulation:: getSettlementType(const string type){
    SettlementType s;
    if (type == "0") {
        s = SettlementType::VILLAGE;
    }
    else if (type == "1") {
        s = SettlementType::CITY;
    }
    else if (type == "2") {
        s = SettlementType::METROPOLIS;
    }
    return s;
}
FacilityCategory Simulation:: getFacitlityType(const string type){
    FacilityCategory cat;
    if (type == "0") {
        cat = FacilityCategory::LIFE_QUALITY;  // Correct usage
    }
    else if (type == "1") {
        cat = FacilityCategory::ECONOMY;
    }
    else if (type == "2") {
        cat = FacilityCategory::ENVIRONMENT;
    }
    return cat;
}





void Simulation::CreatePlan(const vector<string>& args) {
            BaseAction* base = new AddPlan(args[1],args[2]);
            base->act(*this);
            addAction(base);
}

