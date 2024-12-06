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
        
        //stage one of the SimulateStep() scheme 
        while(this->status == PlanStatus::AVALIABLE)
        {
            FacilityType selectedType = selectionPolicy->selectFacility(facilityOptions);
            Facility *constracted = new Facility(selectedType, this->getSettlement().getName());
            delete(&selectedType);//@Qustion: do I need to delete it here? or does it gets deleted outside of the ACframe?
            updateStatus();//@note if there is time, create an function that attempt to create a constraction and updates the status as well (attemptConstraction())
        }
        int  sizeOfConstractionList = underConstruction.size();
        for(int facilityIndex = 0; facilityIndex <= sizeOfConstractionList; facilityIndex++)
        { 
            if(underConstruction[facilityIndex]->step() == FacilityStatus::OPERATIONAL)//if the facillity finsihed it's constractin
            {
                finalizeConstraction(facilityIndex);//moves the facility to the correct Vector 
            }
        }
        
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
    void Plan::finalizeConstraction(int facilityIndex){
    
        this->facilities.push_back(underConstruction[facilityIndex]);
        this->underConstruction.erase(underConstruction.begin() + facilityIndex);//@quastion: does this removes the pointer of the facility from underconstraction and addes the facility by address to the facilities vector as needed? 
        this->updateStatus();
    }
    //**updates the status of the plan, checks if there is a slot in the constraction list for another facility and updates the plan's status to indicate acordinglly */
    void Plan::updateStatus(){
        int size = underConstruction.size();
        if(size < (this->getSettlement()).getTypeCapacity())
            this->status = PlanStatus::AVALIABLE;
        else
          this->status = PlanStatus::BUSY;  
    }
