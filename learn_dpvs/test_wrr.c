/***********************
 *https://blog.csdn.net/yangbodong22011/article/details/73369426
 wrr and smooth wrr
 * *********************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_NR 10
int arr[MAX_NR];
int nodes[MAX_NR];
int nr = 0;

int main(int argc, char *argv[])
{
	int loop = 0;
	int i;
	int best;
	int sum = 0;

	if (argc < 3 || strcmp(argv[1], "wrr") && strcmp(argv[1], "swrr") ){
		printf("usage: ./a.out {wrr|swrr} 5 1 1\n");
		return -1;
	}

	for (i=0; i<argc-2 && i<MAX_NR; ++i){
		nodes[i] = atoi(argv[i+2]);
		if (nodes[i] <= 0){
			printf("argv[%d]:%s is invalid\n", i+2, argv[i+2]);
			return -1;
		}
		++nr;
	}

	for (i=0; i<nr; ++i)
		printf("%2d  ", nodes[i]);
	printf("\n");

	printf("\nstart loop:\n");
	memcpy(arr, nodes, sizeof(int)*nr);

	if (!strcmp(argv[1], "wrr")){
	    while(1){
		best = 0;
		for (i=1; i<nr; ++i){
			if (arr[i] > arr[best])
				best = i;
		}

		if (arr[best] > 0){
			--arr[best];
			printf("[%d] %c\n", ++loop, 'a'+best);
		}else{
			memcpy(arr, nodes, sizeof(int)*nr);
		}
		
		sleep(1);		
	    }
	}
	else
	{
		for (i=0; i<nr; ++i)
			sum += arr[i];
		while(1){
			best = 0;
			for (i=1; i<nr; ++i){
				if (arr[i] > arr[best])
					best = i;
			}

			if (arr[best] > 0){
				printf("[%d] %c\n", ++loop, 'a'+best);

				arr[best] -= sum;
				for (i=0; i<nr; ++i)
					arr[i] += nodes[i];
			}else{
				printf("never reachable\n");
			}

			#if 1
			for (i=0; i<nr; ++i)
			    printf("%2d  ", arr[i]);
			printf("\n\n");
			#endif

			sleep(1);
		}
	}

	return 0;
}
