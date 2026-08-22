# Recursion in C

## What Is Recursion?

**Recursion** is a programming technique where a function **calls itself** to solve a problem.

Instead of solving the entire problem at once, the function solves a smaller version of the same problem repeatedly until it reaches a condition that tells it to stop.

Basic structure:

```c
void function(int n)
{
    if (/* stopping condition */)
        return;

    /* do something */

    function(/* smaller or changed problem */);
}
```

The two most important parts of recursion are:

1. **Base Case** → tells the recursion when to stop.
2. **Recursive Case** → calls the function again with a smaller or changed input.

---

## 1. The Base Case

The **base case** is the condition that stops the recursive calls.

Example:

```c
if (n < 0)
{
    return;
}
```

Without a base case, the function could continue calling itself until the program runs out of stack memory.

Example:

```c
void print(int n)
{
    printf("%d\n", n);
    print(n - 1);
}
```

This never intentionally stops:

```text
print(4)
↓
print(3)
↓
print(2)
↓
print(1)
↓
print(0)
↓
print(-1)
↓
print(-2)
↓
...
```

Eventually this can cause a **stack overflow**.

A base case fixes the problem:

```c
void print(int n)
{
    if (n < 0)
        return;

    printf("%d\n", n);
    print(n - 1);
}
```

---

## 2. The Recursive Case

The recursive case is where the function calls itself.

Example:

```c
print(n - 1);
```

If we start with:

```c
print(4);
```

the calls become:

```text
print(4)
   ↓
print(3)
   ↓
print(2)
   ↓
print(1)
   ↓
print(0)
   ↓
print(-1)
```

At `print(-1)`, the base case becomes true and stops further recursive calls.

---

# The Most Important Recursion Concept

When a function calls another function, the first function does **not disappear**.

It **pauses and waits** for the called function to finish.

Example:

```c
int result = 10 + calculate(5);
```

The program cannot finish the addition until it knows:

```text
calculate(5) = ?
```

So the current function pauses while `calculate(5)` runs.

When `calculate(5)` executes `return`, execution goes back to the function that was waiting.

Remember:

```text
Function call → go deeper ↓

return        → go back ↑
```

---

# Example: Printing Numbers With Recursion

```c
void print(int n)
{
    if (n < 0)
        return;

    printf("%d ", n);

    print(n - 1);
}
```

Calling:

```c
print(4);
```

produces:

```text
4 3 2 1 0
```

Execution:

```text
print(4)
│
├── print 4
│
└── print(3)
      │
      ├── print 3
      │
      └── print(2)
            │
            ├── print 2
            │
            └── print(1)
                  │
                  ├── print 1
                  │
                  └── print(0)
                        │
                        ├── print 0
                        │
                        └── print(-1)
                              │
                              └── return
```

---

# Going Down vs Coming Back Up

This is one of the most important ideas in recursion.

Consider:

```c
void example(int n)
{
    if (n == 0)
        return;

    printf("%d ", n);

    example(n - 1);
}
```

Because `printf` happens **before** the recursive call:

```c
printf(...);

example(...);
```

the numbers are printed while recursion is going **down**.

Result:

```text
3 2 1
```

But consider:

```c
void example(int n)
{
    if (n == 0)
        return;

    example(n - 1);

    printf("%d ", n);
}
```

Now `printf` happens **after** the recursive call.

The current function must wait for the recursive call to finish first.

Calling:

```c
example(3);
```

goes down:

```text
example(3) ⏸
    ↓
example(2) ⏸
    ↓
example(1) ⏸
    ↓
example(0)
    ↓
return
```

Then execution comes back up:

```text
example(1) → print 1
    ↑
example(2) → print 2
    ↑
example(3) → print 3
```

Output:

```text
1 2 3
```

Therefore:

```text
BEFORE recursion = work while going DOWN ↓

AFTER recursion  = work while coming BACK UP ↑
```

---

# What Does `return` Do?

