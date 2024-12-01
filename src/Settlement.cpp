#include "../include/Settlement.h"
using std::string;

        Settlement::Settlement(const string &name, SettlementType type):
            name(name) , type(type){}

        Settlement::Settlement(const Settlement& other):
            name(other.name) , type(other.type)
        {}

        string Settlement::getTypeString(SettlementType type) {
            if (type == SettlementType::CITY)
                return "city";
            else if (type == SettlementType::METROPOLIS)
                return "metropolis";
            else
                return "village";
        }

        SettlementType Settlement::parseSettlementType(const string& type){
            if(type == "1")
                return SettlementType::CITY;
            else if(type == "2")
                return SettlementType::METROPOLIS;
            else
                return SettlementType::VILLAGE;
        }

        const string &Settlement::getName() const{
            return this->name;
        }

        SettlementType Settlement::getType() const{
            return this->type;
        }

        const string Settlement::toString() const{
            //write type to string here!
            return name;
        }

        Settlement* Settlement::clone(){
            return new Settlement(name,type);
        }

        const int Settlement::getTypeCapacity() const{//@Qustion: is there a better why to implement this? seems to me that the enum needs to "hold" the capacity value somehow... phrhaps make it a struct?

            int capacity = 0;//@NOTE: might need to added error handling/defult case later.
            switch (this->type)
            {
            case SettlementType::VILLAGE:
                capacity = VILLAGE_CONSTRACTION_CAPACITY;
                break;
            case SettlementType::CITY:
                capacity = CITY_CONSTRACTION_CAPACITY;
                break;
            case SettlementType::METROPOLIS:
                capacity = METROPOLIS_CONSTRACTION_CAPACITY;
                break;
            }
            return capacity;
        }