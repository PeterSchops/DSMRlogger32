#ifndef FSMANAGER_H
#define FSMANAGER_H

//============ Includes ====================
#include "arduinoGlue.h"
#include <HTTPClient.h>
#include "UpdateManager.h"
//#include <update.h>

//============ Prototypes ==================
bool handleList();                                          
void deleteRecursive(const char *path);                     
bool handleFile(String &&path);              
void handleFileUpload();               
//void handleUpload();        
void handleLocalUpdate();
void handleRemoteUpdate();
//void RFUlistFirmware();
void RFUlistFiles(const char* startWith);
void formatFS();                                            
void listFS();                                              
void sendResponce();                                        
const String formatBytes(size_t const &bytes);              
void reBootESP();                                           
void doRedirect(String msg, int wait, const char *URL, bool reboot);
String getContentType(String filename);                     

#endif // FSMANAGER_H
