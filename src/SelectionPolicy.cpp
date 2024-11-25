#include "../include/SelectionPolicy.h"
#include "../include/Facility.h"

#include <vector>
using std::vector;

//NaiveSelection

    NaiveSelection::NaiveSelection(): lastSelectedIndex(0){}
    NaiveSelection::NaiveSelection(const NaiveSelection& other): lastSelectedIndex(other.lastSelectedIndex){

    }
    const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
        return facilitiesOptions[++lastSelectedIndex];
    }
    const string NaiveSelection::toString() const { }                                                                     //implement!
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
    const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {}             //implement!!
    const string BalancedSelection::toString() const { }//implement!
    BalancedSelection *BalancedSelection::clone() const {
        return new BalancedSelection(*this);
    }

//EconomySelection
    EconomySelection::EconomySelection(): lastSelectedIndex(0){}
    EconomySelection::EconomySelection(const EconomySelection& other): lastSelectedIndex(other.lastSelectedIndex){

    }
    const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {}              //implement!
    const string EconomySelection::toString() const { }                                                                 //implement!
    EconomySelection *EconomySelection::clone() const {
        return new EconomySelection(*this);
    }

//SustainabilitySelection
    SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(0){}
    SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection& other): lastSelectedIndex(other.lastSelectedIndex){

    }
    const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {}              //implement!
    const string SustainabilitySelection::toString() const { }                                                                 //implement!
    SustainabilitySelection *SustainabilitySelection::clone() const {
        return new SustainabilitySelection(*this);
    }
