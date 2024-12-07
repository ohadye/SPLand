#include "../include/Action.h"
#include <iostream>
#include <sstream>



//BaseAction
    BaseAction::BaseAction():errorMsg("IN PROGRESS"),status(ActionStatus::ERROR){

    }
    ActionStatus BaseAction::getStatus() const{
        return status;
    }
    void BaseAction::complete(){
        status = ActionStatus::COMPLETED;
    }
    void BaseAction::error(string errorMsg){
        status = ActionStatus::ERROR;
        this->errorMsg = errorMsg;
    }
    const string &BaseAction::getErrorMsg() const{
        return errorMsg;
    }

//SimulateStep
/**
 * makes the simulation preform a passage of one unit of time. 
 */
    void SimulateStep::act(Simulation &simulation) {
           for(int i=0;i<numOfSteps;i++) simulation.step();
           complete();
    }

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
        std::ostringstream st;
        st<< "Simulate step: ";
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st<<"error! "<< BaseAction::getErrorMsg();
        }
        else{
            st<<"completed! performed "<< numOfSteps<<" steps.";
        }
        return st.str();
    }
    SimulateStep *SimulateStep::clone() const {
        return new SimulateStep(*this);
    }

//AddPlan

    void AddPlan::act(Simulation &simulation) {
        SelectionPolicy* sp = Simulation::parseSelectionPolicy(selectionPolicy);
        if(sp == nullptr || !simulation.isSettlementExists(settlementName)){
            error("Cannot create this plan");
            return;
        }
        cout<<"selection Policy is "+sp->toString()<<endl;
        simulation.addPlan(simulation.getSettlement(settlementName), sp);
        complete();
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
        if(simulation.isSettlementExists(settlementName)){
            error("Settelment already exists");
            return;
        }
        simulation.addSettlement(new Settlement(settlementName,settlementType)); //why does this return bool?
        complete();
    }

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

//AddFacility
    void AddFacility::act(Simulation &simulation) {
        if(simulation.doesFacilityExist(facilityName)){
            error("Facility already exists");
            return;
        }
        simulation.addFacility(FacilityType(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore));
        cout<<facilityName<<" "<<price<<" "<<lifeQualityScore<<" "<<economyScore<<" "<<environmentScore<<endl;
        complete();
    }

    AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
        facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore)
    {}

    AddFacility::AddFacility(const AddFacility& other): facilityName(other.facilityName), facilityCategory(other.facilityCategory), price(other.price),
        lifeQualityScore(other.lifeQualityScore), economyScore(other.economyScore), environmentScore(other.environmentScore)
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
    void PrintPlanStatus::act(Simulation &simulation) {
        if(!simulation.doesPlanExist(planId)){
            error("Plan doesn’t exist");
            return;
        }
        std::cout<<simulation.getPlan(planId).toString()<<std::endl;
        complete();
    }

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
        std::string st = "Print plan status: ";
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
    void ChangePlanPolicy::act(Simulation &simulation) {
        SelectionPolicy* sp = Simulation::parseSelectionPolicy(newPolicy);
        if(!simulation.doesPlanExist(planId) || sp == nullptr ){
            error("Cannot change selection policy");
            return;
        }
        complete();
    }                                   //implement!

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
    void PrintActionsLog::act(Simulation &simulation) {
        simulation.printLog();
        complete();
    }                                   //implement!

    PrintActionsLog::PrintActionsLog()
    {}
    PrintActionsLog::PrintActionsLog(const PrintActionsLog& other){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string PrintActionsLog::toString() const {
        std::string st;
        if (BaseAction::getStatus() == ActionStatus::ERROR){
            st.append("ERROR"+ BaseAction::getErrorMsg());
        }
        else{
            st.append("COMPLETE");
        }
        return st;
    }
    PrintActionsLog *PrintActionsLog::clone() const {
        return new PrintActionsLog(*this);
    }

//Close
    void Close::act(Simulation &simulation) {
        simulation.close();
        complete();
    }                                   //implement!

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
    void BackupSimulation::act(Simulation &simulation) {
        if(backup!=nullptr){
            delete backup;
            backup = nullptr;
        }
        backup=simulation.clone();
  //      cout<<backup->toString()<<endl;
        complete();
    }

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
    void RestoreSimulation::act(Simulation &simulation) {
        if(backup == nullptr){
            error("No backup available");
            return;
        }
       // cout<<backup->toString()<<endl;
        simulation = *backup;
       // cout<<backup->toString()<<endl;
        complete();
    }                                   //implement!

    RestoreSimulation::RestoreSimulation()
    {}
    RestoreSimulation::RestoreSimulation(const RestoreSimulation& other){
        if(other.getStatus() == ActionStatus::COMPLETED)
            complete();
        else
            error(other.getErrorMsg());
    }
    
    const string RestoreSimulation::toString() const {
        std::string st = "Restore Simulation: ";
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
