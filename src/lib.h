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

class Werewolf;


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
    std::string getName();

    unsigned int getLvl();

    unsigned int getDamage();

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
    Equipment *equipment;
    Spell *spell;

    void refresh();

public:

    Hero(const std::string name, Equipment *equipment, Spell *spell);

    unsigned int getArmor();

    void getReward(Armor &reward);

    void acceptItems();

    void infoIndicators();

    void infoEquipment();

    void infoSpell();

    void castSpell(Spider &monster);

    void hit(Spider &monster);

    void getDamage(unsigned int damage);

    bool alive();
};

class Monster {
public:
    virtual void hitHero(Hero &hero) = 0;

    virtual void getDamage(unsigned int damage) = 0;

    virtual bool alive() = 0;

    virtual void info() = 0;
};

class Spider : Monster {
private:
    unsigned int hp;
    unsigned int damage = 10;
public:
    Spider(unsigned int hp);

    void info();

    void hitHero(Hero &hero) override;

    void getDamage(unsigned int damage) override;

    bool alive() override;
};

class Werewolf : Monster {
private:
    unsigned int hp;
    unsigned int damage;
public:
    void hitHero(Hero &hero) override;

    void getDamage(unsigned int damage) override;

    bool alive() override;
};

class Arena {
private:
    Hero *hero;
    Spider *monster;
    Armor *reward;
public:
    Arena(Hero *hero, Spider *monster, Armor *reward);

    void info();

    void getReward();
};