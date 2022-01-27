#include "inet.h"

/*
 * ./a.out 192.168.100.1-192.168.100.128:1024-65535 
 * ./a.out [2001::1-2001::fe:01]:1000
 * ./a.out [2001::1-2001::fe:01]:1000-2000
 * */

int main(int argc, char *argv[])
{
	char buf[512];
	struct inet_addr_range range;
	int af = -1;

	#if 0
	af = AF_INET;
	range.min_addr.in.s_addr  = htonl(0x0a0a0a01);
	range.max_addr.in.s_addr  = htonl(0x0a0a0afe);
	range.min_port = htons(1000);
	range.max_port = htons(2000);
	inet_addr_range_dump(af, &range, buf, sizeof(buf)-1);
	printf("%s\n\n", buf);
	#else
	if (argc > 1){
		if (EDPVS_OK  == inet_addr_range_parse(argv[1], &range, &af)){
		    inet_addr_range_dump(af, &range, buf, sizeof(buf)-1);
		    printf("%s\n\n", buf);
		}
	}
	#endif

	#if 0
	struct inet_stats st;
	int len = sizeof(st);
	uint64_t *ptr = (uint64_t *)&st;
	while(len > 0){
		*ptr++ = rand()%0xffffff;
		len -= sizeof(uint64_t);
	}

	inet_stats_dump("statistics:",  NULL, &st);
	#endif

	return 0;
}
