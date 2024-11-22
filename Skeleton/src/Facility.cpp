#include "Facility.h"  // Include the header file




FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
    : name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score) {}

const string &FacilityType::getName() const {
    return name;
}
int FacilityType::getCost() const{
    return price;
}

int FacilityType::getLifeQualityScore() const {
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const {
    return environment_score;
}

// Getter for economy score of the facility type
int FacilityType::getEconomyScore() const {
    return economy_score;
}
FacilityCategory FacilityType::getCategory() const {
    return category;
}






Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score): 
    FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(10) {}

Facility::Facility(FacilityType &type, const string &settlementName)
    : FacilityType(type), settlementName(settlementName), 
      status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(10) {}
        
const string &Facility::getSettlementName() const {
    return settlementName;
}
const int Facility::getTimeLeft() const {
    return timeLeft;
}



FacilityStatus step();



void Facility::setStatus(FacilityStatus newStatus) {
    status = newStatus;
}
const FacilityStatus& Facility::getStatus() const {
    return status;
}
const string Facility::toString() const {
    string statusStr = (status == FacilityStatus::UNDER_CONSTRUCTIONS) ? "Under Construction" : "Operational";
    return name + " in " + settlementName + " [" + statusStr + ", Time Left: " + std::to_string(timeLeft) + "]";
}

