#ifndef CHEMESTRYDB_API_H
#define CHEMESTRYDB_API_H

#include "crow.h"
#include "../Logic/substance.h"
#include "../DataBase/substance.h"
#include "../DataBase/notes.h"
#include "notes.h"

using namespace std;

void Initialize() {
    crow::SimpleApp app;

    CROW_ROUTE(app,"/").methods(crow::HTTPMethod::GET)(
    [](){
        crow::response res;
        res.code=200;
        res.set_static_file_info("./FrontEnd/main.html");
        return res;
    });
    CROW_ROUTE(app,"/CSS/<string>").methods(crow::HTTPMethod::GET)(
            [](const std::string& file){
                std::stringstream ss;
                ss<<"./FrontEnd/CSS/";
                ss<<file;

                crow::response res;
                res.code=200;
                res.set_static_file_info(ss.str());
                return res;
            });
    CROW_ROUTE(app,"/JS/<string>").methods(crow::HTTPMethod::GET)(
            [](const std::string& file){
                std::stringstream ss;
                ss<<"./FrontEnd/JS/";
                ss<<file;

                crow::response res;
                res.code=200;
                res.set_static_file_info(ss.str());
                return res;
            });
    CROW_ROUTE(app,"/Atomi/<string>").methods(crow::HTTPMethod::GET)(
            [](const std::string& file){
                std::stringstream ss;
                ss<<"./FrontEnd/Atomi/";
                ss<<file;

                crow::response res;
                res.code=200;
                res.set_static_file_info(ss.str());
                return res;
            });




    CROW_ROUTE(app, "/hello")(
    []() {
        return "Hello World";
    });
    CROW_ROUTE(app,"/add").methods(crow::HTTPMethod::POST)(
        [](const crow::request& req){
            crow::response res;
            if(!req.get_body_params().get("name") || !req.get_body_params().get("type") || !req.get_body_params().get("struct")){
                res.code=400;
                res.write("Bad Parameters");
                return res;
            }

            string name = req.get_body_params().get("name");
            string tip = req.get_body_params().get("type");
            string stringMatrix = req.get_body_params().get("struct");

            //parse string
            Substance sent;
            try{
                sent.deserialize(stringMatrix);
            }catch(const exception& e){
                res.code=400;
                res.write("Could not parse matrix");
                cout<<e.what()<<"\n";
                return res;
            }
            //validate
            if(!sent.validate()){
                res.code=400;
                res.write("Substance is not valid");
                return res;
            }
            //check if name is taken
            if(data::SubstanceManager::checkForName(name)!=-1){
                res.code=400;
                res.write("Name is taken");
                return res;
            }

            try {
                data::SubstanceManager::addSubstance(tip, sent.getFM(), sent.serialize(), name);
                data::NotesManager::createNotesTable(name);
            }catch(const exception& e){
                res.code=400;
                res.write("Could not put substance");
                cout<<e.what()<<"\n";
                return res;
            }
            res.code=200;
            return res;
        });
    //Find substance by structure
    CROW_ROUTE(app,"/find").methods(crow::HTTPMethod::POST)(
    [](const crow::request& req){
        crow::response res;
        if(!req.get_body_params().get("struct")){
            res.code=400;
            res.write("Bad Parameters");
            return res;
        }
        string stringMatrix=req.get_body_params().get("struct");


        //parse string

        Substance sent;
        try{
            sent.deserialize(stringMatrix);
        }catch(const exception& e){
            res.code=400;
            res.write("Could not parse matrix");
            cout<<e.what()<<"\n";
            return res;
        }
        //validate
        if(!sent.validate()){
            res.code=400;
            res.write("Substance is not valid");
            return res;
        }
        //check db
        vector<Substance> sbsts=data::SubstanceManager::selectSubstancesByFM(sent.getFM());

        for(auto &sbst:sbsts){
            if(sent.same(sbst)){
                res.code=200;
                res.write(sbst.name);
                return res;
            }
        }
        res.code=200;
        res.write("Could not find");
        return res;
    });
    CROW_ROUTE(app,"/remove").methods(crow::HTTPMethod::DELETE)(
        [](const crow::request& req) {
            crow::response res;
            if(!req.get_body_params().get("name")){
                res.code=400;
                res.write("Bad Parameters");
                return res;
            }

            string name=req.get_body_params().get("name");

            try {
                int id=data::SubstanceManager::checkForName(name);
                if(id==-1){
                    res.code=400;
                    res.write("Substance does not exist");
                }else{
                    data::SubstanceManager::removeSubstanceById(id);
                    data::NotesManager::deleteNotesTable(name);
                    res.code=200;
                }
            }catch (...){
                res.code=500;
                res.write("Could not delete substance");
            }
            return res;
        });
    api::NotesAPI(app);
    app.port(2000).multithreaded().run();
}



#endif //CHEMESTRYDB_API_H
