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
        DataBase(){
            driver = get_driver_instance();
            con = driver->connect("localhost", "test", "test");
            con->setSchema("chimie");
        }
        ~DataBase() {
            delete con;
        }
        void exec(const char *query) const{
            try {
                sql::Statement *stmt = con->createStatement();
                stmt->execute(query);
                delete stmt;
            }catch(...) {
                std::cout<<"Could not execute query="<<query;
            }
        }

        sql::ResultSet* query(const char* query) const{
            try {
                sql::Statement *stmt = con->createStatement();
                sql::ResultSet *res = stmt->executeQuery(query);
                return res;
            }catch (...){
                std::cout<<"Could not execute query="<<query;
                return nullptr;
            }
        }

        void Initialize() const{
            this->exec("DROP TABLE IF EXISTS substante");
            this->exec("DROP TABLE IF EXISTS reactii");
            this->exec("CREATE TABLE `substante` (\n"
                       "\t`id` INT NOT NULL AUTO_INCREMENT,\n"
                       "\t`tip` varchar(256),\n"
                       "\t`nume` varchar(256) UNIQUE,\n"
                       "\t`FM` varchar(30) NOT NULL,\n"
                       "\t`FS` varchar(1000) NOT NULL,\n"
                       "\tPRIMARY KEY (`id`)\n"
                       ");");
            this->exec("CREATE TABLE `reactii` (\n"
                       "\t`id` INT NOT NULL AUTO_INCREMENT,\n"
                       "\t`tip` varchar(256),\n"
                       "\t`conditi` TEXT NOT NULL,\n"
                       "\t`reactant1` INT NOT NULL,\n"
                       "\t`reactant2` INT NOT NULL,\n"
                       "\t`produs1` INT NOT NULL,\n"
                       "\t`produs2` INT NOT NULL,\n"
                       "\tPRIMARY KEY (`id`)\n"
                       ");");
            this->exec("ALTER TABLE `Reactii` ADD CONSTRAINT `Reactii_fk0` FOREIGN KEY (`reactant1`) REFERENCES `Substante`(`id`);");
            this->exec("ALTER TABLE `Reactii` ADD CONSTRAINT `Reactii_fk1` FOREIGN KEY (`reactant2`) REFERENCES `Substante`(`id`);");
            this->exec("ALTER TABLE `Reactii` ADD CONSTRAINT `Reactii_fk2` FOREIGN KEY (`produs1`) REFERENCES `Substante`(`id`);");
            this->exec("ALTER TABLE `Reactii` ADD CONSTRAINT `Reactii_fk3` FOREIGN KEY (`produs2`) REFERENCES `Substante`(`id`);");
        }
};
const DataBase db;
#endif //CHEMESTRYDB_DATA_H
