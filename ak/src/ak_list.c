#include "ak_list.h"

#include <stddef.h>

ak_list_node_t *ak_list_ins_bef(ak_list_node_t *pos, ak_list_node_t *new_node) {
  if (!pos || !new_node) {
    return NULL;
  }

  new_node->next = pos;
  new_node->prev = pos->prev;
  if (pos->prev) {
    pos->prev->next = new_node;
  }
  pos->prev = new_node;
  return new_node;
}

ak_list_node_t *ak_list_ins_aft(ak_list_node_t *pos, ak_list_node_t *new_node) {
  if (!pos || !new_node) {
    return NULL;
  }

  new_node->prev = pos;
  new_node->next = pos->next;
  if (pos->next) {
    pos->next->prev = new_node;
  }
  pos->next = new_node;
  return new_node;
}
  
ak_list_node_t *ak_list_rem(ak_list_node_t *pos) {
  if (!pos) {
    return NULL;
  }

  if (pos->prev) {
    pos->prev->next = pos->next;
  }
  if (pos->next) {
    pos->next->prev = pos->prev;
  }
  return pos->next;
}
