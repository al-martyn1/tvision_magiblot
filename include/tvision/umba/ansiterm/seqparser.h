#pragma once

#ifndef UMBA_ASSERT
    #include "../internal/umba/umba_assert.h"
#endif

#include "termasciici.h"
#include "../c_tokenizer.h"

//

#include <array>
#include <algorithm>


// tvision::umba::ansiterm::
namespace tvision{
namespace umba{
namespace ansiterm{



//!
/*!
    @tparam TValidKeyHandler       (ushort keyCode, ushort controlKeyState)
    @tparam TInvalidSequenceHandler(const uchar* pData, size_t size)
*/
template<typename TValidKeyHandler, typename TInvalidSequenceHandler>
class AnsiTerminalKeySequenceParser
{

    using TrieIndexType    = umba::tokenizer::trie_index_type;
    using TrieTokenType    = umba::tokenizer::token_type     ;
    using TriePayloadType  = umba::tokenizer::payload_type   ;
    using TrieNode         = umba::tokenizer::TrieNode       ;
    

    enum State
    {
        stStart    = 0,
        stGotEsc   = 1
        //stdReadSeq = 2
    };

    State                          st        = stStart;
    TrieIndexType                  trieIndex = umba::tokenizer::trie_index_invalid;
    TValidKeyHandler               validKeyHandler;
    TInvalidSequenceHandler        invalidSequenceHandler;

    TrieIndexType                  seqLen = 0;

    static constexpr const uchar   esc_code = 0x1B;

    static
    const auto& getAnsiTerminalSequencesTrie()
    {
        #include "seqtrie.h"

        return ansiTerminalSequencesTrie;
    }



// operatorIdx = umba::tokenizer::tokenTrieFindNext(operatorsTrie, trie_index_invalid, (token_type)ch);
// trie_index_type tokenTrieFindFirst(const ContainerType &tokenTrie, token_type tk)
// trie_index_type tokenTrieTraverse(const ContainerType &tokenTrie, TokenSequenceIteratorType b, TokenSequenceIteratorType e)
// void umba::tokenizer::tokenTrieBackTrace(const ContainerType &tokenTrie, trie_index_type curIndex, BackTraceHandlerType handler)

    static
    TrieIndexType trieFindFirst(uchar ch)
    {
        return tvision::umba::tokenizer::tokenTrieFindFirst(getAnsiTerminalSequencesTrie(), (TrieTokenType)ch);
    }

    static
    TrieIndexType trieFindNext(TrieIndexType curIdx, uchar ch)
    {
        return tvision::umba::tokenizer::tokenTrieFindNext(getAnsiTerminalSequencesTrie(), curIdx, (TrieTokenType)ch);
    }

    template<typename BackTraceHandlerType>
    static
    void trieBackTrace(TrieIndexType curIndex, BackTraceHandlerType handler)
    {
        tvision::umba::tokenizer::tokenTrieBackTrace(getAnsiTerminalSequencesTrie(), curIndex, handler);
    }

