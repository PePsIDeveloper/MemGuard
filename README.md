
# MemGuard

MemGuard is a tool for detecting and preventing memory-related security vulnerabilities in C/C++ programs. It works by instrumenting the program to track memory accesses and detect any attempts to access memory that has been freed or is out of bounds.

## Usage

MemGuard provides two main functions for detecting memory issues in C/C++ programs:

1.  Operators for allocating and deallocating memory safely. These include `new`, `delete`, `malloc`, `calloc`, `realloc`, and `free`. By using these operators instead of the standard C/C++ memory allocation functions, MemGuard can detect and prevent common memory-related vulnerabilities such as buffer overflows and use-after-free errors.
    
2.  The `CheckMemoryAccess` function, which can be used to check whether a given memory address is valid and safe to access. This function can be used to detect attempts to access memory that has been freed or is out of bounds.
    

Here is an example of how to use the MemGuard operators:

   ```cpp
    int main() {
	  int* array = new int[10];
	  for (int i = 0; i < 10; i++) {
	    array[i] = i;
	  }
	  for (int i = 0; i < 10; i++) {
	    std::cout << array[i] << " ";
	  }
	  std::cout << std::endl;
	  array = realloc(array, 20 * sizeof(int));                
	  for (int i = 10; i < 20; i++) {
	    array[i] = i;
	  }
	  for (int i = 0; i < 20; i++) {
	    std::cout << array[i] << " ";
	  }
	  std::cout << std::endl;
	  delete[] array;
	  return 0;
	}
```

And here is an example of how to use the `CheckMemoryAccess` function:
```cpp
int* ptr;
CheckMemoryAccess(ptr);  // This will trigger an error because 'ptr' has not been initialized.

ptr = new int;
*ptr = 42;
CheckMemoryAccess(ptr);  // This will not trigger an error because 'ptr' points to a valid memory block.

delete ptr;
CheckMemoryAccess(ptr);  // This will trigger an error because 'ptr' points to a freed memory block.
```
