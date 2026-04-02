#ifndef AK_PRIO_H
#define AK_PRIO_H

#include "ak_cfg.h"

#include <stdint.h>

#if (AK_CFG_PRIO_MAX <= 255)
typedef uint8_t ak_prio_t;
#elif (AK_CFG_PRIO_MAX <= (1 << 16) - 1)
typedef uint16_t ak_prio_t;
#else
typedef uint32_t ak_prio_t;
#endif /* AK_CFG_PRIO_MAX */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int ak_prio_bit_set(ak_prio_t prio);
int ak_prio_bit_clear(ak_prio_t prio);
ak_prio_t ak_prio_get_max(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_PRIO_H */
