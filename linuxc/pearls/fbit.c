
#include "fbit.h"
const uint32_t N = 10000000;
struct fBit *  bitInit(uint32_t cap)
{
    uint32_t size_num = cap/32 + 1;
    struct fBit * bit = (struct fBit *) malloc( sizeof(struct fBit) );

    bit->mdata = (uint32_t * )malloc(sizeof(uint32_t ) * size_num);
    bit->mlen =  size_num;

    return bit;
}
int bitInsert(uint32_t value ,struct fBit * bit_ptr )
{
    uint32_t pos = value/32;
    uint32_t pos2 = value%32;


    bit_ptr->mdata[pos] |= (1<<pos2);
    return 1;
}
int bitFind(uint32_t value ,struct fBit * bit_ptr)
{
     uint32_t pos = value/32;
    uint32_t pos2 = value%32;


    if( bit_ptr->mdata[pos] & (1<<pos2) == 1)
        return 1;
    else
        return 0;
}

void bitPrint(struct fBit * bit_ptr)
{
    FILE * fp = fopen("out","w");
    for(int i = 0 ; i < bit_ptr ->mlen ; ++i){
        uint32_t data = bit_ptr->mdata[i];
        for(int j = 0 ; j < 32 ; j ++){
            fprintf(fp,"%d ",data&1);
            data>>=1;
        }
        fprintf(fp,"\n");
    }
}
void bitMain()
{
    struct fBit * test = bitInit(N + 2);
    int i = 0;
    FILE * fp = fopen("in","r");
    while(fscanf(fp,"%d",&i)!= EOF){
        bitInsert(i,test);
    }

    //bitPrint(test);
}
void bitCreat()
{
    FILE * fp = fopen("in","w");
    char * buf = (char *)malloc(sizeof(char) * 2048);
    int *data = (char *)malloc(sizeof(int) * N);
    for(int i = 0 ; i < N ; ++i){
        data[i] = i;
    }
    //打乱顺序
    for(int i =0 ; i < N ; ++i ){
        int j = rand()%N;
        int t = data[i];
        data[i] = data[j];
        data[j] = t;
    }
    setbuf(fp,buf);
    for(int i = 1 ; i<= N  ; i ++){
        //write(fp, const void *buf, size_t length);
        fprintf(fp,"%d\n",data[i]);
    }
    fclose(fp);
}


