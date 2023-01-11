#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
struct new_entry{
    char NAME[16];
    int32_t *LIST_BLOCK;
}new_entry;
struct entry_list{
struct new_entry entries[127];
}entry_list;
struct BLOCK{
    int16_t SIZE;
    int32_t *DATA;
};
struct BLOCK_LIST{
struct BLOCK BLOCK_LIST[255];
};
struct head{
    char MAGIC[6];
    int32_t *head;
}head;

//head functions
    //from top of file pointer read 'CT2018'
    //read int_32t right after this
    //put int_32t into byte swap
//steps for entry list
    //read values from specified pointer in head, iterating roughly about 20 bytes every time, which is the aproximate size of entry
    // stop when 127 iterations is reached, or a hex value of 0xFFFFFFFF
//steps for each entry
    //store name for each entry
    //convert int32_t value to pointer to little endian, and use it to point to BLOCK_LIST
    //from specified pointer iterate 255 times for each BLOCK in BLOCK_LIST
//steps for each block
    //size can be defined as "n"
    //from specified pointer, after byte switching, iterate n times to pull the bytes from data, and store data into giant byte array
//after byte array is complete, use algoritm from problem one to solve the problem







void *Crypt(unsigned char* data,int dataLength,unsigned int initialValue){
    long F = 0x87654321;
    unsigned char *final=malloc(sizeof(*data));
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
        //saneValue= saneValue << 24;
        saneValue = (0X000000FF & saneValue);
        final[k]=saneValue;
        printf("%.2x\n",final[k]);


    }
    for(int z=0;z<strlen((char*)final);z++) {
                   printf("%c",final[z]);
        }
    return final;
}

void byte_swap(void* data, size_t size) {
  char* p = (char*) data;
  for (size_t i = 0; i < size / 2; i++) {
    char tmp = p[i];
    p[i] = p[size - i - 1];
    p[size - i - 1] = tmp;
  }
}

void seek_data(int32_t data_pointer,int16_t size){
    FILE* fptr = fopen("./SW_2018/store.kdb", "rb");
    FILE* decode = fopen("document.txt", "w");
    fseek(fptr,data_pointer,SEEK_SET);
    unsigned char *c = malloc(sizeof(char));
    for (int i = 0; i < size; i++){
       unsigned char temp;
        fread(&temp,sizeof(unsigned char),1,fptr);
        fwrite(&temp,sizeof(unsigned char),1,decode);
    }
    Crypt(c,sizeof((char *) c),0x4F574154);
    fclose(fptr);
    fclose(decode);
}

void seek_block_list(FILE *fptr,int32_t pointer){
    fseek(fptr,pointer,SEEK_SET);
    int16_t k;
    int32_t data_pointer;
    fread(&k,sizeof(int16_t),1,fptr);
    fread(&data_pointer,sizeof(int32_t),1,fptr);
    seek_data(data_pointer,k);
    printf("size:%d pointer:%d \n",k,data_pointer);
   
}


int main()
{  
    FILE* file_ptr = fopen("./store.kdb", "rb");

    char *magic = malloc(sizeof(char)*6);
    long pointer;
    fread(&magic,sizeof(char),6,file_ptr);
    fread(&pointer,sizeof(int32_t),1,file_ptr);
    fseek(file_ptr,pointer,SEEK_SET);
    
    int32_t* data = (int32_t*)malloc(sizeof(int32_t) * 8);
    for(int i=0;i<8;i++){
        int32_t k;
        char *c = malloc(sizeof(char)*16);
        fread(c,sizeof(char),16,file_ptr);
        fread(&k,sizeof(int32_t),1,file_ptr);
        //printf("Name:%s Pointer:%d\n",c,k);
	data[i] = k;
    }
    for(int j=0;j<8;j++){
	       	
	        fseek(file_ptr,data[j],0);
		int16_t data_size;
    		int32_t data_pointer;
    		fread(&data_size,sizeof(int16_t),1,file_ptr);
    		fread(&data_pointer,sizeof(int32_t),1,file_ptr);
    		seek_data(data_pointer,data_size);
    		//free(k);
		//free(data_pointer);
		printf("size:%u pointer:%u \n",data_size,data_pointer);
    }

    //for(int j=0;j<8;j++) printf(ptr_list[j]);




}
