#define Uses_TKeys

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

// https://ru.wikipedia.org/wiki/ASCII

struct TerminalAsciiCharInfo
{
   ushort          scanCode;        // std::uint8_t
   ushort          controlKeyState; // kbShift | kbLeftAlt | kbLeftCtrl
   ushort          remapKeyCode;

};

// TerminalAsciiCharInfo занимает 2+2+2 - 6 байт, 128*6=768, + плюс какое-то место (но небольшое) займет дополнительный код

// TrieNode - в минимальном варианте - занимает 12 байт
// На 128 символов + 128 символов с нажатым Alt (ESC-префикс) - 12*256=3072 


inline
const std::array<TerminalAsciiCharInfo, 128>& getTerminalAsciiCharInfo()
{
    // static std::array<TerminalAsciiCharInfo, 2> _ { { { 0x00, 0 , 0 }, { 0x00, 0 , 0 } } };

    static std::array<TerminalAsciiCharInfo, 128> _ {
    //  Scan   Flags     Remap     Ascii Char/Key
    //  code
    { { 0x00,          0 ,       0 }  // 0x00  NUL  - null
    , { 0x1E, kbLeftCtrl , kbCtrlA }  // 0x01  SOH  - start of heading
    , { 0x30, kbLeftCtrl , kbCtrlB }  // 0x02  STX  - start of text
    , { 0x2E, kbLeftCtrl , kbCtrlC }  // 0x03  ETX  - end of text
    , { 0x20, kbLeftCtrl , kbCtrlD }  // 0x04  EOT  - end of transmission
    , { 0x12, kbLeftCtrl , kbCtrlE }  // 0x05  ENQ  - enquire
    , { 0x21, kbLeftCtrl , kbCtrlF }  // 0x06  ACK  - acknowledgement
    , { 0x22, kbLeftCtrl , kbCtrlG }  // 0x07  BEL  - bell
    , { 0x0E,    kbShift ,  kbBack }  // 0x08  BS   - backspace   kbCtrlH generates Backsace, Shift+Backspace generates backspace instead of 0x7F
    , { 0x0F,          0 ,       0 }  // 0x09  HT   - tabulation  kbCtrlI generates Tab, no way to distinguish it in terminal
    , { 0x24, kbLeftCtrl , kbCtrlJ }  // 0x0A  LF   - line feed, not used, allow it as kbCtrlJ
    , { 0x25, kbLeftCtrl , kbCtrlK }  // 0x0B  VT   - vertical tab
    , { 0x26, kbLeftCtrl , kbCtrlL }  // 0x0C  FF   - form feed
    , { 0x1C,          0 ,       0 }  // 0x0D  CR   - carriage return kbCtrlM generates CR, no way to distinguish it in terminal
    , { 0x31, kbLeftCtrl , kbCtrlN }  // 0x0E  SO   - shift out
    , { 0x18, kbLeftCtrl , kbCtrlO }  // 0x0F  SI   - shift in
    , { 0x19, kbLeftCtrl , kbCtrlP }  // 0x10  DLE  - data link escape
    , { 0x10, kbLeftCtrl , kbCtrlQ }  // 0x11  DC1  - device control 1
    , { 0x13, kbLeftCtrl , kbCtrlR }  // 0x12  DC2  - device control 2
    , { 0x1F, kbLeftCtrl , kbCtrlS }  // 0x13  DC3  - device control 3
    , { 0x14, kbLeftCtrl , kbCtrlT }  // 0x14  DC4  - device control 4
    , { 0x16, kbLeftCtrl , kbCtrlU }  // 0x15  NAK  - negative acknowledgment
    , { 0x2F, kbLeftCtrl , kbCtrlV }  // 0x16  SYN  - synchronization
    , { 0x11, kbLeftCtrl , kbCtrlW }  // 0x17  ETB  - end of text block
    , { 0x2D, kbLeftCtrl , kbCtrlX }  // 0x18  CAN  - cancel
    , { 0x15, kbLeftCtrl , kbCtrlY }  // 0x19  EM   - end of medium
    , { 0x2C, kbLeftCtrl , kbCtrlZ }  // 0x1A  SUB  - substitute
    , { 0x01,          0 ,       0 }  // 0x1B  ESC  - escape
    , { 0x00,          0 ,       0 }  // 0x1C  FS   - file separator
    , { 0x00,          0 ,       0 }  // 0x1D  GS   - group separator
    , { 0x00,          0 ,       0 }  // 0x1E  RS   - record separator
    , { 0x00,          0 ,       0 }  // 0x1F  US   - unit separator    kbCtrlMinus?
    , { 0x39,          0 ,       0 }  // 0x20  space 
    , { 0x02,    kbShift ,       0 }  // 0x21  ! + Shift
    , { 0x28,    kbShift ,       0 }  // 0x22  " + Shift
    , { 0x04,    kbShift ,       0 }  // 0x23  # + Shift
    , { 0x05,    kbShift ,       0 }  // 0x24  $ + Shift
    , { 0x06,    kbShift ,       0 }  // 0x25  % + Shift
    , { 0x08,    kbShift ,       0 }  // 0x26  & + Shift
    , { 0x28,    kbShift ,       0 }  // 0x27  ' + Shift
    , { 0x0A,    kbShift ,       0 }  // 0x28  ( + Shift
    , { 0x0B,    kbShift ,       0 }  // 0x29  ) + Shift
    , { 0x09,    kbShift ,       0 }  // 0x2a  * + Shift
    , { 0x0D,    kbShift ,       0 }  // 0x2b  + + Shift
    , { 0x33,          0 ,       0 }  // 0x2c  ,
    , { 0x0C,          0 ,       0 }  // 0x2d  - 
    , { 0x34,          0 ,       0 }  // 0x2e  .
    , { 0x35,          0 ,       0 }  // 0x2f  / 
    , { 0x0B,          0 ,       0 }  // 0x30  0
    , { 0x02,          0 ,       0 }  // 0x31  1
    , { 0x03,          0 ,       0 }  // 0x32  2
    , { 0x04,          0 ,       0 }  // 0x33  3
    , { 0x05,          0 ,       0 }  // 0x34  4
    , { 0x06,          0 ,       0 }  // 0x35  5
    , { 0x07,          0 ,       0 }  // 0x36  6
    , { 0x08,          0 ,       0 }  // 0x37  7
    , { 0x09,          0 ,       0 }  // 0x38  8
    , { 0x0A,          0 ,       0 }  // 0x39  9
    , { 0x27,    kbShift ,       0 }  // 0x3a  : + Shift
    , { 0x27,          0 ,       0 }  // 0x3b  ;
    , { 0x33,    kbShift ,       0 }  // 0x3c  < + Shift
    , { 0x0D,          0 ,       0 }  // 0x3d  =
    , { 0x34,    kbShift ,       0 }  // 0x3e  > + Shift
    , { 0x34,          0 ,       0 }  // 0x3f  ?
    , { 0x03,          0 ,       0 }  // 0x40  @
    , { 0x1E,    kbShift ,       0 }  // 0x41  A  + Shift
    , { 0x30,    kbShift ,       0 }  // 0x42  B  + Shift
    , { 0x2E,    kbShift ,       0 }  // 0x43  C  + Shift
    , { 0x20,    kbShift ,       0 }  // 0x44  D  + Shift
    , { 0x12,    kbShift ,       0 }  // 0x45  E  + Shift
    , { 0x21,    kbShift ,       0 }  // 0x46  F  + Shift
    , { 0x22,    kbShift ,       0 }  // 0x47  G  + Shift
    , { 0x23,    kbShift ,       0 }  // 0x48  H  + Shift
    , { 0x17,    kbShift ,       0 }  // 0x49  I  + Shift
    , { 0x24,    kbShift ,       0 }  // 0x4a  J  + Shift
    , { 0x25,    kbShift ,       0 }  // 0x4b  K  + Shift
    , { 0x26,    kbShift ,       0 }  // 0x4c  L  + Shift
    , { 0x32,    kbShift ,       0 }  // 0x4d  M  + Shift
    , { 0x31,    kbShift ,       0 }  // 0x4e  N  + Shift
    , { 0x18,    kbShift ,       0 }  // 0x4f  O  + Shift
    , { 0x19,    kbShift ,       0 }  // 0x50  P  + Shift
    , { 0x10,    kbShift ,       0 }  // 0x51  Q  + Shift
    , { 0x13,    kbShift ,       0 }  // 0x52  R  + Shift
    , { 0x1F,    kbShift ,       0 }  // 0x53  S  + Shift
    , { 0x14,    kbShift ,       0 }  // 0x54  T  + Shift
    , { 0x16,    kbShift ,       0 }  // 0x55  U  + Shift
    , { 0x2F,    kbShift ,       0 }  // 0x56  V  + Shift
    , { 0x11,    kbShift ,       0 }  // 0x57  W  + Shift
    , { 0x2D,    kbShift ,       0 }  // 0x58  X  + Shift
    , { 0x15,    kbShift ,       0 }  // 0x59  Y  + Shift
    , { 0x2C,    kbShift ,       0 }  // 0x5a  Z  + Shift
    , { 0x1A,          0 ,       0 }  // 0x5b  [  
    , { 0x2B,          0 ,       0 }  // 0x5c  \  
    , { 0x1B,          0 ,       0 }  // 0x5d  ]
    , { 0x07,    kbShift ,       0 }  // 0x5e  ^  + Shift
    , { 0x0C,    kbShift ,       0 }  // 0x5f  _  + Shift
    , { 0x29,          0 ,       0 }  // 0x60  `
    , { 0x1E,          0 ,       0 }  // 0x61  a
    , { 0x30,          0 ,       0 }  // 0x62  b
    , { 0x2E,          0 ,       0 }  // 0x63  c
    , { 0x20,          0 ,       0 }  // 0x64  d
    , { 0x12,          0 ,       0 }  // 0x65  e
    , { 0x21,          0 ,       0 }  // 0x66  f
    , { 0x22,          0 ,       0 }  // 0x67  g
    , { 0x23,          0 ,       0 }  // 0x68  h
    , { 0x17,          0 ,       0 }  // 0x69  i
    , { 0x24,          0 ,       0 }  // 0x6a  j
    , { 0x25,          0 ,       0 }  // 0x6b  k
    , { 0x26,          0 ,       0 }  // 0x6c  l
    , { 0x32,          0 ,       0 }  // 0x6d  m
    , { 0x31,          0 ,       0 }  // 0x6e  n
    , { 0x18,          0 ,       0 }  // 0x6f  o
    , { 0x19,          0 ,       0 }  // 0x70  p
    , { 0x10,          0 ,       0 }  // 0x71  q
    , { 0x13,          0 ,       0 }  // 0x72  r
    , { 0x1F,          0 ,       0 }  // 0x73  s
    , { 0x14,          0 ,       0 }  // 0x74  t
    , { 0x16,          0 ,       0 }  // 0x75  u
    , { 0x2F,          0 ,       0 }  // 0x76  v
    , { 0x11,          0 ,       0 }  // 0x77  w
    , { 0x2D,          0 ,       0 }  // 0x78  x
    , { 0x15,          0 ,       0 }  // 0x79  y
    , { 0x2C,          0 ,       0 }  // 0x7a  z
    , { 0x1A,    kbShift ,       0 }  // 0x7b  {  + Shift
    , { 0x2B,    kbShift ,       0 }  // 0x7c  |  + Shift
    , { 0x1B,    kbShift ,       0 }  // 0x7d  }  + Shift
    , { 0x29,    kbShift ,       0 }  // 0x7e  ~  + Shift
    , { 0x0E,          0 ,  kbBack }  // 0x7F - Backspace/Del - remap to backspace
    } };

    return _;
}



using std::cout;
using std::cerr;

int main(int argc, char* argv[])
{

    using umba::tokenizer::payload_type;

    // ESC - 0x1B "\x1B"

    trieBuilder.addTokenSequence("\x1B", (payload_type)kbEsc)   ;

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
    cout << "std::array<umba::tokenizer::TrieNode, " << trie.size() << "> ansiTerminalSequencesTrie\n{\n";

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

