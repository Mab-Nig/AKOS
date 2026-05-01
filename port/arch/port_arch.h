#ifndef PORT_ARCH
#define PORT_ARCH

#if defined(__arm__) || defined(__aarch64__)
#  include "arm/port_arm.h"
#endif /* defined(__arm__) || defined(__aarch64__) */

#endif /* PORT_ARCH */
