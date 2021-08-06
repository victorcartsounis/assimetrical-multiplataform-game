#ifndef CREATURES
#define CREATURES

#include "items.h"

#include <map>
#include <vector>


using namespace ItemsFeatures;

namespace CreaturesFeatures {

class Creature {
    public:
        Creature(std::string name, std::map<std::string, int> creatureStats) 
            : m_name(name)
            , m_maxHealth(creatureStats["maxHealth"])
            , m_maxSkillPoints(creatureStats["maxSkillsPoints"])
            , m_actualHealth(m_maxHealth)
            , m_actualSkillPoints(m_maxSkillPoints)
            , m_attack(10)
            , m_defense(10)
        {
        };

        std::string GetName() const { return m_name; }

        int GetHealth() const { return m_actualHealth; }

        int GetMaxHealth() const { return m_maxHealth; }

        int GetDefense() const { return m_defense; }

        int GetSkillPoints() const { return m_actualSkillPoints; }

        int GetMaxSkillPoints() const { return m_maxSkillPoints; }

        bool TakeDamage(int attackPower) {
            m_actualHealth -= attackPower;
            return (m_actualHealth <= 0);
        }
       
    private:
        std::string m_name;
        int m_maxHealth;
        int m_maxSkillPoints;

    protected:
        int m_actualHealth;
        int m_actualSkillPoints;
        int m_attack;
        int m_defense;


};

class Enemy : public Creature {
    public:
        Enemy(std::string name, std::map<std::string, int> creatureStats) 
            : Creature(name, creatureStats)
            , m_experience(creatureStats["experience"])
        {
        };

        int GetExperience() const { return m_experience; }
        
        bool Attack(Creature& player);

    private:
        int m_experience;


};

class Player : public Creature {
    public:
        Player(std::string name, std::map<std::string, int> playerStats)
            : Creature(name, playerStats)
            , m_level(playerStats["level"])
            , m_totalExperience(playerStats["totalExperience"])
        {
        };

        int GetAttack() const { return m_attack; }

        int GetLevel() const { return m_level; }

        int GetExperience() const { return m_totalExperience; }

        int GetNextLevelExperience() const { return m_levelExperience[m_level]; }
        
        void AddExperience(int experience) { m_totalExperience += experience; }

        void AddLevel() { m_level += 1; }

        void AddDefense(int defense) { m_defense += defense; }
        
        void RemoveDefense(int defense) { m_defense -= defense; }

        void AddAttack(int attack) { m_attack += attack; }
        
        void RemoveAttack(int attack) { m_attack -= attack; }
        
        bool Attack(Creature& enemy);

        //ITEMS

        void AddItemToInventory(Item item) { m_inventory.emplace_back(item); }

        std::vector<Item> GetInventory() const { return m_inventory; }

        void OnEquip(Item& item);

        void OnDequip(Item& item);

    private:
        int m_level = 0;
        int m_totalExperience = 0;
        std::vector<int> m_levelExperience {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000, 2048000};
        std::vector<Item> m_inventory;

};

}
#endif