`return` ends the **current function call** and gives control back to the function that called it.

For a `void` function:

```c
return;
```

means:

```text
Stop this function call.
Go back to the caller.
```

For a function returning `int`:

```c
return (5);
```

means:

```text
Stop this function call.
Go back to the caller.
Give the caller the value 5.
```

For example:

```c
int get_number(void)
{
    return (5);
}
```

Then:

```c
int x = 10 + get_number();
```

becomes:

```c
int x = 10 + 5;
```

So:

```text
printf() → displays something

return   → sends a result back to the caller
```

They are NOT the same thing.

---

# Recursion and the Call Stack

Every function call gets its own **stack frame** in memory.

If we call:

```c
print(3);
```

and `print()` recursively calls itself:

```text
print(3)
↓
print(2)
↓
print(1)
↓
print(0)
```

the call stack conceptually becomes:

```text
┌─────────────┐
│ print(0)    │ ← currently executing
├─────────────┤
│ print(1)    │ ← waiting
├─────────────┤
│ print(2)    │ ← waiting
├─────────────┤
│ print(3)    │ ← waiting
├─────────────┤
│ main()      │
└─────────────┘
```

Each call has its **own local variables**.

When `print(0)` returns, its stack frame is removed.

Then:

```text
print(1)
```

continues from where it was paused.

The process continues until all calls have returned.

This process is called **stack unwinding**.

---

# Recursion With Strings

Strings in C end with the null terminator:

```c
'\0'
```

For:

```c
char *s = "Hello";
```

memory conceptually contains:

```text
 H    e    l    l    o   \0
 ↑
 s
```

`*s` gives the current character:

```c
*s
```

which is:

```text
'H'
```

And:

```c
s + 1
```

points to the next character:

```text
 H    e    l    l    o   \0
      ↑
     s+1
```

This makes recursion very useful for processing strings.

Example:

```c
void _puts_recursion(char *s)
{
    if (*s == '\0')
    {
        _putchar('\n');
        return;
    }

    _putchar(*s);

    _puts_recursion(s + 1);
}
```

For:

```text
"Cat"
```

execution is:

```text
s → "Cat"
print C
↓
s → "at"
print a
↓
s → "t"
print t
↓
s → "\0"
print newline
return
```

Output:

```text
Cat
```

In this example:

```c
s + 1
```

plays a role similar to:

```c
i++;
```

in a loop.

---

# Loop Thinking vs Recursion Thinking

A loop might process a string like this:

```c
for (i = 0; s[i] != '\0'; i++)
{
    _putchar(s[i]);
}
```

Recursion can express the same idea differently:

```c
if (*s == '\0')
    return;

_putchar(*s);

_puts_recursion(s + 1);
```

Think of it as:

```text
LOOP                         RECURSION

s[i]                         *s
 ↓                            ↓
process character            process character
 ↓                            ↓
i++                          s + 1
 ↓                            ↓
next iteration               recursive call
 ↓                            ↓
s[i] == '\0'                 *s == '\0'
 ↓                            ↓
STOP                         RETURN
```

---

# Returning Values With Recursion

Recursive functions can also calculate and return values.

A classic example is factorial:

```c
int factorial(int n)
{
    if (n == 0)
        return (1);

    return (n * factorial(n - 1));
}
```

Calling:

```c
factorial(4);
```

first goes down:

```text
factorial(4)
= 4 × factorial(3)

factorial(3)
= 3 × factorial(2)

factorial(2)
= 2 × factorial(1)

factorial(1)
= 1 × factorial(0)

factorial(0)
= 1
```

Now the base case gives us the first known answer.

Then we come back up:

```text
factorial(0) = 1
       ↑
factorial(1) = 1 × 1 = 1
       ↑
factorial(2) = 2 × 1 = 2
       ↑
factorial(3) = 3 × 2 = 6
       ↑
factorial(4) = 4 × 6 = 24
```

Result:

```text
24
```

This demonstrates an important pattern:

