#include "../include/Simulation.h"
#include "../include/Auxiliary.h"
#include <iostream>
#include <fstream>

    Simulation::Simulation(const string &configFilePath){
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
    bool Simulation::addSettlement(Settlement settlement){
        
    }
    bool Simulation::addFacility(FacilityType facility){

    }
    bool Simulation::isSettlementExists(const string &settlementName){

    }
    Settlement &Simulation::getSettlement(const string &settlementName){

    }
    Plan &Simulation::getPlan(const int planID){

    }
    void Simulation::step(){

    }
    void Simulation::close(){

    }
    void Simulation::open(){}
