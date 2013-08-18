/*****************************************************************************
*   This program is free software: you can redistribute it and/or modify     *
*   it under the terms of the GNU General Public License as published by     *
*   the Free Software Foundation, either version 3 of the License, or        *
*   (at your option) any later version.                                      *
*                                                                            *
*   This program is distributed in the hope that it will be useful,          *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*   GNU General Public License for more details.                             *
*                                                                            *
*   You should have received a copy of the GNU General Public License        *
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
*   Author - shkrajat (https://github.com/shkrajat)                         *
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

int rand_lcg();
static int rseed = 0, multi = 1103515245;
static int inc = 12345, mod = 2147483647, num = 100;
 
inline void srand_lcg(int x)
{
	rseed = x;
}
 
inline int rand_lcg()
{
	return rseed = (rseed * multi + inc) % mod;
}
 
int main(int argc, char *argv[])
{
	int ca, format = 0, out = 0;
	char *file;
	
	srand_lcg((int)time(NULL));
	
	printf("\n\n*****************************************************************************");
	printf("\n   LCG RANDOM NUMBERS by - shkrajat");
	printf("\n      find me at - http://sf.net/users/shkrajat/");
	printf("\n*****************************************************************************\n");
	
	for(ca = 1; ca < argc; ca++)
	{
		if(!strcmp(argv[ca],"-n"))
		{
			ca++;
			if(ca < argc)
				num = atoi(argv[ca]);
		}
		else if(!strcmp(argv[ca],"-s"))
		{
			ca++;
			if(ca < argc)
				rseed = atoi(argv[ca]);
		}
		else if(!strcmp(argv[ca],"-a"))
		{
			ca++;
			if(ca < argc)
				multi = atoi(argv[ca]);
		}
		else if(!strcmp(argv[ca],"-c"))
		{
			ca++;
			if(ca < argc)
				inc = atoi(argv[ca]);
		}
		else if(!strcmp(argv[ca],"-m"))
		{
			ca++;
			if(ca < argc)
				mod = atoi(argv[ca]);
		}
		else if(!strcmp(argv[ca],"-o"))
		{
			ca++;
			out = 1;
			if(ca < argc)
				file = argv[ca];
		}
		else if(!strcmp(argv[ca],"-f"))
		{
			ca++;
			if(ca < argc)
				format = atoi(argv[ca]);
		}
		else if(!strcmp(argv[ca],"-h"))
		{
			printf("\nUSAGE :: >>%s [option] <enter>",argv[0]);
			printf("\nOPTIONS are");
			printf("\n   -a");
			printf("   the multiplier to use. default = 1103515245");
			printf("\n   -c");
			printf("   the increment to use. default = 12345");
			printf("\n   -m");
			printf("   the modulus to use. default = 2147483647");
			printf("\n   -s");
			printf("   the initial seed to use. default = time(NULL)");
			printf("\n   -n");
			printf("   the no of random numbers to be generated. default = 100");
			printf("\n   -o");
			printf("   the output file name to write numbers in. default = write to stdout");
			printf("\n   -f");
			printf("   the data separation format to use.");
			printf("\n           default is space separated values");
			printf("\n           1 is newline separated values");
			printf("\n           2 is comma separated values");
			exit(0);
		}
		else
		;
	}
	
	if(!out)
	{
		
		printf("\n\n*****************************************************************************");
		printf("\nLCG RANDOM NUMBERS by - LCG");
		printf("\n   find me at - http://sf.net/users/shkrajat/");
		printf("\nPARAMETERS are as -");
		printf("\nseed = %u, multiplier = %u, incremet = %u", rseed, multi, inc);
		printf("\nmod = %u, numbers = %u", mod, num);
		printf("\n*****************************************************************************\n");
		
		for(ca = 0; ca < num; ca++)
		{
			if(!(ca % 7))
				printf("\n");
			else
				printf(" ");
			printf("%u",rand_lcg());
		}
	}
	else
	{
		FILE *fp;
		fp = fopen(file, "w");
		
		fprintf(fp, "#****************************************************************************");
		fprintf(fp, "\n#LCG RANDOM NUMBERS by - LCG");
		fprintf(fp, "\n#   find me at - http://sf.net/users/shkrajat/");
		fprintf(fp, "\n#PARAMETERS are as -");
		fprintf(fp, "\nseed = %u, multiplier = %u, incremet = %u", rseed, multi, inc);
		fprintf(fp, "\nmod = %u, numbers = %u, fomat = %u", mod, num, format);
		fprintf(fp, "\n#****************************************************************************");
		
		if(format == 1)
		{
			for(ca = 0; ca < num; ca++)
			{
				fprintf(fp, "\n");
				fprintf(fp, "%u", rand_lcg());
			}
		}
		else if(format == 2)
		{
			for(ca = 0; ca < num; ca++)
			{
				if(!(ca % 7))
					fprintf(fp, "\n");
				else
					fprintf(fp, ",");
				fprintf(fp, "%u", rand_lcg());
			}
		}
		else
		{
			for(ca = 0; ca < num; ca++)
			{
				if(!(ca % 7))
					fprintf(fp, "\n");
				else
					fprintf(fp, " ");
				fprintf(fp, "%u", rand_lcg());
			}
		}
	}
	
	return 0;
}
