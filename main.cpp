#include <iostream>
#include "src/lib.h"


int main() {

    Armor helmet("Шлем безумия", 1, 3);
    Armor chest("Броня Гитлерa", 2, 5);
    Armor weapon("Шпага Атоса", 0, 15);
    Armor pants("Штаны бедуина", 3, 1);

Equipment equipment;

equipment.addItem(helmet);
equipment.addItem(chest);
equipment.addItem(weapon);
equipment.addItem(pants);

Spell fireball;

Hero hero("Вячеслав", &equipment, &fireball);

Spider spider(100);

Armor ring("Кольцо королевской раскоши", 3, 3);

Arena arena(&hero, &spider, &ring);

arena.info();

hero.castSpell(spider);
hero.castSpell(spider);
hero.castSpell(spider);

arena.info();

hero.hit(spider);
hero.hit(spider);

arena.info();

arena.getReward();

hero.infoEquipment();

    return 0;
}
