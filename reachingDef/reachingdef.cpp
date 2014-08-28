#include "reachingdef.h"
void ReachingDefAna::ComputeDestInstList(Program* pr){

 for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
         for( list<instruction*>::iterator instIt = (*it)->get_begin_inst(), instEnd = (*it)->get_end_inst(); instIt != instEnd; ++instIt){
            
         }   
 
 }

}
void ReachingDefAna::startReachingDefAna(Program* pr){
    ComputeDestInstList(pr);
}
