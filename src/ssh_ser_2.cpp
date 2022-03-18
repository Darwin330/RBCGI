#include"Reactor.hpp"
#include"Handle.hpp"
#include"EventHandler.hpp"
#include"Threadpool.hpp"
#include"Request.hpp"
#include<unordered_map>

#define MAX_CONLIMITS 10
//#define BUFFER_SIZE 1000

enum IO_MODE
{
    MODE_READ=0x001,
#define MODE_READ MODE_READ
    MODE_WRITE=0x002,
#define MODE_WRITE MODE_WRITE
    MODE_ERROR=0x004
#define MODE_ERROR MODE_ERROR
};

Reactor* m_reactor;
struct sockaddr_in cliaddr;
socklen_t cliaddrlen;
std::unordered_map<int ,Handle*>map;
Threadpool<Request>* pool=nullptr;
std::unordered_map<int ,Request*>users;

//事件具体处理器和回调的绑定不对
void reactor_add(Reactor* m_reactor,int fd,Eventcallback m_cb,int flag ,int mode)
{
    Handle* handle=new Handle(fd) ;
    assert(handle!=nullptr);

    handle->set_event(flag);

    ConcreteHandler* m_handler=new ConcreteHandler(handle);
    assert(m_handler!=nullptr);
    //m_handler->set_handle(handle);

    if(mode&MODE_READ)
    {
        m_handler->set_readcb(m_cb);        
    }

    if(mode&MODE_WRITE)
    {   
        m_handler ->set_writecb(m_cb);    
    }          
    
    if(mode&MODE_ERROR)
    {
        m_handler ->set_errorcb(m_cb);
    }
    //handle_sockfd->set_handler(m_handler);

    m_reactor->register_handler(handle);

    map.emplace(fd,handle);
}

void
readcb2(int fd)
{
    char buf[BUFFER_SIZE];
    
    memset(&buf,0,BUFFER_SIZE);
    
    //回射服务器
    int n=recv(fd,&buf,BUFFER_SIZE,0);
    if(n<=0){
        printf("client %d exit\n",fd);
        Handle* cur=map[fd];
        m_reactor->remove_handler(cur);
        map.erase(fd);
        users.erase(fd);
    }
    else{
        pool->append(users[fd]);
    }
    //return;
}

void
readcb1(int fd)
{
    
    memset(&cliaddr,0,sizeof(cliaddr));
    cliaddrlen=sizeof(cliaddr);
    
    int connfd=accept(fd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    int flag= EPOLLIN|EPOLLET;

    Request* cli=new Request();
    cli->request_init(connfd,&cliaddr);

    users[connfd]=cli;

    reactor_add(m_reactor,connfd,std::bind(readcb2,std::placeholders::_1),flag,MODE_READ);

    //return ;
}


int main(int argv,char**argc){
    if(argv<=2){
        printf("usage: %s ip port_number",argc[0]);
        return -1;
    }

    int port=atoi(argc[2]);
    const char* ip=argc[1];
    pool = Threadpool<Request>::getInstance();
    struct sockaddr_in servaddr,cliaddr;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&servaddr.sin_addr);

    int sockfd,connfd,ret;

    sockfd=socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);

    ret=bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    assert(ret!=-1);

    ret=listen(sockfd,MAX_CONLIMITS);
    assert(ret!=-1);
    
    int nready,n,connums;
    socklen_t cliaddr_size;

    connums=0;

    char buf[BUFFER_SIZE];
    printf("Server started\n");

    m_reactor=new Reactor();

    reactor_add(m_reactor,sockfd,std::bind(readcb1,std::placeholders::_1),EPOLLIN|EPOLLET,MODE_READ);

    m_reactor->handle_event();


    
    return 0;
}