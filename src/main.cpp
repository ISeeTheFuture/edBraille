#include "htmlDoc.h"
#include "errHandler.h"
// #include "brailleConv.h"

#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <cstring>

#include "dirent.h"

enum FileORDir {
    NOT_FILE_OR_DIR = 0,
    DIRECTORY_PATH,
    FILE_PATH
};

#define MAX_PATH_LENGTH 256

static int isFileOrDirectory(const char* path) {
    struct stat s;
    if(stat(path, &s) == 0) {
        if(s.st_mode & S_IFDIR) {
            return DIRECTORY_PATH;
        } else if (s.st_mode & S_IFREG) {
            return FILE_PATH;
        }
        return NOT_FILE_OR_DIR;
    }
    return NOT_FILE_OR_DIR;
}

static std::vector<std::string> getFileList(const char* path) {
    // c++ 17부터는 <filesystem>의 directory_iterator() 사용해 2줄로 끝낼 수 있음
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> fileList;
    if((dir = opendir(path)) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            char fullPath[MAX_PATH_LENGTH] = {0,};
            std::snprintf(fullPath, MAX_PATH_LENGTH,"%s/%s", path, ent->d_name);
            if(isFileOrDirectory(fullPath) == FILE_PATH){
                fileList.push_back(std::string(fullPath));
            }
        }
    } else {
        return fileList;
    }
    return fileList;
}

static std::vector<std::string> pickHtmlOnly(const std::vector<std::string>& fileList, const htmlDoc &pHtmlDoc){
    std::vector<std::string> htmlList;
    std::vector<std::string>::const_iterator iter;
    for(iter = fileList.begin(); iter != fileList.end(); ++iter) {
        std::string filePath = *iter;
        if(pHtmlDoc.isHtmlFile(filePath.c_str())) {
            htmlList.push_back(filePath.c_str());
        }
    }
    return htmlList;
}

static std::string getFileName(const char* filePath) {
    std::string filePathStr = filePath;
    const int sepIndex = filePathStr.rfind('/');
    filePathStr = filePathStr.substr(sepIndex + 1);
    return filePathStr;
}

int main(int argc, char* argv[]) {
    int ret = NO_ERROR;
    const char *srcPath = argv[1];
    const char *resPath = argv[2];
    if(!srcPath || std::strlen(srcPath) == 0) {
        puts("please put the src file or directory path\n");
        return ret;
    } else if (!resPath || std::strlen(resPath) == 0) {
        puts("please put the result directory path\n");
        return ret;
    }

    htmlDoc pHtmlDoc;
    int srcFileOrDir = isFileOrDirectory(srcPath);
    int resFileOrDir = isFileOrDirectory(resPath);
    if(resFileOrDir != DIRECTORY_PATH) {
        ret = ERROR_MAIN_DEST_PATH_NOT_DIR;
    }

    std::vector<std::string> fileList;
    if (ret != NO_ERROR) {
    } else if (srcFileOrDir == DIRECTORY_PATH) {
        fileList = getFileList(srcPath);
    } else if(srcFileOrDir == FILE_PATH) {
        if (pHtmlDoc.isHtmlFile(srcPath)) {
            fileList.push_back(srcPath);
        } else {
            ret = ERROR_MAIN_SRC_PATH_NO_FILE_OR_DIR;
        }
    }
    std::vector<std::string> htmlList;
    if (ret == NO_ERROR) {
        htmlList = pickHtmlOnly(fileList, pHtmlDoc);
    }

    if(ret == NO_ERROR) {
        std::vector<std::string>::const_iterator iter;
        for(iter = htmlList.begin(); iter != htmlList.end(); ++iter) {
            char resFilePath[MAX_PATH_LENGTH] = {0,};
            std::string srcFilePath = *iter;
            snprintf(resFilePath, MAX_PATH_LENGTH, "%s/%s", resPath, getFileName(srcFilePath.c_str()).c_str());
            ret = pHtmlDoc.processFile(srcFilePath.c_str(), resFilePath);
            if(ret != NO_ERROR) {
                break;
            }
        }
    }

    if(ret != NO_ERROR) {
        printf("ERROR CODE : %d\n", ret);
    }

    return 0;
}