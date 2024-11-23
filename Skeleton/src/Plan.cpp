#include "Plan.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
    : plan_id(planId),
      settlement(settlement),
      selectionPolicy(selectionPolicy),
      facilityOptions(facilityOptions), // Add a comma here
      status(PlanStatus::AVALIABLE),    // Fix the spelling of AVAILABLE
      life_quality_score(0),
      economy_score(0),
      environment_score(0) {}


const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}

const int Plan::getEconomyScore() const {
    return economy_score;
}

const int Plan::getEnvironmentScore() const {
    return environment_score;
}

const vector<Facility*> &Plan::getFacilities() const {
    return facilities;
}

// Set Selection Policy
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    delete this->selectionPolicy;
    this->selectionPolicy = selectionPolicy;
}
void Plan::addFacility(Facility* facility) {
    //chack status available
    underConstruction.push_back(facility);
}
void Plan::printStatus() {
    string statuse_val = (status == PlanStatus::AVALIABLE) ? "Available" : "Busy";
      cout << "Status: " + statuse_val + "\n" << endl;
}

void Plan::step() {
    for (auto it = underConstruction.begin(); it != underConstruction.end(); ) {
        FacilityStatus st = (*it)->step(); // Dereference the iterator to get the Facility object, then call step()
        if (st == FacilityStatus::OPERATIONAL) {
            this->status = PlanStatus::AVALIABLE; // Assign the status
            it = underConstruction.erase(it);    // Erase and get the next valid iterator
        } else {
            ++it; // Move to the next element
        }
    }
}



const int Plan::getPlanId(){
    return plan_id;
}

const string Plan::toString() const {
    string str = "Plan ID: " + std::to_string(plan_id) + "\n";
    string statuse_val = (status == PlanStatus::AVALIABLE) ? "Available" : "Busy";
    str += "Status: " + statuse_val + "\n";
    str += "Life Quality Score: " + std::to_string(life_quality_score) + "\n";
    str += "Economy Score: " + std::to_string(economy_score) + "\n";
    str += "Environment Score: " + std::to_string(environment_score) + "\n";
    for(Facility* f : facilities){
        str+="facilityName:"+f->getName();
        str+="facilityStatus: OPERATIONAL \n";
    }
    for(Facility* f : underConstruction){
        str+="facilityName:"+f->getName();
        str+="facilityStatus: UNDER_CONSTRUCTIONS \n";
    }
    return str;
}
