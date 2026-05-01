#ifndef PORT_GCC_CPU_H
#define PORT_GCC_CPU_H

#ifndef PORT_CLZ
#  define PORT_CLZ(num) __builtin_clz(num)
#endif /* PORT_CLZ */
#ifndef PORT_CTZ
#  define PORT_CTZ(num) __builtin_ctz(num)
#endif /* PORT_CTZ */
#ifndef PORT_CLZLL
#  define PORT_CLZLL(num) __builtin_clzll(num)
#endif /* PORT_CLZLL */
#ifndef PORT_CTZLL
#  define PORT_CTZLL(num) __builtin_ctzll(num)
#endif /* PORT_CTZLL */

#endif /* PORT_GCC_CPU_H */
