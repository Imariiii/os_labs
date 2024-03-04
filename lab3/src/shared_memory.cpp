#include "shared_memory.h"

#include <sys/mman.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "utils.h"

template <class T>
void WeakSharedMemory<T>::construct(std::string& name, std::size_t size) {
    _wSemPtr = sem_open((name + "W").c_str(), O_CREAT, S_IRUSR | S_IWUSR, 1);
    _rSemPtr = sem_open((name + "R").c_str(), O_CREAT, S_IRUSR | S_IWUSR, 0);
    _FD = shm_open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (_FD < 0) {
        switch (errno) {
            case EACCES:
                throw std::runtime_error("Permission Exception");
                break;
            case EINVAL:
                throw std::runtime_error("Invalid shared memory name passed");
                break;
            case EMFILE:
                throw std::runtime_error(
                    "The process already has the maximum number of files "
                    "open");
                break;
            case ENAMETOOLONG:
                throw std::runtime_error("The length of name exceeds PATH_MAX");
                break;
            case ENFILE:
                throw std::runtime_error(
                    "The limit on the total number of files open on the "
                    "system "
                    "has been reached");
                break;
            default:
                throw std::runtime_error(
                    "Invalid exception occurred in shared memory creation");
                break;
        }
    }
    ftruncate(_FD, size);
    _ptr = mmap(nullptr, size, O_RDWR, MAP_SHARED, _FD, 0);
    if (_ptr == nullptr) {
        throw std::runtime_error(
            "Exception in attaching the shared memory region");
    }
}

static bool SemTimedWait(sem_t* sem) {
    struct timespec absoluteTime;
    if (clock_gettime(CLOCK_REALTIME, &absoluteTime) == -1) {
        return false;
    }
    absoluteTime.tv_sec += 5;
    return sem_timedwait(sem, &absoluteTime) == 0;
}

template <class T>
bool WeakSharedMemory<T>::writeLock(bool timed) {
    if (timed) return SemTimedWait(_wSemPtr);
    sem_wait(_wSemPtr);
    return true;
}
template <class T>
void WeakSharedMemory<T>::writeUnlock() {
    sem_post(_wSemPtr);
}

template <class T>
bool WeakSharedMemory<T>::readLock(bool timed) {
    if (timed) return SemTimedWait(_rSemPtr);
    sem_wait(_rSemPtr);
    return true;
}

template <class T>
void WeakSharedMemory<T>::readUnlock() {
    sem_post(_rSemPtr);
}

template <class T>
WeakSharedMemory<T>::~WeakSharedMemory() {
    if (sem_close(_rSemPtr) < 0) {
        std::perror("sem_close");
        std::abort();
    }
    if (sem_close(_wSemPtr) < 0) {
        std::perror("sem_close");
        std::abort();
    }
    if (munmap(_ptr, _size) < 0) {
        std::perror("munmap");
        std::abort();
    }
}

template <class T>
SharedMemory<T>::~SharedMemory() {
    if (this->isEmpty()) {
        return;
    }
    if (shm_unlink(this->getName().c_str()) < 0) {
        std::perror("shm_unlink");
        std::abort();
    }
    if (sem_unlink((this->getName() + "W").c_str()) < 0) {
        std::perror("sem_unlink");
        std::abort();
    }
    if (sem_unlink((this->getName() + "R").c_str()) < 0) {
        std::perror("sem_unlink");
        std::abort();
    }
}

template <class T>
WeakSharedMemory<T>::WeakSharedMemory(WeakSharedMemory<T>&& other) noexcept {
    other = *this;
    _size = 0;
}

template <class T>
WeakSharedMemory<T>& WeakSharedMemory<T>::operator=(
    WeakSharedMemory<T>&& other) noexcept {
    other = *this;
    _size = 0;
    return *this;
}

template class WeakSharedMemory<Slot>;
template class SharedMemory<Slot>;