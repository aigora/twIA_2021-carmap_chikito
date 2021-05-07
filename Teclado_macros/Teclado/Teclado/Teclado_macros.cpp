#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "SerialClass/SerialClass.h"

#define BUFF 200

typedef struct{
	int n,s,e,o;
}pulsation;

/*functions' prototypes*/
void connect(Serial*, char[]);
bool compare(char[],char[]);
void disconnect(Serial*,char[]);

void main() {
	Serial* Arduino;
	char port[] = "COM3", char buffer_in[BUFF];
	char north[]="pressing key: N",south[]="pressing key: S";
	char east[]="pressing key: E",west[]="pressing key: O";
	int nBytes = 0,count_n=0,count_s=0,count_e=0,count_o=0;
	int counter=0;
	pulsation p0={count_n,count_s,count_e,count_o};
	pulsation*p=(pulsation*)malloc(BUFF*sizeof(pulsation));
	*(p+0)={count_n,count_s,count_e,count_o};
	connect(Arduino, port);
	while (Arduino->IsConnected()) {
		nBytes=Arduino->ReadData(buffer_in,BUFF);
		if(nBytes!=-1) {
			buffer_in[nBytes]='\0';
			if(compare(buffer_in,north)==true)count_n++;
			if(compare(buffer_in,south)==true)count_s++;
			if(compare(buffer_in,east)==true)count_e++;
			if(compare(buffer_in,west)==true)count_o++;
			counter++;
			if(counter==BUFF-1)p=(pulsation*)realloc(p,BUFF);
			*(p+counter)={count_n,count_s,count_e,count_o};
		}
	}
}

/*set up connection with Arduino in COM3 port*/
void connect(Serial* Arduino, char port[]) {
	Arduino = new Serial((char*)port);
}

/*compares two strings and returns true if they are the same; 0 if not;*/
bool compare(char str1[],char str2[]){
	if(sizeof(str1)!=sizeof(str2)) return false;
	else{
		int*i=(int*)calloc(1,sizeof(int));
		while(str1[*i]!='\0'){ if(str1[*i]!=str2[*i]) return false; }
		return true;
	}
}

/*ends connection with Arduino and closes the program;*/
void disconnect(Serial* Arduino,char port[]){
	Arduino->~Serial();
	exit(1);
}