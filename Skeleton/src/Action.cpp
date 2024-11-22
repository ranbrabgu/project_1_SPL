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
