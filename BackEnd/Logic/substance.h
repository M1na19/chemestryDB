#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class Atom{
    public:
        int id;
        string name;
        vector<int> ties;
        Atom(){id=0;name="";}
        Atom(int id,string name,vector<int> ties){
            this->id=id;
            this->name=name;
            this->ties=ties;
        }

        string serialize(){
            stringstream ss;
            ss<< to_string(id) << "-"<< name<< "-" << "[";
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

            getline(ss,name,'-');
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
        vector<Atom*> getNeighbours(int id){
            vector<Atom*> neigh;
            for(auto &ties:atoms[id].ties){
                neigh.push_back(&atoms[ties]);
            }
            return neigh;
        }

        bool same(Substance& x){
            int equivalent=0;
            map<string,int> ties1;
            map<string,int> ties2;

            vector<bool> used(x.atoms.size(),false);

            int idx1=0;
            for(auto &atomA:atoms){
                for(auto &neigh: getNeighbours(idx1)){
                    ties1[neigh->name]++;
                }
                int idx2=0;
                for(auto atomB:x.atoms){
                    if(!used[idx2] && atomA.name==atomB.name){
                        for(auto &neigh: x.getNeighbours(idx2)){
                            ties2[neigh->name]++;
                        }
                        for(auto& pair:ties1){
                            if(pair.second==ties2[pair.first]) {
                                ties2.erase(pair.first);
                            }else{
                                break;
                            }
                        }
                        if(ties2.empty()) {
                            equivalent++;
                            used[idx2] = true;
                            break;
                        }else{
                            ties2.clear();
                        }
                    }
                    idx2++;
                }
                idx1++;
                ties1.clear();
            }
            if(equivalent==x.atoms.size() && equivalent==atoms.size()){
                return true;
            }else{
                return false;
            }
        }
};