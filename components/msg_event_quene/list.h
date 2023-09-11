#ifndef _LIST_H
#define _LIST_H
#include <pthread.h>
#define _offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
// #define container_of(ptr, type, member) (	\
// 	{			\
// 	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
// 	(type *)( (char *)__mptr - _offsetof(type,member) );	\
// 	}	\
// 	)

#ifndef container_of
#define container_of(ptr, type, member)					\
	({								\
		const __typeof__(((type *) NULL)->member) *__mptr = (ptr);	\
		(type *) ((char *) __mptr - offsetof(type, member));	\
	})
#endif


#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)	
	
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

struct wrt_list_head 
{
	struct wrt_list_head *next, *prev;
};
typedef struct list_queue_head
{
	struct wrt_list_head list;
	pthread_mutex_t mutex;
	pthread_cond_t  ready;
}LIST_QUEUE_HEAD;

typedef struct list_queue_head_rw
{
	struct wrt_list_head list;
}LIST_QUEUE_HEAD_RW;


static inline void INIT_wrt_list_head(struct wrt_list_head *list)
{
	list->next = list;
	list->prev = list;
}
static inline void __list_push(struct wrt_list_head *new_add,
			      struct wrt_list_head *prev,
			      struct wrt_list_head *next)
{
	next->prev = new_add;
	new_add->next = next;
	new_add->prev = prev;
	prev->next = new_add;
}

static inline void list_push(struct wrt_list_head *new_add, struct wrt_list_head *head)
{
	__list_push(new_add, head, head->next);
}
static inline void list_push_tail(struct wrt_list_head *new_add, struct wrt_list_head *head)
{
	__list_push(new_add, head->prev, head);
}
static inline void __list_del(struct wrt_list_head * prev, struct wrt_list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void wrt_list_del(struct wrt_list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}
static inline struct wrt_list_head * list_pop(struct wrt_list_head *head)
{
	struct wrt_list_head* pop_entry = NULL;
	if(head->prev == head ||  head->next == head )
		return NULL;
	pop_entry = head->prev;
	wrt_list_del(pop_entry);
	return pop_entry;
}
#endif 



