#include <iostream>
#include <vector>
#include <string>

class Hero;

class Equipment;

class Armor;

class Spell;

class Arena;

class Monster;

class Spider;

class BossSpider;

class InfectedHero;


class Armor {
private:
    std::string name;
    unsigned int protection;
    unsigned int damage;
public:
    Armor(std::string name, unsigned int protection, unsigned int damage);

    std::string getName();

    unsigned int getDamage();

    unsigned int getPeotection();
};

class Equipment {
private:
    std::vector<Armor> equipment;
public:

    void addItem(Armor item);

    void deleteItem(Armor item);

    unsigned int returnArmor();

    unsigned int returnDamage();

    void info();

    void clearEquipment();
};

class Spell {
private:
    std::string name = "Fireball";
    unsigned int lvl = 1;
    unsigned int damage = 30;
    unsigned int manaCost = 50;
public:

    unsigned int getManaCost();

    unsigned int cast();

    void lvlUp();

    void lvlDown();

    void info();
};

class Hero {
private:
    std::string name;
    unsigned int hp = 100;
    unsigned int mana = 100;
    unsigned int damage = 20;
    unsigned int protection = 3;
    unsigned int arenaPoinnt = 0;
    Equipment *equipment;
    Spell *spell;

    void refresh();

public:

    Hero(const std::string name, Equipment *equipment, Spell *spell);

    unsigned int getArmor();

    unsigned int getHp();

    unsigned int getDamage();

    void getReward(Armor &reward);

    void acceptItems();

    void infoIndicators();

    void infoEquipment();

    void infoSpell();

    void castSpell(Monster *monster);

    void hit(Monster *monster);

    void getDamage(unsigned int damage);

    void getArenaPoint();

    void lvlUpSpell();

    bool alive();
};

class Monster {
public:
    virtual void hitHero(Hero &hero) = 0;

    virtual void getDamage(unsigned int damage) = 0;

    virtual bool alive() = 0;

    virtual void info() = 0;
};

class Spider : public Monster {
private:
    unsigned int hp = 100;
    unsigned int damage = 10;
public:

    void info() override;

    void hitHero(Hero &hero) override;

    void getDamage(unsigned int damage) override;

    bool alive() override;
};

class BossSpider : public Spider {
private:
    unsigned int hp = 200;
    unsigned int damage = 30;
public:
    BossSpider(unsigned int hp);

    void info() override;

    void hitHero(Hero &hero) override;

    void getDamage(unsigned int damage) override;

    bool alive() override;
};

class InfectedHero : public Monster{   //Adapter
private:
    Hero *infectedHero;
public:
    InfectedHero(Hero *infectedHero);

    void info() override;

    void hitHero(Hero &hero) override;

    void getDamage(unsigned int damage) override;

    bool alive() override;
};


class Arena {
private:
    Hero *hero;
    Monster *monster;
    Armor *reward;
public:
    Arena(Hero *hero, Monster *monster, Armor *reward);

    void info();

    void getReward();
};

