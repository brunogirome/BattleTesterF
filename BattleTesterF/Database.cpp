#include "Database.h"

Database::Database()
{
    loadHeroesFromDatabase();
}

void Database::listHeroes()
{
    for (int i = 0; i < Heroes.size(); i++) {
        cout << Heroes[i] << endl;
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

    string name;

    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) != SQLITE_OK) {
        cout << "Error while executing the query: " << query << endl;

        disconnect(statement);

        return;
    }

    while ((ret_code = sqlite3_step(statement)) == SQLITE_ROW) {
        name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));

        Heroes.push_back(name);
    }

    disconnect(statement);
}
