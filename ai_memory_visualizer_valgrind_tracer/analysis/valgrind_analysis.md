# Valgrind Analysis

This file explains the Valgrind results for the programs in the `programs` directory.

## stack_example

Valgrind reported:
- 0 errors
- 0 memory leaks

This program mainly uses stack memory. Each recursive call to `walk_stack()` creates a new stack frame.

For example:

    walk_stack(0)
    walk_stack(1)
    walk_stack(2)
    walk_stack(3)

Each call has its own local variable called `marker`:

    depth 0 -> marker = 0
    depth 1 -> marker = 10
    depth 2 -> marker = 20
    depth 3 -> marker = 30

When a function returns, its stack frame is removed automatically. That is why Valgrind did not report any memory errors or leaks.

---

## heap_example

Valgrind reported:

    6 bytes in 1 block are definitely lost

This is a memory leak.

The memory was allocated inside `person_new()` for Alice's name.

The string `"Alice"` needs 5 characters plus `\0`, so it uses 6 bytes.

The problem happens when the program calls:

    person_free_partial(alice);

Inside this function, only the Person structure is freed:

    free(p);

But the memory used by `p->name` is not freed.

Before freeing:

    alice
      |
      v
    [ Person ]
        |
        +----> "Alice"

After `person_free_partial(alice)`:

    [ Person ] -> freed
    "Alice"    -> still allocated in heap

There is no valid pointer left to free `"Alice"`.

This is a memory leak caused by lost ownership.

Valgrind reported:

    definitely lost: 6 bytes

---

## aliasing_example

Valgrind reported:

    Invalid read of size 4
    Invalid write of size 4
    Invalid read of size 4

The problem is caused by pointer aliasing.

First:

    b = a;

Now both pointers point to the same heap memory:

    a ----\
           ---> heap array
    b ----/

Then:

    free(a);

The heap memory is freed, but `b` still contains the same old address.

So both pointers are now dangling pointers:

    a -> dangling pointer
    b -> dangling pointer

Then the program reads:

    b[2]

Valgrind reports an `Invalid read of size 4` because the memory was already freed.

Then the program writes:

    b[3] = 1234;

Valgrind reports an `Invalid write of size 4` because the program is writing to freed memory.

The program then reads `b[3]` again, which causes another invalid read.

This type of memory misuse is called `use-after-free`.

There is no memory leak in this example because the allocated heap block was freed. The problem is that the program continues using a pointer to that freed block.

---

## crash_example

Valgrind reported:

    Invalid write of size 4

The program also ended with:

    Segmentation fault

The program starts with:

    int n = 0;

Then it calls:

    nums = allocate_numbers(n);

Inside `allocate_numbers()` there is this check:

    if (n <= 0)
        return NULL;

Because `n` is 0, the function returns `NULL`.

Therefore:

    nums = NULL

The program then tries to execute:

    nums[0] = 42;

This is equivalent to trying to write through the `NULL` pointer.

The address is:

    0x0

Valgrind reports:

    Address 0x0 is not stack'd, malloc'd or (recently) free'd

The program then terminates with `SIGSEGV`.

This error is a `NULL pointer dereference`.

Valgrind also reported 1024 bytes as still reachable when the program crashed. This is not the main memory error in this example. The program terminated abnormally before normal runtime cleanup. The important error is the invalid write through the NULL pointer.

---

## AI Review and Correction

While reviewing the programs, an AI explanation could incorrectly say:

    After free(a), pointer b becomes NULL.

This explanation is incorrect.

In `aliasing_example`, both `a` and `b` contain the same address because:

    b = a;

Calling:

    free(a);

releases the heap block, but `free()` does not automatically set `a` or `b` to `NULL`.

Before `free(a)`:

    a ----\
           ---> heap memory
    b ----/

After `free(a)`:

    a -> old address
    b -> old address

The heap object's lifetime has ended, but both pointers still contain its old address. They are dangling pointers.

Therefore, accessing `b[2]` or `b[3]` is a use-after-free.

Another possible incorrect explanation is:

    heap_example frees Alice completely.

This is also incorrect.

The program calls `person_free_partial(alice)`, which only performs:

    free(p);

This frees the `Person` object but does not free `alice->name`.

The name was allocated separately on the heap, so it must also be freed separately.

Because the pointer to the name is lost when the Person object is freed, the 6-byte allocation containing `"Alice"` becomes definitely lost.

---

## Summary

### stack_example
- 0 Valgrind errors
- No memory leaks
- Recursive calls create separate stack frames
- Stack variables are automatically removed when their functions return

### heap_example
- 1 Valgrind error
- 6 bytes definitely lost
- Memory leak caused by Alice's name not being freed
- The Person object is freed while its separate name allocation remains in the heap
- This is lost ownership

### aliasing_example
- 3 Valgrind errors
- 2 invalid reads
- 1 invalid write
- `a` and `b` point to the same heap allocation
- `free(a)` ends the lifetime of that allocation
- `b` becomes a dangling pointer
- Using `b` after the free causes use-after-free errors
- No heap leak was reported

### crash_example
- 1 Valgrind error
- Invalid write of size 4
- `allocate_numbers(0)` returns NULL
- The program tries to execute `nums[0] = 42`
- This is a NULL pointer dereference
- The program terminates with SIGSEGV