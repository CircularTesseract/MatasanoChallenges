#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
*Please note that this will only accurately decrypt cyphertexts that
*are english strings for anything else it will not yeild desirable results. 
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

char* binaryToHex(char* binaryString) {
	if(strlen(binaryString)%4 != 0) {
		printf("Binary string cannot be converted to hex, string length error"); 
		exit(0); 
	}
	char* hexString = (char*)malloc(strlen(binaryString)/4+1); //sizeof string is 1 byte  	 				
	hexString[strlen(binaryString)/4] = '\0';    
	int index =0; 
	for(index; index < strlen(binaryString); index+=4) {
		int count = 0; 
		if(binaryString[index]=='1'){
			count += 8; 
		}
		if(binaryString[index+1]=='1'){
			count += 4; 
		}
		if(binaryString[index+2]=='1'){
			count += 2;
		}
		if(binaryString[index+3]=='1'){
			count += 1; 
		}
		if(count<=9){
			hexString[index/4] = (char)(count + 48); 
		}else{
			hexString[index/4] = (char)((count-10)+65); 
		}
	}

	return hexString;
}

//a more general approach to the xor cypher seen in 2.c
char* xorCypher(char* cyphertext, char* counter){
	char* cypherTextBinary = hexToBinary(cyphertext); 
	char* counterTextBinary = hexToBinary(counter); 
	if(strlen(cypherTextBinary)%strlen(counterTextBinary)!=0){
		printf("Incompatible XOR input"); 
		exit(1); 
	}
	char* result = malloc(strlen(cypherTextBinary)+1); 
	result[strlen(result)-1]='\n'; 
	int i=0; 
	for(i; i<strlen(cypherTextBinary);i++){
		if(cypherTextBinary[i] == '1'){
			if(counterTextBinary[i%(strlen(counterTextBinary))]=='1'){
				result[i]='0'; 
			}else{
				result[i]='1'; 
			}
		}else{
			if(counterTextBinary[i%strlen(counterTextBinary)]=='0'){
				result[i]='0'; 
			}else{
				result[i]='1'; 
			}
		}
	}
	return binaryToHex(result); 
}

//since it is a character we can take some liberties in assuming the
//result is an 8 bit string. 
//Note this implementation is innelegant:
/*
	TODO: Make this method more elegant
*/
char* charToBinary(char c){
	int charVal = (int)c;
	int i =7; //the first bit in bianry 
	char* result = malloc(9); //8 characters + null termination
	result[8]='\0'; //ensure to properly null terminate
	int j =0; 
	//set the intial results to the binary string 00000000; 
	for(j; j <8;j++){
		result[j] = '0'; 
	}
	if(charVal == 0){
		//special case
		return result; 
	}
	for(i; i >= 0; charVal>>=1 ){
		if(charVal == 0){
			return result; 
		} 
		if(charVal & 1){
			result[i] ='1'; 
		}else{
			result[i]='0'; 
		}
		i--; 
	}
	return result; 
}
//TODO fix ugly implementation from cascade of ifs to something more elegant
char binaryStringtoChar(char* binaryString){

	if(strlen(binaryString) != 8) {
		printf("%d\n", strlen(binaryString)); 
		printf("Binary string cannot be converted to char, string length error\n"); 
		exit(0); 
	}
	char result = '\0'; //temporary 
	int count=0; 
	if(binaryString[0]=='1')
		count += 126; 
	if(binaryString[1]=='1')
		count += 64; 
	if(binaryString[2]=='1')
		count += 32;
	if(binaryString[3]=='1')
		count += 16; 
	if(binaryString[4]=='1')
		count += 8; 
	if(binaryString[5]=='1')
		count += 4; 
	if(binaryString[6]=='1')
		count += 2; 
	if(binaryString[7]=='1')
		count += 1; 
	
	return (char)count; 

}

