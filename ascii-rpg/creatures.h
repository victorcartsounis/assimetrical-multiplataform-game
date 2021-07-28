#ifndef CREATURES
#define CREATURES

#include <map>

namespace CreaturesFeatures {

class Creature {
    public:
        Creature(std::map<std::string, int> creatureStats) 
            : m_maxHealth(creatureStats["maxHealth"])
            , m_maxSkillsPoints(creatureStats["maxSkillsPoints"])
            , m_actualHealth(m_maxHealth)
            , m_actualSkillPoints(m_maxSkillsPoints)
            , m_attack(10)
            , m_defense(10)
        {
        };

        int GetHealth() const { return m_actualHealth; }

        int GetDefense() const { return m_defense; }

        bool TakeDamage(int attackPower) { 
            m_actualHealth -= attackPower;
            return (m_actualHealth <= 0);
        }
       
    private:
        int m_maxHealth;
        int m_maxSkillsPoints;

    protected:
        int m_actualHealth;
        int m_actualSkillPoints;
        int m_attack;
        int m_defense;


};

class Enemy : public Creature {
    public:
        Enemy(std::map<std::string, int> creatureStats) : Creature(creatureStats)
        {
        };
        
        bool Attack(Creature& player);

    private:


};

class Player : public Creature {
    public:
        Player(std::map<std::string, int> creatureStats) : Creature(creatureStats)
        {
        };

        bool Attack(Creature& enemy);

    private:
        int m_level;
        int m_experience;
        int m_totalExperience;

};

}
#endif