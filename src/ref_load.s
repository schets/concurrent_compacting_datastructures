/*
 * Contains assembler routines for performing a store to
 * a reference and determining if a sigsegv occured within
 * the store routine
*/

/*
 * These seemingly simple routines are written in assembler
 * to keep them out of the grasp of the optimizing C compiler,
 * and make it easy for the bad_write signal handler to
 * repair the calling pointer. Also, the return conventions are
 * slightly different than the C calling convention
 */

.section text

/*
 * This function performs a store to the value, and updates the parent
 * pointer as needed
 * Params: (store_addr: Obj ** - RDI,
 *          parent_val: Obj ** - RAX,
 *          new_val: Obj* - RDX)
 *
 * Returns:
 *
 * Could try some optimizing around allowing the register update
 * from the signal handler to be directly updated as the object pointer
 * but who knows. Looks like asking for the wrath of an optimizing compiler
 *
 * Could also have user pass in parent value as well, but I figure that
 * will just be fresh on the stack and super quick to read. This is not
 * the general use case object loader, so may not need ultra optimizing
 */
.globl ref_store
.type ref_store, @function
ref_store:
 /* Load the current value of the parent object */
 mov rax
 /* Possibly faulting store of new_val to store_addr */
 mov rdx, (%rdi)
 /* Update parent address - if a fault occurs, RDX will be updated */

ref_store_end:
 ret

/*
 * This function determines if the instruction pointer
 * was inside the ref_store routine
 */
.globl segv_in_ref_store
.type segv_in_ref_store, @function
