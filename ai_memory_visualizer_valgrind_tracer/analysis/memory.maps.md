Memory Maps Analysis

This document analyzes the memory behavior of the programs in the programs/ directory.

The programs are:

stack_example.c

heap_example.c

aliasing_example.c

crash_example.c

The goal is to distinguish stack memory from heap memory, track pointer values and aliases, explain object lifetimes, and identify invalid memory operations.

1. stack_example.c

Purpose

This program demonstrates recursive function calls and how each call creates its own stack frame.

main() calls:

walk_stack(0, 3);

walk_stack() recursively calls itself until depth == 3.

Each call has its own local variable:

int marker = depth * 10;

It also calls dump_frame(), which creates another temporary stack frame containing:

int local_int = 100 + depth;
char local_buf[16];
int *p_local = &local_int;

No heap memory is used in this program.

Step 1 - main() starts

STACK
+----------------------+
| main                 |
+----------------------+

HEAP
(empty)

main() calls walk_stack(0, 3).

Step 2 - walk_stack(0, 3)

A new stack frame is created.

marker = 0 * 10;

STACK
+----------------------+
| walk_stack depth=0   |
| marker = 0           |
+----------------------+
| main                 |
+----------------------+

HEAP
(empty)

Then dump_frame("enter", 0) is called.

Step 3 - dump_frame("enter", 0)

Values:

local_int = 100;
local_buf[0] = 'A';
local_buf[1] = '\0';
p_local = &local_int;

STACK
+--------------------------------+
| dump_frame depth=0             |
| local_int = 100                |
| local_buf = "A"                |
| p_local --------------------+  |
|                            |   |
|              &local_int <--+   |
+--------------------------------+
| walk_stack depth=0             |
| marker = 0                     |
+--------------------------------+
| main                           |
+--------------------------------+

HEAP
(empty)

p_local aliases local_int because it stores the address of that local variable.

When dump_frame() returns, its entire stack frame is destroyed. local_int, local_buf, and p_local no longer exist.

Recursive calls

The program recursively calls:

walk_stack(1, 3);
walk_stack(2, 3);
walk_stack(3, 3);

At the deepest point:

STACK
+----------------------+
| walk_stack depth=3   |
| marker = 30          |
+----------------------+
| walk_stack depth=2   |
| marker = 20          |
+----------------------+
| walk_stack depth=1   |
| marker = 10          |
+----------------------+
| walk_stack depth=0   |
| marker = 0           |
+----------------------+
| main                 |
+----------------------+

HEAP
(empty)

Each call owns a separate marker, even though the variable has the same name in the source code.

After reaching depth 3, the calls return in reverse order. Each returning walk_stack() frame is destroyed, so that invocation's marker stops existing.

The later call dump_frame("exit", depth) creates a new temporary dump_frame() frame; it is not the same frame that existed during "enter".

Variable lifetimes

marker lives from entry into one invocation of walk_stack() until that invocation returns.

local_int, local_buf, and p_local live only during one invocation of dump_frame().

2. heap_example.c

Purpose

This program demonstrates dynamic allocation, nested heap objects, correct deallocation for Bob, and a deliberate memory leak for Alice.

typedef struct Person
{
    char *name;
    int age;
} Person;

A Person struct and its name string are allocated separately.

Step 1 - main() starts

Person *alice = NULL;
Person *bob = NULL;

STACK
+--------------------------+
| main                     |
| alice = NULL             |
| bob   = NULL             |
+--------------------------+

HEAP
(empty)

Step 2 - person_new("Alice", 30)

First:

Person *p = malloc(sizeof(Person));

This allocates one Person object on the heap.

Then:

p->name = malloc(len + 1);

allocates a second heap object for the copied string.

After initialization:

STACK
main:
alice = NULL
bob   = NULL

person_new:
p --------------------+
                      |
HEAP                  v
+------------------+
| Person Alice     |
| name ----------+ |
| age = 30       | |
+----------------|-+
                 |
                 v
            +-----------+
            | Alice\0    |
            +-----------+

When person_new() returns, local pointer p disappears, but the heap allocations remain alive. alice receives the returned address.

Step 3 - person_new("Bob", 41)

