#include "Database.h"

Database::Database()
{
    loadHeroesFromDatabase();
}

Hero Database::getAHero(int id)
{
    const Hero findHero = Heroes[id];

    return findHero;
}

void Database::listHeroes()
{
    cout << "+---------------------------+" << endl;
    cout << "| Display all Heroes        |" << endl;
    cout << "+---------------------------+" << endl;

    for (int i = 0; i < Heroes.size(); i++) {
        cout << "id: " << Heroes[i].Id << endl;
        cout << "name: " << Heroes[i].Name << endl;
        cout << "combatType: " << Heroes[i].CombatType << endl;
        cout << "element: " << Heroes[i].Element << endl;
        cout << "strength: " << Heroes[i].Strength << endl;
        cout << "agility: " << Heroes[i].Agility << endl;
        cout << "intelligence: " << Heroes[i].Intelligence << endl;
        cout << "hpBase: " << Heroes[i].HpBase << endl;
        cout << "manaBase: " << Heroes[i].ManaBase << endl;
        cout << "speedBase: " << Heroes[i].SpeedBase << endl;
        cout << "evasionBase: " << Heroes[i].EvasionBase << endl;
        cout << "staminaBase: " << Heroes[i].StaminaBase << endl;
        cout << "meelePowerBase: " << Heroes[i].MeelePowerBase << endl;
        cout << "magicPowerBase: " << Heroes[i].MagicPowerBase << endl;
        cout << "meeleDefenseBase: " << Heroes[i].MeeleDefenseBase << endl;
        cout << "magicDefenseBase: " << Heroes[i].MagicDefenseBase << endl;
        cout << "hpTotal: " << Heroes[i].HpTotal << endl;
        cout << "manaTotal: " << Heroes[i].ManaTotal << endl;
        cout << "speedTotal: " << Heroes[i].SpeedTotal << endl;
        cout << "evasionTotal: " << Heroes[i].EvasionTotal << endl;
        cout << "staminaTotal: " << Heroes[i].StaminaTotal << endl;
        cout << "meelePowerTotal: " << Heroes[i].MeelePowerTotal << endl;
        cout << "magicPowerTotal: " << Heroes[i].MagicPowerTotal << endl;
        cout << "meeleDefenseTotal: " << Heroes[i].MeeleDefenseTotal << endl;
        cout << "magicDefenseTotal: " << Heroes[i].MagicDefenseTotal << endl;
        cout << "-------------------------------" << endl << endl;
    }
}

void Database::loadHeroesFromDatabase()
{
    sqlite3* database = connect();

    if (database == NULL) {
        return;
    }

    int ret_code = 0;

    string query = "SELECT * FROM Heroes;";

    int id, strength, agility, intelligence, hpBase, manaBase, speedBase, 
        evasionBase, staminaBase, meelePowerBase, magicPowerBase, meeleDefenseBase, magicDefenseBase;

    CombatTypesEnum combatType;

    ElementsEnum element;

    string name;

    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) != SQLITE_OK) {
        cout << "Error while executing the query: " << query << endl;

        disconnect(statement);

        return;
    }

    while ((ret_code = sqlite3_step(statement)) == SQLITE_ROW) {
        id = sqlite3_column_int(statement, 0);
        name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
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
