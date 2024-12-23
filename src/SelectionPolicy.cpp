#include "../include/SelectionPolicy.h"
#include "../include/Facility.h"

#include <vector>
using std::vector;

//NaiveSelection

    NaiveSelection::NaiveSelection(): lastSelectedIndex(0){}
    NaiveSelection::NaiveSelection(const NaiveSelection& other): lastSelectedIndex(other.lastSelectedIndex){

    }
    const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
        int size = facilitiesOptions.size();
        if (lastSelectedIndex == size)
            lastSelectedIndex = 0;
        return facilitiesOptions[lastSelectedIndex++];
    }
    const string NaiveSelection::toString() const { return "nve";}
    NaiveSelection *NaiveSelection::clone() const {
        return new NaiveSelection(*this);
    }


//BalancedSelection

    BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore):
        LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore)
    {}
    BalancedSelection::BalancedSelection(const BalancedSelection& other): 
        LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore)
    {}
    const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
        int distance = -1;
        int facilityIndex = 0, balancedIndex;

        for(const FacilityType& f: facilitiesOptions){
            int max = std::max(std::max( f.getEconomyScore()+ EconomyScore , f.getEnvironmentScore() + EnvironmentScore),f.getLifeQualityScore()+ LifeQualityScore  );
            int min = std::min(std::min( f.getEconomyScore()+ EconomyScore , f.getEnvironmentScore() + EnvironmentScore),f.getLifeQualityScore()+ LifeQualityScore  );
            if( max - min < distance || facilityIndex == 0){
                distance = max-min;
                balancedIndex = facilityIndex;
            }
            facilityIndex++;
        }
        EconomyScore+=facilitiesOptions[balancedIndex].getEconomyScore();
        EnvironmentScore+=facilitiesOptions[balancedIndex].getEnvironmentScore();
        LifeQualityScore+=facilitiesOptions[balancedIndex].getLifeQualityScore();
        return facilitiesOptions[balancedIndex];

    }
    const string BalancedSelection::toString() const { return "bal";}
    BalancedSelection *BalancedSelection::clone() const {
        return new BalancedSelection(*this);
    }

//EconomySelection
    EconomySelection::EconomySelection(): lastSelectedIndex(0){}
    EconomySelection::EconomySelection(const EconomySelection& other): lastSelectedIndex(other.lastSelectedIndex){

    }
    const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
        int size = facilitiesOptions.size();
        for(int index = lastSelectedIndex + 1; index < size;index++){
            if(facilitiesOptions[index].getCategory() == FacilityCategory::ECONOMY){
                lastSelectedIndex = index;
                return facilitiesOptions[index];
            }
        }
        for(int index = 0;index < lastSelectedIndex + 1;index++){
            if(facilitiesOptions[index].getCategory() == FacilityCategory::ECONOMY){
                lastSelectedIndex = index;
                return facilitiesOptions[index];
            }
        }
        return facilitiesOptions[++lastSelectedIndex];
    }
    const string EconomySelection::toString() const { return "eco";}
    EconomySelection *EconomySelection::clone() const {
        return new EconomySelection(*this);
    }

//SustainabilitySelection
    SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(0){}
    SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection& other): lastSelectedIndex(other.lastSelectedIndex){
        
    }
    const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
        int size = facilitiesOptions.size();
        for(int index = lastSelectedIndex + 1; index < size;index++){
            if(facilitiesOptions[index].getCategory() == FacilityCategory::ENVIRONMENT){
                lastSelectedIndex = index;
                return facilitiesOptions[index];
            }
        }
        for(int index = 0;index < lastSelectedIndex + 1;index++){
            if(facilitiesOptions[index].getCategory() == FacilityCategory::ENVIRONMENT){
                lastSelectedIndex = index;
                return facilitiesOptions[index];
            }
        }
        return facilitiesOptions[++lastSelectedIndex];
    }
    const string SustainabilitySelection::toString() const { return "env";}
    SustainabilitySelection *SustainabilitySelection::clone() const {
        return new SustainabilitySelection(*this);
    }
