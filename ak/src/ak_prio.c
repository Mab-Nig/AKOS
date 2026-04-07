#include "ak_prio.h"
#include "ak_cfg.h"
#include "port.h"

#include <stddef.h>

#ifdef AK_CFG_PRIO_MAX
#  define AK_PRIO_MAX AK_CFG_PRIO_MAX
#else
#  define AK_PRIO_MAX 255u
#endif /* AK_CFG_PRIO_MAX */

#define AK_NPRIO_PER_ENT sizeof(size_t)
#define AK_PRIO_BITSET_SZ                                                      \
  (((AK_PRIO_MAX >> AK_NPRIO_PER_ENT) << AK_NPRIO_PER_ENT) + 1)

static size_t _ak_prio_bitset[AK_PRIO_BITSET_SZ];

int ak_prio_bit_set(ak_prio_t prio) {
  if (!prio || prio > AK_CFG_PRIO_MAX) {
    return -1;
  }

  ak_prio_t ent = (prio >> AK_NPRIO_PER_ENT) << AK_NPRIO_PER_ENT;
  _ak_prio_bitset[ent] |= 1 << (ent & (AK_NPRIO_PER_ENT - 1));
  return 0;
}

int ak_prio_bit_clear(ak_prio_t prio) {
  if (prio > AK_CFG_PRIO_MAX) {
    return -1;
  }

  ak_prio_t ent = prio / AK_NPRIO_PER_ENT;
  _ak_prio_bitset[ent] &= ~(1 << (ent & (AK_NPRIO_PER_ENT - 1)));
  return 0;
}

ak_prio_t ak_prio_get_max(void) {
  ak_prio_t res = 0;
  for (int i = AK_PRIO_BITSET_SZ - 1; i; --i) {
    if (_ak_prio_bitset[i]) {
      res -= PORT_CLZ(_ak_prio_bitset[i]);
      break;
    }
    res -= AK_NPRIO_PER_ENT;
  }
  return res;
}
