#include "bitbool.h"
    bitvec::bitvec(){
        blocks=1;
        index=0;
        cindex=0;
        bb=new bool;
        bb[0]=0;
    }
    bitvec::bitvec(int s){
        blocks=s;
        index=0;
        cindex=0;
        bb=new bool[blocks];
        for(int i=0;i<blocks;i++)
        bb[i]=0;
    }
    bitvec :: ~bitvec(){
        delete(bb);
    }
    bitvec :: bitvec(const bitvec &b2){
        blocks=b2.blocks;
        index=b2.index;
        bb=new bool[blocks];
        for(int i=0;i<blocks;i++){
            bb[i]=b2.bb[i];
        }
    }
    void bitvec::push_bit(bool val){
        if(index >= blocks ){
                //double
               // cout<<"\ndoubling..\n";
                int i;
                bool *bt=bb;
                bb=new bool[blocks*2];
                for(i=0;i<blocks;i++)
                    bb[i]=bt[i];
                for(i=blocks;i<blocks*2;i++)
                    bb[i]=0;
                blocks=blocks*2;
                delete(bt);
            }
         bb[index] = val;
         index++;
    }

    void bitvec :: resize(int nsize){
        int i;
        bool *bt=bb;
        bb=new bool[nsize];
        if(nsize >= blocks ){
                //double
                //cout<<"\ndoubling..\n";

                for(i=0;i<blocks;i++)
                    bb[i]=bt[i];
                for(i=blocks;i<nsize;i++)
                    bb[i]=0;
                blocks=nsize;
                delete(bt);
        }else{
            for(i=0;i<nsize;i++)
                    bb[i]=bt[i];
            index=nsize-1;
        }
        blocks=nsize;
        index = nsize;
    }
    void bitvec :: show_bit(){

                for(int i=index-1;i>=0;i--){
                 cout<<query_bit(i);


        }
        cout<<"\n";
    }

    void bitvec :: set_bit(int bn){
         if(bn >= blocks){
            //cout<<".set not pushed\n";
        }else{
            if(index < bn)
                index = bn + 1;
            bb[bn]=true;
        }
    }

    void bitvec :: clear_bit(int bn){

        if(bn >= blocks){
           // cout<<".clear not pushed\n";
        }else{
        bb[bn]=false;
        }
    }

    bool bitvec :: query_bit(int bn){

        if(bn >= index){
            //cout<<".q  not pushed\n";
            //assert(false);
        }else{
            return bb[bn];
        }

    }
    bitvec bitvec :: operator&(const bitvec& b2){
        int lsize,i,lindex;
        lsize = index < b2.index ? index : b2.index;
        bitvec ansbv= bitvec(lsize);
        lsize == index? ansbv.index=index : ansbv.index=b2.index;
        lindex = index > b2.index ? b2.index: index ;
        for(i=0;i<lindex;i++){
            ansbv.bb[i]=bb[i]&b2.bb[i];
        //    cout<<"\n..and of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
        }
    return ansbv;
    }
bitvec bitvec :: operator-(const bitvec& b2){
        int i;
        bitvec ansbv= bitvec(blocks);
        for(i=0;i<index;i++){
            if(bb[i] && !b2.bb[i])
                ansbv.bb[i]=1;
            else
                ansbv.bb[i]=0;
        }
    return ansbv;
    }


    bitvec bitvec :: operator|(const bitvec& b2){
        int hsize,i,lindex;
        index = blocks;
        
        hsize = index > b2.index ? index : b2.index;
        bitvec ansbv= bitvec(hsize);
        hsize == index? ansbv.index=index : ansbv.index=b2.index;
        lindex = index > b2.index ? b2.index: index ;
        for(i=0;i<lindex;i++){
            ansbv.bb[i]=bb[i]|b2.bb[i];
          // cout<<"\n.."<<i<<" or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
        }
        if( hsize == index ){
            for(i = lindex; i < hsize; ++i){
                ansbv.bb[i] = bb[i];
            //    cout<<"\n:::or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
            }
        }else{
            for(i = lindex; i < hsize; ++i){
                ansbv.bb[i] = b2.bb[i];
//                 cout<<"\n:::or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
            }
        }

    return ansbv;
    }
    bitvec bitvec :: operator^(const bitvec& b2){
        int hsize,i,lindex;
        hsize = index > b2.index ? index : b2.index;
        bitvec ansbv= bitvec(hsize);
        hsize == index? ansbv.index=index : ansbv.index=b2.index;
        lindex = index > b2.index ? b2.index: index ;
        for(i=0;i<lindex;i++){
            ansbv.bb[i]=bb[i]^b2.bb[i];
  //         cout<<"\n.."<<i<<" or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
        }
        if( hsize == index ){
            for(i = lindex; i < hsize; ++i){
                ansbv.bb[i] = bb[i];
    //            cout<<"\n:::or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];

            }
        }else{
            for(i = lindex; i < hsize; ++i){
                ansbv.bb[i] = b2.bb[i];
      //           cout<<"\n:::or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
            }
        }
    return ansbv;
    }

    bool& bitvec :: operator[](int in) {
        return bb[in];
    }

    bitvec& bitvec :: operator=(const bitvec& b2){
        int i;
        if(blocks < b2.blocks){
            delete(bb);
            bb=new bool[b2.blocks];
        }
        for(i=0;i<b2.blocks;i++){
            bb[i]=b2.bb[i];
        }
        if(blocks > b2.blocks){
            for(i=b2.blocks;i<blocks;i++){
                bb[i]=0;
            }
        }else{
            blocks=b2.blocks;
        }
        index=b2.index;
        return *this;
    }
    bool bitvec::operator==(const bitvec& bv){
       if(blocks == bv.blocks){
            for(int i = 0; i < blocks; ++i){
                if(bb[i] != bv.bb[i])
                    return false;
            }
            return true;
       }else
          return false; 
    }
    bool bitvec :: getbegin(){
       return query_bit(0);
    }

    bool bitvec :: getend(){
       return query_bit(index-1);
    }

    int bitvec :: itbegin(){
    return 0;
    }

    int bitvec :: itend(){
    return index;
    }
    bool bitvec :: next(){
         return query_bit(cindex++);
    }
    bool bitvec :: previous(){
        if(cindex==0){
            cout<<"\n You are at beginning\n";
        }else
        return query_bit(--cindex);
    }
    void bitvec :: setit(int i){
        cindex=i;
    }
