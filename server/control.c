#include<stdio.h>

int main()
{
	while (1)
	{
		char val='0';

		scanf("%c",&val);
		printf("%c",val);

		FILE *ctrl=fopen("ctrl.in","w");
		if(ctrl == NULL)
			printf("Error!");      
		else {
			fprintf(ctrl,"%c",'0');
			fclose(ctrl);
		}
	}

}
