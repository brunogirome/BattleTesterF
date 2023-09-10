#pragma once

#include <iostream>
#include <string>

#include <sqlite3.h>

using namespace std;

sqlite3* connect();

void disconnect(sqlite3_stmt* statement);