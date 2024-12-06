#include "Action.h"



//BaseAction
    BaseAction::BaseAction():errorMsg("IN PROGRESS"),status(ActionStatus::ERROR){

    }
    ActionStatus BaseAction::getStatus() const{
        return status;
    }
    void BaseAction::complete(){
        status = ActionStatus::COMPLETED;
    }
    /**
     * @brief 
     * @note for now I put the printing of the error messge inside this function aswell
     * @param errorMsg 
     */
    void BaseAction::error(string errorMsg){
        status = ActionStatus::ERROR;
        this->errorMsg = errorMsg;
        std::cout << ERROR_MSG_PREFIX << errorMsg << endl;/**@warning might not be good pracice to print here */
    }
    const string &BaseAction::getErrorMsg() const{
        return errorMsg;
    }


//SimulateStep
/**
 * makes the simulation preform a passage of one unit of time. 
 */
    void SimulateStep::act(Simulation &simulation) {
            simulation.step();
    }                                   //implemented

    SimulateStep::SimulateStep(const int numOfSteps): numOfSteps(numOfSteps)
    {}
    SimulateStep::SimulateStep(const SimulateStep& other): 
        numOfSteps(other.numOfSteps){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string SimulateStep::toString() const {
        std::string st = "Simulate step: ";
        std::string num = ""+ numOfSteps;                                       //theres a better way to do this
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed! performed "+num+" steps.");
        }
        return st;
    }
    SimulateStep *SimulateStep::clone() const {
        return new SimulateStep(*this);
    }

//AddPlan

    void AddPlan::act(Simulation &simulation) {
    }                                

    AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy): settlementName(settlementName), selectionPolicy(selectionPolicy) 
    {}

    AddPlan::AddPlan(const AddPlan& other): settlementName(other.settlementName), selectionPolicy(other.selectionPolicy){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string AddPlan::toString() const {
        std::string st = "Add Plan: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed! Added plan with "+selectionPolicy+" to settlement "+settlementName);
        }
        return st;
    }
    AddPlan *AddPlan::clone() const {
        return new AddPlan(*this);
    }

//AddSettlement

    void AddSettlement::act(Simulation &simulation) {
        if(&simulation.getSettlement(this->settlementName)!= nullptr)//checks if there is an instance of a settlemnt with the given name
        {
            error(ATTEMTING_TO_CREATE_EXSISTING_SETTLEMENT_ERROR_MSG);
        }
        else
        {
            simulation.addSettlement(new Settlement(this->settlementName, this->settlementType));
            complete();
        }
    }                        
/**
 * @brief creates an instance of AddSettlemnt Action 
 * @if the settelment name is already take print an error
 * 
 * @param simulation simulation
 */
    AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType): settlementName(settlementName), settlementType(settlementType) 
    {}

    AddSettlement::AddSettlement(const AddSettlement& other): settlementName(other.settlementName), settlementType(other.settlementType){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string AddSettlement::toString() const {
        std::string st = "Add Settlement: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed! Added settlement "+settlementName+" of type "+Settlement::getTypeString(settlementType));
        }
        return st;
    }
    AddSettlement *AddSettlement::clone() const {
        return new AddSettlement(*this);
    }

    /**
     * @brief – This action creates and stores a new facility(actually FacilityType). The provided
        category integer value will be used to set the corresponding category enum value.
     * 
     * @param simulation 
     */
    void AddFacility::act(Simulation &simulation) {
        
        if(simulation.doesFacilityExist(this->facilityName))//if the facility type exist in simulation
        {
            error(ATTEMTING_TO_CREATE_EXSISTING_FACILITY_ERROR_MSG);
        }
        else
        {//@Note 
            simulation.addFacility(*new FacilityType(this->facilityName, this->facilityCategory,this->price, this->lifeQualityScore, this->economyScore, this->environmentScore));
        }
    }

    AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
        facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(economyScore)
    {}

    AddFacility::AddFacility(const AddFacility& other): facilityName(other.facilityName), facilityCategory(other.facilityCategory), price(other.price),
        lifeQualityScore(other.lifeQualityScore), economyScore(other.economyScore), environmentScore(other.economyScore)
    {
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    const string AddFacility::toString() const {
        std::string st = "Add Facility: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed! Added Facility "+facilityName+" of category "+FacilityType::getCategoryString(facilityCategory)); //might need to add rest of info
        }
        return st;
    }
    AddFacility *AddFacility::clone() const {
        return new AddFacility(*this);
    }

//PrintPlanStatus
    void PrintPlanStatus::act(Simulation &simulation) {}                                   //implement!

    PrintPlanStatus::PrintPlanStatus(const int planId): planId(planId)
    {}
    PrintPlanStatus::PrintPlanStatus(const PrintPlanStatus& other): 
        planId(other.planId){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string PrintPlanStatus::toString() const {
        std::string st = "Prrint plan status: ";
        std::string num = ""+ planId;                                       //theres a better way to do this
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed! Printed status of plan "+num);
        }
        return st;
    }
    PrintPlanStatus *PrintPlanStatus::clone() const {
        return new PrintPlanStatus(*this);
    }

//ChangePlanPolicy
    void ChangePlanPolicy::act(Simulation &simulation) {}                                   //implement!

    ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy): planId(planId), newPolicy(newPolicy)
    {}
    ChangePlanPolicy::ChangePlanPolicy(const ChangePlanPolicy& other): 
        planId(other.planId), newPolicy(other.newPolicy){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string ChangePlanPolicy::toString() const {
        std::string st = "Change plan policy: ";
        std::string num = ""+ planId;                                       //theres a better way to do this
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed! Changed plan "+num+" to "+newPolicy+" policy.");
        }
        return st;
    }
    ChangePlanPolicy *ChangePlanPolicy::clone() const {
        return new ChangePlanPolicy(*this);
    }

//PrintActionsLog
    void PrintActionsLog::act(Simulation &simulation) {}                                   //implement!

    PrintActionsLog::PrintActionsLog()
    {}
    PrintActionsLog::PrintActionsLog(const PrintActionsLog& other){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string PrintActionsLog::toString() const {
        std::string st = "Print Actions Log: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed!");
        }
        return st;
    }
    PrintActionsLog *PrintActionsLog::clone() const {
        return new PrintActionsLog(*this);
    }

//Close
    void Close::act(Simulation &simulation) {}                                   //implement!

    Close::Close()
    {}
    Close::Close(const Close& other){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string Close::toString() const {
        std::string st = "Close: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed!");
        }
        return st;
    }
    Close *Close::clone() const {
        return new Close(*this);
    }

//BackupSimulation
    void BackupSimulation::act(Simulation &simulation) {}                                   //implement!

    BackupSimulation::BackupSimulation()
    {}
    BackupSimulation::BackupSimulation(const BackupSimulation& other){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string BackupSimulation::toString() const {
        std::string st = "Backup Simulation: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed!");
        }
        return st;
    }
    BackupSimulation *BackupSimulation::clone() const {
        return new BackupSimulation(*this);
    }

//RestoreSimulation
    void RestoreSimulation::act(Simulation &simulation) {}                                   //implement!

    RestoreSimulation::RestoreSimulation()
    {}
    RestoreSimulation::RestoreSimulation(const RestoreSimulation& other){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string RestoreSimulation::toString() const {
        std::string st = "Backup Simulation: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("error! "+ BaseAction::getErrorMsg());
        }
        else{
            st.append("completed!");
        }
        return st;
    }
    RestoreSimulation *RestoreSimulation::clone() const {
        return new RestoreSimulation(*this);
    }
