#include "../include/Facility.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
//  FacilityType
    FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
        name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score)
    {}

    FacilityType::FacilityType(const FacilityType& other):
        name(other.name), category(other.category), price(other.price), lifeQuality_score(other.lifeQuality_score), economy_score(other.economy_score), environment_score(other.environment_score)
    {

    }

    const string &FacilityType::getName() const{
        return this->name;
    }
    int FacilityType::getCost() const{
        return price;
    }
    int FacilityType::getLifeQualityScore() const{
        return lifeQuality_score;
    }
    int FacilityType::getEnvironmentScore() const{
        return environment_score;
    }
    int FacilityType::getEconomyScore() const{
        return economy_score;
    }
    FacilityCategory FacilityType::getCategory() const{
        return category;
    }

//  Facility
    Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
        FacilityType::FacilityType(name,category,price,lifeQuality_score,environment_score,economy_score), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price)
    {}

    Facility::Facility(const FacilityType &type, const string &settlementName):
        FacilityType::FacilityType(type.getName(),type.getCategory(),type.getCost(),type.getLifeQualityScore(),type.getEconomyScore(),type.getEconomyScore()), 
        settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(type.getCost())
    {}

    Facility::Facility(const Facility& other): 
        FacilityType::FacilityType(other.name, other.category, other.price, other.lifeQuality_score, other.environment_score, other.economy_score),
        settlementName(other.settlementName), status(other.status), timeLeft(other.timeLeft)
    {
        
    }

    const string &Facility::getSettlementName() const {
        return settlementName;
    }

    const int Facility::getTimeLeft() const{
        return timeLeft;
    }

    Facility* Facility::clone(){
        return new Facility(*this);
    }

    FacilityStatus Facility::step(){ return FacilityStatus::UNDER_CONSTRUCTIONS;} //implement!
    
    void Facility::setStatus(FacilityStatus status){
        this->status = status;
    }

    const FacilityStatus& Facility::getStatus() const{
        return status;
    }

    const string Facility::toString() const{
        return FacilityType::getName() + " at " + settlementName;
    }