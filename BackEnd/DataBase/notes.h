//
// Created by mihai on 03.02.2024.
//

#ifndef DB_NOTES_H
#define DB_NOTES_H

#include "data.h"
#include <sstream>
#include <vector>
namespace data {
    class Note {
    public:
        int index = 0;
        std::string type;
        std::string text;
    };

    class NotesManager {
    private:
        static void strip(std::string &s) {
            for (char &c: s) {
                if (isalnum(c) == false) {
                    c = '_';
                }
            }
        }

    public:
        static void createNotesTable(std::string name) {
            strip(name);
            std::stringstream ss;
            ss << "CREATE TABLE `" << name << "` (\n"
                                              "\t`id` INT NOT NULL AUTO_INCREMENT,\n"
                                              "\t`tip` varchar(256),\n"
                                              "\t`note` text,\n"
                                              "\tPRIMARY KEY (`id`)\n"
                                              ");";
            db.exec(ss.str().c_str());
        }

        static void deleteNotesTable(std::string name) {
            strip(name);
            std::stringstream ss;
            ss << "DROP TABLE IF EXISTS `" << name << "`";
            db.exec(ss.str().c_str());
        }

        static std::vector<Note> getNotes(std::string name) {

            strip(name);

            std::vector<Note> nts;
            std::stringstream ss;
            ss << "SELECT id,tip,note FROM " << name;
            auto results = db.query(ss.str().c_str());

            while (results->next()) {
                Note nou;
                nou.index = results->getInt("id");
                nou.type = results->getString("tip");
                nou.text = results->getString("note");
                nts.push_back(nou);
            }
            return nts;
        }

        static void addNote(std::string name, const std::string &type, const std::string &note) {
            strip(name);

            std::stringstream ss;
            ss << "INSERT INTO " << name << "(tip,note) VALUES('" << type << "','" << note << "')";
            db.exec(ss.str().c_str());
        }

        static void removeNote(std::string name, const int &id) {
            strip(name);

            std::stringstream ss;
            ss << "DELETE FROM " << name << " WHERE id=" << id;
            db.exec(ss.str().c_str());
        }

    };
}



#endif //DB_NOTES_H