char* binaryStringToASCII(char* binaryString){

	if(strlen(binaryString)%8!=0){
		printf("Error in binary to ASCII, passed binary string is not compatible\n"); 
		exit(1); 
	}
	int i = 0; 
	char* result = malloc( (strlen(binaryString)/8)+1);
	result[strlen(binaryString)/8+1] ='\0'; //safe
	for(i;i<strlen(binaryString)/8;i++){ //as to avoid overriding our null char
		result[i] = '0'; //temporary
	}

	//Note do not remove the reseting of i, it is important
	i=0;
	for(i; i<strlen(binaryString);i+=8){
		//abusing the  conventions for the bit length of characters
		char* binaryChar = malloc(9);
		int k=0;
		for(k;k<8;k++){
			binaryChar[k]='0'; 
		}  

		binaryChar[8]='\0';
		int j = 0;  
		for(j;j<8;j++){ 
			char c = binaryString[i+j];
			binaryChar[j]=c; 
		}
		result[i/8] = binaryStringtoChar(binaryChar); 

	}
	return result; 
}
/*
	Expects a stirng in ASCII characters in order to
	score how "english" the string sounds
	For now uses a naive letter frequency analysis:
	TODO: make it use a more interesting heuristic
*/
double score(char* string){
	double lookupRegChar[26];
	double stringFrequency[26];  
	int stringCharCount[26];  
	int index=0;
	for(index;index<26;index++){
		stringCharCount[index]=0; //ensure that the array is properly zeroed. 
	}
	double score=0; 
	//the following simply sets the character frequencies
	//in the english language, as these have no mathematical
	//significance we must simply manually insert them
	//NOTE: the array keys follow the natural lexicographic ordering
	//of our alphabet
	lookupRegChar[0]  = 0.08167;
	lookupRegChar[1]  = 0.01492;
	lookupRegChar[2]  = 0.02782;
	lookupRegChar[3]  = 0.04253;
	lookupRegChar[4]  = 0.127; 
	lookupRegChar[5]  = 0.02228; 
	lookupRegChar[6]  = 0.02015; 
	lookupRegChar[7]  = 0.06094;
	lookupRegChar[8]  = 0.06966;
	lookupRegChar[9]  = 0.00153;
	lookupRegChar[10] = 0.00772;
	lookupRegChar[11] = 0.04025; 
	lookupRegChar[12] = 0.02406;
	lookupRegChar[13] = 0.06749;
	lookupRegChar[14] = 0.07507; 
	lookupRegChar[15] = 0.01929; 
	lookupRegChar[16] = 0.0095; 
	lookupRegChar[17] = 0.05987; 
	lookupRegChar[18] = 0.06327; 
	lookupRegChar[19] = 0.09056; 
	lookupRegChar[20] = 0.02758;
	lookupRegChar[21] = 0.00978;
	lookupRegChar[22] = 0.02360;
	lookupRegChar[23] = 0.00150; 
	lookupRegChar[24] = 0.01975;
	lookupRegChar[25] = 0.0074; 

	int i=0; 
	int capitalCount=0; 
	for(i; i < strlen(string);i++){
		if(65<=(int)string[i]&&(int)string[i]<=90){
			capitalCount++;
			stringCharCount[(int)string[i]-65] +=1; 
		}else if(97<=(int)string[i]&&(int)string[i]<=122){
			stringCharCount[(int)string[i]-97] +=1; 
		}
	}
	int length = strlen(string); 
	//note do not remove the resting of i to 0
	i=0;
	for(i;i<26;i++){
		stringFrequency[i] = ((double)stringCharCount[i])/((double)length); 
		if( lookupRegChar[i] - 0.7*lookupRegChar[i]<= stringFrequency[i] && stringFrequency[i] <= lookupRegChar[i] +(0.7)*lookupRegChar[i]){
			score += 1 - 0.5*abs(lookupRegChar[i] - stringFrequency[i]); 
		}
	}
	if(capitalCount >= (0.3)*((double)length)){
		return score*0.5; 
	} else {
	return score; 
	}
}

char* solveSingleCypher(char* cypherText){
	double scoreList[256]; 
	int i = 0;
	for(i; i < 256;i++){
		scoreList[i] = score(binaryStringToASCII(xorCypher(hexToBinary(cypherText),(charToBinary((char)i)))));
	}
	i = 0;
	double max = 0;
	int maxKey = 0;  
	for(i;i<256;i++){
		if(scoreList[i]>=max){
			max = scoreList[i];
			maxKey = i; 
			printf("found new best string: %s\n",binaryStringToASCII(xorCypher(hexToBinary(cypherText),(charToBinary((char)maxKey))))); 
		}
	}
	return binaryStringToASCII(xorCypher(hexToBinary(cypherText),(charToBinary((char)maxKey)))); 
}
void main(){
	char* cypherText = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"; 
	printf("%s\n",solveSingleCypher(cypherText)); 
}