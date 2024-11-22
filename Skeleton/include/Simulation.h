#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement &getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();

        ////our functions
        void CreateSettlement(const vector<string>& args);
        void CreateFacility(const vector<string>& args);
        void addFacilityToPlan(const vector<string>& args);
        void CreatePlan(const vector<string>& args);
        SelectionPolicy getSellectionPolicy(string policy);
 


    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement> settlements;
        vector<FacilityType> facilitiesOptions;

};