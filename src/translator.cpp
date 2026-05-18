#include "translator.hpp"

// static const CharMapping mappings[] = {
//     {'A', 1, 2, 3},
//     {'B', 4, 5, 6}
// };

Translator::Translator() = default;

Translator::~Translator() = default;

CharMapping Translator::Translate(const char* messageEng) {
    for(int i = 0; messageEng[i] != '\0'; i++) {
        char curr = messageEng[i];


    }
} 