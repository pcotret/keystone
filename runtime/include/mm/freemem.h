/**
 * @file freemem.h
 */
#ifndef __FREEMEM_H__
#define __FREEMEM_H__

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Get the next page in the list.
 * 
 * @param page A pointer to the current page.
 * @return The address of the next page in the list.
 */
#define NEXT_PAGE(page) *((uintptr_t*)page)
/**
 * @brief Check if a page list is empty.
 * 
 * @param list The page list to check.
 * @return True if the list is empty, false otherwise.
 */
#define LIST_EMPTY(list) ((list).count == 0 || (list).head == 0)
/**
 * @brief Initialize a page list to empty.
 * 
 * @param list The list to initialize.
 */
#define LIST_INIT(list) { (list).count = 0; (list).head = 0; (list).tail = 0; }

/**
 * @struct pg_list
 * @brief Structure representing a list of free pages.
 *
 * This structure tracks a singly-linked list of free memory pages,
 * including head and tail pointers and a count of pages.
 */
struct pg_list
{
	uintptr_t head;/**< Address of the first page in the list. */
	uintptr_t tail;/**< Address of the last page in the list. */
	unsigned int count; /**< Number of pages in the list. */
};
/**
 * @brief Initialize the simple physical allocator.
 *
 * @param base The base physical address of the memory region.
 * @param size The size of the memory region in bytes.
 */
void spa_init(uintptr_t base, size_t size);
/**
 * @brief Allocate a page of memory.
 *
 * @return The physical address of the allocated page, or 0 if none available.
 */
uintptr_t spa_get(void);
/**
 * @brief Allocate and zero a page of memory.
 *
 * @return The physical address of the allocated and zeroed page, or 0 if none available.
 */
uintptr_t spa_get_zero(void);

/**
 * @brief Free a previously allocated page of memory.
 *
 * @param page The physical address of the page to free.
 */
void spa_put(uintptr_t page);
/**
 * @brief Get the number of available free pages.
 *
 * @return The number of free pages currently available.
 */
unsigned int spa_available();
#endif
