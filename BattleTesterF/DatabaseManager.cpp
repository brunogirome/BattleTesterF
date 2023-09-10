#include "Databasemanager.h"

sqlite3* db;

sqlite3* connect()
{
    if (sqlite3_open("../Database/BattleTesterF.db", &db) != SQLITE_OK) {
        cout << "Error while connection to the database\n";

        return NULL;
    }

    return db;
}

void disconnect(sqlite3_stmt* statement) 
{
    sqlite3_finalize(statement);
    sqlite3_close(db);
}
