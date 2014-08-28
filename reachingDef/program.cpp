#include "program.h"
#include <list>
#include <iostream>
#include <fstream>
using namespace std;
list<BasicBlock*>::iterator Program::get_begin(){
    return basicBlock.begin();
}
list<BasicBlock*>::iterator Program::get_end(){
    return basicBlock.end();
}
void Program::print_program(){
    cout << "\n"; 
    for( list<BasicBlock*>::iterator it = basicBlock.begin(), end = basicBlock.end(); it != end; ++it){
        cout << (*it)->getBBLabel() << "-------Predecessor: ";
        (*it)->print_pred();
        cout << "; Successor ";
        (*it)->print_succ();
        cout << ";\n";
        (*it)->print_instruction();
        cout << "\n";
    }
}
BasicBlock* Program::GetBasicBlockFromLabel(string& label){
    BasicBlock* bb;
    if(mapBB.find(label) == mapBB.end()){//BB not present
        bb = new BasicBlock();
        basicBlock.push_back(bb);
        mapBB[label] = bb;
        bb->setBBLabel(label);
    }else{
        bb = mapBB[label];
    }
    return bb;

}
void Program::add_instruction(instruction* inst,BasicBlock* bb){
    string label = inst->getLabel();
    if(label.length() > 0){//this is instruction of BB 'label'
        //cout<<"\n  BB Present \n";
        BasicBlock* bB = GetBasicBlockFromLabel(label);    
        bB->add_instruction(inst);
        bB->setBBLabel(label);
    }else{
        // cout<<"\n  No label \n";
        label = inst->getLabelFromOperand(); 
        if( label.length() > 0 ){//Creates edge b/w 2 BB
            //cout<<"creating new BB";
            BasicBlock* nBB = GetBasicBlockFromLabel(label);        
            //add Pred Succ Info
            bb->pushSucc(nBB);
            nBB->pushPred(nBB);
        } 
        bb->add_instruction(inst);

    }

}

void Program::add_instruction(instruction* inst,instruction* inThis){
    add_instruction(inst,inThis->getParent()); 
}


void create_dot_file(ostream os){

}
