#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <limits.h>
#include "logger.h"

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ))

int fd, wd; 
char *dir;

static int display_info(const char *fpath, 
                        const struct stat *sb,
                        int tflag, 
                        struct FTW *ftwbuf) {
    
    

        wd = inotify_add_watch( fd, fpath, IN_MODIFY | IN_CREATE | IN_DELETE );
        //if( wd < 0 ){
        //    errorf("Error creating watch descriptor\n");
        //    exit(1);
        //}
    
    return 0;         
}

int main(int argc, char **argv){
    //UNCOMMENT HERE FOR LOGGING
    //initLogger("syslog");
    dir = argv[1];
    //int flags = 0;
    int traverse;
    int rd;
    char buffer[BUF_LEN];
    //flags |= FTW_DEPTH;
    //flags |= FTW_PHYS;
    //flags |= FTW_CHDIR;
    //flags |= FTW_MOUNT;

    if(argc < 1){
        errorf("Path missing\n");
        exit(1);
    }

    fd = inotify_init();
    if ( fd < 0 ) {
        errorf("Error creating file descriptor\n");
        exit(1);
    }

    traverse = nftw(dir, display_info, 30, FTW_PHYS );

    if (traverse < 0) {
        errorf("Error in nftw\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        int i = 0;

        rd = read( fd, buffer, BUF_LEN );
        if ( rd < 0 ) {
            errorf( "Error in 'read'\n" );
            exit(1);
        }  

        while ( i < rd ) { 
            struct inotify_event *event = (struct inotify_event *) buffer;     
            if ( event->len ) {
                if ( event->mask & IN_CREATE) {
                    if (event->mask & IN_ISDIR)
                    infof( "The directory %s was created.\n", event->name );       
                    else
                    infof( "The file %s was created.\n", event->name );       
                }
                
                if ( event->mask & IN_MODIFY) {
                    if (event->mask & IN_ISDIR)
                    infof( "The directory %s was modified.\n", event->name );       
                    else
                    infof( "The file %s was modified.\n", event->name );       
                }
                
                if ( event->mask & IN_DELETE) {
                    if (event->mask & IN_ISDIR)
                    infof( "The directory %s was deleted.\n", event->name );       
                    else
                    infof( "The file %s was deleted\n", event->name );       
                }  
        
        
            }
            i += EVENT_SIZE + event->len;
            
        }
    }

    inotify_rm_watch( fd, wd );
    close( fd );

    return 0;
}
