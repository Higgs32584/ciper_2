#include<stdlib.h>
#include<stdio.h>

//data-->the initial data
//data_length--> length of the data
// initialValue--> Value to start withn during decryption
// final--> final value

// Crypt is the main function that passes the code through the LFSR algorithm
unsigned char* Crypt(unsigned char* data,int dataLength,unsigned int initialValue){
    
    const long F = 0x87654321;
    //final value
    unsigned char *final = malloc(sizeof(*data)*dataLength);
    if(!final){
    return NULL;
    }
    for(int k=0;k<dataLength;k++){
	
        for(int i=0;i<8;i++){
        // Check if the least significant bit is 0    
	if(initialValue % 2 == 0){
                // Shift the initial value right by 1 bit
		initialValue = initialValue >> 1;
            }
	 //Check if the least signifigant bit is 1
            else if(initialValue % 2 == 1){
		// Shift the initial value right by 1 bit and XOR with F    
                initialValue= (initialValue>>1)^F;

            }
        }
	//Covert Character to an int and modify initial value
        int num = (int)data[k];
        int saneValue = (initialValue ^ num);
	//Formatting for the final value stored
        saneValue = (0X000000FF & saneValue);
        final[k]=saneValue;
    }
    return final;
}
//This is for printing the variables 
void print_unsigned(unsigned char* c,int dataLength,int k){
	if(k==0){
	for(int i=0;i<dataLength;i++){
		printf("%c",c[i]);
	}
	}
	if(k==1){
       for(int j=0;j<dataLength;j++){
                printf("%x",c[j]);
        }
	}
	printf("\n");
}
int main(){
//Test case#1
unsigned char* test1=Crypt((unsigned char*)"apple",5,0x12345678);
if(!test1){
test1=NULL;
}
//Test case#2
print_unsigned(test1,5,1);
unsigned char* test2=Crypt((unsigned char*)"\xCD\x01\xEF\xD7\x30",5,0x12345678);
print_unsigned(test2,5,0);
if(!test2){
test1=NULL;
}


}
