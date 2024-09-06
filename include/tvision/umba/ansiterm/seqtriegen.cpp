#define Uses_TKeys

// Requires umba and marty_decimal libs
// git clone --recurse-submodules https://github.com/al-martyn1/marty_decimal.git      libs/marty_decimal
// git clone --recurse-submodules https://github.com/al-martyn1/umba_mm_mod_umba.git   libs/umba


#include "umba/umba.h"
//
#include "umba/tokenizer.h"
#include "umba/char_class.h"
#include "umba/c_tokenizer.h"

//
#include "tvision/tv.h"
// 
#include "tvision/ttypes.h"
//
#include "tvision/tkeys.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <array>



umba::tokenizer::TrieBuilder  trieBuilder;



using std::cout;
using std::cerr;

int main(int argc, char* argv[])
{

    using umba::tokenizer::payload_type;

    // ESC - 0x1B "\x1B"

    trieBuilder.addTokenSequence("\x1B"    , (payload_type)kbEsc)   ;
    trieBuilder.addTokenSequence("\x1B\x1B", (payload_type)kbAltEsc);

    trieBuilder.addTokenSequence("\x1B[11~", (payload_type)kbF1 );
    trieBuilder.addTokenSequence("\x1B[12~", (payload_type)kbF2 );
    trieBuilder.addTokenSequence("\x1B[13~", (payload_type)kbF3 );
    trieBuilder.addTokenSequence("\x1B[14~", (payload_type)kbF4 );
    trieBuilder.addTokenSequence("\x1B[15~", (payload_type)kbF5 );
    trieBuilder.addTokenSequence("\x1B[17~", (payload_type)kbF6 );
    trieBuilder.addTokenSequence("\x1B[18~", (payload_type)kbF7 );
    trieBuilder.addTokenSequence("\x1B[19~", (payload_type)kbF8 );
    trieBuilder.addTokenSequence("\x1B[20~", (payload_type)kbF9 );
    trieBuilder.addTokenSequence("\x1B[21~", (payload_type)kbF10);
    trieBuilder.addTokenSequence("\x1B[23~", (payload_type)kbF11);
    trieBuilder.addTokenSequence("\x1B[24~", (payload_type)kbF12);

    trieBuilder.addTokenSequence("\x1B[23~", (payload_type)kbShiftF1 );
    trieBuilder.addTokenSequence("\x1B[24~", (payload_type)kbShiftF2 );
    trieBuilder.addTokenSequence("\x1B[25~", (payload_type)kbShiftF3 );
    trieBuilder.addTokenSequence("\x1B[26~", (payload_type)kbShiftF4 );
    trieBuilder.addTokenSequence("\x1B[28~", (payload_type)kbShiftF5 );
    trieBuilder.addTokenSequence("\x1B[29~", (payload_type)kbShiftF6 );
    trieBuilder.addTokenSequence("\x1B[31~", (payload_type)kbShiftF7 );
    trieBuilder.addTokenSequence("\x1B[32~", (payload_type)kbShiftF8 );
    trieBuilder.addTokenSequence("\x1B[33~", (payload_type)kbShiftF9 );
    trieBuilder.addTokenSequence("\x1B[34~", (payload_type)kbShiftF10);
    trieBuilder.addTokenSequence("\x1B[23~", (payload_type)kbShiftF11);
    trieBuilder.addTokenSequence("\x1B[24~", (payload_type)kbShiftF12);

    trieBuilder.addTokenSequence("\x1B\x1B[11~", (payload_type)kbAltF1 );
    trieBuilder.addTokenSequence("\x1B\x1B[12~", (payload_type)kbAltF2 );
    trieBuilder.addTokenSequence("\x1B\x1B[13~", (payload_type)kbAltF3 );
    trieBuilder.addTokenSequence("\x1B\x1B[14~", (payload_type)kbAltF4 );
    trieBuilder.addTokenSequence("\x1B\x1B[15~", (payload_type)kbAltF5 );
    trieBuilder.addTokenSequence("\x1B\x1B[17~", (payload_type)kbAltF6 );
    trieBuilder.addTokenSequence("\x1B\x1B[18~", (payload_type)kbAltF7 );
    trieBuilder.addTokenSequence("\x1B\x1B[19~", (payload_type)kbAltF8 );
    trieBuilder.addTokenSequence("\x1B\x1B[20~", (payload_type)kbAltF9 );
    trieBuilder.addTokenSequence("\x1B\x1B[21~", (payload_type)kbAltF10);
    trieBuilder.addTokenSequence("\x1B\x1B[23~", (payload_type)kbAltF11);
    trieBuilder.addTokenSequence("\x1B\x1B[24~", (payload_type)kbAltF12);

#if 0
    trieBuilder.addTokenSequence("\x1B", (payload_type));
#endif

    std::vector<umba::tokenizer::TrieNode> trie;

    trieBuilder.buildTokenTrie(trie);

    cout << "static const\n";
    cout << "::std::array<umba::tokenizer::TrieNode, " << trie.size() << "> ansiTerminalSequencesTrie\n{\n";

    cout << "\n// parendIdx, lookupStartIdx, chunkSize, childsIdx[, extra], tokenId[, level]\n\n";

    auto printTrieIndex = [&](UMBA_TOKENIZER_TRIE_INDEX_TYPE idx)
    {
        if (idx==UMBA_TOKENIZER_TRIE_INDEX_INVALID)
            cout << "UMBA_TOKENIZER_TRIE_INDEX_INVALID";
        else
            cout << idx;
    };

    auto printPayloadValue = [&](UMBA_TOKENIZER_PAYLOAD_TYPE p)
    {
        if (p==UMBA_TOKENIZER_PAYLOAD_INVALID)
            cout << "UMBA_TOKENIZER_PAYLOAD_INVALID";
        else
            cout << p;
    };

    for(std::size_t i=0; i!=trie.size(); ++i)
    {
        const umba::tokenizer::TrieNode& node = trie[i];

        if (!i)
            cout << "{ ";
        else
            cout << ", ";

        cout << "{ "; printTrieIndex(node.parentNodeIndex); cout << ", "; printTrieIndex(node.lookupChunkStartIndex); cout << ", "; printTrieIndex(node.lookupChunkSize); cout << ", "; printTrieIndex(node.childsIndex); 
        cout << ", "; printPayloadValue(node.payload);

#if !defined(UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_DISABLE)
        cout << " /*,*/ UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_INITIALIZER_LIST_INIT(" << node.payloadExtra << ")";
#else
        cout << " /*,*/ UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_INITIALIZER_LIST_INIT(0)";
#endif

        cout << ", " << node.token; 

#if !defined(UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE)
        cout << " /*,*/ UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_INITIALIZER_LIST_INIT(" << node.level << ")";
#else
        cout << " /*,*/ UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_INITIALIZER_LIST_INIT(0)";
#endif

        cout << "}\n";

    }

    cout << "}\n};\n\n";

    return 0;
}

