#include "parse.h"


INT main(INT argc, CHAR *argv[])
{   
    if(argc != 2)
    {
        fprintf(stderr,"Usage : ./viewer [PE File]\n");
        exit(0);
    }

    if(!FileOpen(argv[1]))
    {
        fprintf(stderr,"%s does not exist.\n",argv[1]);
        Clean();
        exit(0);
    }
    
    if(!Parse())
    {
        Clean();
        exit(0);
    }

    Clean();
    return 0;
}

