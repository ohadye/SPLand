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
        else if(policy == "env")
            return new SustainabilitySelection();
        else
            return nullptr;
    }

    void Simulation::start(){
        Simulation::open();
        //start reading commands in loop and creating corresponding actions
        //stop when !isRunning
        while(isRunning){
            string input;
            BaseAction* action;
            std::vector<std::string> argumentLine;
            std::cout<<">";
            getline(std::cin, input); //waits user command
            argumentLine = Auxiliary::parseArguments(input);
            if(argumentLine[0] == "step"){
                action = new SimulateStep(stoi(argumentLine[1]));
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "plan"){
                action = new AddPlan(argumentLine[1],argumentLine[2]);
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "settlement"){
                action = new AddSettlement(argumentLine[1],Settlement::parseSettlementType(argumentLine[2]));
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "facility"){
                action = new AddFacility(argumentLine[1],
                                        FacilityType::parseFacilityCategory(argumentLine[2]),
                                        stoi(argumentLine[3]),
                                        stoi(argumentLine[4]),
                                        stoi(argumentLine[5]),
                                        stoi(argumentLine[6]));
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "planStatus"){
                action = new PrintPlanStatus(stoi(argumentLine[1]));
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "changePolicy"){
                action = new ChangePlanPolicy(stoi(argumentLine[1]), argumentLine[2]);
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "log"){
                action = new PrintActionsLog();
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "close"){
                action = new Close();
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "backup"){
                action = new BackupSimulation();
                action->act(*this);
                actionsLog.push_back(action);
            }
            else if(argumentLine[0] == "restore"){
                action = new RestoreSimulation();
                action->act(*this);
                actionsLog.push_back(action);
            }
        }
    }
    void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
//        std::cout<<"add Plan accessed!" <<std::endl;
        plans.push_back(Plan(planCounter++, settlement, selectionPolicy, this->facilitiesOptions));
    }
    void Simulation::addAction(BaseAction *action){
        actionsLog.push_back(action);
    }
    bool Simulation::addSettlement(Settlement* settlement){ 
//        std::cout<<"add Settlement accessed!" <<std::endl;
        if(isSettlementExists(settlement->getName()))           // is this my job to check or action AddSettlement? YES!
            return false;    
        settlements.push_back(settlement);
        return true;
    }
    bool Simulation::addFacility(FacilityType facility){
//        std::cout<<"add Facility accessed!" <<std::endl;
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

    bool Simulation::doesPlanExist(const int planID){
        for(const Plan& p : plans){
            if(p.getID()==planID)
                return true;
        }
        return false;
    }

    Plan &Simulation::getPlan(const int planID){
        for(Plan& p : plans){
            if(p.getID() == planID)
                return p;
        }
        Plan& p = plans.back();             //dont know if theres a better practice
        return p;
    }

    void Simulation::printLog(){
        for(BaseAction* a: actionsLog){
            cout<<a->toString()<<endl;
        }
//        cout<<toString()<<endl;
    }
    const string Simulation::toString() const{
        ostringstream s;
        s<<"Simulation: \nfacility options:\n";
        for(FacilityType f : facilitiesOptions){
            s<<f.getName()<<" "<<f.getCost()<<" "<<f.getLifeQualityScore()<<" "<<f.getEconomyScore()<<" "<<f.getEnvironmentScore()<<"\n";
        }
        s<<"settlements:\n";
        for(Settlement* set: settlements){
            s<<set->getName();
        }
        s<<"and plans:\n";
        for(const Plan &p: plans){
            s<<p.toString() << "\n";
        }
        return s.str();
    }
    void Simulation::step(){
        for (Plan& p :this->plans){
            p.step();
        }

    }
    void Simulation::close(){
        isRunning = false;
    }
    void Simulation::open(){
        isRunning = true;
    }
    Simulation::~Simulation(){
        for(BaseAction* a : actionsLog)
            delete a;
        for(Settlement* s : settlements)
            delete s;
    }
