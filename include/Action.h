#pragma once
#include <string>
#include <vector>
#include "Simulation.h"

class Simulation;

enum class SettlementType;
enum class FacilityCategory;

enum class ActionStatus{
    COMPLETED, ERROR
};

using namespace::std;

class BaseAction{
    public:
        BaseAction();
        ActionStatus getStatus() const;
        virtual void act(Simulation& simulation)=0;
        virtual const string toString() const=0;
        virtual BaseAction* clone() const = 0;
        virtual ~BaseAction() = default;

    protected:
        void complete();
        void error(string errorMsg);
        const string &getErrorMsg() const;

    private:
        string errorMsg;
        ActionStatus status;
};

class SimulateStep : public BaseAction {

    public:
        SimulateStep(const int numOfSteps);
        SimulateStep(const SimulateStep& other);
        void act(Simulation &simulation) override;
        const string toString() const override;
        SimulateStep *clone() const override;
    private:
        const int numOfSteps;
};

class AddPlan : public BaseAction {
    public:
        AddPlan(const string &settlementName, const string &selectionPolicy);
        AddPlan(const AddPlan& other);
        void act(Simulation &simulation) override;
        const string toString() const override;
        AddPlan *clone() const override;
    private:
        const string settlementName;
        const string selectionPolicy;
};


class AddSettlement : public BaseAction {
    public:
        AddSettlement(const string &settlementName,SettlementType settlementType);
        AddSettlement(const AddSettlement& other);
        void act(Simulation &simulation) override;
        AddSettlement *clone() const override;
        const string toString() const override;
    private:
        const string settlementName;
        const SettlementType settlementType;
};



class AddFacility : public BaseAction {
    public:
        AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore);
        AddFacility(const AddFacility& other);
        void act(Simulation &simulation) override;
        AddFacility *clone() const override;
        const string toString() const override;
    private:
        const string facilityName;
        const FacilityCategory facilityCategory;
        const int price;
        const int lifeQualityScore;
        const int economyScore;
        const int environmentScore;

};

class PrintPlanStatus: public BaseAction {
    public:
        PrintPlanStatus(int planId);
        PrintPlanStatus(const PrintPlanStatus& other);
        void act(Simulation &simulation) override;
        PrintPlanStatus *clone() const override;
        const string toString() const override;
    private:
        const int planId;
};


class ChangePlanPolicy : public BaseAction {
    public:
        ChangePlanPolicy(const int planId, const string &newPolicy);
        ChangePlanPolicy(const ChangePlanPolicy& other);
        void act(Simulation &simulation) override;
        ChangePlanPolicy *clone() const override;
        const string toString() const override;
    private:
        const int planId;
        const string newPolicy;
};


class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        PrintActionsLog(const PrintActionsLog& other);
        void act(Simulation &simulation) override;
        PrintActionsLog *clone() const override;
        const string toString() const override;
    private:
};

class Close : public BaseAction {
    public:
        Close();
        Close(const Close& other);
        void act(Simulation &simulation) override;
        Close *clone() const override;
        const string toString() const override;
    private:
};

class BackupSimulation : public BaseAction {
    public:
        BackupSimulation();
        BackupSimulation(const BackupSimulation& other);
        void act(Simulation &simulation) override;
        BackupSimulation *clone() const override;
        const string toString() const override;
    private:
};


class RestoreSimulation : public BaseAction {
    public:
        RestoreSimulation();
        RestoreSimulation(const RestoreSimulation& other);
        void act(Simulation &simulation) override;
        RestoreSimulation *clone() const override;
        const string toString() const override;
    private:
};