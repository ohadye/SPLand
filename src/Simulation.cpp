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
                std::cout<<"add settlement accessed"<<std::endl;
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

    }
    void Simulation::addAction(BaseAction *action){

    }
    bool Simulation::addSettlement(Settlement* settlement){
        return 1; //implement!
    }
    bool Simulation::addFacility(FacilityType facility){
        return 1; //implement!
    }
    bool Simulation::isSettlementExists(const string &settlementName){
        return 1; //implement!
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
