#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>

/*************************************************
root@2004a:/home/zcw# gcc -g test_backtrace.c  
root@2004a:/home/zcw# ./a.out 
[00] ./a.out(+0x127c) [0x5588545b027c]
[01] ./a.out(+0x13cc) [0x5588545b03cc]
[02] ./a.out(+0x1427) [0x5588545b0427]
[03] ./a.out(+0x143b) [0x5588545b043b]
[04] ./a.out(+0x144f) [0x5588545b044f]
[05] ./a.out(+0x1463) [0x5588545b0463]
[06] ./a.out(+0x1477) [0x5588545b0477]
[07] ./a.out(+0x1496) [0x5588545b0496]
[08] /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7f5cbaeb10b3]
[09] ./a.out(+0x114e) [0x5588545b014e]

root@2004a:/home/zcw# gcc -O0 -g test_backtrace.c 
root@2004a:/home/zcw# ./a.out 
[00] ./a.out(+0x127c) [0x5649c80b627c]
[01] ./a.out(+0x13cc) [0x5649c80b63cc]
[02] ./a.out(+0x1427) [0x5649c80b6427]
[03] ./a.out(+0x143b) [0x5649c80b643b]
[04] ./a.out(+0x144f) [0x5649c80b644f]
[05] ./a.out(+0x1463) [0x5649c80b6463]
[06] ./a.out(+0x1477) [0x5649c80b6477]
[07] ./a.out(+0x1496) [0x5649c80b6496]
[08] /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7fe257b520b3]
[09] ./a.out(+0x114e) [0x5649c80b614e]

root@2004a:/home/zcw# gcc test_backtrace.c -rdynamic 
root@2004a:/home/zcw# ./a.out 
[00] ./a.out(dpvs_backtrace+0x73) [0x556a0b54727c]
[01] ./a.out(func6+0x32) [0x556a0b5473cc]
[02] ./a.out(func5+0x12) [0x556a0b547427]
[03] ./a.out(func4+0x12) [0x556a0b54743b]
[04] ./a.out(func3+0x12) [0x556a0b54744f]
[05] ./a.out(func2+0x12) [0x556a0b547463]
[06] ./a.out(func1+0x12) [0x556a0b547477]
[07] ./a.out(main+0x1d) [0x556a0b547496]
[08] /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7f9b229c40b3]
[09] ./a.out(_start+0x2e) [0x556a0b54714e]
*************************************************/

#define TRACE_STACK_DEPTH_MAX       128

int dpvs_backtrace(char *buf, int len)
{
    int ii, depth, slen;
    char **trace;
    void *btbuf[TRACE_STACK_DEPTH_MAX] = { NULL };

    if (len <= 0)
        return 0;
    buf[0] = '\0';

    depth = backtrace(btbuf, TRACE_STACK_DEPTH_MAX);
    trace = backtrace_symbols(btbuf, depth);
    if (!trace)
        return 0;

    for (ii = 0; ii < depth; ++ii) {
        slen = strlen(buf);
        if (slen + 1 >= len)
            break;
        snprintf(buf+slen, len-slen-1, "[%02d] %s\n", ii, trace[ii]);
    }
    free(trace);

    return strlen(buf);
}


int func6()
{
	char buf[1024];
	int ret = dpvs_backtrace(buf, sizeof(buf)-1);
	if (ret > 0){
		buf[ret] = 0;
		printf("%s\n", buf);
	}
	return 0;
}
int func5(){return func6();}
int func4(){return func5();}
int func3(){return func4();}
int func2(){return func3();}
int func1(){return func2();}

int main(int argc, char *argv[])
{
	func1();
	return 0;
}
