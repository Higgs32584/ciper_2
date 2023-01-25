#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
void Crypt(unsigned char* data,int dataLength,unsigned int initialValue){
    long F = 0x87654321;
    unsigned char *final = malloc(sizeof(*data));
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
        final[k]=saneValue;


    }
    //for(int z=0;z<dataLength;z++) {
    //               printf("%c",final[z]);
       //}
}
void charToUnsignedChar(char* charArray, unsigned char* unsignedCharArray, int size) {
	for (int i = 0; i < size; i++) {
        	unsignedCharArray[i] = (unsigned char) charArray[i];
    	}

	}
char *test_func(){
	char *c =(char *)malloc(sizeof(char)*16);
	return c;
}


void decode(int argc,char** argv)
{  
    FILE* file_ptr;
    file_ptr= fopen(argv[1], "rb");
    char *magic = malloc(sizeof(char)*6);
    long pointer;
    fread(magic,sizeof(char),6,file_ptr);
    fread(&pointer,sizeof(int32_t),1,file_ptr);
    fseek(file_ptr,pointer,SEEK_SET);
    
    int32_t* data=(int32_t*)malloc(sizeof(int32_t)*127);
    int32_t k;
    int i=0;
    while(k != 0){
	char *c = test_func();
	fread(c,sizeof(char),16,file_ptr);
        fread(&k,sizeof(int32_t),1,file_ptr);
	data[i] = k;
	i++;
	free(c);
    }
    data=realloc(data,i*sizeof(int32_t));
    i=i-1;
    for(int j=0;j<i;j++){
	       	
	        fseek(file_ptr,data[j],SEEK_SET);
		int16_t data_size;
    		int32_t data_pointer;
    		//printf("%d %d",data_size,data_pointer);
		fread(&data_size,sizeof(int16_t),1,file_ptr);
    		fread(&data_pointer,sizeof(int32_t),1,file_ptr);
		fseek(file_ptr,data_pointer,0);
		char buffer[data_size];
		size_t bytesRead;  
		bytesRead = fread(buffer, 1, data_size,file_ptr);
		unsigned char *actual_buffer = (unsigned char *) malloc(bytesRead);
		charToUnsignedChar(buffer,actual_buffer,data_size);
		Crypt(actual_buffer,bytesRead,0x4F574154);		
   		
    }		
    fclose(file_ptr);
}


int main(int argc,char** argv){
//decode(argc,argv);
FILE* file_pt;
FILE* file_pt2;
file_pt = fopen("./input.bin", "rb");
file_pt2 = fopen("./file.jpeg","wb");


for(int i=0;i<3;i++){
unsigned char c;
unsigned char d;
fread(&c,sizeof(unsigned char),1,file_pt);
fread(&c,sizeof(unsigned char),1,file_pt);
fread(&c,sizeof(unsigned char),1,file_pt);

unsigned char distort1=0xFF;
unsigned char distort2=0xD8;

fwrite(&distort1,sizeof(unsigned char),1,file_pt2);
fwrite(&distort2,sizeof(unsigned char),1,file_pt2);
fwrite(&distort1,sizeof(unsigned char),1,file_pt2);
while((c != 0xFF) && (d != 0xD8)){
	
	fread(&c,sizeof(unsigned char),1,file_pt);
	fread(&d,sizeof(unsigned char),1,file_pt);
	fwrite(&c,sizeof(unsigned char),1,file_pt2);
        fwrite(&d,sizeof(unsigned char),1,file_pt2);

	/*if((c == 0xFF) && (d == 0xd9)){*/
		printf("%.2x %.2x",c,d);
}
printf("\n");

return 0;

}






