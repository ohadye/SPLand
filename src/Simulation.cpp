#include "../include/Simulation.h"
#include "../include/Auxiliary.h"
#include <iostream>
#include <fstream>

    Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions(){
        std::ifstream configFile;
        configFile.open(configFilePath,std::ios::in);
        if(!configFile)
            std::cout<<"file does not exist!";
        std::string line;
        std::vector<std::string> argumentLine;
        while(getline(configFile,line)){
            argumentLine = Auxiliary::parseArguments(line);
            if(argumentLine[0] == "settlement"){
                Simulation::addSettlement(new Settlement(argumentLine[1], Settlement::parseSettlementType(argumentLine[2])));
            }
            else if(argumentLine[0] == "facility"){
                std::cout<<"add facility accessed"<<std::endl;
            }
            else if(argumentLine[0] == "plan"){
                std::cout<<"add plan accessed"<<std::endl;
            }
        }
        configFile.close();
    }
    void Simulation::start(){

    }
    void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
        plans.push_back(Plan(planCounter++, settlement, selectionPolicy, this->facilitiesOptions));
    }
    void Simulation::addAction(BaseAction *action){
        actionsLog.push_back(action);
    }
    bool Simulation::addSettlement(Settlement* settlement){ 
        if(isSettlementExists(settlement->getName()))           // is this my job to check or action AddSettlement?
            return false;    
        settlements.push_back(settlement);
        return true;
    }
    bool Simulation::addFacility(FacilityType facility){
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
    void Simulation::step(){

    }
    void Simulation::close(){

    }
    void Simulation::open(){}
