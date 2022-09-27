#ifndef __brailleConv_H__
#define __brailleConv_H__

#include <string>
#include <vector>
#include <iostream>

class brailleConv {
private:
    static const int CHOSUNG_COUNT = 19;
    static const int JOONGSUNG_COUNT = 21;
    static const int JONGSUNG_COUNT = 28;

    // ㄱ ㄲ ㄴ ㄷ ㄸ ㄹ ㅁ ㅂ ㅃ ㅅ ㅆ ㅇ ㅈ ㅉ ㅊ ㅋ ㅌ ㅍ ㅎ
    // int top[19] = { 0x3131, 0x3132, 0x3134, 0x3137, 0x3138, 0x3139, 0x3141, 0x3142, 0x3143, 0x3145, 0x3146, 0x3147, 0x3148, 0x3149, 0x314a, 0x314b, 0x314c, 0x314d, 0x314e };
    std::string top[CHOSUNG_COUNT] = {"⠈", "⠠⠈", "⠉" ,"⠊" ,"⠠⠊", "⠐", "⠑", "⠘", "⠠⠘", "⠠", "⠠⠠", "⠛", "⠨", "⠠⠨", "⠰", "⠋", "⠓", "⠙", "⠚"};
    //                                 ㄱ    ㄲ    ㄴ   ㄷ     ㄸ     ㄹ   ㅁ   ㅂ    ㅃ     ㅅ    ㅆ     ㅇ   ㅈ    ㅉ     ㅊ   ㅋ   ㅌ    ㅍ    ㅎ

    // ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ
    // int mid[21] = { 0x314f, 0x3150, 0x3151, 0x3152, 0x3153, 0x3154, 0x3155, 0x3156, 0x3157, 0x3158, 0x3159, 0x315a, 0x315b, 0x315c, 0x315d, 0x315e, 0x315f, 0x3160, 0x3161, 0x3162, 0x3163 };
    std::string mid[JOONGSUNG_COUNT] = {"⠣", "⠗", "⠜", "⠜⠗", "⠎", "⠝", "⠱", "⠌", "⠥", "⠧", "⠧⠗", "⠽", "⠬", "⠍", "⠏", "⠏⠗", "⠍⠗", "⠩", "⠪", "⠺", "⠕"};

    // ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ
    // int bot[28] = { 0, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136, 0x3137, 0x3139, 0x313a, 0x313b, 0x313c, 0x313d, 0x313e, 0x313f, 0x3140, 0x3141, 0x3142, 0x3144, 0x3145, 0x3146, 0x3147, 0x3148, 0x314a, 0x314b, 0x314c, 0x314d, 0x314e };
    std::string bot[JONGSUNG_COUNT] = {"⠁", "⠁⠁", "⠁⠄", "⠒", "⠒⠅", "⠒⠴", "⠔", "⠂", "⠂⠁", "⠂⠢", "⠂⠃", "⠂⠄", "⠂⠦", "⠂⠲", "⠂⠴", "⠢", "⠃", "⠃⠄", "⠄", "⠌", "⠶", "⠅", "⠆", "⠖", "⠦", "⠲", "⠴"};


    // 추가할 규칙
    // 1. 초성 ㅇ은 중성이 있다면 표현X
    // 2. ㄱㄹㅅㅇㅊ를 제외하고 +ㅏ 는 생략
    // 3. 가, 사는 별도 약자가 있음
    // ...그외에도 약어 규칙이 많은데.. 약자가 권장되지만, 안써도 틀린 것은 아닌 모양이라.. 나중에 패치로 넣을 것
private:
    /**
    * 한글은 초성, 중성, 종성의 조합이므로 분해한다.
    * wstring 쓰지말 것. 유니코드와 멀티바이트 변환이 추가로 들어가야 하며, 리눅스와 윈도우의 멀티바이트 단위가 달라서 별도로 처리해야 함.
    * 또한 어차피 한글 영문 구분할 때 사용할 함수가 wstring 쓴다고 해서 장점이 있는 것도 아님.
    */
    int separateChar(std::string* dest, const std::string wSrc);
    std::string koWCharToBraille(const int koWChar);

public:
    int strToBraille(std::string* dest, const std::string src);
};

#endif