# LIST

The most basic operations includes:
* creation
* getting the size
* getting the value at a specific position
* getting the first element
* getting the last element
* adding at the last element
* adding at the first position
* adding / inserting at a specific position
* check if the list contains a specific element

## 1.00 

Create the interface for the basic operations with no dependencies and type d
efinitions.

## 1.01

Abstract data type `list_t` defined.

The abstract data type `list_t` will be used, created, and operated on by the 
function implementation of each of the concrete data types.

## 1.02

List type implementation basic implementation.

Basic implementation of `list_implementation` and `list_intf` done. Stub 
implementation of a concrete data type array list in thourgh `ARRAYLIST_T` or
`&arraylist_implementation`.

## 1.03

Define base for list implementation type

The typedef for function prototype definitions for functions needed for the 
abstract data type to function are defined. This includes the function to
check of equality of elements, to compare one element to another and to 
dispose of the memory allocated to each of the elements.

## 1.04

Incorporated base impl in array list.

The implementation details in `list_impl_base` is incorporated in 
the concrete data type array list. The required functions are reflected
in all the `struct`s needed in the abstract data type. The basic
`list_t` create by the `array_list_implementation` and the `size`
function is implemented.

### 1.04a

ArrayList getters implemented.

### 1.04b

Fixed error introduced by above commit regarding return type.
Return type `void *` changed to `const void *` in the respective
function declarations.

### 1.04c

Implemented grow function for array list.

## 1.05

Basic array list fully implemented.

All the getters works and tested superficially. All the adders are 
also implemented superficially. Further decisions on what the return
types will be for each of the setters and getters should be finalised.
Further additional provisions for iterator functions and type and an
abstract data type `list_node_t` or list node type with specific 
behaviours should be explored.

### 1.05a

Added mechanism to free memory of the array list. Added it to 
`list_interface` also.

### 1.05b

`data_structures.c` demonstrates that the `void *` returned from the getters,
also originally typed as `const void *` could be casted to a non-const pointer
and is thus mutable and the underlying value contained in the array list will
be changed also.

## 1.06

Commented more interface functions added.

Functions that cater to the `list_node_t` is added to the `list_interface`.
Further, initial function prototypes for list iterators are also added.
The addition of these functions to the `list_implementeion` and the
implementation in `list.c` will be added later as will the implementation
in the concrete data type `array_list`.

### 1.06a

Trying out implementing `set_node_value`.

### 1.07

Unity C Testing incorporated.

## 1.08

Fixed memory / syntax errors

Fixed error :   `uintptr_t` not found in ubuntu / linux.
Fixed error :   uninitialised pointer on creation of array list. Used
                `calloc` instead of `malloc`.
Fixed error :   Memory leak on `set_node_value` as the old memory of an
                array list is not set free.
Feat :  Incorporated `data_structures.c` in the test temporarily. Has to 
        change format and content to actual test.

## 1.09

Implemented `remove_at` function

### 1.09a

Refactor `remove_at`: change return type of `remove_at` to `bool`.

C++ removes the element and frees the memory occupied by the element.
Java removes the element and return the removed element. Java is a 
garbage-collected language and thus this will not cause any problems.
C++ though is not GC. Returning a pointer to the element to the user
gives the user the responsibility to free up the memory. Instead, the 
implementation in this library will follow `gnulib`, with a small change,
that frees the memory on removal and return `bool` true for a successful 
operation and `false` otherwise. If the element is needed, the user
should just `get_at()` first before removing it. An option is also to 
copy the content of that element to a new memory to preserve the element
once it is removed from the `list`.

### 1.09b

Added `remove_first` and `remove_last`.

### 1.09c

Added `last_node`: getter for last node.

### 1.09d

Added `nx_get_at`, `previous_node`, and `next_node`.

### 1.09e

Docs: Added markdown files for explanation of list algorithm

### 1.09f

Docs: Explanation on how the algorithm is used.

TTD
---------
* Implement thread safety or multiprocessing / parallel computing
* Determine policy and implement iterator invalidation
* Determine policy on memory management in relation to changing values of existing list elements
* Determine policy on return types (`const void *` vs `list_node_t`) and effects possibly on thread-safety.
* Makefile / Autoconf :
  * Add more configuration to accomodate different platforms
  * Refactor and clean-up makefile esp part regarding different platforms


