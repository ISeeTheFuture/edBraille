#ifndef __htmlDoc_H__
#define __htmlDoc_H__

#include <string>

class htmlDoc {
public:
    bool isHtmlFile(const char* srcPath) const;
    int processFile(const char* srcPath, const char* resPath);
};

#endif