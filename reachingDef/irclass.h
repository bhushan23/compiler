#ifndef IRCLASS_H
#define IRCLASS_H
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include "basicblock.h"
using namespace std;
enum operandtype{reg=0,sym,con,oplabel};
enum opcodeenum {ld=0,st,mov,add,mul,bdiv,sub,jmp,jmpe,jmpne,jmpge};
class operand{
    operandtype type;
    int value;
    string vallabel;
    
    public:
    operand(){
    }
    operand(operandtype, string);//symbol register
    operand(operandtype,int); //constant
    operand* operator=(operand* op){
        type = op->type;
        value = op->value;
        vallabel = op->vallabel;
    }
    void print_opcode();
    void print_opcode(ofstream&);
    operandtype get_operandtype();
    void set_data(int);
    int get_data();
    string getvalLabel(){
        return vallabel;
    }
    void set_type(operandtype);

};
class BasicBlock;//forward declaring BasicBlock which is defined in basicblock.h file
class instruction{
 
    opcodeenum opcodeno;
    operand *destination;
    vector< operand* > source;
    string label;
    BasicBlock* parent;
    public:
    instruction(){}
    BasicBlock* getParent(){
        return parent;
    }
    void setParent(BasicBlock* bb){
        parent = bb;
    }
    operand* get_source_operand(int);
    int get_source_count();
    void add_source_operand(operand*);
    void set_opcodeno(opcodeenum);
    opcodeenum get_opcodeno();
    void set_destination_operand(operand*);
    operand* get_destination_operand();
    string getLabelFromOperand();
    void print_instruction();
    void print_instruction(ofstream&);
    string getLabel(){
        return label;
    }
    bool check_src_operand_correctness(opcodeenum,int);
    
    instruction(opcodeenum,operand*);
    instruction(opcodeenum,operand*,operand*,string = "");
   instruction(opcodeenum,operand*,operand*,operand*, string = "");
   // instruction* createInstruction(opcodeenum,operand&,operand&,operand);
    /*  template <class Copcode,class...Csrc>
        instruction (Copcode opcode,Csrc...src){
        int total_src=sizeof...(src);
        if(check_src_operand_correctness(opcode,total_src-1)){//opcode and source operand error check
        opcodeno=opcode;
        operand tmpop[total_src]={src...};
        destination=tmpop[0];
        for(int i=1;i<total_src;i++)
        source.push_back(tmpop[i]);
        }else{
        cout<<"Error...Invalid Arguments\n";
        assert(false);
        }
        }*/

};
#endif
