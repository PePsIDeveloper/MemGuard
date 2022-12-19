#include <iostream>
#include <map>
#include <vector>

class MemoryBlock {
 public:
  MemoryBlock(void* ptr, size_t size) : ptr_(ptr), size_(size), freed_(false) {}

  void* ptr() { return ptr_; }
  size_t size() { return size_; }
  bool freed() { return freed_; }
  void set_freed(bool freed) { freed_ = freed; }

 private:
  void* ptr_;
  size_t size_;
  bool freed_;
};

class MemGuard {
 public:
  void* malloc(size_t size) {
    void* ptr = ::malloc(size);
    blocks_.emplace_back(ptr, size);
    return ptr;
  }

  void free(void* ptr) {
    auto it = FindBlock(ptr);
    if (it == blocks_.end()) {
      std::cerr << "Error: attempt to free invalid memory block" << std::endl;
      return;
    }
    it->set_freed(true);
  }

  void* realloc(void* ptr, size_t size) {
    auto it = FindBlock(ptr);
    if (it == blocks_.end()) {
      std::cerr << "Error: attempt to reallocate invalid memory block" << std::endl;
      return nullptr;
    }
    void* new_ptr = ::realloc(ptr, size);
    if (new_ptr == ptr) {
      it->set_freed(false);
    } else {
      blocks_.emplace_back(new_ptr, size);
      it->set_freed(true);
    }
    return new_ptr;
  }

  void CheckMemoryAccess(void* ptr) {
    auto it = FindBlock(ptr);
    if (it == blocks_.end()) {
      std::cerr << "Error: attempt to access invalid memory block" << std::endl;
      return;
    }
    if (it->freed()) {
      std::cerr << "Error: attempt to access freed memory block" << std::endl;
      return;
    }
  }

 private:
  std::vector<MemoryBlock> blocks_;

  std::vector<MemoryBlock>::iterator FindBlock(void* ptr) {
    return std::find_if(blocks_.begin(), blocks_.end(), [ptr](const MemoryBlock& block) {
      return block.ptr() == ptr;
    });
  }
}mem_guard;

void* operator new(size_t size) {
  return mem_guard.malloc(size);
}

void operator delete(void* ptr) noexcept {
  mem_guard.free(ptr);
}

void* operator new[](size_t size) {
  return mem_guard.malloc(size);
}

void operator delete[](void* ptr) noexcept {
  mem_guard.free(ptr);
}

void* operator new(size_t size, std::nothrow_t) noexcept {
  return mem_guard.malloc(size);
}

void* operator new[](size_t size, std::nothrow_t) noexcept {
  return mem_guard.malloc(size);
}

void* operator new(size_t size, std::align_val_t alignment) {
  return mem_guard.malloc(size);
}

void* operator new[](size_t size, std::align_val_t alignment) {
  return mem_guard.malloc(size);
}

void* operator new(size_t size, std::align_val_t alignment, std::nothrow_t) noexcept {
  return mem_guard.malloc(size);
}

void* operator new[](size_t size, std::align_val_t alignment, std::nothrow_t) noexcept {
  return mem_guard.malloc(size);
}

void* realloc(void* ptr, size_t size) {
  return mem_guard.realloc(ptr, size);
}

void CheckMemoryAccess(void* ptr) {
  mem_guard.CheckMemoryAccess(ptr);
}
