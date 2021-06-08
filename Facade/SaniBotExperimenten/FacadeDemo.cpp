// FacadeDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include <wiringPi.h>
#include <iostream>
#include "ControllerFacade.h"

int main()
{
    int stickYreceive;
    int stickXreceive;
    ControllerFacade* facade = new ControllerFacade();
    //wiringPiSetup();
    facade->bepaal_richting_snelheid_rupsbanden(stickYreceive, stickXreceive);
    return 0;
    
    //char *myfifo_write = "/tmp/martin_cpp_out";
    //char *myfifo_read  = "/tmp/martin_cpp_in";

    //mkfifo(myfifo_read, 0666);
    //mkfifo(myfifo_write, 0666);

    //int fd_write = open(myfifo_write, O_WRONLY);
    //int fd_read  = open(myfifo_read, O_RDONLY);

    //command MyCommand;
    //MyCommand.filename = "/home/martin/input.file";  // FIXME: Change filename according to current situation
    //MyCommand.processingInstruction = "copy";

    //long int i=0;
    //for (;;) {
        //char hexlen[8 + 1];
        //size_t chars_read;

        //uint64_t start = getTimestamp();

        //writeStringToPipe(fd_write, MyCommand.filename);
        //writeStringToPipe(fd_write, MyCommand.processingInstruction);
        //writeFileToPipe  (fd_write, MyCommand.filename);

        //uint64_t ended = getTimestamp();
        //std::cout << "Sending finished in " << (ended - start) << "ms" << std::endl;

        //char answer[512];
        //readStringFromPipe(answer, fd_read);

        //std::cout << answer << std::endl;  //Answer moet hier gekoppeld worden aan stickYreceive en stickXreceive
    //}
}
