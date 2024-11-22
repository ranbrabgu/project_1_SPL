#include "Settlement.h"  // Include the header file

// Constructor for the Settlement class
Settlement::Settlement(const string &name, SettlementType type)
    : name(name), type(type) {}

// Getter for the name of the settlement
const string &Settlement::getName() const {
    return name;
}

// Getter for the type of the settlement
SettlementType Settlement::getType() const {
    return type;
}

// toString function to represent the settlement as a string
const string Settlement::toString() const {
    string typeStr;
    switch (type) {
        case SettlementType::VILLAGE:
            typeStr = "Village";
            break;
        case SettlementType::CITY:
            typeStr = "City";
            break;
        case SettlementType::METROPOLIS:
            typeStr = "Metropolis";
            break;
    }
    return name + " (" + typeStr + ")";
}
