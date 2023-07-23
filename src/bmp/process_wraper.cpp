//
// Created by saintedlittle on 23.07.2023.
//

#include "process_wraper.h"
#include "../cpp/process.h"

#ifdef __cplusplus
extern "C" {
#endif

void WriteAudioWrapper(void* process) {
    Process* processObj = static_cast<Process*>(process);
    processObj->WriteAudio();
}

void ConvertWrapper(void* process) {
    Process* processObj = static_cast<Process*>(process);
    processObj->Convert();
}

#ifdef __cplusplus
}

#endif