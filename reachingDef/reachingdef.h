#include "program.h"
#include "basicblock.h"
#include "irclass.h"
#include <map>
#include <list>
#include <vector>
#include <iostream>
using namespace std;
class ReachingDefAna{
    
    map< operand*,list<instruction*> > dIList;
   map< instruction* , int > instBitTable;
    vector<int>  DestV;
    map <operand*,vector<int> > DestTable;
    public:
    void ComputeDestInstList(Program*);
    ReachingDefAna(){
    }

    void startReachingDefAna(Program*);
    ReachingDefAna(Program* pr){
        startReachingDefAna(pr);
    }
    bool isDefInst(opcodeenum op){
        if(op >= ld && op <= sub)
            return true;
        else
            return false;
    }

};
