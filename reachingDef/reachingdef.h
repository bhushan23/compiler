#include "program.h"
#include "basicblock.h"
#include "irclass.h"
#include <map>
#include <list>
#include <vector>
#include <iostream>
using namespace std;
class ReachingDefAna{
    Program* pr;
    map< operand*,list<instruction*> > dIList;
   map< instruction* , int > instBitTable;
   map<int, instruction*> bitInstTable;
    map <operand*,vector<int> > DestTable;
    public:
    void ComputeDestInstList();
    ReachingDefAna(){
    }

    void startReachingDefAna();
    ReachingDefAna(Program* pr){
        this->pr = pr;
        startReachingDefAna();
    }
    bool isDefInst(opcodeenum op){
        if(op >= ld && op <= sub)
            return true;
        else
            return false;
    }
    void ComputeGenKill();
    void printProgram();
    void printBitSet(bitvec&);
    void printBitSet(bitvec&,ofstream&);
    void printBitSet(string&,bitvec&);
    void ComputeINOUT();
    void printBB(BasicBlock*);
    void printBB(BasicBlock*,ofstream&);
    void createDotFile(string&);
};

