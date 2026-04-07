#include "ak_list.h"

#include <stddef.h>
#include <stdint.h>

ak_list_node_t *
ak_list_ins_bef(ak_list_node_t *pos, ak_list_node_t *new_node, size_t offset) {
  if (!pos || !new_node) {
    return NULL;
  }

  new_node->next = (uint8_t *)pos - offset;
  new_node->prev = (uint8_t *)pos->prev - offset;
  if (pos->prev) {
    RM_OFFSET(ak_list_node_t *, pos->prev, offset)->next = new_node;
  }
  pos->prev = new_node;
  return new_node;
}

ak_list_node_t *
ak_list_ins_aft(ak_list_node_t *pos, ak_list_node_t *new_node, size_t offset) {
  if (!pos || !new_node) {
    return NULL;
  }

  new_node->prev = (uint8_t *)pos - offset;
  new_node->next = (uint8_t *)pos->next - offset;
  if (pos->next) {
    RM_OFFSET(ak_list_node_t *, pos->next, offset)->prev = new_node;
  }
  pos->next = new_node;
  return new_node;
}

ak_list_node_t *ak_list_rm(ak_list_node_t *pos, size_t offset) {
  if (!pos) {
    return NULL;
  }

  if (pos->prev) {
    RM_OFFSET(ak_list_node_t *, pos->prev, offset)->next = pos->next;
  }
  if (pos->next) {
    RM_OFFSET(ak_list_node_t *, pos->next, offset)->prev = pos->prev;
  }
  return pos->next;
}
