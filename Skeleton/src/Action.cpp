#include "Action.h"
#include "Simulation.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

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

//AddSettlement *AddSettlement:: *clone() {return new AddSettlement(*this)}
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

AddFacility *clone() {

}
const string AddFacility::toString() const {
    return "AddFacility: " + facilityName + 
           " [Category: " + std::to_string(static_cast<int>(facilityCategory)) +
           ", Price: " + std::to_string(price) +
           ", Life Quality: " + std::to_string(lifeQualityScore) +
           ", Economy: " + std::to_string(economyScore) +
           ", Environment: " + std::to_string(environmentScore) + "]";
}
