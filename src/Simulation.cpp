#include "../include/Simulation.h"
#include "../include/Auxiliary.h"
#include <iostream>
#include <fstream>

    Simulation::Simulation(const string &configFilePath) : isRunning(false), 
                                                            planCounter(0), 
                                                            actionsLog(), 
                                                            plans(), 
                                                            settlements(), 
                                                            facilitiesOptions(){
        std::ifstream configFile;
        configFile.open(configFilePath,std::ios::in);
        if(!configFile)
            std::cout<<"file does not exist!";
        std::string line;
        std::vector<std::string> argumentLine;
        while(getline(configFile,line)){
            argumentLine = Auxiliary::parseArguments(line);
            if(argumentLine[0] == "settlement"){
                Simulation::addSettlement(new Settlement(argumentLine[1], 
                                        Settlement::parseSettlementType(argumentLine[2])));
            }
            else if(argumentLine[0] == "facility"){
                Simulation::addFacility(FacilityType(argumentLine[1], 
                                        FacilityType::parseFacilityCategory(argumentLine[2]), 
                                        stoi(argumentLine[3]), 
                                        stoi(argumentLine[4]), 
                                        stoi(argumentLine[5]), 
                                        stoi(argumentLine[6])));
            }
            else if(argumentLine[0] == "plan"){
                Simulation::addPlan(Simulation::getSettlement(argumentLine[1]), Simulation::parseSelectionPolicy(argumentLine[2]));
            }
        }
        configFile.close();
        std::cout<<this->toString()<<std::endl;
    }

    SelectionPolicy* Simulation::parseSelectionPolicy(const string& policy){
        if(policy == "nve")
            return new NaiveSelection();
        else if(policy == "bal")
            return new BalancedSelection(0,0,0);
        else if(policy == "eco")
            return new EconomySelection();
        else
            return new SustainabilitySelection();
    }

    void Simulation::start(){
        
    }
    void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
        std::cout<<"add Plan accessed!" <<std::endl;
        plans.push_back(Plan(planCounter++, settlement, selectionPolicy, this->facilitiesOptions));
    }
    void Simulation::addAction(BaseAction *action){
        actionsLog.push_back(action);
    }
    bool Simulation::addSettlement(Settlement* settlement){ 
        std::cout<<"add Settlement accessed!" <<std::endl;
        if(isSettlementExists(settlement->getName()))           // is this my job to check or action AddSettlement?
            return false;    
        settlements.push_back(settlement);
        return true;
    }
    bool Simulation::addFacility(FacilityType facility){
        std::cout<<"add Facility accessed!" <<std::endl;
        if(Simulation::doesFacilityExist(facility.getName()))   // is this my job to check or action AddFacility?
            return false;
        facilitiesOptions.push_back(facility);
        return true;
    }

    bool Simulation::doesFacilityExist(const string &facilityName){
        for(FacilityType &f : this->facilitiesOptions){
            if(f.FacilityType::getName() == facilityName)
                return true;
        }
        return false;
    }

    bool Simulation::isSettlementExists(const string &settlementName){
        for(Settlement* set : this->settlements){
            if(set->Settlement::getName() == settlementName)
                return true;
        }
        return false;
    }
    Settlement &Simulation::getSettlement(const string &settlementName){
        Settlement *setPoint =  nullptr;//@todo check if this is good practice
        for(Settlement* set : this->settlements){
            if(set->Settlement::getName() == settlementName)
                setPoint = set;
        }
        return *setPoint;
    }
    Plan &Simulation::getPlan(const int planID){
        Plan *planPoint = & this->plans.back();
        for(Plan p : this->plans){
            if(p.Plan::getID() == planID)
                planPoint = &p;
        }
        return *planPoint;
    }

    const string Simulation::toString() const{
        string st = "Simulation: \nfacility options:\n" ;
        for(FacilityType f : facilitiesOptions){
            st.append(f.getName() + "\n");
        }
        st.append("settlements:\n");
        for(Settlement* s: settlements){
            st.append(s->getName());
        }
        st.append("and plans:\n");
        for(Plan p: plans){
            st.append(std::to_string(p.getID())+" in settlement "+p.getSettlement().getName()+"\n");
        }
        return st;
    }

    void Simulation::step(){

    }
    void Simulation::close(){

    }
    void Simulation::open(){}
