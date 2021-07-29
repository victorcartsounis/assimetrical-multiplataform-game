#ifndef CREATURES
#define CREATURES

#include <map>
#include <vector>

namespace CreaturesFeatures {

class Creature {
    public:
        Creature(std::string name, std::map<std::string, int> creatureStats) 
            : m_name(name)
            , m_maxHealth(creatureStats["maxHealth"])
            , m_maxSkillsPoints(creatureStats["maxSkillsPoints"])
            , m_actualHealth(m_maxHealth)
            , m_actualSkillPoints(m_maxSkillsPoints)
            , m_attack(10)
            , m_defense(10)
        {
        };

        std::string GetName() const { return m_name; }

        int GetHealth() const { return m_actualHealth; }

        int GetMaxHealth() const { return m_maxHealth; }

        int GetDefense() const { return m_defense; }

        bool TakeDamage(int attackPower) { 
            m_actualHealth -= attackPower;
            return (m_actualHealth <= 0);
        }
       
    private:
        std::string m_name;
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
        Enemy(std::string name, std::map<std::string, int> creatureStats) : Creature(name, creatureStats)
        {
        };

        int GetExperience() const { return m_experience; }
        
        bool Attack(Creature& player);

    private:
        int m_experience = 1000;


};

class Player : public Creature {
    public:
        Player(std::string name, std::map<std::string, int> creatureStats) : Creature(name, creatureStats)
        {
        };

        void AddExperience(int experience) { m_totalExperience += experience; }

        void AddLevel() { m_level += 1; }

        int GetLevel() const { return m_level; }

        int GetExperience() const { return m_totalExperience; }

        int GetNextLevelExperience() const { return m_levelExperience[m_level]; }

        bool Attack(Creature& enemy);

    private:
        int m_level = 0;
        int m_totalExperience = 0;
        std::vector<int> m_levelExperience {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000, 2048000};

};

}
#endif