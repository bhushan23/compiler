#include <iostream>
#include <vector>
#include <cstdarg>
#include <cassert>
#include "basicblock.h"
#include "irclass.h"
#include "table.h"
using namespace std;
int opcode_par_cnt[]={1,1,1,2,2,2,2,1,3,3,3};
operand :: operand(operandtype otype,string t){//for symbol and register
    
    if(otype==reg){//register
        type=reg;
        value=t[1]-48; //Need to change code for index having more than 9
    }else if(otype == oplabel){
        type = otype;
        vallabel = t;
    }else{//Symbol
        type=sym;
        value=add_symbol(t);
    }
}
operand :: operand(operandtype otype,int val){//for index based
    switch(otype){
        case reg:
            type=reg;
            value=val;
            break;
        case sym:
            type=sym;
            value=val;
            break;
        case con:
            type=con;
            value=val;
            break;
    }

}
void operand :: set_data(int d){
    value=d;
}
int operand :: get_data(){
    return value;
}
void operand :: set_type(operandtype optype){
    type=optype;
}
void operand :: print_opcode(){
    switch(type){
        case 0://reg
            cout<<"r"<<value;
            break;
        case 1:
            cout<<get_symbol(value);
            break;
        case 2:
            cout<<value;
            break;
        case 3:
            cout << "label "<<vallabel;
            break;
        default:
            cout<<"..";
            break;
    };
}

operandtype operand :: get_operandtype(){
    return type;
}
instruction::instruction(opcodeenum opcode,operand &lop){
    opcodeno = opcode;
    destination = lop;
}
instruction :: instruction(opcodeenum opcode,operand& dest,operand& src,string lab){
    opcodeno=opcode;
    destination=dest;
    label = lab;
    source.push_back(src);
}

instruction :: instruction(opcodeenum opcode,operand& dest,operand& src1,operand& src2,string lab){
    opcodeno=opcode;
    destination=dest;
    label = lab;
    source.push_back(src1);
    source.push_back(src2);
}/*
instruction* instruction::createInstruction(opcodeenum opcode,operand& dest,operand& src1,operand& src2){
    opcodeno=opcode;
    destination=dest;
    source.push_back(src1);
    source.push_back(src2);
}*/

void instruction :: print_instruction(){
    //if(label.length() > 0)
    //cout << label << ": ";
    cout<<opcode_table_getinst(opcodeno)<<" ";
    destination.print_opcode();

    for(int i=0,size = source.size(); i < size;i++){
        cout<<" ";
        source[i].print_opcode();
    }
}

operand instruction :: get_source_operand(int i){
    if( i >= 0 && i < source.size() )
        return source[i];
    else
        assert(false);

}

void instruction :: set_opcodeno(opcodeenum i){
    opcodeno=i;
}

opcodeenum instruction :: get_opcodeno(){
    return opcodeno;
}
void instruction :: set_destination_operand(operand& op){
    destination=op;
}

operand instruction :: get_destination_operand(){
    return destination;
}


void instruction :: add_source_operand(operand& op){
    source.push_back(op);
}
int instruction :: get_source_count(){
    return source.size();
}

bool instruction :: check_src_operand_correctness(opcodeenum opcode,int src){
    if(opcode_par_cnt[opcode]==src)
        return true;
    return false;
}
string instruction::getLabelFromOperand(){
string opLabel;
    switch(opcodeno){
        case jmp:
            //if(destination.get_operandtype() == oplabel){//Xcheck if operand is LabelType
                opLabel = destination.getvalLabel();
           // }
            break;
        case jmpe:
        case jmpne:
        case jmpge:
            opLabel = source[source.size()-1].getvalLabel();
            break;

        default:
            opLabel = "";
            break;
   }
return opLabel;
}

