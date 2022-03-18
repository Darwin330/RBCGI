#pragma once;
#include"Common.hpp"
//#include<>
#include<queue>
#include<mutex>
#include<semaphore.h>
template<class T>
class Threadpool
{
public:
    static Threadpool* getInstance(int threadnums =8 ,int requestsnums=1000);
    bool append(T*);
    ~Threadpool();
private:
    Threadpool(int ,int );
    void run();
    void* worker(void*);
private:
    static std::once_flag flag;
    static Threadpool* pool;
    pthread_t* m_threads;
    int thread_numbers;
    int max_requests;
    std::queue<T*>workqueue;
    pthread_mutex_t m_mutex;
    sem_t m_sem;
    bool m_stop;
};