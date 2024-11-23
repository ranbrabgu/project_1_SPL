#include "Action.h"
#include "Simulation.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
    errorMsg = "";
}

void BaseAction::error(string errorMsg) {
    status = ActionStatus::ERROR;
    this->errorMsg = std::move(errorMsg);
}

const string &BaseAction::getErrorMsg() const {
    return errorMsg;
}



AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy): settlementName(settlementName), selectionPolicy(selectionPolicy) {}
void AddPlan::act(Simulation &simulation) {
    try {
        Settlement &settlement = simulation.getSettlement(settlementName);
        SelectionPolicy* policy = simulation.getSellectionPolicy(selectionPolicy);
        simulation.addPlan(settlement, policy);  // Add the plan
        complete();  // Mark the action as completed
    } catch (const std::exception &e) {
        error("Error during AddPlan: " + string(e.what()));
    }
}
const string AddPlan::toString() const {
    return "AddPlan for " + settlementName + " using policy " + selectionPolicy;
}
AddPlan *AddPlan::clone() const {
    return new AddPlan(*this);
}



AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):settlementName(settlementName),settlementType(settlementType){}
 
 void AddSettlement:: act(Simulation &simulation) {
    Settlement settlement(settlementName, settlementType);
    simulation.addSettlement(settlement); 
}

AddSettlement* AddSettlement::clone() const {
    return new AddSettlement(*this);
}
const string AddSettlement::toString()const {
    string typeStr;
    switch (settlementType) {
        case SettlementType::VILLAGE:
            typeStr = "Village";
            break;
        case SettlementType::CITY:
            typeStr = "City";
            break;
        case SettlementType::METROPOLIS:
            typeStr = "Metropolis";
            break;
        default:
            typeStr = "Unknown";
            break;
    }
    return settlementName + " (" + typeStr + ")";
}


AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
    : facilityName(facilityName),  // Use member variable names
      facilityCategory(facilityCategory),
      price(price),
      lifeQualityScore(lifeQualityScore),
      economyScore(economyScore),
      environmentScore(environmentScore) {}

void AddFacility::act(Simulation &simulation) {
    // Dynamically create the facility
    FacilityType* facility = new FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    simulation.addFacility(*facility);  // Pass the pointer
}

// Action.cpp (or wherever AddFacility is defined)

AddFacility* AddFacility::clone() const {

  return new AddFacility(*this); // Example using copy constructor
}
const string AddFacility::toString() const {
    return "AddFacility: " + facilityName + 
           " [Category: " + std::to_string(static_cast<int>(facilityCategory)) +
           ", Price: " + std::to_string(price) +
           ", Life Quality: " + std::to_string(lifeQualityScore) +
           ", Economy: " + std::to_string(economyScore) +
           ", Environment: " + std::to_string(environmentScore) + "]";
}

PrintPlanStatus::PrintPlanStatus(int planId): planId(planId) {}
void PrintPlanStatus::act(Simulation &simulation){
            cout << "p.toString() "<< endl;

    Plan& p=simulation.getPlan(planId);
        cout << p.toString() << endl;

}
PrintPlanStatus* PrintPlanStatus::clone() const {

  return new PrintPlanStatus(*this); // Example using copy constructor
}
const string PrintPlanStatus::toString() const {
    return "planId: "+planId;
}

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):planId(planId),newPolicy(newPolicy){}
        void ChangePlanPolicy:: act(Simulation &simulation) {
                cout << "this place" << endl;

            Plan p = simulation.getPlan(planId);
        cout << "this place" << endl;

           SelectionPolicy* s1;
        if (newPolicy == "eco") {
        s1 = new EconomySelection();
    }
    else if (newPolicy == "bal") {
        s1 = new BalancedSelection(0, 0, 0);  // Adjust parameters as needed
    }
    else if (newPolicy == "nve") {
        s1 = new NaiveSelection();
    }
    else if (newPolicy == "env") {
        s1 = new SustainabilitySelection();
    }
    else {
        cout << "Error: Unknown selection policy '" << newPolicy << "'." << endl;
        return;
    }
    p.setSelectionPolicy(s1);

        }
ChangePlanPolicy* ChangePlanPolicy::clone() const {

  return new ChangePlanPolicy(*this); // Example using copy constructor
}
const string ChangePlanPolicy::toString() const {
    string str="planId: "+std::to_string(planId)+"\n";
    str+="newPolicy: "+ newPolicy;
    return str;
}

PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog:: act(Simulation &simulation) {
    std::vector<BaseAction*>& list = simulation.getAction(); // Reference to the actionsLog
    for (BaseAction* b : list) { // Iterate using pointers
        if (b) { // Check for null pointer safety
            cout << b->toString() << endl; // Call the virtual function via the pointer
        }
    }
}

PrintActionsLog* PrintActionsLog::clone() const {

  return new PrintActionsLog(*this); // Example using copy constructor
}
const string PrintActionsLog::toString() const {
    string str="";
    return str;
}

Close::Close(){}
void Close:: act(Simulation &simulation) {
     simulation.close(); // Reference to the actionsLog

}

Close* Close::clone() const {

  return new Close(*this); // Example using copy constructor
}
const string Close::toString() const {
    string str="";
    return str;
}


RestoreSimulation::RestoreSimulation(){}
void RestoreSimulation:: act(Simulation &simulation) {

}

RestoreSimulation* RestoreSimulation::clone() const {

  return new RestoreSimulation(*this); // Example using copy constructor
}
const string RestoreSimulation::toString() const {
    string str="";
    return str;
}

BackupSimulation::BackupSimulation(){}
void BackupSimulation:: act(Simulation &simulation) {

}

BackupSimulation* BackupSimulation::clone() const {

  return new BackupSimulation(*this); // Example using copy constructor
}
const string BackupSimulation::toString() const {
    string str="";
    return str;
}