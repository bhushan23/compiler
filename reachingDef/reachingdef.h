#include "program.h"
#include "basicblock.h"
#include "irclass.h"
#include <map>
#include <list>
using namespace std;
class ReachingDefAna{
    map< string,list<instruction*> > destInstList;
    public:
    void ComputeDestInstList(Program*);
    ReachingDefAna(){
    }

    void startReachingDefAna(Program*);
    ReachingDefAna(Program* pr){
        startReachingDefAna(pr);
    }

};
