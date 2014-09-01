    #include <iostream>
    #define BITS 8

    using namespace std;
    class bitvec{

            int blocks;
            int index;
            bool *bb;
            int cindex; //for iterator
        public:
            bitvec();
            bitvec(int);
            bitvec(const bitvec &);
            ~bitvec();
            void push_bit(bool);
            void resize(int);
            void show_bit();
            void set_bit(int);
            void clear_bit(int);
            bool query_bit(int);
            bitvec operator&(const bitvec&);
            bitvec operator|(const bitvec&);
            bitvec operator^(const bitvec&);
            bitvec& operator=(const bitvec&);
            bool& operator[](int);
            //for iterator
            bool getbegin();
            bool getend();
            int itbegin();
            int itend();
            bool next();
            bool previous();
            void setit(int);
    };

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
                cout<<"\ndoubling..\n";
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

    bitvec bitvec :: operator|(const bitvec& b2){
        int hsize,i,lindex;
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
        cout<<"in [] \n";
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

/*

    int main(){
    bitvec bv1=bitvec();
    bitvec bv2=bitvec();
    bitvec bv3=bitvec();
    bitvec bv4=bitvec();

    bv1.resize(32);
    bv2.resize(32);
    bv3.resize(32);
    bv4.resize(32);

    bv1.set_bit(1);
    bv1.set_bit(2);
    bv1.set_bit(3);
    bv1.set_bit(7);
    bv1.set_bit(4);
    bv1.clear_bit(7);

    bv2.set_bit(1);
    bv2.set_bit(3);
    bv2.set_bit(4);
    bv2.set_bit(5);

    bv3.set_bit(1);
    bv3.set_bit(2);
    bv3.set_bit(3);
    bv3.set_bit(7);

    bv4.set_bit(1);
    bv4.set_bit(2);
    bv4.set_bit(3);
    bv4.set_bit(5);

    bitvec band=bitvec();
    bitvec bor=bitvec();
    bitvec bxor=bitvec();

    band=bv1&bv2;//&bv3&bv4;
    cout<<"\nAND\n";
    bv1.show_bit();
    bv2.show_bit();
    bv3.show_bit();
    bv4.show_bit();
    cout<<"----------\n";
    band.show_bit();
    bv1.resize(50);
    bv1.set_bit(40);
    bv1.set_bit(34);
    bor=bv1|bv2|bv3|bv4;
    cout<<"\nOR\n";
    bv1.show_bit();
    bv2.show_bit();
    bv3.show_bit();
    bv4.show_bit();
    cout<<"----------\n";
    bor.show_bit();


    bxor=bv1^bv2^bv3^bv4;

    cout<<"\nXOR\n";
    bv1.show_bit();
    bv2.show_bit();
    bv3.show_bit();
    bv4.show_bit();
    cout<<"----------\n";
    bxor.show_bit();

    cout<<"\n\n subscript Overloading \n";
    cout<<bv1[0]<<"   "<<bv1[1]<<"\n";

bv1.resize(64);
bv2.resize(32);

     bv2.set_bit(20);
     bv1.set_bit(40);
     bv2.set_bit(22);
     bv1.push_bit(true);
     bv1.show_bit();
    bitvec bvaa=bitvec();
    bvaa=bv1 | bv2;
    cout<<"and of \n";
    bv1.show_bit();
    bv2.show_bit();
    cout<<"----------\n";
    bvaa.show_bit();
    cout<<"Iterator\n";

    for(int i=bv1.itbegin();i<bv1.itend();i++){
        cout<<bv1.next();
    }
    cout<<"\n";

    cout<"\n\n";
    bitvec be1=bitvec();
    bitvec be2=bitvec();
    bitvec be3=bitvec();
    bitvec be4=bitvec();

    be1.show_bit();
    be2.show_bit();
    be3.show_bit();
    be4.show_bit();

    return 0;
    }

    */
