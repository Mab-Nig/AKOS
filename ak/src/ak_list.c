#include "ak_list.h"

#include <stddef.h>
#include <stdint.h>

void *
ak_list_ins_bef(ak_list_node_t *pos, ak_list_node_t *new_node, size_t offset) {
  if (!pos || !new_node) {
    return NULL;
  }

  void *new_wrapper = (uint8_t *)new_node - offset;
  new_node->next = (uint8_t *)pos - offset;
  if (pos->prev) {
    new_node->prev = pos->prev;
    FWD_OFFSET(ak_list_node_t *, pos->prev, offset)->next = new_wrapper;
  }
  pos->prev = new_wrapper;
  return new_wrapper;
}

void *
ak_list_ins_aft(ak_list_node_t *pos, ak_list_node_t *new_node, size_t offset) {
  if (!pos || !new_node) {
    return NULL;
  }

  void *new_wrapper = (uint8_t *)new_node - offset;  
  new_node->prev = (uint8_t *)pos - offset;
  if (pos->next) {
    new_node->next = pos->next;
    FWD_OFFSET(ak_list_node_t *, pos->next, offset)->prev = new_wrapper;
  }
  pos->next = new_wrapper;
  return new_wrapper;
}

void *ak_list_rm(ak_list_node_t *pos, size_t offset) {
  if (!pos) {
    return NULL;
  }

  if (pos->prev) {
    FWD_OFFSET(ak_list_node_t *, pos->prev, offset)->next = pos->next;
  }
  if (pos->next) {
    FWD_OFFSET(ak_list_node_t *, pos->next, offset)->prev = pos->prev;
  }
  return pos->next;
}