The same process creates Bob's Person and Bob's name.

After both allocations succeed:

STACK
+--------------------------+
| alice -----------+       |
| bob  ----------- |----+  |
+------------------+----|--+
                   |    |
HEAP               |    |
                   v    |
        +------------------+
        | Person Alice     |
        | name ----------+ |
        | age = 30       | |
        +----------------|-+
                         |
                         v
                    "Alice\0"

                        +------------------+
                        | Person Bob       |
                        | name ----------+ |
                        | age = 41       | |
                        +----------------|-+
                                         |
                                         v
                                      "Bob\0"

There are four live heap allocations:

Alice Person

Alice name

Bob Person

Bob name

Step 4 - freeing Bob

free(bob->name);
free(bob);

Bob's name is freed first, then Bob's struct.

STACK
alice ---> live Alice Person
bob   ---> old address (dangling)

HEAP
Alice Person ---> Alice name
Bob Person: freed
Bob name:   freed

free() does not automatically set bob to NULL; the variable still contains the previous address, but the object's lifetime has ended.

Step 5 - partially freeing Alice

The program calls:

person_free_partial(alice);

That function only executes:

free(p);

It does not free p->name.

After the call:

STACK
alice = old address (dangling)
bob   = old address (dangling)

HEAP
Alice Person: freed

+-----------+
| Alice\0    |  <-- still allocated but unreachable
+-----------+

Alice's name allocation is leaked.

The leaked allocation is the block created by:

p->name = malloc(len + 1);

for Alice.

Failure-path detail

If one person_new() succeeds and the other fails, the cleanup path calls person_free_partial() on the successful object. Because that function frees only the struct and not the separately allocated name, the name can leak on that path as well.

Correct complete deallocation

A complete destructor would free in this order:

free(p->name);
free(p);

The nested allocation must be freed before the struct containing the pointer is destroyed.

Object lifetimes

Alice Person:

malloc(sizeof(Person)) -> alive -> person_free_partial(alice) -> freed

Alice name:

malloc(len + 1) -> alive -> never freed -> leak

Bob name:

malloc -> alive -> free(bob->name)

Bob Person:

malloc -> alive -> free(bob)

3. aliasing_example.c

Purpose

This program demonstrates pointer aliasing and deliberate use-after-free.

make_numbers(5) allocates five integers and initializes them to:

[1, 11, 21, 31, 41]

Step 1 - main() starts

int *a = NULL;
int *b = NULL;
int n = 5;

STACK
+----------------------+
| a = NULL             |
| b = NULL             |
| n = 5                |
+----------------------+

HEAP
(empty)

Step 2 - make_numbers(5)

Inside the function:

int i = 0;
int *arr = NULL;

Then:

arr = malloc((size_t)n * sizeof(int));

After initialization:

STACK
make_numbers:
arr ----------------------+
i                         |
n = 5                     |
                          |
HEAP                      v
+----+----+----+----+----+
| 1  | 11 | 21 | 31 | 41 |
+----+----+----+----+----+

When make_numbers() returns, local arr stops existing, but the heap array remains alive. a receives the returned address.

STACK
a ---------------------+
b = NULL               |
n = 5                  |
                       |
HEAP                   v
+----+----+----+----+----+
| 1  | 11 | 21 | 31 | 41 |
+----+----+----+----+----+

Step 3 - aliasing

b = a;

No copy is made and no new allocation occurs.

STACK

a --------+
          |
b --------+
          |
          v
HEAP
+----+----+----+----+----+
| 1  | 11 | 21 | 31 | 41 |
+----+----+----+----+----+

a and b are different pointer variables containing the same heap address. Therefore a[2] and b[2] refer to the same integer object.

Step 4 - free(a)

free(a);

The heap array's lifetime ends immediately.

STACK

a --------+  dangling
          |
b --------+  dangling
          |
          X
HEAP
former array: FREED

Neither pointer is automatically set to NULL. Both still contain the old address.

Step 5 - reading through b

printf("reading b[2]=%d\n", b[2]);

This dereferences a dangling pointer after the allocation has been freed. It is a use-after-free and therefore undefined behavior.

Valgrind should report an invalid read.

The program might appear to print 21, but that is not guaranteed and must not be treated as valid behavior.

