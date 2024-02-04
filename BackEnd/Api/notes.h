//
// Created by mihai on 03.02.2024.
//

#ifndef API_NOTES_H
#define API_NOTES_H

#include "crow.h"
#include "../DataBase/notes.h"
#include "../DataBase/substance.h"
namespace api{
    void NotesAPI(crow::SimpleApp& app){
        CROW_ROUTE(app,"/addNote").methods(crow::HTTPMethod::POST)(
            [](const crow::request& req){
                crow::response res;
                if(!req.get_body_params().get("substance") || !req.get_body_params().get("type") || !req.get_body_params().get("text")){
                    res.code=400;
                    res.write("Bad Parameters");
                    return res;
                }
                std::string name=req.get_body_params().get("substance");
                std::string tip=req.get_body_params().get("type");
                std::string text=req.get_body_params().get("text");

                //check if substance is in db
                if(data::SubstanceManager::checkForName(name)==-1){
                    res.code=400;
                    res.write("Substance does not exist");
                    return res;
                }
                try{
                    data::NotesManager::addNote(name,tip,text);
                    res.code=200;
                    return res;
                }catch(...) {
                    res.code=500;
                    res.write("Could not upload note");
                    return res;
                }
            });
        CROW_ROUTE(app,"/getNotes").methods(crow::HTTPMethod::GET)(
        [](const crow::request& req){
            crow::response res;
            if(!req.url_params.get("substance")){
                res.code=400;
                res.write("Bad Parameters");
                return res;
            }
            std::string name=req.url_params.get("substance");

            //check if substance is in db
            if(data::SubstanceManager::checkForName(name)==-1){
                res.code=400;
                res.write("Substance does not exist");
                return res;
            }
            try{
                auto notes=data::NotesManager::getNotes(name);
                std::stringstream data;
                for(auto& note:notes){
                    data<<note.index<<" "<<note.type<<" "<<note.text<<'\n';
                }
                res.code=200;
                res.write(data.str());
                return res;
            }catch(...){
                res.code=500;
                res.write("Could not parse notes");
                return res;
            }
        });
        CROW_ROUTE(app,"/removeNote").methods(crow::HTTPMethod::DELETE)(
                [](const crow::request& req){
                    crow::response res;
                    if(!req.get_body_params().get("substance") || !req.get_body_params().get("id")){
                        res.code=400;
                        res.write("Bad Parameters");
                        return res;
                    }
                    std::string name=req.get_body_params().get("substance");
                    int id=0;
                    try {
                        id = stoi(req.get_body_params().get("id"));
                    }catch(...){
                        res.code=400;
                        res.write("ID is not integer");
                        return res;
                    }

                    //check if substance is in db
                    if(data::SubstanceManager::checkForName(name)==-1){
                        res.code=400;
                        res.write("Substance does not exist");
                        return res;
                    }
                    try{
                        data::NotesManager::removeNote(name,id);
                        res.code=200;
                        return res;
                    }catch(...){
                        res.code=500;
                        res.write("Could not remove note");
                        return res;
                    }
                });
    }
}
#endif //API_NOTES_H
