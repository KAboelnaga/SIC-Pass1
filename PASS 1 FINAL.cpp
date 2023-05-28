#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
int  main()
{
	FILE *f1,*f2,*f3,*f4;
	char label[20], operat[20], operand[20], location[5] = "0000", instruction[20], null[100];
	int temp= 0, format, dec = 0, i = 0, spaces[100], x = 0, j = 0, key;
	f1 = fopen("in.txt","r");
	f2 = fopen("instruction.txt","r");
	f3 = fopen("out.txt","w");
	f4 = fopen("symbTable.txt","w");
	while(!feof(f1)){
		i = 0;
		spaces[j] = 0;
		fgets(null,100,f1);
		while(i < strlen(null)){
			if(null[i] == ' '){
				spaces[j]++;
			}
			i++;
		}
		j++;
	}
	rewind(f1);
	j = 0;
	while(!feof(f1)){
		if(spaces[j] > 3){
			fscanf(f1,"%s%s", operat, operand);
			key = 1;
	}
		else{
			fscanf(f1,"%s%s%s", label, operat, operand);
			key = 0;
		}
	if( strcmp(operat,"START") == 0){
		strcpy(location, operand);
		int k = 0;
 		for(i = 3 ; i >= 0 ; i--){
			int temp;
			if(operand[k] >= 'A'){
				temp = operand[k] - 55;
			}
			else temp = operand[k] - '0';
			dec += pow(16,i) * temp;
			k++;
		}
	}
	temp = dec;
	for(i = 3 ; i >= 0 ; i--){
		int remainder = temp % 16;
		temp /= 16;
		if(remainder > 9){
			location[i] = 'A' + remainder - 10;
		}
		else location[i] = remainder + '0';

	}
	if(key)
		fprintf(f3,"%s\t%s\t%s\n", location, operat, operand);
	else{
		fprintf(f3,"%s\t%s\t%s\t%s\n", location, label, operat, operand);
		fprintf(f4,"%s\t%s\t%s\t%s\n", location, label, operat, operand);
	}
while(!feof(f2)){
  	fscanf(f2,"%s%d",instruction,&format);
   	if(strcmp(operat,instruction) == 0){
    	dec += format;
   		break;
   		}
}
if(operat[0] == '&'){
	dec += 5;
}
if(operat[0] == '$'){
	dec += 6;
}
if(strcmp(operat,"WORD") == 0){
	dec += 3;
}
if(strcmp(operat,"RESW") == 0){
    dec += (3*atoi(operand));
}
if(strcmp(operat,"BYTE") == 0)
	if(operand[0] == 'C')
    	dec += strlen(operand)-3;
    else if(operand[0] == 'X')
		dec += (strlen(operand)-3)/2;
if(strcmp(operat,"RESB") == 0){
    dec += atoi(operand);
   }
   rewind(f2);
   j++;
   if(!strcmp(operat,"END"))
   		break;
}
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
return 0;
}
