#include "creatures.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <ctime>


using namespace CreaturesFeatures;

bool 
Player::Attack(Creature& enemy) {
    m_actualSkillPoints -= 100;
    srand((unsigned) time(0));
    int attackRange = 70 + (rand() % 60);

    int attackPower;
    if (enemy.GetDefense() > 0) {
        attackPower = (attackRange/100.0) * ((10 * m_attack * m_level) / (enemy.GetDefense()));
    } else {
        attackPower = (m_attack * m_level);
    }
    bool isDead = enemy.TakeDamage(attackPower);
    return isDead;
}

void
Player::OnEquip(Item& item) {
    switch (item.GetProperty().first) {
        case (PropertyName::kAttack):
            m_attack += item.GetProperty().second;
            break;
        case (PropertyName::kDefense):
            m_defense += item.GetProperty().second;
            break;
        default:
            break;
    }
}

void
Player::OnDequip(Item& item) {
    switch (item.GetProperty().first) {
        case (PropertyName::kAttack):
            m_attack -= item.GetProperty().second;
            break;
        case (PropertyName::kDefense):
            m_defense -= item.GetProperty().second;
            break;
        default:
            break;
    }
}