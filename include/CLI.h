#ifndef CLI_H
#define CLI_H

#define InputBufferSize 128 // i have ibs
#define MaxPathLength (InputBufferSize - 6)
#define ProfileIterations 10000000 // call MakeMove followed by TakeMove this many times

#define InvalidPath -1

extern void CommandLoop();

#endif