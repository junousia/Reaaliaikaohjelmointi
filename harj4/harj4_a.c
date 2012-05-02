#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int descriptor_flags, file_flags, fd;
    fd = open("file.txt", O_RDONLY|O_NONBLOCK);
    descriptor_flags = fcntl(fd, F_GETFD, 0); 
    file_flags = fcntl(fd, F_GETFL, 0);

    printf("File descriptor flag FD_CLOEXEC %s\n",descriptor_flags & FD_CLOEXEC?"enabled":"disabled");

    printf("\nO_NONBLOCK: %s",file_flags & O_NONBLOCK?"on":"off");
    printf("\nO_APPEND: %s",file_flags & O_APPEND?"on":"off");
    printf("\nO_ASYNC: %s",file_flags & O_ASYNC?"on":"off");

    file_flags ^= O_NONBLOCK; 

    printf("\n\nUpdating file flags...");
    fcntl( fd, F_SETFL, file_flags);
    printf("\nFetching new flags...\n");
    file_flags = fcntl(fd, F_GETFL, 0);

    printf("\nO_NONBLOCK: %s",file_flags & O_NONBLOCK?"on":"off");
    printf("\nO_APPEND: %s",file_flags & O_APPEND?"on":"off");
    printf("\nO_ASYNC: %s",file_flags & O_ASYNC?"on":"off");
    printf("\n");
    close (fd);
    return 0;
}
