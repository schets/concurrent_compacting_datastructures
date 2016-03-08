/*
 * Contains assembler routines for performing a store to
 * a reference and determining if a sigsegv occured within
 * the store routine
*/

/*
 * These seemingly simple routines are written in assembler
 * to keep them out of the grasp of the optimizing C compiler,
 * and make it easy for the bad_write signal handler to
 * repair the calling pointer.
 */

.section text,

/*
 * This function performs a store to the value and returns a potentially
 * modified parent pointer. When this is called, the current parent value
 * is expected to be stored in RAX
 *
 * Params: (store_addr: Obj ** - RDI,
            new_val: Obj* - RSI,
            parent_val: Obj* - RDX)
 *
 * Returns: new_parent_val: Obj* - RAX
 *
 * Some tricky calling conventions and dubious gcc manipulation
 * may allow us to elide the explicit store into rax and instead convince
 * gcc to just keep the object pointer in rax. But I do not think that is
 * worth it for a probably minor performance gain, with the risk of the
 * optimizer breaking everything
 *
 */

.globl ref_store
.align 4
ref_store:
  mov %rdx, %rax
  /* Possibly faulting! */
  mov %rsi, (%rdi)
  /* If a fault occurs, RAX will be reloaded with the new address */

ref_store_end:
  ret

/*
 * This function determines if the instruction pointer
 * was inside the ref_store routine
 *
 * Params: fault_instr_ptr: void * - RDI
 *
 * Returns: was_in_ref_store: bool - RAX
 */
.globl segv_in_ref_store
.align 4
segv_in_ref_store:
  xor %rax, %rax
  xor %rdx, %rdx
  mov ref_store(%rip), %rsi
  cmpq %rsi, %rdi
  setae %dl
  mov ref_store_end(%rip), %rsi
  cmpq %rsi, %rdi
  setbe %al
  and %rdx, %rax
  ret


