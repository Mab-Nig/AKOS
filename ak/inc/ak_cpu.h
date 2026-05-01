#ifndef AK_CPU_H
#define AK_CPU_H

#include "port.h"

#define AK_CPU_CRIT_ENTER()                                                    \
  uint32_t irq_state = PORT_GET_IRQ_STATE();                                   \
  PORT_DIS_IRQ()
#define AK_CPU_CRIT_EXIT() PORT_SET_IRQ_STATE(irq_state)

#endif /* AK_CPU_H */
