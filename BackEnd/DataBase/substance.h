//
// Created by mihai on 27.01.2024.
//

#ifndef CHEMESTRYDB_SUBSTANCE_H
#define CHEMESTRYDB_SUBSTANCE_H

#include "data.h"
#include <string>
#include <sstream>

class SubstanceManager{
    public:
        static void addSubstance(std::string type,std::string FM,std::string FS,std::string name){
            std::stringstream ss;
            ss<<"INSERT INTO substante(tip,nume,FM,FS) VALUES('"<<type<<"','"<<name<<"','"<<FM<<"','"<<FS<<"')";
            db.exec(ss.str().c_str());
        }
        static void removeSubstanceById(int id){
            std::stringstream ss;
            ss<<"DELETE FROM substante WHERE id="<<id;
            db.exec(ss.str().c_str());
        }
        static void selectAtomByStructure(){
            //to do
        }
};

#endif //CHEMESTRYDB_SUBSTANCE_H
