#ifndef PORT_ARM_GCC_H
#define PORT_ARM_GCC_H

#include <stdint.h>

#ifdef __GNUC__
#  include "cmsis_gcc.h"

#  ifndef PORT_CLZ
#    define PORT_CLZ(num) __CLZ(num)
#  endif /* PORT_CLZ */

#  define PORT_EN_IRQ()             __enable_irq()
#  define PORT_DIS_IRQ()            __disable_irq()
#  define PORT_GET_IRQ_STATE()      __get_PRIMASK()
#  define PORT_SET_IRQ_STATE(state) __set_PRIMASK(state)
#endif /* __GNUC__ */

#endif /* PORT_ARM_GCC_H */
