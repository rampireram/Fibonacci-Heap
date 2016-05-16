Fibonacci-Heap
==============

Implementation of Fibonacci Heap in C

This project has a Fibonacci heap that could perform the following operations:

1.insert_into_root_list   //method to insert a node into the root list

2.insert_into_child_list  //method to insert a node into another node's child list

3.remove_from_root_list   //method to remove a node from the root list

4.insert                  //method to initialize a node to insert it into the root list

5.view_root_list          //method to view the nodes in the root list

6.view_child_list         //method to view the nodes in child list of a node

7.fib_heap_link           //method to link a node to another node's child list

8.consolidate             //auxilary method for "extract_min"

9.extract_min             //method to extract the minimal node from the list

10.heap_init              //method to initialize the heap struct

Methods to be implemented yet.
a.Decrease_key
b.Delete a node from the list

The JNI interface allows for a Java implementation of the fibonacci heaps. This requires that you run the makefile and make the Cpp project into a DLL/SO and then access it from Java using JNI. It's faster when compared to a Java based implementation of Fibonacci heap.
