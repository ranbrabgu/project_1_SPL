#include "SelectionPolicy.h"
#include <vector>
#include <iostream>
#include "Facility.cpp"  // Include the header file



NaiveSelection::NaiveSelection() : lastSelectedIndex(0) {}
const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if(facilitiesOptions.empty()){
        ///// sent error
    }
    lastSelectedIndex = (lastSelectedIndex + 1);
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const {
    return "Naive Selection Policy";
}
NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}







BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if (facilitiesOptions.empty()) {
        /// sent error
    }

    const FacilityType* bestFacility = nullptr;
    
    FacilityType facil = facilitiesOptions[0];

    int lifeScore = LifeQualityScore + facil.getLifeQualityScore();
    int economyScore = EconomyScore + facil.getEconomyScore();
    int environmentScore = EnvironmentScore + facil.getEnvironmentScore();
    
    int maxScore = std::max({lifeScore, economyScore, environmentScore});
    int minScore = std::min({lifeScore, economyScore, environmentScore});
    
    int scoreDifference = maxScore - minScore; 
    int smallestScoreDifference = scoreDifference;


    for (const auto& facility : facilitiesOptions) {
        lifeScore = LifeQualityScore + facility.getLifeQualityScore();
        economyScore = EconomyScore + facility.getEconomyScore();
        environmentScore = EnvironmentScore + facility.getEnvironmentScore();
        maxScore = std::max({lifeScore, economyScore, environmentScore});
        minScore = std::min({lifeScore, economyScore, environmentScore});
        scoreDifference = maxScore - minScore; 
        if (scoreDifference < smallestScoreDifference) {
            smallestScoreDifference = scoreDifference;
            bestFacility = &facility;
        }
    }

    if (!bestFacility) {
        /// sent error
    }
    return *bestFacility;
}

const string BalancedSelection::toString() const {
    return "Balanced Selection Policy";
}
// Clones the BalancedSelection object
BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}



EconomySelection::EconomySelection() : lastSelectedIndex(0) {}

const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if (facilitiesOptions.empty()) {
        // Send error if the vector is empty (you can replace this with error handling code)
        throw std::invalid_argument("Facilities options cannot be empty.");
    }

    int bestScore = facilitiesOptions[0].getEconomyScore();
    int lastSelectedIndex = 0;  // Initialize index of the best facility

    for (int i = 1; i < facilitiesOptions.size(); i++) {  // Start from index 1, as 0 is already considered
        if (facilitiesOptions[i].getEconomyScore() > bestScore) {
            bestScore = facilitiesOptions[i].getEconomyScore();
            lastSelectedIndex = i;
        }
    }
    
    

    // Return the reference to the best facility
    return facilitiesOptions[lastSelectedIndex];
    }
        

        const string EconomySelection::toString() const {
            return "Economy Selection Policy";
        }
        EconomySelection* EconomySelection::clone() const {
            return new EconomySelection(*this);
        }





SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(0) {}
const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if (facilitiesOptions.empty()) {
        //// sent error
    }
    int bestScore = facilitiesOptions[0].getEnvironmentScore();
    FacilityType* bestFacility = nullptr;
        for(int i=0;i<facilitiesOptions.size();i++){
            if (facilitiesOptions[i].getEnvironmentScore() > bestScore) {
                bestScore = facilitiesOptions[i].getEconomyScore();
                lastSelectedIndex = i;
            }
        }
    if (!bestFacility) {
        //// sent error
        throw std::runtime_error("No facility found");
    }
    return facilitiesOptions[lastSelectedIndex];

}
const string SustainabilitySelection::toString() const {
    return "Sustainability Selection Policy";
}

// Clones the SustainabilitySelection object
SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}