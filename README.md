# MemGuard
MemGuard is a tool for detecting and preventing memory-related security vulnerabilities in C/C++ programs. It works by instrumenting the program to track memory accesses and detect any attempts to access memory that has been freed or is out of bounds.


**Usage for MemGuard's Operators.**

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

**Usage for CheckMemoryAccess.**

    int* ptr;
	CheckMemoryAccess(ptr);  // This will trigger an error because 'ptr' has not been initialized.

	ptr = new int;
	*ptr = 42;
	CheckMemoryAccess(ptr);  // This will not trigger an error because 'ptr' points to a valid memory block.

	delete ptr;
	CheckMemoryAccess(ptr);  // This will trigger an error because 'ptr' points to a freed memory block.


***
