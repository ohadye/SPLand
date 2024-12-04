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
    string FacilityType::getCategoryString(FacilityCategory category){
        switch (category){
            case FacilityCategory::ECONOMY : return "economy";
            case FacilityCategory::ENVIRONMENT : return "environment";
            case FacilityCategory::LIFE_QUALITY : return "life quality";
        }
        return "no category";
    }
    
    FacilityCategory FacilityType::parseFacilityCategory(const string& category){
        if(category == "0")
            return FacilityCategory::LIFE_QUALITY;
        else if( category == "1")
            return FacilityCategory::ECONOMY;
        else
            return FacilityCategory::ENVIRONMENT;
    }
    
    /** 

    bool FacilityType::operator==(FacilityType& other){
        if( this->name != other.name || this->category != other.category ||
            this->price != other.price || this->lifeQuality_score != other.lifeQuality_score ||
            this->economy_score != other.economy_score || this->environment_score != other.environment_score)
            return false;
        return true;
    }*/

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
    Facility::Facility(const string &name, 
                        const string &settlementName, 
                        const FacilityCategory category, 
                        const int price, 
                        const int lifeQuality_score, 
                        const int economy_score, 
                        const int environment_score):
        FacilityType::FacilityType(name,category,price,lifeQuality_score,environment_score,economy_score), 
        settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price)
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

    /*Preforms the logic of progressing the Constraction of the instace of the facility by one unit of time*/
    FacilityStatus Facility::step(){
        if(--timeLeft == CONSTRACTION_TIME_DONE)
            status = FacilityStatus::OPERATIONAL;//change the status of the facility to operational when there is no more time left for the faciliti'es complation

        return status;
    }

    void Facility::setStatus(FacilityStatus status){
        this->status = status;
    }

    const FacilityStatus& Facility::getStatus() const{
        return status;
    }

    const string Facility::toString() const{
        string st = "facilityName: "+FacilityType::getName() + "facilityStatus: ";
        if(status == FacilityStatus::OPERATIONAL)
            st.append("OPERATIONAL");
        else    
            st.append("UNDER_CONSTRUCTION");
        return st;
    }