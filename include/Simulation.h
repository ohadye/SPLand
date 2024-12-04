#pragma once
#include <string>
#include <vector>
#include "Action.h"
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
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