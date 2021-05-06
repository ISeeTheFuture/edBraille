#include <cstdio>
#include <string>

class Braille {
private:
    // ㄱ ㄲ ㄴ ㄷ ㄸ ㄹ ㅁ ㅂ ㅃ ㅅ ㅆ ㅇ ㅈ ㅉ ㅊ ㅋ ㅌ ㅍ ㅎ
    int top[19] = { 0x3131, 0x3132, 0x3134, 0x3137, 0x3138, 0x3139, 0x3141, 0x3142, 0x3143, 0x3145, 0x3146, 0x3147, 0x3148, 0x3149, 0x314a, 0x314b, 0x314c, 0x314d, 0x314e };
    // 0x2808, 0x2820 0x2808, 0x2809, 0x280A, 0x2820 0x280A, 0x2810, 0x2811, 0x2818, 0x2820 0x2818, 0x2820, 0x2820 0x2820, 0x281B, 0x2828, 0x2820 0x2828, 0x2830, 0x280B, 0x2813, 0x2819, 0x281A
    // ⠈
    // ⠠⠈
    // ⠉
    // ⠊
    // ⠠⠊
    // ⠐
    // ⠑
    // ⠘
    // ⠠⠘
    // ⠠
    // ⠠⠠
    // ⠛
    // ⠨
    // ⠠⠨
    // ⠰
    // ⠋
    // ⠓
    // ⠙
    // ⠚


    // ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ
    int mid[21] = { 0x314f, 0x3150, 0x3151, 0x3152, 0x3153, 0x3154, 0x3155, 0x3156, 0x3157, 0x3158, 0x3159, 0x315a, 0x315b, 0x315c, 0x315d, 0x315e, 0x315f, 0x3160, 0x3161, 0x3162, 0x3163 };
    // ⠣
    // ⠗
    // ⠜
    // ⠜⠗
    // ⠎
    // ⠝
    // ⠱
    // ⠌
    // ⠥
    // ⠧
    // ⠧⠗
    // ⠽
    // ⠬
    // ⠍
    // ⠏
    // ⠏⠗
    // ⠍⠗
    // ⠩
    // ⠪
    // ⠺
    // ⠕

    // ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ
    int bot[28] = { 0, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136, 0x3137, 0x3139, 0x313a, 0x313b, 0x313c, 0x313d, 0x313e, 0x313f, 0x3140, 0x3141, 0x3142, 0x3144, 0x3145, 0x3146, 0x3147, 0x3148, 0x314a, 0x314b, 0x314c, 0x314d, 0x314e };
    // ⠁
    // ⠁⠁
    // ⠁⠄
    // ⠒
    // ⠒⠅
    // ⠒⠴
    // ⠔
    // ⠂
    // ⠂⠁
    // ⠂⠢
    // ⠂⠃
    // ⠂⠄
    // ⠂⠦
    // ⠂⠲
    // ⠂⠴
    // ⠢
    // ⠃
    // ⠃⠄
    // ⠄
    // ⠌
    // ⠶
    // ⠅
    // ⠆
    // ⠖
    // ⠦
    // ⠲
    // ⠴


public:
    int separater(std::string dest, std::string src) {
        for(int i = 0; i < src.size(); i++) {
            int topBuf = 0;
            int midBuf = 0;
            int botBuf = 0;
            int ch = src.at(i);
            if(ch >= 0xAC00 && ch <= 0xD7A3) {
                botBuf = ch - 0xAC00;
                topBuf = botBuf / (21 * 28);
                dest += top[topBuf];
                
                botBuf = botBuf % (21 * 28);
                midBuf = botBuf / 28;
                dest += mid[midBuf];
                
                botBuf = botBuf % 28;
                if(botBuf != 0) {
                    dest += bot[botBuf];
                }
            }
            return 1;
        }
    };

    std::string charToBraille(char src) {
        std::string ret = 0;

        switch (src) {
            // case 0x3131 : ret = 0x2808; break;
            // case 0x3132 : ret = 0x2800+""+0x2808; break;
            // case 0x3133 : ret =  0x2800+""+0x2840; break;
            // case 0x3134 : ret =  ; break;
            // case 0x3135 : ret =  ; break;
            // case 0x3136 : ret =  ; break;
            // case 0x3137 : ret =  ; break;
            // case 0x3139 : ret =  ; break;
            // case 0x313a : ret =  ; break;
            // case 0x313b : ret =  ; break;
            // case 0x313c : ret =  ; break;
            // case 0x313d : ret =  ; break;
            // case 0x313e : ret =  ; break;
            // case 0x313f : ret =  ; break;
            // case 0x3140 : ret =  ; break;
            // case 0x3141 : ret =  ; break;
            // case 0x3142 : ret =  ; break;
            // case 0x3144 : ret =  ; break;
            // case 0x3145 : ret =  ; break;
            // case 0x3146 : ret =  ; break;
            // case 0x3147 : ret =  ; break;
            // case 0x3148 : ret =  ; break;
            // case 0x314a : ret =  ; break;
            // case 0x314b : ret =  ; break;
            // case 0x314c : ret =  ; break;
            // case 0x314d : ret =  ; break;
            // case 0x314e : ret =  ; break;

        
        default:
            break;
        }
    }
    int strToBraille(std::string dest, std::string src) {
        return 1;
    };
};