    static
    ushort getControlKeyStateForKnownKeyCode(ushort knownKey)
    {
        // I couldn't understand the system, so I just used lists and ranges

        // kbShift kbLeftCtrl kbAltShift, kbLeftAlt

        if (knownKey>=kbCtrlA && knownKey<=kbCtrlZ)
            return kbLeftCtrl;

        // kbAltQ      ,   kbAltW      ,    kbAltE      ,   kbAltR      ,   kbAltT      ,    kbAltY      ,   kbAltU      ,   kbAltI      ,    kbAltO      ,   kbAltP
        // kbAltA      ,   kbAltS      ,    kbAltD      ,   kbAltF      ,   kbAltG      ,    kbAltH      ,   kbAltJ      ,   kbAltK      ,    kbAltL      ,   kbAltZ      ,   kbAltX      ,    kbAltC      ,   kbAltV      ,   kbAltB      ,    kbAltN      ,   kbAltM

        //static std::array<ushort, 0> altShiftKeys{};
        static ::std::array<ushort, 16> shiftKeys{ kbShiftIns, kbShiftDel, kbShiftTab, kbShiftF1, kbShiftF2, kbShiftF3, kbShiftF4, kbShiftF5, kbShiftF6, kbShiftF7, kbShiftF8, kbShiftF9, kbShiftF10, kbShiftF11, kbShiftF12, kbCtrlEnter };
        static ::std::array<ushort, 26> ctrlKeys { kbCtrlIns , kbCtrlDel , kbCtrlTab , kbCtrlF1 , kbCtrlF2 , kbCtrlF3 , kbCtrlF4 , kbCtrlF5 , kbCtrlF6 , kbCtrlF7 , kbCtrlF8 , kbCtrlF9 , kbCtrlF10 , kbCtrlF11 , kbCtrlF12 , kbAltEnter , kbCtrlLeft, kbCtrlRight, kbCtrlUp, kbCtrlDown, kbCtrlEnd, kbCtrlPgDn, kbCtrlHome, kbCtrlPgUp, kbCtrlBack, kbCtrlPrtSc };
        static ::std::array<ushort, 38> altKeys  { kbAltSpace, kbAltDel  , kbAltTab  , kbAltF1  , kbAltF2  , kbAltF3  , kbAltF4  , kbAltF5  , kbAltF6  , kbAltF7  , kbAltF8  , kbAltF9  , kbAltF10  , kbAltF11  , kbAltF12               , kbAltLeft , kbAltRight , kbAltUp , kbAltDown , kbAltEnd , kbAltPgDn , kbAltHome , kbAltPgUp , kbAltBack              , kbAlt1, kbAlt2, kbAlt3, kbAlt4, kbAlt5, kbAlt6, kbAlt7, kbAlt8, kbAlt9, kbAlt0, kbAltIns, kbAltMinus, kbAltEqual, kbAltEsc};

        // for(auto c : altShiftKeys)
        // {
        //     if (c==knownKey)
        //         return kbShift | kbLeftAlt | kbAltShift; // ???
        // }

        for(auto c : shiftKeys)
        {
            if (c==knownKey)
                return kbShift;
        }

        for(auto c : ctrlKeys)
        {
            if (c==knownKey)
                return kbLeftCtrl;
        }

        for(auto c : altKeys)
        {
            if (c==knownKey)
                return kbLeftAlt;
        }

        return 0;
    }

   // ushort          scanCode;        // std::uint8_t
   // ushort          controlKeyState; // kbShift | kbLeftAlt | kbLeftCtrl

   void resetState()
   {
        st        = stStart;
        trieIndex = umba::tokenizer::trie_index_invalid;
        seqLen    = 0;
   }


