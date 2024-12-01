#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
#define VILLAGE_CONSTRACTION_CAPACITY 1
#define CITY_CONSTRACTION_CAPACITY 2
#define METROPOLIS_CONSTRACTION_CAPACITY 3

class Facility;
enum class SettlementTypeCapcity {//@QUASTION: is there a better practice for this? as far as I understand I can't add fields to enums. is it allowed to make it into a struct?
   
};
enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        Settlement(const Settlement& other);
        static string getTypeString(SettlementType type);
        static SettlementType parseSettlementType(const string& type);
        const string &getName() const;
        SettlementType getType() const;
        const string toString() const;
        Settlement* clone();
        const int getTypeCapacity() const;//added method
        private:
            const string name;
            SettlementType type;
};