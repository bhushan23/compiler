//#include "irclass.h"
#include <iostream>
#include "program.h"
#include "basicblock.h"
#include "reachingdef.h"
using namespace std;


int main(){
    BasicBlock* entryBB = new BasicBlock();
    //operand *op[5],*oplab[5];
    //instruction ir[6];
    Program* program= new Program();

    operand* op0= new operand(reg,"r0");
    operand* op1= new operand(reg,"r1");
    operand* op2= new operand(reg,"r2");
    operand* op3= new operand(sym,"A");
    operand* op4= new operand(con,5);
    operand* oplab0 = new operand(oplabel,"BB1");
    operand* oplab1 = new operand(oplabel,"BB2");
    instruction* irs1 = new instruction(mov,op0,op4,"entry");
    instruction* irs1a = new instruction(ld,op1,op3);
    instruction* irs2 = new instruction(mov,op2,op0);
    instruction* irs3 = new instruction(jmpe,op2,op1,oplab0);
    instruction* irs4 = new instruction(add,op0,op1,"BB1");
    instruction* irs5 = new instruction(add,op0,op0,op1);
    instruction* irs6 = new instruction(st,op3,op0);
    instruction* irj = new instruction(jmp,oplab1);
    instruction* irj1 = new instruction(add,op0,op1,"BB2");

    program->add_instruction(irs1,entryBB);  
    program->add_instruction(irs1a,irs1);
    program->add_instruction(irs2,irs1a);
    program->add_instruction(irs3,irs2); 
    program->add_instruction(irs4,irs3);
    // (irs5->getParent())->add_instruction(irj);
    program->add_instruction(irs5,irs4);
    program->add_instruction(irs6,irs5);
    program->add_instruction(irj,irs6);
    program->add_instruction(irj1,irj);
    irs4->set_opcodeno(sub);
    /*
       instruction& irs5 = program->add_instruction(instruction(ld,op[0],op[3]));
       instruction& irs1 = program->add_instruction(instruction(ld,op[1],op[4]));
       instruction& irs3 = program->add_instruction(instruction(add,op[2],op[1],op[0]));
       instruction& irs6 = program->add_instruction(instruction(st,op[3],op[2]));
       */
    // entryBB->print_instruction();
    irs6->set_opcodeno(ld);
    //entryBB->print_instruction();

    program->print_program();
    ReachingDefAna* ra = new ReachingDefAna(program);
    return 0;
}
