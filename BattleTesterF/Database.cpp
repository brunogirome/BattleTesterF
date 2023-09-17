#include "Database.h"

Database::Database()
{
    loadHeroesFromDatabase();

    loadEnemiesFromDatabase();

}

Hero Database::getAHero(int id)
{
    const Hero findHero = Heroes[id - 1];

    return findHero;
}

Enemy Database::getAEnemy(int id)
{
    const Enemy findEnemy = Enemies[id - 1];

    return findEnemy;
}

void Database::listHeroes()
{
    std::cout << "+---------------------------+" << '\n';
    std::cout << "| Display all Heroes        |" << '\n';
    std::cout << "+---------------------------+" << '\n';

    for (int i = 0; i < Heroes.size(); i++) {
        std::cout << "id: " << Heroes[i].Id << '\n';
        std::cout << "name: " << Heroes[i].Name << '\n';
        std::cout << "combatType: " << Heroes[i].CombatType << '\n';
        std::cout << "element: " << Heroes[i].Element << '\n';
        std::cout << "strength: " << Heroes[i].Strength << '\n';
        std::cout << "agility: " << Heroes[i].Agility << '\n';
        std::cout << "intelligence: " << Heroes[i].Intelligence << '\n';
        std::cout << "hpBase: " << Heroes[i].HpBase << '\n';
        std::cout << "manaBase: " << Heroes[i].ManaBase << '\n';
        std::cout << "speedBase: " << Heroes[i].SpeedBase << '\n';
        std::cout << "evasionBase: " << Heroes[i].EvasionBase << '\n';
        std::cout << "staminaBase: " << Heroes[i].StaminaBase << '\n';
        std::cout << "meelePowerBase: " << Heroes[i].MeelePowerBase << '\n';
        std::cout << "magicPowerBase: " << Heroes[i].MagicPowerBase << '\n';
        std::cout << "meeleDefenseBase: " << Heroes[i].MeeleDefenseBase << '\n';
        std::cout << "magicDefenseBase: " << Heroes[i].MagicDefenseBase << '\n';
        std::cout << "hpTotal: " << Heroes[i].HpTotal << '\n';
        std::cout << "manaTotal: " << Heroes[i].ManaTotal << '\n';
        std::cout << "speedTotal: " << Heroes[i].SpeedTotal << '\n';
        std::cout << "evasionTotal: " << Heroes[i].EvasionTotal << '\n';
        std::cout << "staminaTotal: " << Heroes[i].StaminaTotal << '\n';
        std::cout << "meelePowerTotal: " << Heroes[i].MeelePowerTotal << '\n';
        std::cout << "magicPowerTotal: " << Heroes[i].MagicPowerTotal << '\n';
        std::cout << "meeleDefenseTotal: " << Heroes[i].MeeleDefenseTotal << '\n';
        std::cout << "magicDefenseTotal: " << Heroes[i].MagicDefenseTotal << '\n';
        std::cout << "-------------------------------" << '\n' << '\n';
    }
}

void Database::listEnemies()
{
    std::cout << "+---------------------------+" << '\n';
    std::cout << "| Display all Enemies       |" << '\n';
    std::cout << "+---------------------------+" << '\n';

    for (int i = 0; i < Enemies.size(); i++) {
        std::cout << "id: " << Enemies[i].Id << '\n';
        std::cout << "name: " << Enemies[i].Name << '\n';
        std::cout << "combatType: " << Enemies[i].CombatType << '\n';
        std::cout << "element: " << Enemies[i].Element << '\n';
        std::cout << "strength: " << Enemies[i].Strength << '\n';
        std::cout << "agility: " << Enemies[i].Agility << '\n';
        std::cout << "intelligence: " << Enemies[i].Intelligence << '\n';
        std::cout << "hpBase: " << Enemies[i].HpBase << '\n';
        std::cout << "manaBase: " << Enemies[i].ManaBase << '\n';
        std::cout << "speedBase: " << Enemies[i].SpeedBase << '\n';
        std::cout << "evasionBase: " << Enemies[i].EvasionBase << '\n';
        std::cout << "staminaBase: " << Enemies[i].StaminaBase << '\n';
        std::cout << "meelePowerBase: " << Enemies[i].MeelePowerBase << '\n';
        std::cout << "magicPowerBase: " << Enemies[i].MagicPowerBase << '\n';
        std::cout << "meeleDefenseBase: " << Enemies[i].MeeleDefenseBase << '\n';
        std::cout << "magicDefenseBase: " << Enemies[i].MagicDefenseBase << '\n';
        std::cout << "hpTotal: " << Enemies[i].HpTotal << '\n';
        std::cout << "manaTotal: " << Enemies[i].ManaTotal << '\n';
        std::cout << "speedTotal: " << Enemies[i].SpeedTotal << '\n';
        std::cout << "evasionTotal: " << Enemies[i].EvasionTotal << '\n';
        std::cout << "staminaTotal: " << Enemies[i].StaminaTotal << '\n';
        std::cout << "meelePowerTotal: " << Enemies[i].MeelePowerTotal << '\n';
        std::cout << "magicPowerTotal: " << Enemies[i].MagicPowerTotal << '\n';
        std::cout << "meeleDefenseTotal: " << Enemies[i].MeeleDefenseTotal << '\n';
        std::cout << "magicDefenseTotal: " << Enemies[i].MagicDefenseTotal << '\n';
        std::cout << "-------------------------------" << '\n' << '\n';
    }
}

