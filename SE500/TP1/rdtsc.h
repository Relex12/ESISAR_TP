#ifndef __RDTSC_H__
#define __RDTSC_H__

#ifdef __x86_64__
static inline unsigned long long read_tsc (void)
{
	unsigned hi, lo;

	asm volatile ("lfence\n\trdtsc\n\t" : "=d" (hi), "=a" (lo) : : "memory");

	return ((unsigned long long)hi << 32) | lo;
}
#elif __i386__
static inline unsigned long long read_tsc (void)
{
	unsigned long long value;

	asm volatile ("lfence\n\trdtsc\n\t" : "=A" (value) : : "memory");

	return value;
}
#endif


#endif // __RDTSC_H__
