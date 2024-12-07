#pragma once
#include <string>
#include <vector>
#include "Action.h"
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

/*Macro definitions of command saved word*/
#define STEP_CMD_SAVED_WORD "step"
#define ADD_PLAN_CMD_SAVED_WORD "plan"
#define ADD_SETTLEMENT_CMD_SAVED_WORD "settlement"
#define ADD_FACILITY_CMD_SAVED_WORD "facility"
#define PRINT_PLAN_STATUS_CMD_SAVED_WORD "planStatus"
#define CHANGE_POLICY_PLAN_CMD_SAVED_WORD "changePolicy"
#define PRINT_ACTIONS_LOG_PLAN_CMD_SAVED_WORD "log"
#define CLOSE_CMD_SAVED_WORD "close"
#define BACKUP_SIMULATION_CMD_SAVED_WORD "backup"
#define RESTORE_CMD_SAVED_WORD "restore"

/*Macro definitions of Selection policy saved word*/
#define NAIVE_POLCY_SAVED_WORD "nve"
#define BALANCED_POLCY_SAVED_WORD "bal"
#define CONOMY_POLCY_SAVED_WORD "eco"
#define ENVIORMENT_POLCY_SAVED_WORD "env"

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
        Simulation(const Simulation &other);
        Simulation operator=(const Simulation& other);
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        bool doesFacilityExist(const string& facilityName);
        bool doesPlanExist(const int planId);
        Settlement &getSettlement(const string &settlementName);
        static SelectionPolicy* parseSelectionPolicy(const string& policy);
        Plan &getPlan(const int planID);
        void printLog();
        const string toString() const;
        void step();
        void close();
        void open();
        ~Simulation();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;

};