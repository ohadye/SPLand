#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        Plan(const Plan& other);
        Plan(Plan&& other);
        Plan& operator=(const Plan& other)=delete;
        Plan& operator=(Plan && other)=delete;
        Plan* clone();
        const Settlement& getSettlement() const;
        const int getID() const;
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setScores(const int lfs, const int ecs, const int ens);
        const string getSelectionPolicyString() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        /*added methods */
        void updatePlanConstractionFinalized(int facilityIndex);//@quastion, is passing it as a pointer the best here? why it and not by address, also what do you think of this name?
        void updateStatus();
        const vector<Facility*>& getUnderConstruction() const;
        void addUnderConstruction(Facility* facility);
        const string toString() const;
        const string closeToString() const;
        ~Plan();

    private:
        int plan_id;
        const Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};