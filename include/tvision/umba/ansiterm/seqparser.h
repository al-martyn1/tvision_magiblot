#pragma once

#include "termasciici.h"


namespace tvision
{


template<typename TValidKeyHandler, typename TInvalidSequenceHandler>
class AnsiTerminalKeySequenceParser
{
    enum State
    {
        stStart    = 0,
        stGotEsc   = 1,
        stdReadSeq = 2
    };

    State                              st = stStart;
    umba::tokenizer::trie_index_type   operatorIdx = umba::tokenizer::trie_index_invalid;
    TValidKeyHandler                   validKeyHandler;
    TInvalidSequenceHandler            invalidSequenceHandler;

    static
    const auto& getAnsiTerminalSequencesTrie()
    {
        #include "ansitermseqtrie.h"

        return ansiTerminalSequencesTrie;
    }

// operatorIdx = umba::tokenizer::tokenTrieFindNext(operatorsTrie, trie_index_invalid, (token_type)ch);
// trie_index_type tokenTrieFindFirst(const ContainerType &tokenTrie, token_type tk)
// trie_index_type tokenTrieTraverse(const ContainerType &tokenTrie, TokenSequenceIteratorType b, TokenSequenceIteratorType e)
// void tokenTrieBackTrace(const ContainerType &tokenTrie, trie_index_type curIndex, BackTraceHandlerType handler)

   // ushort          scanCode;        // std::uint8_t
   // ushort          controlKeyState; // kbShift | kbLeftAlt | kbLeftCtrl


    void processInputByte()
    {
        switch(st)
        {
            case stStart   :
            {
            }

            case stGotEsc  :
            case stdReadSeq:
        }
        //State

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

    }

    void putTimeout()
    {

    }


};


} // namespace tvision

