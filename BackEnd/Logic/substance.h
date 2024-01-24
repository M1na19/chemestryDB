#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Atom{
    public:
        int id;
        string type;
        int maxTies;
        vector<int> ties;

        string serialize(){
            stringstream ss;
            ss<< to_string(id) << "-"<< type<< "-" << "[";
            for(auto &tie:ties){
                ss<<to_string(tie)<<",";
            }
            ss<< "]";
            return ss.str();
        }
        void deserialize(string str){
            stringstream ss(str);

            string idString;
            getline(ss,idString,'-');
            id=stoi(idString);

            getline(ss,type,'-');
            ss.ignore();

            string tieString;
            while(getline(ss,tieString,',') && tieString.find(']')==-1){
                ties.push_back(stoi(tieString));
            }
        }
};
class Substance{
    public:
        vector<Atom> atoms;
        string type;
        string serialize(){
            stringstream ss;
            ss<<type<<'{';
            int idx=0;
            for(auto &atom:atoms){
                ss<<atom.serialize()<< ';';
            }
            ss<<"}";
            return ss.str();
        }
        void deserialize(string str){
            stringstream ss(str);

            getline(ss,type,'{');

            string atomString;
            while(getline(ss,atomString,';') && atomString.find('}')==-1){
                Atom newAtom;
                newAtom.deserialize(atomString);
                atoms.push_back(newAtom);
            }
        }
};