#include "brailleConv.h"

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

const int KOREAN_LETTER_LEN = 3;

/**
 * 1110xxxx / 10xxxxxx / 10xxxxxx 확인
*/
static bool isWChar(const char* pStr, const int idx) {
    if ((pStr[idx] & 0xf0) >> 4 != 0b1110) {
        return false;
    }
    if ((pStr[idx + 1] & 0xc0) >> 6 != 0b10) {
        return false;
    }
    if ((pStr[idx + 2] & 0xc0) >> 6 != 0b10) {
        return false;
    }
    return true;
}

int brailleConv::separateChar(std::string* dest, const std::string src) {
    std::string ret;

    const char* cStr = src.c_str();
    const int cStrLen = std::strlen(cStr);

    for(int i = 0; i < cStrLen; ++i) {
        char notKor = 0;

        int wChar = 0;
        if(i < (cStrLen - KOREAN_LETTER_LEN + 1) && isWChar(cStr, i)) {
            // 3바이트 길이의 utf-8에서 쓰는 바이트
            wChar = ((cStr[i] & 0xf) << 12) + ((cStr[i+1] & 0x3f) << 6) + (cStr[i+2] & 0x3f);
        }

        std::string koBraille = koWCharToBraille(wChar);
        if(!koBraille.empty()) {
            i += 2;
            ret += koBraille;
        } else { // 한글 외의 문자는 변환하지 않는다
            notKor = cStr[i];
            ret += notKor;
        }
    }
    *dest = ret;

    return 1;
}

#define NO_BRAILLE -1
std::string brailleConv::koWCharToBraille(const int koWChar) {
    int topIdx = NO_BRAILLE;
    int midIdx = NO_BRAILLE;
    int botIdx = NO_BRAILLE;
    std::string ret;
    if(koWChar >= 0xAC00 && koWChar <= 0xD7A3) { // 가(AC00) ~ 힣(D7A3)일 경우
        int botBuf = 0;

        botBuf = koWChar - 0xAC00;
        topIdx = botBuf / (JOONGSUNG_COUNT * JONGSUNG_COUNT);

        if(top[topIdx] == "⠛") { // o은 생략, 약어 변환 함수는 따로 만들 것
            topIdx = NO_BRAILLE;
        }

        botBuf = botBuf % (JOONGSUNG_COUNT * JONGSUNG_COUNT);
        midIdx = botBuf / JONGSUNG_COUNT;

        if(mid[midIdx] == "⠣") {
            std::string topBraille = top[topIdx];
            if (topBraille == "⠈" || topBraille == "⠐" || topBraille == "⠠" || topBraille == "⠰") { // ㄱㄹㅅㅊ 는 ㅏ 생략 가능
                midIdx = NO_BRAILLE;
            }
        }

        botIdx = botBuf % JONGSUNG_COUNT;
    } else if (koWChar >= 0x3131 && koWChar <= 0x314E) { // ㄱ ~ ㅎ일 경우
        topIdx = koWChar - 0x3131;
    } else if (koWChar >= 0x314F && koWChar <= 0x3163) { // ㅏ ~ ㅣ일 경우
        midIdx = koWChar - 0x314F;
    }

    if(topIdx != NO_BRAILLE) {
        ret.append(top[topIdx]);
    }
    if(midIdx != NO_BRAILLE) {
        ret.append(mid[midIdx]);
    }
    if(botIdx != NO_BRAILLE) {
        ret.append(bot[botIdx]);
    }
    return ret;
}

int brailleConv::strToBraille(std::string* dest, const std::string src) {
    separateChar(dest, src);
    return 0;
}