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