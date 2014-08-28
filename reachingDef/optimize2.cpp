#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include <climits>
#include "optimize.h"
using namespace std;

/* you can add operand opcodeenum
 * which should not be removed by optimizer function
 * question is should i expose this function in .h ?
 */
bool roptimizer :: removable_opcode(opcodeenum opcode){
  switch( opcode  ){
  case ld:
    return false;
    break;
  case st:
    return false;
    break;
  default:
    return true;
    break;
  }
}

/*
 * This function takes input program in SSA FORM
 * Starts iterating from last instruction to begining 
 * If Instruction is removable instruction is removed
 * Otherwise rhs count of its source operand is incremented by 1
 */
void roptimizer :: start_optimize( program& p ){
  
  operand op;
  int instNo=0,src_cnt,i,j,len,tmpi;
  int psize = p.get_len();
  list <instruction> :: iterator rbeg = p.get_begin_inst();
  list <instruction> :: iterator it = p.get_end_inst();
  list <instruction> :: iterator inc_it;
  operand tmpop;
  vector <int> rhs_cnt(len,0);
  
  len = p.get_len();
  
  while(len--){
    --it;
    src_cnt=it->get_source_count();
   
    if( removable_opcode( it->get_opcodeno() ) && rhs_cnt[len] == 0 ){
      it= p.remove_instruction(it);//remove instruction
    }else{
      for(int i = 0; i < src_cnt; ++i){//increment source operand rhs_count
	tmpop=it-> get_source_operand(i);
	tmpi=p.find_lhs(tmpop);
	if(tmpi < len)
	  rhs_cnt[tmpi]++;
      }
    }
  }
}



