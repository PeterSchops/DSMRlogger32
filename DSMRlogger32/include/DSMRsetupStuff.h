#ifndef DSMRSETUPSTUFF_H
#define DSMRSETUPSTUFF_H

//============ Includes ====================

//-- from DSMRsetupStuff.ino -----------
//-- Used in: DSMRlogger32.cpp, DSMRsetupStuff.cpp
void setupFileSystem();                                     
//-- Used in: DSMRlogger32.cpp, DSMRsetupStuff.cpp
void setupSysLogger(const char*);                                      
//-- Used in: DSMRlogger32.cpp, DSMRsetupStuff.cpp
void setupPsram();                                          
//-- Used in: DSMRlogger32.cpp, DSMRsetupStuff.cpp
bool setupIsFsPopulated();                                  

#endif // DSMRSETUPSTUFF_H