```text
Go DOWN until the base case ↓

Get a known answer

Use that answer while returning UP ↑
```

---

# How to Solve a Recursion Problem

When writing a recursive function, ask these questions in order:

### 1. What is my smallest possible problem?

This usually becomes the **base case**.

Examples:

```c
n == 0
```

```c
n < 0
```

```c
*s == '\0'
```

### 2. What should happen during one call?

For example:

```c
_putchar(*s);
```

or:

```c
result = n * ...
```

### 3. How do I make the problem smaller?

Examples:

```c
n - 1
```

or:

```c
s + 1
```

### 4. Should the action happen before or after recursion?

Before:

```c
printf(...);
function(n - 1);
```

means the action happens while going **down**.

After:

```c
function(n - 1);
printf(...);
```

means the action happens while coming **back up**.

---

# Time and Space Complexity

Consider:

```c
void print(int n)
{
    if (n == 0)
        return;

    printf("%d", n);

    print(n - 1);
}
```

For input `n`, approximately `n` calls are made:

```text
n
n - 1
n - 2
...
1
0
```

Therefore:

```text
Time Complexity: O(n)
```

Because recursive calls remain on the call stack until they return, approximately `n` stack frames may exist:

```text
Space Complexity: O(n)
```

This is an important difference from many loops.

A loop may have:

```text
Time  → O(n)
Space → O(1)
```

while a recursive implementation of the same operation may have:

```text
Time  → O(n)
Space → O(n)
```

because of the call stack.

---

# Common Recursion Mistakes

### 1. Missing the base case

Bad:

```c
void f(int n)
{
    f(n - 1);
}
```

There is no stopping condition.

---

### 2. Input never approaches the base case

Bad:

```c
void f(int n)
{
    if (n == 0)
        return;

    f(n + 1);
}
```

If we start with:

```c
f(5);
```

we get:

```text
5 → 6 → 7 → 8 → ...
```

We are moving AWAY from `0`.

Correct direction:

```c
f(n - 1);
```

---

### 3. Confusing `printf` with `return`

Remember:

```text
printf → show something to the user

return → give control/value back to the caller
```

---

### 4. Forgetting that previous calls are waiting

When:

```c
f(4)
```

calls:

```c
f(3)
```

`f(4)` is not deleted.

It is paused on the call stack waiting for `f(3)` to finish.

---

### 5. Using a loop when recursion is required

If an exercise specifically asks for recursion, code such as:

```c
for (...)
```

or:

```c
while (...)
```

usually defeats the purpose of the exercise.

Try to identify:

```text
current item
+
smaller problem
+
base case
```

instead.

---

# Quick Recursion Cheat Sheet

```text
RECURSION
│
├── Function calls itself
│
├── Must have a BASE CASE
│
├── Must move toward the base case
│
├── Recursive call → deeper ↓
│
├── return → back to caller ↑
│
├── Previous function calls WAIT
│
├── Each call gets its own stack frame
│
└── Stack frames disappear when functions return
```

The basic template:

```c
return_type function(input)
{
    /* BASE CASE */
    if (stop_condition)
        return (base_value);

    /* RECURSIVE CASE */
    return function(smaller_input);
}
```

For a `void` function:

```c
void function(input)
{
    if (stop_condition)
        return;

    /* do something */

    function(smaller_input);
}
```

---

## Golden Rule

When recursion becomes confusing, do **not** try to understand every call at once.

Write the calls vertically:

```text
f(4)
↓
f(3)
↓
f(2)
↓
f(1)
↓
f(0) ← BASE CASE
```

Then ask:

```text
What does f(0) return?
```

Once you know that, work **back upward one call at a time**:

```text
f(0)
↑
f(1)
↑
f(2)
↑
f(3)
↑
f(4)
```

### Remember

**Recursive call = go down.**

**Base case = stop going down.**

**Return = go back to the waiting caller.**

**Code before the recursive call runs on the way down.**

**Code after the recursive call runs on the way back up.**