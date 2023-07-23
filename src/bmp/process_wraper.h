//
// Created by saintedlittle on 23.07.2023.
//

#ifndef WAVGENERATOR_PROCESS_WRAPER_H
#define WAVGENERATOR_PROCESS_WRAPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Declarations for the C++ functions, treated as C functions
void WriteAudioWrapper(void* process);
void ConvertWrapper(void* process);

#ifdef __cplusplus
}
#endif

#endif //WAVGENERATOR_PROCESS_WRAPER_H
