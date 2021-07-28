#include "creatures.h"
#include <iostream>

using namespace CreaturesFeatures;

bool 
Enemy::Attack(Creature& player) {
    bool isDead = player.TakeDamage(m_attack);
    return isDead;
}
