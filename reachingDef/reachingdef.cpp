#include "reachingdef.h"
#include <queue>
#include <iostream>
#include <ctype.h>
#include <fstream>
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
void ReachingDefAna::ComputeINOUT(){
    BasicBlock* entry = *pr->get_begin();
    bool changed = true;
    int i = 0;
 string ts("Iteration");
            
    do{
        queue <BasicBlock*> toVisit;    
        toVisit.push(entry);
        cout<<"## Iteration "<<i++<<" ##\n";

        while(!toVisit.empty()){
            BasicBlock* cBB = toVisit.front();
            toVisit.pop();
            for(list<BasicBlock*>::iterator it = cBB->get_begin_succ(), end = cBB->get_end_succ(); it != end; ++it){
                toVisit.push(*it);
            }
            bitvec in = cBB->getIn();
            bitvec out = cBB->getOut();
            bitvec tin(in.getSize()); 
            bitvec tout(out.getSize());
            for(list<BasicBlock*>::iterator pit = cBB->get_begin_pred(), pend = cBB->get_end_pred(); pit != pend; ++pit){
                tin = tin | (*pit)->getOut();
            }
           tout = tin - cBB->getKill();
            tout = tout | cBB->getGen();
            if( (in == tin) && (out == tout) )
                changed = false;
            else{
                changed = true;
                cBB->setIn(tin);
                cBB->setOut(tout);
            }
            printBB(cBB);
        } 
    ts.append("1");
   createDotFile(ts);
        
    }while(changed);

}
void ReachingDefAna::startReachingDefAna(){
    ComputeDestInstList();
    ComputeGenKill();
    ComputeINOUT();
    string finaldot ("FinalIt");    
    createDotFile(finaldot);
}
void ReachingDefAna::printBitSet(bitvec& bv){
    for(int i = 0; i < bv.getSize(); ++i){
        if(bv[i] == 1){
            bitInstTable[i]->print_instruction();
            cout<<" ,";        
        } 
    }
}

void ReachingDefAna::printBitSet(bitvec& bv,ofstream& cout){
    for(int i = 0; i < bv.getSize(); ++i){
        if(bv[i] == 1){
            bitInstTable[i]->print_instruction(cout);
            cout<<" ,";        
        } 
    }
}
void ReachingDefAna::printBitSet(string& st,bitvec& bv){
    cout<<st<<" {";
    printBitSet(bv);
}
void ReachingDefAna::printProgram(){
    cout << "\n";

    for( list<BasicBlock*>::iterator it = pr->get_begin(), end = pr->get_end(); it != end; ++it){
        printBB(*it);       
    }
}
void ReachingDefAna::printBB(BasicBlock* it){
    cout<<"IN:{ ";
    bitvec in = it->getIn();
    printBitSet(in);
    cout<<"\nOUT:{ ";
    bitvec out =  it->getOut();
    printBitSet(out);
    bitvec gen = it->getGen();
    bitvec kill = it->getKill(); 
    cout<<"\nGEN:{ ";
    printBitSet(gen);
    cout<<" }\nKILL:{ ";
    printBitSet(kill);  
    cout<<" }\n"; 
    cout <<it->getBBLabel() << "-------Predecessor: ";
    it->print_pred();
    cout << "; Successor ";
    it->print_succ();
    cout << ";\n";
    it->print_instruction();
    cout << "\n";

}
void ReachingDefAna::printBB(BasicBlock* it,ofstream& cout){
    cout<<"IN: ";
    bitvec in = it->getIn();
    printBitSet(in,cout);
    cout<<"|{OUT: ";
    bitvec out =  it->getOut();
    printBitSet(out,cout);
    bitvec gen = it->getGen();
    bitvec kill = it->getKill(); 
    cout<<"}|{GEN: ";
    printBitSet(gen,cout);
    cout<<"}|{KILL: ";
    printBitSet(kill,cout);  
    cout<<"}|{"; 

}


void ReachingDefAna::createDotFile(string& name){
    std::string Filename = "cfg." + name + ".dot";
    ofstream ost;
    ost.open(Filename.c_str());
    BasicBlock* succN;
    ost <<"digraph \"CFG for " << name << "' function\" {\n label=\"CFG for \";\n";
    for (list<BasicBlock*>::iterator it = pr->get_begin(), bbie = pr->get_end(); it != bbie; ++it){
        BasicBlock* BB = *it;
        ost << "\nNode" << BB << " [shape=record,label=\"{";
        printBB(BB,ost);
        for (list<instruction*>::iterator instit = BB->get_begin_inst(), instend = BB->get_end_inst(); instit != instend; ++instit) {
            ost << "\\l";
            //it->print_instruction(ost);
            //ost << (*instit)->get_opcodeno();
            (*instit)->print_instruction(ost);

        }
       ost << "}}\"];";
            for (list<BasicBlock*>::iterator SI = BB->get_begin_succ(), E = BB->get_end_succ(); SI != E;  ++SI) {
                succN = *SI;
                ost << "\n";
                ost <<"Node" << BB <<" -> "<<"Node" << succN <<";";
            }
        }


    ost << "}\n";

}

