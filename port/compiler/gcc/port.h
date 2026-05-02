#ifndef PORT_GCC_CPU_H
#define PORT_GCC_CPU_H

#define PORT_CLZ(num)   __builtin_clz(num)
#define PORT_CTZ(num)   __builtin_ctz(num)
#define PORT_CLZLL(num) __builtin_clzll(num)
#define PORT_CTZLL(num) __builtin_ctzll(num)

#endif /* PORT_GCC_CPU_H */
