#include "substance.h"
#include "../DataBase/substance.h"
#include <iostream>
int main(){
    Substance izobutan;
    izobutan.name="IzoButan";
    izobutan.type="Alcan";
    izobutan.atoms.push_back(*new Atom(0,"C",{1,4,5,6}));
    izobutan.atoms.push_back(*new Atom(1,"C",{0,2,3,7}));
    izobutan.atoms.push_back(*new Atom(2,"C",{1,8,9,10}));
    izobutan.atoms.push_back(*new Atom(3,"C",{1,11,12,13}));
    izobutan.atoms.push_back(*new Atom(4,"H",{0}));
    izobutan.atoms.push_back(*new Atom(5,"H",{0}));
    izobutan.atoms.push_back(*new Atom(6,"H",{0}));
    izobutan.atoms.push_back(*new Atom(7,"H",{1}));
    izobutan.atoms.push_back(*new Atom(8,"H",{2}));
    izobutan.atoms.push_back(*new Atom(9,"H",{2}));
    izobutan.atoms.push_back(*new Atom(10,"H",{2}));
    izobutan.atoms.push_back(*new Atom(11,"H",{3}));
    izobutan.atoms.push_back(*new Atom(12,"H",{3}));
    izobutan.atoms.push_back(*new Atom(13,"H",{3}));

    Substance butan;
    butan.type="Alcan";
    butan.name="Butan";
    butan.atoms.push_back(*new Atom(0,"C",{1,4,5,6}));
    butan.atoms.push_back(*new Atom(1,"C",{0,2,7,13}));
    butan.atoms.push_back(*new Atom(2,"C",{1,3,8,12}));
    butan.atoms.push_back(*new Atom(3,"C",{2,9,10,11}));
    butan.atoms.push_back(*new Atom(4,"H",{0}));
    butan.atoms.push_back(*new Atom(5,"H",{0}));
    butan.atoms.push_back(*new Atom(6,"H",{0}));
    butan.atoms.push_back(*new Atom(7,"H",{1}));
    butan.atoms.push_back(*new Atom(8,"H",{2}));
    butan.atoms.push_back(*new Atom(9,"H",{3}));
    butan.atoms.push_back(*new Atom(10,"H",{3}));
    butan.atoms.push_back(*new Atom(11,"H",{3}));
    butan.atoms.push_back(*new Atom(12,"H",{2}));
    butan.atoms.push_back(*new Atom(13,"H",{1}));

    SubstanceManager::addSubstance(butan.type,butan.getFM(),butan.serialize(),butan.name);
    SubstanceManager::addSubstance(izobutan.type,izobutan.getFM(),izobutan.serialize(),izobutan.name);
}