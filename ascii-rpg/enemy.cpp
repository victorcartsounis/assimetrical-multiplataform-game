#include "creatures.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace CreaturesFeatures;

bool 
Enemy::Attack(Creature& player) {
    m_actualSkillPoints -= 100;
    srand((unsigned) time(0));
    int attackRange = 70 + (rand() % 60);

    int attackPower;
    if (player.GetDefense() > 0) {
        attackPower = (attackRange/100.0) * ((10 * m_attack) / (player.GetDefense()));
    } else {
        attackPower = (attackRange/100.0) * (m_attack);
    }
    bool isDead = player.TakeDamage(attackPower);
    return isDead;
}
