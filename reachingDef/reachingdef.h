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

    void ReachingDefAnaIterative();
    void ReachingDefAnaWtList();
    ReachingDefAna(Program* pr,int analysisType){
        this->pr = pr;
        switch(analysisType){
            case 0:
                ReachingDefAnaIterative();
                break;
            case 1:
                ReachingDefAnaWtList();
                break;
        }
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
        void InitINOUT();
        void printBitSet(bitvec&,ofstream&);
        void printBitSet(string&,bitvec&);
        void ComputeINOUTIterative();
        void ComputeINOUTWtList();
        void printBB(BasicBlock*);
        void printBB(BasicBlock*,ofstream&);
        void createDotFile(string&);
    };

