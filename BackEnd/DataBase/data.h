//
// Created by mihai on 23.01.2024.
//

#ifndef CHEMESTRYDB_DATA_H
#define CHEMESTRYDB_DATA_H

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class DataBase{
    private:
        sql::Driver *driver;
        sql::Connection *con;
    public:
        void Initialize(){
            driver = get_driver_instance();
            con = driver->connect("localhost", "test", "test");
            con->setSchema("chimie");
        }
        ~DataBase() {
            delete con;
        }
        void exec(char* query) {
            sql::Statement *stmt = con->createStatement();
            stmt->execute(query);
            delete stmt;
        }

        sql::ResultSet* query(char* query) {
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery(query);
            return res;
        }

        void createTables(){
        }
};

#endif //CHEMESTRYDB_DATA_H
