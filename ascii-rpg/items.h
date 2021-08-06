#ifndef ITEMS
#define ITEMS

#include <iostream>

namespace ItemsFeatures {

enum class PropertyName {
    kAttack,
    kDefense
};

typedef std::pair<PropertyName, int> Property;

class Item {
    public:
        Item(std::string name, std::string description, std::string iconPath, Property property)
            : m_name(name)
            , m_description(description)
            , m_iconPath(iconPath)
            , m_property(property)
        {
        };

        std::string GetName() const { return m_name; }

        std::string GetDescription() const { return m_description; }

        Property GetProperty() { return m_property; }
    
    private:
        Property m_property;
        std::string m_name;
        std::string m_description;
        std::string m_iconPath;
};

class Helmet : public Item {
    public:
        Helmet(std::string name, std::string description, std::string iconPath, int defense, Property property)
            : Item(name, description, iconPath, property)
            , m_defense(defense)
        {
        };

    private:
        int m_defense;
};

class Weapon : public Item {
    public:
        Weapon(std::string name, std::string description, std::string iconPath, int attack, Property property)
            : Item(name, description, iconPath, property)
            , m_attack(attack)
        {
        };


    private:
        int m_attack;
};

}
#endif