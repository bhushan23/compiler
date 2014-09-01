#include "reachingdef.h"
void ReachingDefAna::ComputeDestInstList(Program* pr){

    for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
        for( list<instruction*>::iterator instIt = (*it)->get_begin_inst(), instEnd = (*it)->get_end_inst(); instIt != instEnd; ++instIt){
            if( isDefInst((*instIt)->get_opcodeno())){
                /*operand* dest = (*instIt)->get_destination_operand();
                if( dIList.find(dest) == dIList.end() ){//Need to push list<insttruction*>
                    list<instruction*> tlist;
                    tlist.push_back(*instIt);
                     
                }else{

                }*/
                dIList[(*instIt)->get_destination_operand()].push_back(*instIt);

            }    
        } 
    }
int bitnumber = 0;
for(map<operand*,list<instruction*> >::iterator it = dIList.begin(),end=dIList.end(); it != end; ++it){
   //(it->first)->print_opcode();
   //cout<<"\n";
   list<instruction*> tlist = it->second;
   DestTable[(it->first)].push_back(tlist.size());//Total no. of definitions
 DestTable[(it->first)].push_back(bitnumber);//start bit no.
   for(list<instruction*>::iterator it = tlist.begin(), end = tlist.end(); it != end; ++it){
        //(*it)->print_instruction();
        //cout<<"\n";
        instBitTable[*it] = bitnumber++;
    }
DestTable[(it->first)].push_back(bitnumber-1);//end bit no.
  
   //cout<<"\n......";
}
}
void ReachingDefAna::startReachingDefAna(Program* pr){
    ComputeDestInstList(pr);

}
