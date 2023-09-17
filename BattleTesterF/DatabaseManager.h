#pragma once

#include <iostream>
#include <string>

#include <sqlite3.h>

sqlite3* connect();

void disconnect(sqlite3_stmt* statement);