    bool processInputByte(uchar ch)
    {
        switch(st)
        {
            case stStart   :
            {
                if (ch==esc_code)
                {
                    st        = stGotEsc;
                    trieIndex = trieFindFirst(ch);
                    seqLen    = 1;
                    break;
                }
                else if (ch<=0x7F)
                {
                    const auto &taCharInfo = getTerminalAsciiCharInfo()[ch];

                    ushort keyCode         = taCharInfo.remapKeyCode;
                    ushort controlKeyState = taCharInfo.controlKeyState;

                    if (keyCode==0) // No keyCode remap
                    {
                        keyCode = (ushort)(((ushort)taCharInfo.scanCode) << 8) | ((ushort)ch);
                    }

                    validKeyHandler(keyCode, controlKeyState);
                    resetState();
                    break;
                }
                else
                {
                    // Unicode?
                    // There is no Unicode support currently
                    resetState();
                    return false;
                }
            }

            case stGotEsc  :
            {
                if (trieIndex==umba::tokenizer::trie_index_invalid) // Something goes wrong
                {
                    resetState();
                    return processInputByte(ch);
                }

                TrieIndexType nextTrieIndex = trieFindNext(trieIndex, ch); // looking for maximal len sequence while valid
                if (nextTrieIndex!=umba::tokenizer::trie_index_invalid)
                {
                    const auto &trieNode = getAnsiTerminalSequencesTrie()[nextTrieIndex];
                    if (trieNode.childsIndex==umba::tokenizer::trie_index_invalid) // Is node a sequence final node?
                    {
                        if (trieNode.payload!=umba::tokenizer::payload_invalid)
                        {
                            validKeyHandler((ushort)trieNode.payload, getControlKeyStateForKnownKeyCode((ushort)trieNode.payload));
                            resetState();
                            return true;
                        }
                    }

                    trieIndex = nextTrieIndex;
                    ++seqLen;
                    break;
                }
                
                // sequence continuation not found

                const auto &trieNode = getAnsiTerminalSequencesTrie()[trieIndex];
                if (trieNode.payload!=umba::tokenizer::payload_invalid && seqLen>1)
                {
                    validKeyHandler((ushort)trieNode.payload, getControlKeyStateForKnownKeyCode((ushort)trieNode.payload));
                    resetState();
                    return processInputByte(ch);
                }

                if (seqLen==1) // Not including current char
                {
                    uchar prevCh = (uchar)trieNode.token;
                    // check for escaped normal code
                    if (prevCh==esc_code && ch>=0 && ch<=0x7F)
                    {
                        const auto &taCharInfo = getTerminalAsciiCharInfo()[ch];
    
                        ushort keyCode         = taCharInfo.remapKeyCode;
                        ushort controlKeyState = taCharInfo.controlKeyState;
    
                        if (keyCode==0) // No keyCode remap
                        {
                            keyCode = (ushort)(((ushort)taCharInfo.scanCode) << 8) | ((ushort)ch);

                            if (controlKeyState==kbShift)
                            {
                                controlKeyState = kbShift | kbAltShift | kbLeftAlt; // ???
                            }
                            else
                            {
                                controlKeyState = kbLeftAlt; // ???
                            }
                        }

                        validKeyHandler(keyCode, controlKeyState);
                        resetState();
                        return processInputByte(ch);
                    }
                }

                // look for valid sequence and invalid tail
                // restore input sequence by backtracing trie

                uchar backTracedSequence[16];
                std::size_t      backTracedCount     = 0;
                std::size_t      idxLastHasPayload  = (std::size_t)-1;
                TriePayloadType  foundPayload       = umba::tokenizer::payload_invalid;
                trieBackTrace( trieIndex
                             , [&]( TrieTokenType tch, const auto &trieNode )
                               {
                                   if (backTracedCount<16)
                                   {
                                       backTracedSequence[backTracedCount] = (uchar)tch;
                                       if (trieNode.payload!=umba::tokenizer::payload_invalid && idxLastHasPayload!=(std::size_t)-1)
                                       {
                                           idxLastHasPayload = backTracedCount;
                                           foundPayload      = trieNode.payload;
                                       }
                                       ++backTracedCount;
                                   }
                               }
                             );

                std::reverse(&backTracedSequence[0], &backTracedSequence[backTracedCount]);
                if (idxLastHasPayload!=(std::size_t)-1)
                {
                    idxLastHasPayload = backTracedCount-idxLastHasPayload-1;
                }

                if (foundPayload!=umba::tokenizer::payload_invalid)
                {
                    validKeyHandler((ushort)foundPayload, getControlKeyStateForKnownKeyCode((ushort)foundPayload));
                }

                resetState();

                std::size_t idxFirstToReprocess = 0;
                if (idxLastHasPayload!=(std::size_t)-1)
                    idxFirstToReprocess = idxLastHasPayload+1;

                if (idxFirstToReprocess<backTracedCount)
                    putData(&backTracedSequence[idxFirstToReprocess], backTracedCount-idxFirstToReprocess);

                break;
            }

            //case stdReadSeq:
        }

        return true;

    }

public:

    AnsiTerminalKeySequenceParser() = delete;

    AnsiTerminalKeySequenceParser(const AnsiTerminalKeySequenceParser&) = default;
    AnsiTerminalKeySequenceParser&operator=(const AnsiTerminalKeySequenceParser&) = default;
    AnsiTerminalKeySequenceParser(AnsiTerminalKeySequenceParser&&) = default;
    AnsiTerminalKeySequenceParser&operator=(AnsiTerminalKeySequenceParser&&) = default;

