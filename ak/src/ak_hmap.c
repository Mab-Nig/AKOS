#include "ak_hmap.h"
#include "ak_list.h"
#include <stdint.h>

int ak_hmap_ins(ak_hmap_t *hmap, int key, void *item) {
  if (!hmap || !hmap->tbl || !hmap->tbl_sz) {
    return -1;
  }
  if (!item) {
    return 0;
  }

  size_t bucket = key % hmap->tbl_sz;
  void **ent = &hmap->tbl[bucket];
  void **end = &hmap->ends[bucket];
  if (!(*ent)) {
    *ent = *end = item;
  } else {
    *end = ak_list_ins_aft(*end, item, hmap->offset);
  }
  return *ent ? 0 : -1;
}

int ak_hmap_rm(ak_hmap_t *hmap, int key, void *item) {
  if (!hmap || !hmap->tbl || !hmap->tbl_sz) {
    return -1;
  }
  if (!item) {
    return 0;
  }

  size_t bucket = key % hmap->tbl_sz;
  void **ent = &hmap->tbl[bucket];
  void **end = &hmap->ends[bucket];
  int ret;
  
  if (!(*ent)) {
    ret = -1;
    
  } else {
    ret = 0;

    ak_list_node_t *node = FWD_OFFSET(ak_list_node_t *, item, hmap->offset);
    if (*end == item) {
      *end = node->prev;
    }
    if (*ent == item) {
      *ent = node->next;
    }
    ak_list_rm(node, hmap->offset);
  }

  return ret;
}
