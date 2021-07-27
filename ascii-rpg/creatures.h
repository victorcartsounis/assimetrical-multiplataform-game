#ifndef CREATURES
#define CREATURES

namespace CreaturesFeatures {


#include <map>

class Creature {
    public:
        Creature(std::map<std::string, float> creatureStats) 
            : m_maxHealth(creatureStats["maxHealth"])
            , m_actualHealth(m_maxHealth)
            , m_maxSkillsPoints(creatureStats["maxSkillsPoints"])
            , m_actualSkillPoints(m_maxSkillsPoints)
        {
        }; 

    private:
        float m_actualHealth;
        float m_maxHealth;
        float m_actualSkillPoints;
        float m_maxSkillsPoints;
};

class Enemy : Creature {
    public:
        Enemy(std::map<std::string, float> creatureStats) : Creature(creatureStats)
        {
        };
};

class Player : Creature {
    public:
        Player(std::map<std::string, float> creatureStats) : Creature(creatureStats)
        {
        };

    private:
        int m_level;
        float m_experience;
        float m_totalExperience;

};

}
#endif