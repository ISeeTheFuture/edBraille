#include "htmlDoc.h"
#include "errHandler.h"
#include "brailleConv.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

static htmlDocPtr readHtmlDoc(const char *srcPath){
    htmlParserCtxtPtr parserCtx = htmlNewParserCtxt();
    htmlDocPtr doc = htmlCtxtReadFile(parserCtx, srcPath, NULL, 0);
    htmlFreeParserCtxt(parserCtx);
    return doc;
}

static void xmlNodeToString(xmlNodePtr node, std::string& strResult){
    xmlBuffer* lpBuf = xmlBufferCreate();
    xmlNodeDump(lpBuf, node->doc, node, 0, 0);

    strResult = (const char*)xmlBufferContent(lpBuf);
    xmlBufferFree(lpBuf);
}

static int writeHtml(std::string& filename, long int size, char* body) {
    std::fstream stream;
    stream.open(filename.c_str(), std::ios_base::out | std::ios_base::binary);
    if (stream.good()) {
        stream.write((char*)body, size);
        stream.close();
        return NO_ERROR;
    }
    return ERROR_HTMLDOC_WRITE_FILE_FAILURE;
}

static void printNode(htmlNodePtr node) {
    if (node->type == XML_ELEMENT_NODE) {
        printf("node name : %s\n", node->name);
    } else {
        printf("not elem : %s\n", node->content);
    }
}

static void convNodeText(htmlNodePtr node) {
    if (node->type == XML_TEXT_NODE) {
        // printf("text node : %s\n", node->content);
        // int originStrLen = xmlStrlen(node->content);
        // const char* originStr = (char*)node->content;
        brailleConv pBrailleConv;
        std::string brailleStr;
        pBrailleConv.strToBraille(&brailleStr, std::string((char*)node->content));
        node->content = 0;

        const xmlChar* xmlBrailleStr = (xmlChar*)brailleStr.c_str();
        xmlTextConcat(node, xmlBrailleStr, xmlStrlen(xmlBrailleStr));
    }
}

static void nodeTravel(htmlNodePtr node) {
    // printNode(node);
    convNodeText(node);
    if(node->children) {
        nodeTravel(node->children);
    } else if(node->next) {
        nodeTravel(node->next);
    } else if(node->parent->next) {
        nodeTravel(node->parent->next);
    }
}

bool htmlDoc::isHtmlFile(const char* srcFile) const {
    xmlInitParser();
    htmlDocPtr m_pDoc = readHtmlDoc(srcFile);
    if(!m_pDoc) {
        return false;
    }
    xmlFreeDoc(m_pDoc);
    xmlCleanupParser();
    return true;
}

int htmlDoc::processFile(const char* srcFile, const char* resFile) {
    // libxml의 함수들은 자동으로 xml파서를 초기화하기 때문에 굳이 명시적으로 초기화 안해도 웬만해선 정상 동작함.
    // 그러나 초기화 안하면 복잡한 작업이나 쓰레드 환경에서는 메모리 누수 가능성이 있음.
    // 메모리 누수 가능성 : https://mail.gnome.org/archives/xml/2007-October/msg00004.html
    // 쓰레드 환경 : http://batsu05.egloos.com/v/2517310
    xmlInitParser();

    printf("srcFile : %s\n", srcFile);
    printf("resFile : %s\n", resFile);
    int ret = NO_ERROR;

    htmlDocPtr m_pDoc = readHtmlDoc(srcFile);

    htmlNodePtr rootNode = xmlDocGetRootElement(m_pDoc);
    if(!rootNode) {
        xmlFreeDoc(m_pDoc);
        xmlCleanupParser();
        return ERROR_HTMLDOC_CANNOT_FIND_ROOTNODE;
    }

    // 변환
    nodeTravel(rootNode);

    // 여기서부터 결과 파일 생성
    std::string resHtmlStr;
    xmlNodeToString(rootNode, resHtmlStr);

    long int nSize = resHtmlStr.size();

    std::string resHtmlPath = resFile;
    ret = writeHtml(resHtmlPath, nSize, (char*)resHtmlStr.c_str()); // 여긴 어차피 마지막이라 에러 처리 필요 없음

    xmlFreeDoc(m_pDoc);
    xmlCleanupParser();
    return ret;
}