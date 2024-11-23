#include "../include/Plan.h"

using std::vector;
using std::string;

    Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
        plan_id(planId), facilityOptions(facilityOptions), settlement()
    {
        this->selectionPolicy = selectionPolicy;
    }
    const int Plan::getlifeQualityScore() const{

    }

    const int Plan::getEconomyScore() const{

    }

    const int Plan::getEnvironmentScore() const{

    }

    void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){

    }

    void Plan::step(){

    }

    void Plan::printStatus(){

    }

    const Plan::vector<Facility*> &getFacilities() const{

    }

    void Plan::addFacility(Facility* facility){

    }

    Plan::~(){
        
    }

    const Plan::string toString() const{

    }
