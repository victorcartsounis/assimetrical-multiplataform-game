#include "creatures.h"
#include <iostream>

using namespace CreaturesFeatures;

bool 
Player::Attack(Creature& enemy) {
    bool isDead = enemy.TakeDamage(m_attack);
    return isDead;
}