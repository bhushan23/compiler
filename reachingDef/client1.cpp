//#include "irclass.h"
#include <iostream>
#include "program.h"
#include "basicblock.h"
#include "reachingdef.h"
using namespace std;


int main(){
    BasicBlock* entryBB = new BasicBlock();
    Program* program= new Program(entryBB);
    // operand* a,b,c;
    //    operand* b2,b3,b4,b5;
    operand* a = new operand(sym,"a");
    operand* b = new operand(sym,"b");
    operand* c = new operand(sym,"c");
    operand* d = new operand(sym,"d");

    operand* b2 = new operand(oplabel,"n2");
    operand* b3 = new operand(oplabel,"n3");
    operand* b4 = new operand(oplabel,"n4");
    operand* b5 = new operand(oplabel,"n5");


    instruction* irs1 = new instruction(jmp,b2);//,ew instruction(mov,op0,op4,"entry");
    instruction* irs2 = new instruction(add,c,a,b,"n2");
    instruction* irs3 = new instruction(jmpe,a,b,b3);
    instruction* irs4 = new instruction(jmp,b4);
    instruction* irs5 = new instruction(add,d,b,c,"n3");
    instruction* irs6 = new instruction(jmpe,d,b,b4);
    instruction* irs7 = new instruction(jmp,b5);
    instruction* irs8 = new instruction(jmpe,d,b,b2,"n4");
    instruction* irs9 = new instruction(jmp,b5);
    //instruction* irs9a = new instruction(jmp,b2);

    instruction* irs10 = new instruction(add,c,a,b,"n5");
    instruction* irs11 =  new instruction(jmp,b4);
    program->add_instruction(irs1,entryBB);  
    program->add_instruction(irs2,irs1);
    program->add_instruction(irs3,irs2); 
    program->add_instruction(irs4,irs3);
    program->add_instruction(irs5,irs4);
    program->add_instruction(irs6,irs5);
    program->add_instruction(irs7,irs6);
    program->add_instruction(irs8,irs7);
    program->add_instruction(irs9,irs8);
    program->add_instruction(irs10,irs9);
    program->add_instruction(irs11,irs10);
    //program->add_instruction(irs9a,irs9);
    cout<<"INPUT PROGRAM\n";
    program->print_program();
    cout<<"Reaching Def Analysis \n";
    ReachingDefAna* ra = new ReachingDefAna(program,0);
    ReachingDefAna* ra1 = new ReachingDefAna(program,1);
    
    return 0;
}
