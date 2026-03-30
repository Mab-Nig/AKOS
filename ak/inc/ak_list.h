#ifndef AK_LIST_H
#define AK_LIST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct __ak_list_node ak_list_node_t;
struct __ak_list_node {
  ak_list_node_t *prev;
  ak_list_node_t *next;
};

/** Insert new_node before pos. Insert at end if pos is NULL.
 * @return new_node if success. NULL if not.
 */
ak_list_node_t *ak_list_ins(ak_list_node_t *pos, ak_list_node_t *new_node);

/** Remove node at pos.
 * @return pos->next if success. NULL if not.
 */
ak_list_node_t *ak_list_rem(ak_list_node_t *pos);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_LIST_H */
