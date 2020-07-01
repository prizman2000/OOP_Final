#include "lib.h"

Armor::Armor(const std::string name, unsigned int protection, unsigned int damage) {
    this->name = name;
    this->protection = protection;
    this->damage = damage;
}

std::string Armor::getName() {
    return name;
}

unsigned int Armor::getDamage() {
    return damage;
}

unsigned int Armor::getProtection() {
    return protection;
}

void Equipment::addItem(Armor item) {
    equipment.push_back(item);
}

void Equipment::deleteItem(Armor item) {
    equipment.pop_back();
}

void Equipment::info() {
    std::cout << "---------------------------------------------------\n";
    std::cout << "Снаряжение героя.\n";
    std::cout << "---------------------------------------------------\n";
    for (int i = 0; i < equipment.size(); i++) {
        std::cout << equipment[i].getName() << "\nУрон: +" << equipment[i].getDamage() << "\nБроня: +"
                  << equipment[i].getProtection() << std::endl;
        std::cout << "*_________*_________*\n";
    }
}

unsigned int Equipment::returnArmor() {
    unsigned int result = 0;
    for (int i = 0; i < equipment.size(); i++) {
        result += equipment[i].getProtection();
    }
    return result;
}

unsigned int Equipment::returnDamage() {
    unsigned int result = 0;
    for (int i = 0; i < equipment.size(); i++) {
        result += equipment[i].getDamage();
    }
    return result;
}

void Equipment::clearEquipment() {
    equipment.clear();
}

unsigned int Spell::getManaCost() {
    return manaCost;
}

unsigned int Spell::cast() {
    return damage;
}

void Spell::lvlUp() {
    ++lvl;
    damage += lvl * 4;
}

void Spell::lvlDown() {
    this->lvl = 0;
    damage = 0;
    manaCost = 0;
}

void Spell::info() {
    std::cout << "---------------------------------------------------\n";
    std::cout << "Способность героя.\n";
    std::cout << "---------------------------------------------------\n";
    std::cout << name << " lvl " << lvl << std::endl;
    std::cout << "Урон: " << damage << std::endl;
    std::cout << "Мана: " << manaCost << std::endl;
}

Hero::Hero(const std::string name, Equipment *equipment, Spell *spell) {
    this->name = name;
    this->equipment = equipment;
    this->spell = spell;
}

unsigned int Hero::getHp() {
    return this->hp;
}

unsigned int Hero::getDamage() {
    return this->damage;
}

unsigned int Hero::getArmor() {
    return this->protection;
}

void Hero::getArenaPoint() {
    arenaPoinnt++;
}

void Hero::refresh() {
    if (this->hp == 0) {
        damage = 0;
        protection = 0;
        mana = 0;
        equipment->clearEquipment();
        spell->lvlDown();
    }
}

void Hero::acceptItems() {
    this->protection += equipment->returnArmor();
    this->damage += equipment->returnDamage();
}

void Hero::infoIndicators() {
    if (!this->alive()) {
        std::cout << "---------------------------------------------------\n";
        std::cout << "Ваш герой " << name << " мертв!\n";
        std::cout << "---------------------------------------------------\n";
    } else {
        std::cout << "---------------------------------------------------\n";
        std::cout << name << std::endl;
        std::cout << "Здоровье: " << hp << std::endl;
        std::cout << "Мана: " << mana << std::endl;
        std::cout << "---------------------------------------------------\n";
    }
}

void Hero::infoEquipment() {
    equipment->info();
}

void Hero::infoSpell() {
    spell->info();
    std::cout << "---------------------------------------------------\n";
    std::cout << "Осталось неиспользованных очков арены: "<<arenaPoinnt<<std::endl;
    std::cout << "---------------------------------------------------\n";
}

void Hero::castSpell(Monster *monster) {
    if (mana < spell->getManaCost()) {
        std::cout << "---------------------------------------------------\n";
        std::cout << "Недостаточно маны для использования способности!\n";
        std::cout << "---------------------------------------------------\n";
    } else {
        monster->getDamage(spell->cast());
        mana -= spell->getManaCost();
    }
}

