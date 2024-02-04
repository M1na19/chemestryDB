//
// Created by mihai on 27.01.2024.
//

#ifndef DB_SUBSTANCE_H
#define DB_SUBSTANCE_H

#include "data.h"
#include <string>
#include <sstream>
namespace data {
    class SubstanceManager {
    public:
        static int checkForName(const std::string &name) {
            std::stringstream ss;
            ss << "SELECT id FROM substante WHERE nume='" << name << "'";
            const auto st = ss.str();
            auto results = db.query(ss.str().c_str());
            if (results->next()) {
                return results->getInt("id");
            } else {
                return -1;
            }
        }

        static void addSubstance(std::string type, std::string FM, std::string FS, std::string name) {
            std::stringstream ss;
            ss << "INSERT INTO substante(tip,nume,FM,FS) VALUES('" << type << "','" << name << "','" << FM << "','"
               << FS << "')";
            db.exec(ss.str().c_str());
        }

        static void removeSubstanceById(const int &id) {
            std::stringstream ss;
            ss << "DELETE FROM substante WHERE id=" << id;
            db.exec(ss.str().c_str());
        }

        static vector<Substance> selectSubstancesByFM(const std::string &FM) {
            vector<Substance> sbsts;

            std::stringstream ss;
            ss << "SELECT tip,nume,FS FROM substante WHERE FM='" << FM << "'";
            auto check = ss.str();
            auto results = db.query(ss.str().c_str());
            while (results->next()) {
                Substance sbst;
                sbst.type = results->getString("tip");
                sbst.name = results->getString("nume");
                sbst.deserialize(results->getString("FS"));
                sbsts.push_back(sbst);
            }
            return sbsts;
        }
    };
}
#endif //DB_SUBSTANCE_H
