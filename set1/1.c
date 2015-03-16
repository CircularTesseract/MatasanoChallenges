#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

/*
*Note: Function can take hexStrings encoded with lowercase of uppercase ASCII characters
*/
char* hexToBinary(char* hexString) {
	//pass through binary to encode in base64
	char* binaryString = (char*)malloc(4*strlen(hexString)+1); //sizeof string is 1 byte  	 				
	binaryString[4*strlen(hexString)] = '\0';     
	int sofar=0; 
	while(*hexString != '\0') {
		char* tempHolding = malloc(5);
		//TODO fix this terrible cascade of if statements to case or something more clever
		if(*hexString == '0') {
			tempHolding = "0000"; 
		}else if(*hexString == '1') {
			tempHolding = "0001"; 
		}else if(*hexString == '2') {
			tempHolding = "0010"; 
		}else if(*hexString == '3') {
			tempHolding = "0011";
		}else if(*hexString == '4') {
			tempHolding = "0100"; 
		}else if(*hexString == '5') {
			tempHolding = "0101"; 
		}else if(*hexString == '6') {
			tempHolding = "0110"; 
		}else if(*hexString == '7') {
			tempHolding = "0111"; 
		}else if(*hexString == '8') {
			tempHolding = "1000"; 
		}else if(*hexString == '9') {
			tempHolding = "1001"; 	
		}else if(*hexString == 'a' ||*hexString == 'A') {
			tempHolding = "1010"; 
		}else if(*hexString == 'b' ||*hexString == 'B') {
			tempHolding = "1011";
		}else if(*hexString == 'c' ||*hexString == 'C') {
			tempHolding = "1100"; 
		}else if(*hexString == 'd' ||*hexString == 'D') {
			tempHolding = "1101"; 
		}else if(*hexString == 'e' ||*hexString == 'E') {
			tempHolding = "1110"; 
		}else if(*hexString == 'f' ||*hexString == 'F') {
			tempHolding = "1111"; 
		}else{
			//non base 16 character found, exit 
			printf("incompatible element found, terminating process\n"); 
			exit(0); 
		}
		int i=0; 
		for(i; i<4;i++) {
			if(tempHolding[i] == '\0') {
				printf("error for: %c\n", *hexString); 
				printf("found null char at: %d\n", sofar); 
			}
			binaryString[sofar] = tempHolding[i]; 
			sofar += 1;
		}
		hexString+=1; 
	}
	return binaryString;
}
char* hexTobase64(char* hexString) {
	char* binaryString = hexToBinary(hexString); 
	if(strlen(binaryString)%6 != 0) {
		printf("incompatible base 64 bit length detected"); 
		exit(1);
	}
	//now safe to malloc base64 string
	char* base64String = malloc((int)(strlen(binaryString)/6) + 1); 
	base64String[(int)strlen(binaryString)] = '\0'; //ensure to properly null terminate
	int index=0; 
	for(index; index < strlen(binaryString); index+=6) {
		//we must now convert 6 bit blocks to base64	
		int binarySum = 0; 
		if(binaryString[index] == '1') {
			binarySum += 32;	
		}else{}
		if(binaryString[index+1] =='1') {
			binarySum += 16; 
		} else{}
		if(binaryString[index+2] =='1') {
			binarySum += 8;  
		} else{}
		if(binaryString[index+3] == '1') {
			binarySum += 4; 
		} else{}
		if(binaryString[index+4] == '1') {
			binarySum += 2; 
		}else{}
		if(binaryString[index+5]== '1') {
			binarySum += 1;
		}else{} 
		//we now have the integer value for our base64 character
		if(binarySum<26) {
			//is an upper case letter
			base64String[(index/6)] = (char)(binarySum+65); 	
		}else if(binarySum<52) {
			//is a lower case letter
			base64String[(index/6)] = (char)((binarySum%26)+97); 
		}else if(binarySum<=61) {
			base64String[index/6]  = (char)((binarySum-52)+48); 
		}else if(binarySum == 62) {
			base64String[index/6] = '+'; 
		}else if( binarySum == 63) {
			base64String[index/6] = '/'; 
		}else {
			printf("internal data corruption found, exiting now");
			exit(0); 
		}
		
	}
	return base64String; 
}
void main() {
 	char* s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"; 
	char* encoded = hexTobase64(s); 
	printf("%s\n",encoded); 
}
