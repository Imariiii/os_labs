#pragma once
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <string>
#include <string_view>

template <class T>
class WeakSharedMemory {
   public:
    enum {
        C_READ_ONLY = O_RDONLY,
        C_READ_WRITE = O_RDWR,
    } CREATE_MODE;

    enum {
        A_READ = PROT_READ,
        A_WRITE = PROT_WRITE,
    } ATTACH_MODE;
    WeakSharedMemory() : _size{0} {}
    WeakSharedMemory(std::string_view name)

        : _name(name), _size(sizeof(T)) {
        construct(_name, _size);
    }
    ~WeakSharedMemory();
    WeakSharedMemory(const WeakSharedMemory<T>& other) = delete;
    WeakSharedMemory(WeakSharedMemory<T>&& other) noexcept;
    WeakSharedMemory<T>& operator=(WeakSharedMemory<T>&& other) noexcept;
    bool writeLock(bool timed = false);
    void writeUnlock();
    bool readLock(bool timed = false);
    void readUnlock();
    int getFD() const { return _FD; }
    T* getData() { return static_cast<T*>(_ptr); };
    const T* getData() const { return static_cast<const T*>(_ptr); }
    const std::string& getName() const { return _name; }
    bool isEmpty() const { return _size == 0; }

   private:
    std::string _name;
    int _FD;
    sem_t* _wSemPtr;
    sem_t* _rSemPtr;
    size_t _size;
    void* _ptr;
    void construct(std::string& name, std::size_t size);
    WeakSharedMemory<T>& operator=(const WeakSharedMemory<T>& other) = default;
};

template <class T>
class SharedMemory : public WeakSharedMemory<T> {
   public:
    using WeakSharedMemory<T>::WeakSharedMemory;
    ~SharedMemory();
};
