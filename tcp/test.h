#include <sys/socket.h>
int socket(int domain, int type, int protocol);
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *path, int flag);
O_CREAT 
O_TRUNC 
O_APPEND 
O_RDONLY 
O_WRONLY 
O_RDWR 

#include <unistd.h>
int close(int fd)

#include <unistd.h>
ssize_t write(int fd, const void * buf, size_t nbytes);

struct sockaddr_in 
{
    sa_family_t         sin_family;
    uint16_t            sin_port; 
    struct in_addr      sin_addr;
    char                sin_zero[8];    // 不使用
}

struct in_addr 
{
    In_addr_t           s_addr;        // 32位IPv4地址
}

struct sockaddr 
{
    sa_family  sin_family;
    char       sa_data[14];
}


int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);

#include <sys/socket.h>
ssize_t sendto(int sock, void *buff, size_t nbytes, int flag, struct sockaddr *to, socklen_t addrlen);

ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);

int shutdown(int sock, int howto);

#include <netdb.h>

struct hostent * gethostbyname(const char *hostname);

struct hostent 
{
    char *h_name;           // official name 
    char **h_aliases;       // alias list 
    int h_addrtype;         // host address type 
    int h_length;           // address length 
    char ** h_addr_list;    // address list
}

struct hostent * gethostbyaddr(const char *addr, socklen_t len, int family)

#include <sys/socket.h>

int getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);

int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen);


#include <unistd.h>
pid_t fork(void);

#include <sys/wait.h>

pid_t wait(int * statloc);

pid_t waitpid(pid_t pid, int *statloc, int options);

#include <signal.h>
void (*signal(int signlo, void(*func)(int)))(int);

unsigned int alarm(unsigned int seconds);


#include <signal.h>
int sigaction(int signo, const struct sigaction *act, struct sigaction * oldact);

struct sigaction 
{
    void (*sa_handler)(int);
    sigset_t sa_mask; 
    int sa_flags;
}

int pipe(int filedes[2]);

#include <sys/select.h>
#include <sys/time.h>

int select(
    int maxfd, fd_set * readset, fd_set* writeset, fs_set *exceptset, const struct timeval *timeut
);

struct timeval 
{
    long tv_sec;        // seconds 
    long tvv_usec;      // microseconds
}