void Database::loadHeroesFromDatabase()
{
    sqlite3* database = connect();

    if (database == NULL) {
        return;
    }

    int ret_code = 0;

    std::string query = "SELECT * FROM Heroes;";

    int id, strength, agility, intelligence, hpBase, manaBase, speedBase, 
        evasionBase, staminaBase, meelePowerBase, magicPowerBase, meeleDefenseBase, magicDefenseBase;

    CombatTypesEnum combatType;

    ElementsEnum element;

    std::string name;

    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) != SQLITE_OK) {
        std::cout << "Error while executing the query: " << query << '\n';

        disconnect(statement);

        return;
    }

    while ((ret_code = sqlite3_step(statement)) == SQLITE_ROW) {
        id = sqlite3_column_int(statement, 0);
        name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
        combatType = (CombatTypesEnum)sqlite3_column_int(statement, 2);
        element = (ElementsEnum)sqlite3_column_int(statement, 3);
        strength = sqlite3_column_int(statement, 4);
        agility = sqlite3_column_int(statement, 5);
        intelligence = sqlite3_column_int(statement, 6);
        hpBase = sqlite3_column_int(statement, 7);
        manaBase = sqlite3_column_int(statement, 8);
        speedBase = sqlite3_column_int(statement, 9);
        evasionBase = sqlite3_column_int(statement, 10);
        staminaBase = sqlite3_column_int(statement, 11);
        meelePowerBase = sqlite3_column_int(statement, 12);
        magicPowerBase = sqlite3_column_int(statement, 13);
        meeleDefenseBase = sqlite3_column_int(statement, 14);
        magicDefenseBase = sqlite3_column_int(statement, 15);

        Heroes.emplace_back(id, name, combatType, element, strength, agility, intelligence, hpBase, manaBase, speedBase,
            evasionBase, staminaBase, meelePowerBase, magicPowerBase, meeleDefenseBase, magicDefenseBase);
    }

    disconnect(statement);
}

void Database::loadEnemiesFromDatabase()
{
    sqlite3* database = connect();

    if (database == NULL) {
        return;
    }

    int ret_code = 0;

    std::string query = "SELECT * FROM Enemies;";

    int id, strength, agility, intelligence, hpBase, manaBase, speedBase,
        evasionBase, staminaBase, meelePowerBase, magicPowerBase, meeleDefenseBase, magicDefenseBase;

    CombatTypesEnum combatType;

    ElementsEnum element;

    std::string name;

    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) != SQLITE_OK) {
        std::cout << "Error while executing the query: " << query << '\n';

        disconnect(statement);

        return;
    }

    while ((ret_code = sqlite3_step(statement)) == SQLITE_ROW) {
        id = sqlite3_column_int(statement, 0);
        name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
        combatType = (CombatTypesEnum)sqlite3_column_int(statement, 2);
        element = (ElementsEnum)sqlite3_column_int(statement, 3);
        strength = sqlite3_column_int(statement, 4);
        agility = sqlite3_column_int(statement, 5);
        intelligence = sqlite3_column_int(statement, 6);
        hpBase = sqlite3_column_int(statement, 7);
        manaBase = sqlite3_column_int(statement, 8);
        speedBase = sqlite3_column_int(statement, 9);
        evasionBase = sqlite3_column_int(statement, 10);
        staminaBase = sqlite3_column_int(statement, 11);
        meelePowerBase = sqlite3_column_int(statement, 12);
        magicPowerBase = sqlite3_column_int(statement, 13);
        meeleDefenseBase = sqlite3_column_int(statement, 14);
        magicDefenseBase = sqlite3_column_int(statement, 15);

        Enemies.emplace_back(id, name, combatType, element, strength, agility, intelligence, hpBase, manaBase, speedBase,
            evasionBase, staminaBase, meelePowerBase, magicPowerBase, meeleDefenseBase, magicDefenseBase);
    }

    disconnect(statement);
}
