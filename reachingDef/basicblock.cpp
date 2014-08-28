#include "basicblock.h"
#include <list>
using namespace std;
//#include "irclass.h"
list <instruction*> :: iterator BasicBlock :: get_begin_inst(){
    return inst.begin();
}

list <instruction*> :: iterator BasicBlock :: get_end_inst(){
    return inst.end();
}


void BasicBlock::print_pred(){
    for(list <BasicBlock*> :: iterator it= pred.begin() ;it != pred.end();++it){
        cout << (*it)->getBBLabel() << " ";
    }
}
void BasicBlock::print_succ(){
    for(list <BasicBlock*> :: iterator it= succ.begin() ;it != succ.end();++it){
        cout << (*it)->getBBLabel() << " ";
    }
}

void BasicBlock :: print_instruction(){
    for(list <instruction*> :: iterator it=inst.begin();it != inst.end();++it){
        (*it)->print_instruction();
        cout<<"\n";
    }
}



/*void BasicBlock ::  add_instruction(instruction* in){
  inst.push_back(in);
  }*/
void BasicBlock::pushSucc(BasicBlock* b){
succ.push_back(b);
}
void BasicBlock::pushPred(BasicBlock* b){
pred.push_back(b);
}
int BasicBlock :: find_lhs(operand& opcmp){
    list <instruction*> :: iterator it;
    operand op;
    int i=0;
    for( it = inst.begin(); it != inst.end(); ++it,++i){
        op=(*it)->get_destination_operand();
        if(op.get_operandtype() == opcmp.get_operandtype() && op.get_data() == opcmp.get_data())
            return i;
    }
    return i;
}

