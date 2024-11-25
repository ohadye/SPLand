#include "../include/Plan.h"

#include <iostream>
using std::vector;
using std::string;

    Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
        plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE),
        facilities(),underConstruction(),facilityOptions(facilityOptions), life_quality_score(0),economy_score(0),environment_score(0)
    {}
    Plan::Plan(const Plan& other) : plan_id(other.plan_id), settlement(other.settlement), selectionPolicy(other.selectionPolicy->clone()), status(other.status), 
    facilities(),underConstruction(),facilityOptions(other.facilityOptions), life_quality_score(other.life_quality_score),economy_score(other.economy_score),
    environment_score(other.environment_score){
        for(Facility* f : other.facilities){
            this->facilities.push_back(f->clone());
        }
        for(Facility* f : other.underConstruction){
            this->underConstruction.push_back(f->clone());
        }
    }

    Plan* Plan::clone(){
        return new Plan(*this);
    }

    const Settlement& Plan::getSettlement() const {
        return this->settlement;
    } 

    const int Plan::getlifeQualityScore() const{
        return life_quality_score;
    }

    const int Plan::getEconomyScore() const{
        return economy_score;
    }

    const int Plan::getEnvironmentScore() const{
        return environment_score;
    }

    const int Plan::getID() const{
        return plan_id;
    }

    void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
        delete this->selectionPolicy;
        this->selectionPolicy = selectionPolicy;
    }

    void Plan::step(){

    }

    void Plan::printStatus(){
        std::string st;
        if(status == PlanStatus::AVALIABLE)
            st = "AVAILABLE";
        else
            st = "BUSY";
        std::cout<<st<<std::endl;
    }

    const vector<Facility*> &Plan::getFacilities() const{
        return this->facilities;
    }

    void Plan::addFacility(Facility* facility){
        this->facilities.push_back(facility);
    }

    Plan::~Plan(){
        delete this->selectionPolicy;
        for (Facility* f : this->facilities)
            delete f;
        for (Facility* f : this->underConstruction)
            delete f;
    }

    const string Plan::toString() const{
        return "toString of plan" + this->plan_id ;
    }
