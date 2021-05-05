#ifndef __brailleConverter_H__
#define __brailleConverter_H__

class Braille {
    /**
    * 한글은 초성, 중성, 종성의 조합이므로 분해한다.
    */
    int separater(string dest, string src);

    int strToBraille(string dest, string src);
}

#endif