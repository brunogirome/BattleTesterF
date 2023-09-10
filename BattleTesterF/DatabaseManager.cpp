#include "Databasemanager.h"

sqlite3* db;

bool connect()
{
    if (sqlite3_open("../Database/BattleTesterF.db", &db) != SQLITE_OK) {
        cout << "Error while connection to the database\n";

        return false;
    }

    return true;
}

void disconnect(sqlite3_stmt* statement) {
    sqlite3_finalize(statement);
    sqlite3_close(db);
}

bool getHeroes()
{
    if (!connect()) {
        return false;
    }

    sqlite3_stmt* statement;

    string query = "SELECT * FROM Heroes";

    string name;

    int ret_code = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) != SQLITE_OK) {
        cout << "Error while executing the query: " << query << endl;

        disconnect(statement);

        return false;
    }

    while ((ret_code = sqlite3_step(statement)) == SQLITE_ROW) {
        name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));

        cout << name << endl;
    }

    disconnect(statement);

    return true;
}
