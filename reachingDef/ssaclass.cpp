#include <list>
#include <map>
#include <iostream>
#include "irclass.h"
#include "table.h"
#include "ssaclass.h"
using namespace std;

int ssa_form :: get_reg_operandindex(operand& op){ //if operand of RHS is key in refering then returns
  map <int,int> ::iterator it;                     //its refering register index else creates new key in refering  
  int ind=op.get_data();
  it=refering.find(ind);
  if(it == refering.end()){
    refering[ind]=logical_reg_val;
    return logical_reg_val++;
  }else{
   return it->second;
   
 }

}
ssa_form :: ssa_form(program& p){
  int src_cnt,i;
  operand op;
  logical_reg_val=0;
  list <instruction> :: iterator endit=p.get_end_inst();
  for(list <instruction> :: iterator it=p.get_begin_inst();it!=endit;++it){//iterate through instructions
    instruction ir;
    ir.set_opcodeno(it->get_opcodeno());
    src_cnt=it->get_source_count();
    for(i=0;i<src_cnt;i++){//iterate through source operand
      op=it->get_source_operand(i);
      if(op.get_operandtype() == reg){
	operand op_reg=operand(reg,get_reg_operandindex(op));
	ir.add_source_operand(op_reg);
      }else{
	ir.add_source_operand(op);
      }
    }
    //add destination
    op=it->get_destination_operand();
    if(op.get_operandtype() ==reg){
      refering[op.get_data()]=logical_reg_val;
      op.set_data(logical_reg_val++);
    }
    ir.set_destination_operand(op);
    pm.add_instruction(ir);
  }
  
}
void ssa_form :: print_instruction(){
  pm.print_instruction();

}
