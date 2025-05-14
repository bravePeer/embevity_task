#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>

#define NAMED_PIPE "/var/lock/pipename"

class Communicator
{
    Communicator()
    {}

    void write(unsigned char address, unsigned char* data, unsigned char dataLen)
    {
        int ret = mkfifo(NAMED_PIPE, 0666);        
        // open()
    }
};