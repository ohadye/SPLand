#include "../include/Settlement.h"
using std::string;

        Settlement::Settlement(const string &name, SettlementType type):
            name(name) , type(type){}

        Settlement::Settlement(const Settlement& other):
            name(other.name) , type(other.type)
        {}

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

        Settlement Settlement::clone(){
            return Settlement(name,type);
        }