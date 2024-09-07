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

//
#include "makeseqtriebuilder.h"



using std::cout;
using std::cerr;

int main(int argc, char* argv[])
{

    using umba::tokenizer::payload_type;


#if 0
    trieBuilder.addTokenSequence("\x1B", (payload_type));
#endif

    std::vector<umba::tokenizer::TrieNode> trie;

    umba::tokenizer::TrieBuilder trieBuilder = makeSeqTrieBuilder();

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

