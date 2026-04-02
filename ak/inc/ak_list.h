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

/** Insert new_node before pos.
 * @return new_node if success. NULL if not.
 */
ak_list_node_t *ak_list_ins_bef(ak_list_node_t *pos, ak_list_node_t *new_node);

/** Insert new_node after pos.
 * @return new_node if success. NULL if not.
 */
ak_list_node_t *ak_list_ins_aft(ak_list_node_t *pos, ak_list_node_t *new_node);

/** Remove node at pos.
 * @return pos->next if success. NULL if not.
 */
ak_list_node_t *ak_list_rem(ak_list_node_t *pos);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_LIST_H */
