#include <stdio.h>
#include <stdbool.h>

bool changeBool(bool *change, int set){
	if (!set) change = false;
	if (set)  change = true;
}

int main(){
	
	bool testBool = false;	

	printf("Value of test is %s\n", testBool ? "true" : "false");
	changeBool(&testBool, 1); 
	printf("Value of test is %s\n", testBool ? "true" : "false");
	return 0;
}
