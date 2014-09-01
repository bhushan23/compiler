#include "reachingdef.h"
void ReachingDefAna::ComputeDestInstList(){

    for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
        for( list<instruction*>::iterator instIt = (*it)->get_begin_inst(), instEnd = (*it)->get_end_inst(); instIt != instEnd; ++instIt){
            if( isDefInst((*instIt)->get_opcodeno())){
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
            instBitTable[*it] = bitnumber;
            bitInstTable[bitnumber] = *it;
            ++bitnumber;
        }
        DestTable[(it->first)].push_back(bitnumber-1);//end bit no.

        //cout<<"\n......";
    }
    //Initialize
    for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
        (*it)->bitResize(bitnumber);
        (*it)->initBitToZero(bitnumber);
    } 



}
void ReachingDefAna::ComputeGenKill(){

    for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
        for( list<instruction*>::reverse_iterator instIt = (*it)->get_rbegin_inst(), instEnd = (*it)->get_rend_inst(); instIt != instEnd; ++instIt){
            //cout<<"\n::";
            //(*instIt)->print_instruction();
            if( isDefInst((*instIt)->get_opcodeno())){

                operand* op = (*instIt)->get_destination_operand();
                if( (*it)->isAlreadyKilled(DestTable[op][1],DestTable[op][2]) ){
                    int bin = instBitTable[(*instIt)];
                    (*it)->setGen(bin,DestTable[op][1],DestTable[op][2]);
                }
            }
        }
    }
printProgram();
}
void ReachingDefAna::startReachingDefAna(){
    ComputeDestInstList();
    ComputeGenKill();
}
void ReachingDefAna::printBitSet(bitvec& bv){
    for(int i = 0; i < bv.getSize(); ++i){
       if(bv[i] == 1){
            bitInstTable[i]->print_instruction();
            cout<<" ,";        
       } 
    }
}
void ReachingDefAna::printProgram(){
    cout << "\n";

    for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
        bitvec gen = (*it)->getGen();
        bitvec kill = (*it)->getKill(); 
        cout<<"GEN:{ ";
        printBitSet(gen);
        cout<<" }\nKILL:{ ";
        printBitSet(kill);  
       cout<<" }\n"; 
        cout << (*it)->getBBLabel() << "-------Predecessor: ";
        (*it)->print_pred();
        cout << "; Successor ";
        (*it)->print_succ();
        cout << ";\n";
        (*it)->print_instruction();
        cout << "\n";
    }
}



