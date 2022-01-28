#include <string.h>
#include <stdio.h>
#include "util_rbtree.h"

#define N 16
#define MAX 2*N
struct travel_res{
	int nr;
	int arr[MAX];
}res;

void opera(util_rbtree_node_t *rbnode, void *data)
{
	struct travel_res *res = (struct travel_res *)data;
	if (rbnode->data){
		res->arr[res->nr++] = *(int *)rbnode->data;
	}
}

long hash_func(long data)
{
	return data;
}

int main(int argc, char *argv[])
{
	int i = 0;
	util_rbtree_t rbtree;
	util_rbtree_node_t  *rbnode = NULL, *node = NULL;

	int arr[MAX];
	for (i=0; i<N; ++i)
		arr[i] = rand()%100;
	for (i=0; i<N; ++i){
		if (i && !(i&7))
			printf("\n");
		printf("%3d ", arr[i]);
	}
	printf("\n");

	util_rbtree_init(&rbtree);

	printf("\n\ncreate rbtree:\n");
	for (i=0; i<N; ++i){
		

		rbnode = (util_rbtree_node_t  *)malloc(sizeof(util_rbtree_node_t));
		if (!rbnode){
			printf("%s:%d  alloc util_rbtree_node_t failed\n", __func__, __LINE__);
			goto out;
		}

		memset(rbnode, 0, sizeof(util_rbtree_node_t));
		rbnode->key = hash_func(arr[i]);
	        rbnode->data = &arr[i];
		util_rbtree_insert(&rbtree, rbnode);
		printf("insert elment: %d\n", *(int *)rbnode->data);	
	}

	arr[N] = arr[N-1];
	rbnode = util_rbtree_search(&rbtree, hash_func(arr[N]));
	if (rbnode){
		printf("elem already existed: node:%p value:%d\n", rbnode, *(int *)rbnode->data);
		util_rbtree_delete(&rbtree, rbnode);
		free(rbnode); //add by zhaocw at 2022.1.28
		rbnode = util_rbtree_search(&rbtree, hash_func(arr[N]));
		printf("elem delete %s\n", !rbnode?"success":"fail");
	}


	long key = 0;
	char input_str[128];
	input_str[sizeof(input_str)-1] = 0;
	printf("\ntest util_rbtree_search, and input key:");
	gets(input_str);
	if (input_str[0]){
		key = atoi(input_str);
		rbnode = util_rbtree_search(&rbtree, key);
		if (rbnode)
			printf("found key:%ld value:%d\n", key, *(int *)rbnode->data);
		else
			printf("not found key:%ld\n", key);		
	}

	printf("\ntest util_rbtree_lookup, and input key:");
	gets(input_str);
	if (input_str[0]){
		key = atoi(input_str);
		rbnode = util_rbtree_lookup(&rbtree, key);
		if (rbnode)
			printf("found key:%ld value:%d\n", key, *(int *)rbnode->data);
		else
			printf("not found key:%ld\n", key);
	}

	printf("\ntest rbtree_mid_travel:\n");
	struct travel_res res;
	memset(&res, 0, sizeof(res));
	util_rbtree_mid_travel(&rbtree, opera, &res);
	for (i=0; i<res.nr; ++i){
		if (i && !(i&7))
			printf("\n");
		printf("%3d ", res.arr[i]);
	}
	


out:	
	printf("\n\ndelete rbtree:\n");
	while(!util_rbtree_isempty(&rbtree)){
		rbnode = rbtree.root;
		util_rbtree_delete(&rbtree, rbnode);
		
		printf("remove element: %d\n", *(int *) rbnode->data);
		rbnode->data = NULL;
		free(rbnode);
		rbnode = NULL;
	}

	return 0;
}
