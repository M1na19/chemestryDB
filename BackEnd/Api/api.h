#ifndef CHEMESTRYDB_API_H
#define CHEMESTRYDB_API_H
#include "crow.h"
#include "../DataBase/data.h"
#include "../Logic/substance.h"
void Initialize() {
    DataBase db;
    db.Initialize();
    db.createTables();
    crow::SimpleApp app;

    CROW_ROUTE(app, "/hello")(
    []() {
        return "Hello World";
    });
    app.port(2000).multithreaded().run();
}



#endif //CHEMESTRYDB_API_H
