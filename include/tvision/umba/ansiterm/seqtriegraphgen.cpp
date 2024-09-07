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
#include <sstream>

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


    umba::tokenizer::tokenTriePrintTableGraph( "ansiseq", trie, std::cout
                                             , [](umba::tokenizer::token_type tk)// TokenToStringConverter converter
                                               {
                                                   std::ostringstream oss;

                                                   if (tk==0x1B)
                                                   {
                                                       oss << "ESC";
                                                   }
                                                   else if (tk>0x20 && tk<0x7F)
                                                   {
                                                       oss << "'" << (char)tk << "'";
                                                   }
                                                   else
                                                   {
                                                       oss << "0x" << std::hex << tk;
                                                   }

                                                   return oss.str();
                                               }
                                             );
    return 0;
}

