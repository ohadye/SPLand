#include "../include/Plan.h"

#include <iostream>
#include <sstream>
#include <algorithm>
using std::vector;
using std::string;

    Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
        plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE),
        facilities(),underConstruction(),facilityOptions(facilityOptions), life_quality_score(0),economy_score(0),environment_score(0)
    {}
    Plan::Plan(const Plan& other) : plan_id(other.plan_id), 
                                    settlement(other.settlement), 
                                    selectionPolicy(other.selectionPolicy->clone()), 
                                    status(other.status), 
                                    facilities(),
                                    underConstruction(),
                                    facilityOptions(other.facilityOptions), 
                                    life_quality_score(other.life_quality_score),
                                    economy_score(other.economy_score),
                                    environment_score(other.environment_score){
        for(Facility* f : other.facilities){
            Facility* facClone = f->clone();
            this->facilities.push_back(facClone);
        }
        for(Facility* f : other.underConstruction){
            Facility* facClone = f->clone();
            this->underConstruction.push_back(facClone);
        }
    }

    Plan::Plan(Plan&& other): plan_id(other.plan_id), 
                                settlement(other.settlement),
                                selectionPolicy(other.selectionPolicy),
                                status(other.status),
                                facilities(),
                                underConstruction(),
                                facilityOptions(other.facilityOptions),
                                life_quality_score(other.life_quality_score),
                                economy_score(other.economy_score),
                                environment_score(other.environment_score){
        other.selectionPolicy = nullptr;
        for(Facility* f : other.facilities){
            Facility* facPointer = f;
            this->facilities.push_back(facPointer);
            f = nullptr;
        }
        for(Facility* f : other.underConstruction){
            Facility* facPointer = f;
            this->underConstruction.push_back(facPointer);
            f = nullptr;
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

    void Plan::setScores(const int lqs, const int ecs, const int ens){
        life_quality_score = lqs;
        economy_score = ecs;
        environment_score = ens;
    }

    const int Plan::getID() const{
        return plan_id;
    }

    const string Plan::getSelectionPolicyString() const{
        return selectionPolicy->toString();
    }

    void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
        delete this->selectionPolicy;
        this->selectionPolicy = selectionPolicy;
    }

    void Plan::step(){
        int  sizeOfConstractionList = underConstruction.size();
        for(int facilityIndex = 0; facilityIndex < sizeOfConstractionList; facilityIndex++)
        { 
            if(underConstruction[facilityIndex]->step() == FacilityStatus::OPERATIONAL){//if the facillity finsihed it's constractin
                facilities.push_back(underConstruction[facilityIndex]);
                life_quality_score+=underConstruction[facilityIndex]->getLifeQualityScore();
                economy_score+=underConstruction[facilityIndex]->getEconomyScore();
                environment_score+=underConstruction[facilityIndex]->getEnvironmentScore();
   //             if(this->getSelectionPolicyString() == SELE)
 //               updatePlanConstractionFinalized(facilityIndex);//moves the facility to the correct Vector 
            }
        }
        underConstruction.erase(std::remove_if(underConstruction.begin(),underConstruction.end(),[](Facility* f)-> bool{
           return f->Facility::getStatus()==FacilityStatus::OPERATIONAL;
        }),underConstruction.end());
        updateStatus();
        while(this->status == PlanStatus::AVALIABLE){
            Facility *f = new Facility(selectionPolicy->selectFacility(facilityOptions), this->settlement.getName());
            underConstruction.push_back(f);
            updateStatus();
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

    const vector<Facility*>& Plan::getUnderConstruction() const {
        return this->underConstruction;
    }

    void Plan::addFacility(Facility* facility){
        this->facilities.push_back(facility);
    }

    void Plan::addUnderConstruction(Facility* facility){
        this->underConstruction.push_back(facility);
    }

    Plan::~Plan(){
        delete this->selectionPolicy;
        for (Facility* f : this->facilities)
            delete f;
        for (Facility* f : this->underConstruction)
            delete f;
    }
    const string Plan::closeToString() const{

        std::ostringstream st;
        st << "PlanID: " <<plan_id << " ,Settlement Name: "<<settlement.getName()<< "\nLifeQualityScore: " << getlifeQualityScore() <<"\nEconomyScore: "<< getEconomyScore() <<"\nEnvironmentScore: " <<getEnvironmentScore();
        return st.str();
    }


    const string Plan::toString() const{
        std::ostringstream st;
        st << "PlanID: " <<plan_id << "\nSettlement Name: "<<settlement.getName()<<"\nplanStatus: ";
        if(status == PlanStatus::AVALIABLE)
            st << "AVAILABLE";
        else    
            st<<"BUSY";
        st<<"\nselectionPolicy: " << selectionPolicy->toString();
        st<<"\nLifeQualityScore: "<< life_quality_score <<"\nEconomyScore: "<< economy_score <<"\nEnvironmentScore: "<<environment_score;
        for(Facility* f: facilities){
            st<<"\n"<<f->toString();
        }
        for(Facility* f: underConstruction){
            st<<"\n"<<f->toString();
        }
        return  st.str();
    }   
    void Plan::updatePlanConstractionFinalized(int facilityIndex){
    
        this->facilities.push_back(underConstruction[facilityIndex]);
        this->underConstruction.erase(underConstruction.begin() + facilityIndex);//@quastion: does this removes the pointer of the facility from underconstraction and addes the facility by address to the facilities vector as needed? 
//       std::cout<<toString()<<std::endl;
    }
    //**updates the status of the plan, checks if there is a slot in the constraction list for another facility and updates the plan's status to indicate acordinglly */
    void Plan::updateStatus(){
        int size = underConstruction.size();
        if(size < (this->getSettlement()).getTypeCapacity())
            this->status = PlanStatus::AVALIABLE;
        else
          this->status = PlanStatus::BUSY;  
    }
