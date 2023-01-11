#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned char *Crypt(unsigned char* data,int dataLength,unsigned int initialValue){
    long F = 0x87654321;
    unsigned char *final=malloc(sizeof(data));
    for(int k=0;k<dataLength;k++){
        for(int i=0;i<8;i++){
            if(initialValue % 2 == 0){
                initialValue = initialValue >> 1;
            }
            else if(initialValue % 2 == 1){
                initialValue= (initialValue>>1)^F;
        
            }
        }
        int num = (int)data[k];
        int saneValue = (initialValue ^ num);
        int x = 4294967040;
        //saneValue= saneValue << 24;
        saneValue = (0X000000FF & saneValue);
        final[k]=saneValue;
        //printf("%.2x\n",final[k]);
        
        
    }
    return final;
}
int main(){
    FILE *f = fopen("./document.txt", "r");
    char *c;
    unsigned char* final = Crypt("\xCD\x01\xEF\xD7\x30",5,0x12345678);
    unsigned char* final2 = Crypt("apple",5,0x12345678);
    for(int i=0;i<strlen(final);i++){
        printf("%c",final[i]);
    }
    printf("\n");
    for(int i=0;i<strlen(final2);i++){
        printf("%.02X",final2[i]);
    }
}