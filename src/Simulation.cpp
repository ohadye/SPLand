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
            if(argumentLine[0] == ADD_SETTLEMENT_CMD_SAVED_WORD){
                Simulation::addSettlement(new Settlement(argumentLine[1], 
                                        Settlement::parseSettlementType(argumentLine[2])));
            }
            else if(argumentLine[0] == ADD_FACILITY_CMD_SAVED_WORD){
                Simulation::addFacility(FacilityType(argumentLine[1], 
                                        FacilityType::parseFacilityCategory(argumentLine[2]), 
                                        stoi(argumentLine[3]), 
                                        stoi(argumentLine[4]), 
                                        stoi(argumentLine[5]), 
                                        stoi(argumentLine[6])));
            }
            else if(argumentLine[0] == ADD_PLAN_CMD_SAVED_WORD){
                Simulation::addPlan(Simulation::getSettlement(argumentLine[1]), Simulation::parseSelectionPolicy(argumentLine[2]));
            }
        }
        configFile.close();
    }

    Simulation::Simulation(Simulation&& other):isRunning(), 
                                                planCounter(0), 
                                                actionsLog(),
                                                plans(),
                                                settlements(),
                                                facilitiesOptions(){
        steal(other);
    }    

    Simulation::Simulation(const Simulation& other): isRunning(), 
                                                    planCounter(0), 
                                                    actionsLog(),
                                                    plans(),
                                                    settlements(),
                                                    facilitiesOptions(){
        copy(other);
    }
    
    Simulation& Simulation::operator=(const Simulation& other){
        if(&other != this){
            clear();
            copy(other);
        }
        return *this;
    }

    Simulation& Simulation::operator=(Simulation&& other){
        if(&other != this){
            clear();
            steal(other);
        }
        return *this;
    }

    void Simulation::copy(const Simulation& other){
        this->isRunning = other.isRunning;
        int sizeOfLog = other.actionsLog.size();
        for(int i = 0; i < sizeOfLog; i++){
            BaseAction* actionClone = other.actionsLog[i]->clone();
            this->actionsLog.push_back(actionClone);
        }
        for(Settlement* settlement : other.settlements){
            Settlement* setClone = settlement->clone();
            this->settlements.push_back(setClone);
        }
        int sizeOfPlans = other.plans.size();                                                                           //copy
        for(int i=0;i<sizeOfPlans;i++){
            Simulation::addPlan(Simulation::getSettlement(other.plans[i].getSettlement().getName()), parseSelectionPolicy(other.plans[i].getSelectionPolicyString()));
        }
        for(const FacilityType& f: other.facilitiesOptions){
            FacilityType copyOfF(f);
            this->facilitiesOptions.push_back(copyOfF);
        }
    }
    void Simulation::steal(Simulation& other){
        isRunning = other.isRunning;
        int sizeOfLog = other.actionsLog.size();
        for(int i = 0; i < sizeOfLog; i++){
            BaseAction* actionPointer = other.actionsLog[i];
            this->actionsLog.push_back(actionPointer);
            other.actionsLog[i] = nullptr;
        }
        int sizeOfSettlements = other.settlements.size();
        for(int i = 0; i < sizeOfSettlements; i++){
            Settlement* setPointer = other.settlements[i];
            this->settlements.push_back(setPointer);                          //steal
            other.settlements[i] = nullptr;
        }
        int sizeOfPlans = other.plans.size();                                                                           //copy
        for(int i=0;i<sizeOfPlans;i++){
            Simulation::addPlan(Simulation::getSettlement(other.plans[i].getSettlement().getName()), parseSelectionPolicy(other.plans[i].getSelectionPolicyString()));
        }
        for(FacilityType& f: other.facilitiesOptions){
            FacilityType copyOfF(f);
            this->facilitiesOptions.push_back(copyOfF);
        }
    }

    void Simulation::clear(){
        planCounter = 0;
        plans.clear();
        facilitiesOptions.clear();
        for(BaseAction* ba: this->actionsLog){
            delete ba;
            ba = nullptr;                                                                  //clear
        }
        for(Settlement* set: this->settlements){
            delete set;
            set = nullptr;
        }
        actionsLog.clear();
        settlements.clear();

    }

    Simulation* Simulation::clone() const{
        return new Simulation(*this);
    }

    SelectionPolicy* Simulation::parseSelectionPolicy(const string& policy){
        if(policy == NAIVE_POLCY_SAVED_WORD)
            return new NaiveSelection();
        else if(policy == BALANCED_POLCY_SAVED_WORD)
            return new BalancedSelection(0,0,0);
        else if(policy == CONOMY_POLCY_SAVED_WORD)
            return new EconomySelection();
        else if(policy == ENVIORMENT_POLCY_SAVED_WORD)
            return new SustainabilitySelection();
        else
            return nullptr;
    }

   void Simulation::start(){
        Simulation::open();
        //start reading commands in loop and creating corresponding actions
        //stop when !isRunning
        string input;
        BaseAction* action;
        std::vector<std::string> argumentLine;
        string user_command;
        cout<<"The simulation has started"<<endl;
        while(isRunning){
           
            getline(std::cin, input); //waits user command
            argumentLine = Auxiliary::parseArguments(input);
            user_command = argumentLine[0];

            if(user_command == STEP_CMD_SAVED_WORD)
                action = new SimulateStep(stoi(argumentLine[1]));
    
            else if(user_command == ADD_PLAN_CMD_SAVED_WORD)
                action = new AddPlan(argumentLine[1],argumentLine[2]);

            else if(user_command == ADD_SETTLEMENT_CMD_SAVED_WORD)
                action = new AddSettlement(argumentLine[1],Settlement::parseSettlementType(argumentLine[2]));
            
            else if(user_command == ADD_FACILITY_CMD_SAVED_WORD){
                action = new AddFacility(argumentLine[1],
                                        FacilityType::parseFacilityCategory(argumentLine[2]),//@todo need to check if there is a facilitycategory provided exsit
                                        stoi(argumentLine[3]),
                                        stoi(argumentLine[4]),
                                        stoi(argumentLine[5]),
                                        stoi(argumentLine[6]));
            }
            else if(user_command == PRINT_PLAN_STATUS_CMD_SAVED_WORD)
                action = new PrintPlanStatus(stoi(argumentLine[1]));
 
            else if(user_command == CHANGE_POLICY_PLAN_CMD_SAVED_WORD)
                action = new ChangePlanPolicy(stoi(argumentLine[1]), argumentLine[2]);
             
            else if(user_command == PRINT_ACTIONS_LOG_PLAN_CMD_SAVED_WORD)
                action = new PrintActionsLog();
           
            else if(user_command == CLOSE_CMD_SAVED_WORD)
                action = new Close();
            
            else if(user_command == BACKUP_SIMULATION_CMD_SAVED_WORD)
                action = new BackupSimulation();
           
            else if(user_command == RESTORE_CMD_SAVED_WORD)
                action = new RestoreSimulation();
            else
                continue;

            //@todo check is there is a need to check if the command given doesn't exsits
            action->act(*this);//preform action act, @note responsible ONLY FOR:checks if the action is valid (using functions from simulation), adding the new element in simulation if able, change the action status. 
            addAction(action);//addes action to the action log list
            if(action->getStatus() == ActionStatus::ERROR)
                cout << action->errorToString() <<endl;
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
        Settlement *setPoint =  nullptr;
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
        Plan& p = plans.back();
        return p;
    }

    void Simulation::printLog(){
        for(BaseAction* a: actionsLog){
            cout<<a->toString()<<endl;
        }
    }
    const string Simulation::toString() const{
        ostringstream s;
        s<<"Simulation: \nfacility options:\n";
        for(FacilityType f : facilitiesOptions){
            s<<f.getName()<<" "<<f.getCost()<<" "<<f.getLifeQualityScore()<<" "<<f.getEconomyScore()<<" "<<f.getEnvironmentScore()<<"\n";
        }
        s<<"settlements:\n";
        for(Settlement* set: settlements){
            s<<set->toString();
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
        clear();
    }