void Hero::hit(Monster *monster) {
    monster->getDamage(damage);
    if (mana + 10 < 100) {
        mana += 10;
    } else if (mana + 10 >= 100) {
        mana = 100;
    }
    monster->hitHero(*this);
    refresh();
}

void Hero::getDamage(unsigned int damage) {
    if (hp > damage) {
        hp -= damage;
    } else {
        hp = 0;
    }
}

void Hero::lvlUpSpell() {
    --arenaPoinnt;
    spell->lvlUp();
}

bool Hero::alive() {
    if (hp > 0) {
        return true;
    } else {
        return false;
    }
}

void Hero::getReward(Armor &reward) {
    equipment->addItem(reward);
    this->acceptItems();
}

void Spider::getDamage(unsigned int damage) {
    if (hp > damage) {
        hp = hp - damage;
    } else {
        hp = 0;
    }
}

void Spider::info() {
    std::cout << "---------------------------------------------------\n";
    std::cout << "Здоровье паука: " << hp << std::endl;
    std::cout << "---------------------------------------------------\n";
}

bool Spider::alive() {
    if (hp == 0) {
        return false;
    } else {
        return true;
    }
}

void Spider::hitHero(Hero &hero) {
    hero.getDamage(damage / hero.getArmor());
}

BossSpider::BossSpider(unsigned int hp) {
    if (hp < 200) {
        this->hp = 200;
    }else{
        this->hp = hp;
    }
}

void BossSpider::getDamage(unsigned int damage) {
    if (hp > damage) {
        hp -= damage;
    } else {
        hp = 0;
    }
}

bool BossSpider::alive() {
    if (hp == 0) {
        return false;
    } else {
        return true;
    }
}

void BossSpider::hitHero(Hero &hero) {
    hero.getDamage(damage / hero.getArmor());
}

void BossSpider::info() {
    std::cout << "---------------------------------------------------\n";
    std::cout << "Здоровье паука: " << hp << std::endl;
    std::cout << "---------------------------------------------------\n";
}

Arena::Arena(Hero *hero, Monster *monster, Armor *reward) {
    this->hero = hero;
    this->monster = monster;
    this->reward = reward;

}

void Arena::info() {
    hero->infoIndicators();
    monster->info();
}

void Arena::getReward() {
    if (monster->alive()) {
        std::cout << "---------------------------------------------------\n";
        std::cout << "Убейте мостра, чтобы получить награду!\n";
        std::cout << "---------------------------------------------------\n";
    } else if (!hero->alive()) {
        std::cout << "---------------------------------------------------\n";
        std::cout << "Ваш герой мертв!\n";
        std::cout << "---------------------------------------------------\n";
    } else {
        std::cout << "---------------------------------------------------\n";
        std::cout << "Вы получили награду!\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << reward->getName() << std::endl;
        std::cout << "Броня: +" << reward->getProtection() << std::endl;
        std::cout << "Урон: +" << reward->getDamage() << std::endl;
        std::cout << "---------------------------------------------------\n";
        hero->getArenaPoint();
        hero->getReward(*reward);
    }
}

InfectedHero::InfectedHero(Hero *infectedHero) {
    this->infectedHero = infectedHero;
}

void InfectedHero::getDamage(unsigned int damage) {
        infectedHero->getDamage(damage);
}

bool InfectedHero::alive() {
    infectedHero->alive();
}

void InfectedHero::hitHero(Hero &hero) {
    hero.getDamage(infectedHero->getDamage() / hero.getArmor());
}

void InfectedHero::info() {
    std::cout << "---------------------------------------------------\n";
    std::cout << "Здоровье инфецированного героя: " << infectedHero->getHp() << std::endl;
    std::cout << "---------------------------------------------------\n";
}

Kisoklass::Kisoklass() {
    auto fireball1 = new Spell;
}

void Kisoklass::say() {
    std::cout << "---------------------------------------------------\n";
    std::cout<<"Mew...Mew...Mew...Mew...Mew...Mew...Mew...Mew...Mew...";
    std::cout << "---------------------------------------------------\n";
}

