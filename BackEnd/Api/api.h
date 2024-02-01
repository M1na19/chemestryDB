#ifndef CHEMESTRYDB_API_H
#define CHEMESTRYDB_API_H

#include "crow.h"
#include "../Logic/substance.h"
#include "../DataBase/substance.h"
using namespace std;

void Initialize() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/hello")(
    []() {
        return "Hello World";
    });

    //Find substance by structure
    CROW_ROUTE(app,"/find").methods(crow::HTTPMethod::POST)(
    [](const crow::request& req){
        string stringMatrix=req.get_body_params().get("data");

        crow::response res;
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
        vector<Substance> sbsts=SubstanceManager::selectSubstancesByFM(sent.getFM());

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
    app.port(2000).multithreaded().run();
}



#endif //CHEMESTRYDB_API_H
