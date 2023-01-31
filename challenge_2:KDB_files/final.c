#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void Crypt(unsigned char* data,int dataLength,unsigned int initialValue){
    long F = 0x87654321;
    unsigned char *decryptedData = malloc(sizeof(*data));
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
        saneValue = (0X000000FF & saneValue);
        decryptedData[k] = saneValue;
    }
    for(int z=0;z<dataLength;z++) {
                   printf("%c",decryptedData[z]);
        }
    printf("\n");
}
void charToUnsignedChar(char* charArray, unsigned char* outputUnsignedCharArray, int size) {
	for (int i = 0; i < size; i++) {
        	outputUnsignedCharArray[i] = (unsigned char) charArray[i];
    	}
}
int main(int argc,char** argv)
{  
    FILE* file_ptr;
    file_ptr= fopen(argv[1], "rb");
    char *magic = malloc(sizeof(char)*6);
    long pointer;

    fread(magic,sizeof(char),6,file_ptr);
    fread(&pointer,sizeof(int32_t),1,file_ptr);
    fseek(file_ptr,pointer,SEEK_SET);

    int32_t* data = (int32_t*)malloc(sizeof(int32_t)*127);
    int32_t block_list_pointer= -1;
    
    int i=0;
    while(block_list_pointer!= 0){
	char *c=(char*)malloc(sizeof(char)*16);
	fread(c,sizeof(char),16,file_ptr);
        fread(&block_list_pointer,sizeof(int32_t),1,file_ptr);
	if(block_list_pointer!= 0){
	printf("%s\n",c);
	data[i]=block_list_pointer;
	}
	i++;
    }
    data=realloc(data,i*sizeof(int32_t));
    i=i-1;
    for(int j=0;j<i;j++){
	       	
	        fseek(file_ptr,data[j],SEEK_SET);
		int16_t block_size;
    		int32_t block_ptr;
		fread(&block_size,sizeof(int16_t),1,file_ptr);
    		fread(&block_ptr,sizeof(int32_t),1,file_ptr);
		fseek(file_ptr,block_ptr,0);
		char buffer[block_size];
		size_t decryptedBlockSize;  
		decryptedBlockSize= fread(buffer, 1, block_size,file_ptr);
		unsigned char *unsignedDecryptedBlock  = (unsigned char *) malloc(decryptedBlockSize);
		charToUnsignedChar(buffer,unsignedDecryptedBlock ,block_size);
		Crypt(unsignedDecryptedBlock ,decryptedBlockSize,0x4F574154);		
   		
    }		
    fclose(file_ptr);
    return 0;
}



