#include "ak_mem.h"
#include "ak_cfg.h"
#include "ak_list.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef AK_CFG_HEAP_SZ
#  define AK_MEM_SZ AK_CFG_HEAP_SZ
#else
#  define AK_MEM_SZ 0x200u
#endif /* AK_CFG_HEAP_SZ */

#ifdef AK_CFG_HEAP_ALIGN
#  define AK_MEM_ALIGN AK_CFG_HEAP_ALIGN
#else
#  define AK_MEM_ALIGN 4u
#endif /* AK_CFG_HEAP_ALIGN */

#ifdef AF_CFG_HEAP_CLEAR_ON_FREE
#  define AK_MEM_CLEAR_ON_FREE AF_CFG_HEAP_CLEAR_ON_FREE
#else
#  define AK_MEM_CLEAR_ON_FREE AF_CFG_HEAP_CLEAR_ON_FREE 0u
#endif /* AF_CFG_HEAP_CLEAR_ON_FREE */

#define AK_ALIGN_CEIL(ptr)                                                     \
  (((size_t)(ptr) + AK_MEM_ALIGN - 1) & ~(AK_MEM_ALIGN - 1))
#define AK_IS_ALIGNED(ptr) (!((size_t)(ptr) & (AK_MEM_ALIGN - 1)))
#define AK_BLK_HDR_SZ      AK_ALIGN_CEIL(sizeof(_ak_mem_blk_hdr_t))

typedef enum : uint8_t { AK_BLK_FREE, AK_BLK_BUSY } _ak_mem_blk_state_t;

typedef struct {
  ak_list_node_t node;
  size_t sz; /* size including header */
  _ak_mem_blk_state_t state;
} _ak_mem_blk_hdr_t;

static size_t _ak_mem_avail_sz;
static _ak_mem_blk_hdr_t *_ak_mem_first_blk_p;
static _ak_mem_blk_hdr_t *_ak_mem_last_blk_p;
static void *_ak_mem_start_p;

/* These two must stick together. */
/* clang-format off */
static _ak_mem_blk_hdr_t _ak_mem_ini_blk = {
  .node = {.prev = NULL, .next = NULL},
  .sz = AK_BLK_HDR_SZ + AK_MEM_SZ,
  .state = AK_BLK_BUSY
};
/* clang-format on */
static uint8_t
#ifdef __GNUC__
  __attribute__((aligned(AK_MEM_ALIGN)))
#endif /* __GNUC__ */
  _ak_mem_arr[AK_CFG_HEAP_SZ];

static void _ak_mem_init(void);
static _ak_mem_blk_hdr_t *_ak_mem_find_fit(size_t sz);
static _ak_mem_blk_hdr_t *_ak_mem_get_blk(void *addr);

void *ak_mem_alloc(size_t sz) {
  if (!_ak_mem_start_p) {
    _ak_mem_init();
  }
  if (!sz || _ak_mem_avail_sz < sz) {
    return NULL;
  }

  _ak_mem_blk_hdr_t *p_blk = _ak_mem_find_fit(sz);
  if (p_blk) {
    size_t blk_sz_busy = AK_BLK_HDR_SZ + sz;
    size_t blk_sz_free = p_blk->sz - blk_sz_busy;
    _ak_mem_avail_sz -= blk_sz_busy;
    p_blk->state = AK_BLK_BUSY;

    if (blk_sz_free >= AK_BLK_HDR_SZ) {
      _ak_mem_avail_sz -= AK_BLK_HDR_SZ;
      p_blk->sz = blk_sz_busy;

      _ak_mem_blk_hdr_t *p_new_blk =
        (_ak_mem_blk_hdr_t *)((size_t)p_blk + blk_sz_busy);
      p_new_blk->state = AK_BLK_FREE;
      p_new_blk->sz = blk_sz_free;
      ak_list_ins_aft(&p_blk->node, &p_new_blk->node);
      if (!p_new_blk->node.next) {
        _ak_mem_last_blk_p = p_new_blk;
      }
    }
  }
  return p_blk;
}

int ak_mem_free(void *addr) {
  if (!addr || !AK_IS_ALIGNED(addr)) {
    return -1;
  }

  int ret = 0;
  _ak_mem_blk_hdr_t *p_blk = _ak_mem_get_blk(addr);
  if (!p_blk || p_blk->state == AK_BLK_FREE) {
    ret = -1;
  } else {
    size_t blk_net_sz = p_blk->sz - AK_BLK_HDR_SZ;
    _ak_mem_avail_sz += blk_net_sz;
    p_blk->state = AK_BLK_FREE;
#ifdef AK_MEM_CLEAR_ON_FREE
    memset((void *)((size_t)p_blk + AK_BLK_HDR_SZ), 0, blk_net_sz);
#endif /* AK_MEM_CLEAR_ON_FREE */

    _ak_mem_blk_hdr_t *p_prev_blk = (_ak_mem_blk_hdr_t *)p_blk->node.prev;
    _ak_mem_blk_hdr_t *p_next_blk = (_ak_mem_blk_hdr_t *)p_blk->node.next;
    if (p_next_blk && p_next_blk->state == AK_BLK_FREE) {
      _ak_mem_avail_sz += AK_BLK_HDR_SZ;
      p_blk->sz += p_next_blk->sz;
      ak_list_rem(&p_next_blk->node);
#ifdef AK_MEM_CLEAR_ON_FREE
      memset(p_next_blk, 0, AK_BLK_HDR_SZ);
#endif /* AK_MEM_CLEAR_ON_FREE */
    }
    if (p_prev_blk && p_prev_blk->state == AK_BLK_FREE) {
      _ak_mem_avail_sz += AK_BLK_HDR_SZ;
      p_prev_blk->sz += p_blk->sz;
      ak_list_rem(&p_blk->node);
#ifdef AK_MEM_CLEAR_ON_FREE
      memset(p_blk, 0, AK_BLK_HDR_SZ);
#endif /* AK_MEM_CLEAR_ON_FREE */
    }
  }
  return ret;
}

void _ak_mem_init(void) {
  _ak_mem_avail_sz = AK_MEM_SZ;
  _ak_mem_first_blk_p = &_ak_mem_ini_blk;
  _ak_mem_last_blk_p = &_ak_mem_ini_blk;
#ifdef __GNUC__
  _ak_mem_start_p = &_ak_mem_arr;
#else
  _ak_mem_start_p = (void *)AK_ALIGN_CEIL(&_ak_mem_arr);
#endif /* __GNUC__ */
}

_ak_mem_blk_hdr_t *_ak_mem_find_fit(size_t sz) {
  _ak_mem_blk_hdr_t *p = _ak_mem_first_blk_p;
  for (; p; p = (_ak_mem_blk_hdr_t *)p->node.next) {
    if (p->sz - AK_BLK_HDR_SZ >= sz) {
      break;
    }
  }
  return p;
}

_ak_mem_blk_hdr_t *_ak_mem_get_blk(void *addr) {
  _ak_mem_blk_hdr_t *p = _ak_mem_first_blk_p;
  for (; p; p = (_ak_mem_blk_hdr_t *)p->node.next) {
    if ((size_t)p + AK_BLK_HDR_SZ == (size_t)addr) {
      break;
    }
  }
  return p;
}