Step 6 - writing through b

b[3] = 1234;

This writes to the freed allocation. It is another use-after-free and undefined behavior.

Valgrind should report an invalid write.

Lifetime summary

malloc in make_numbers()
        |
        v
heap array alive
        |
        +--- a points to it
        |
        +--- b aliases it after b = a
        |
        v
free(a)
        |
        v
heap object's lifetime ends
        |
        +--- a dangling
        +--- b dangling

4. crash_example.c

Purpose

This program demonstrates a deterministic null-pointer dereference.

main() begins with:

int *nums = NULL;
int n = 0;

Step 1 - before allocation

STACK
+----------------------+
| nums = NULL          |
| n = 0                |
+----------------------+

HEAP
(empty)

The program calls:

nums = allocate_numbers(n);

with n == 0.

Step 2 - allocate_numbers(0)

Inside:

int *arr = NULL;
int i = 0;

Then:

if (n <= 0)
    return NULL;

Because n is zero, the function returns immediately. malloc() is never executed.

STACK
+---------------------------+
| allocate_numbers          |
| n = 0                     |
| arr = NULL                |
| i = 0                     |
+---------------------------+
| main                      |
| nums = NULL               |
| n = 0                     |
+---------------------------+

HEAP
(empty)

The function frame is destroyed on return, and nums receives NULL.

Step 3 - invalid write

The next statement is:

nums[0] = 42;

Array indexing is equivalent to:

*(nums + 0) = 42;

Since nums == NULL, this attempts to dereference the null pointer.

STACK
+----------------------+
| nums = NULL          |
| n = 0                |
+----------------------+

HEAP
(empty)

Attempted operation:
*(NULL) = 42

This is an invalid memory access and typically terminates the process with a segmentation fault.

The later lines are normally not reached:

printf("nums[0]=%d\n", nums[0]);
free(nums);

Important distinction

The crash is not caused by malloc(0) in this program. malloc() is never reached because the n <= 0 check returns first.

The direct cause is using the returned NULL pointer without checking it.

Stack vs Heap Summary

Program

Stack behavior

Heap behavior

stack_example

Recursive frames and temporary locals

No heap allocation

heap_example

Local pointer variables and function locals

Multiple Person/name allocations; deliberate leak

aliasing_example

a and b become aliases

One integer array; freed while aliases remain

crash_example

nums remains NULL

No allocation occurs because n <= 0

Pointer Aliasing Summary

The clearest aliasing example is:

b = a;

Before:

a ---> heap array
b ---> NULL

After:

a -----+
       |
b -----+----> same heap array

No copy of the array is created.

After free(a), the allocation is released once, and both pointers become dangling because both still contain the address of the released object.

AI Review and Manual Correction

An AI-generated memory explanation must not be assumed correct.

One misleading AI explanation would be:

"After free(a), pointer a becomes NULL, while b still points to the freed memory."

This is incorrect.

free(a) releases the heap allocation but does not modify either pointer variable. Immediately after the call, both a and b still contain the same old address. The allocation's lifetime has ended, so both pointers are dangling.

Corrected map:

Before free:

a -----+
       |
b -----+----> live heap allocation

After free(a):

a -----+
       |
b -----+----> former address of an allocation
             whose lifetime has ended

Dereferencing either pointer after this point is invalid.

Another possible misleading AI explanation would be that Alice is fully freed because the program calls person_free_partial(alice). That is incomplete: person_free_partial() only frees the Person struct. The separately allocated alice->name block is not freed and therefore leaks.

Final Conclusions

Local variables belong to stack frames and stop existing when their functions return.

Recursive calls create independent stack frames even when local variables use the same names.

malloc() creates heap objects whose lifetimes continue until free() is called.

Returning a heap pointer from a function is valid because the heap object outlives the function's local pointer variable.

Multiple pointers can alias the same heap object.

free() ends the object's lifetime but does not clear pointer variables that referred to it.

Dereferencing a dangling pointer is use-after-free and causes undefined behavior.

Dereferencing NULL is invalid and typically causes a segmentation fault.

Every separately allocated heap object must be freed separately. Freeing a struct does not automatically free memory referenced by pointer fields inside it.