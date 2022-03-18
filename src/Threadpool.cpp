#include"Threadpool.hpp"

using namespace std;
template<typename T>
Threadpool<T>* Threadpool<T>::getInstance(int nums,int requests)
{
    call_once(flag,[&](){pool=new Threadpool(nums,requests);});
    return pool;
}

template<typename T>
Threadpool<T>::Threadpool(int nums,int requests):thread_numbers(nums),max_requests(requests),m_stop(false)
{
    m_threads=new pthread_t(thread_numbers);
    sem_init(&m_sem,0,0);
    pthread_mutex_init(&m_mutex,NULL);
    for(int i=0;i<thread_numbers;i++)
    {
        if(pthread_create(m_threads+i,NULL,worker,this)!=0)
        {
            delete[] m_threads;
            throw exception();
        }
        if(pthread_detach(m_threads[i])!=0)
        {
            delete[] m_threads;
            throw exception();
        }
    }
}

template<typename T>
Threadpool<T>::~Threadpool()
{
    delete[] m_threads;
    pthread_mutex_destroy(&m_mutex);
    sem_destroy(&m_sem);
}

template<typename T>
void* Threadpool<T>::worker(void* arg)
{
    Threadpool* m_pool=dynamic_cast<Threadpool*>(arg);
    m_pool->run();
    return m_pool;
}

template<typename T>
bool Threadpool<T>::append(T* request)
{
    pthread_mutex_lock(&m_mutex);
    if(workqueue.size()>=max_requests)
    {
        pthread_mutex_unlock(&m_mutex);
        return false;
    }
    workqueue.push(request);
    pthread_mutex_unlock(&m_mutex);
    sem_post(&m_sem);
    
    return true;
}

template<typename T>
void Threadpool<T>::run()
{
    while(!m_stop)
    {
        sem_wait(&m_sem);    
        pthread_mutex_lock(&m_mutex);
        T* request=workqueue.front();
        workqueue.pop();
        pthread_mutex_unlock(&m_mutex);
        if(request==nullptr)
        {    
            continue;
        }
        //pthread_mutex_unlock(&m_mutex);
        request->process();
    }
}
