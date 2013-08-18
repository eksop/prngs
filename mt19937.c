/* A C-program for MT19937: Integer number version             */
/*   genrand() generates one pseudorandom integer number       */
/*   Coded by Takuji Nishimura, considering the suggestions by */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.           */

/* Modified by - shkrajat in Aug 2013                          */
/*    find me at - https://github.com/shkrajat                    */

/* This library is free software; you can redistribute it and/or   */
/* modify it under the terms of the GNU Library General Public     */
/* License as published by the Free Software Foundation; either    */
/* version 2 of the License, or (at your option) any later         */
/* version.                                                        */
/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
/* See the GNU Library General Public License for more details.    */
/* You should have received a copy of the GNU Library General      */
/* Public License along with this library; if not, write to the    */
/* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */ 
/* 02111-1307  USA                                                 */

/* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
/* Any feedback is very welcome. For any question, comments,       */
/* see http://www.math.keio.ac.jp/matumoto/emt.html or email       */
/* matumoto@math.keio.ac.jp                                        */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Period parameters */

#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   

#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

static unsigned long mt[N]; /* the array for the state vector  */
static int mti = N + 1; /* mti==N+1 means mt[N] is not initialized */
static long num = 100, mod, rseed;

/* initializing the array with a NONZERO seed */

void sgenrand(unsigned long seed)	
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    
	mt[0] = seed & 0xffffffff;
    for (mti = 1; mti < N; mti++)
        mt[mti] = (69069 * mt[mti - 1]) & 0xffffffff;
}

unsigned long /* generating reals */
/* unsigned long */ /* for integer generation */
genrand()
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N + 1)   /* if sgenrand() has not been called, */
            sgenrand(rseed); /* a default initial seed is used   */

        for (kk = 0; kk < N - M; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk < N - 1; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }
  
    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    return y;
}

int main(int argc, char *argv[])
{
	int ca, format = 0, out = 0;
	char *file;
	
	rseed = time(NULL);
	
	printf("\n\n*****************************************************************************");
	printf("\n   MT19937 RANDOM NUMBERS by - shkrajat");
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
		printf("\nMT19937 RANDOM NUMBERS by - LCG");
		printf("\n   find me at - http://sf.net/users/shkrajat/");
		printf("\nPARAMETERS are as -");
		printf("\nseed = %u", rseed);
		printf("\nmod = %u, numbers = %u", mod, num);
		printf("\n*****************************************************************************\n");
		
		for(ca = 0; ca < num; ca++)
		{
			if(!(ca % 7))
				printf("\n");
			else
				printf(" ");
			printf("%u",genrand());
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
		fprintf(fp, "\nseed = %u", rseed);
		fprintf(fp, "\nmod = %u, numbers = %u, fomat = %u", mod, num, format);
		fprintf(fp, "\n#****************************************************************************");
		
		if(format == 1)
		{
			for(ca = 0; ca < num; ca++)
			{
				fprintf(fp, "\n");
				fprintf(fp, "%u", genrand());
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
				fprintf(fp, "%u", genrand());
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
				fprintf(fp, "%u", genrand());
			}
		}
	}
	
	return 0;
}