    AnsiTerminalKeySequenceParser(TValidKeyHandler validHandler, TInvalidSequenceHandler invalidHandler)
    : validKeyHandler       (validHandler)
    , invalidSequenceHandler(invalidHandler)
    {}

    void putData(const uchar* pData, size_t size)
    {
        for(size_t i=0; i!=size; ++i)
        {
            if (!processInputByte(pData[i]))
            {
                invalidSequenceHandler(&pData[i], 1);
                resetState();
            }
            else if (pData[i]==(uchar)'~')
            {
                putTimeout(); // ~ mark sequence end, put "timeout" event to finalize sequence
            }
        }
    }

    void putTimeout()
    {
        if (st!=stGotEsc)
            return;

        if (trieIndex==umba::tokenizer::trie_index_invalid) // Something goes wrong
        {
            resetState();
            return;
        }

        const auto &trieNode = getAnsiTerminalSequencesTrie()[trieIndex];
        if (trieNode.payload!=umba::tokenizer::payload_invalid)
        {
            validKeyHandler((ushort)trieNode.payload, getControlKeyStateForKnownKeyCode((ushort)trieNode.payload));
            resetState();
            return; // processInputByte(ch);
        }

        #if 0
        if (seqLen==2)
        {
            uchar prevCh = (uchar)trieNode.token;
            // check for escaped normal code
            if (prevCh!=esc_code && prevCh<=0x7F)
            {
                const auto &taCharInfo = getTerminalAsciiCharInfo()[prevCh];

                ushort keyCode         = taCharInfo.remapKeyCode;
                ushort controlKeyState = taCharInfo.controlKeyState;

                if (keyCode==0) // No keyCode remap
                {
                    keyCode = (ushort)(((ushort)taCharInfo.scanCode) << 8) | ((ushort)prevCh);

                    if (controlKeyState==kbShift)
                    {
                        controlKeyState = kbShift | kbAltShift | kbLeftAlt; // ???
                    }
                }

                validKeyHandler(keyCode, controlKeyState);
                resetState();
                return; // processInputByte(ch);
            }
        }
        #endif

        // look for valid sequence and invalid tail
        // restore input sequence by backtracing trie

        uchar backTracedSequence[16];
        std::size_t      backTracedCount     = 0;
        std::size_t      idxLastHasPayload  = (std::size_t)-1;
        TriePayloadType  foundPayload       = umba::tokenizer::payload_invalid;
        trieBackTrace( trieIndex
                     , [&]( TrieTokenType tch, const auto &trieNode )
                       {
                           if (backTracedCount<16)
                           {
                               backTracedSequence[backTracedCount] = (uchar)tch;
                               if (trieNode.payload!=umba::tokenizer::payload_invalid && idxLastHasPayload!=(std::size_t)-1)
                               {
                                   idxLastHasPayload = backTracedCount;
                                   foundPayload      = trieNode.payload;
                               }
                               ++backTracedCount;
                           }
                       }
                     );

        std::reverse(&backTracedSequence[0], &backTracedSequence[backTracedCount]);
        if (idxLastHasPayload!=(std::size_t)-1)
        {
            idxLastHasPayload = backTracedCount-idxLastHasPayload-1;
        }

        if (foundPayload!=umba::tokenizer::payload_invalid)
        {
            validKeyHandler((ushort)foundPayload, getControlKeyStateForKnownKeyCode((ushort)foundPayload));
        }

        resetState();

        std::size_t idxFirstToReprocess = 0;
        if (idxLastHasPayload!=(std::size_t)-1)
            idxFirstToReprocess = idxLastHasPayload+1;

        if (idxFirstToReprocess<backTracedCount)
            putData(&backTracedSequence[idxFirstToReprocess], backTracedCount-idxFirstToReprocess);
    }


}; // class AnsiTerminalKeySequenceParser


} // namespace ansiterm
} // namespace umba
} // namespace tvision

