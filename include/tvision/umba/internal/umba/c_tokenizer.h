#pragma once

// #if !defined(__cplusplus)
//     #include <stddef.h>
//     #include <stdint.h>
// #else
//     #include <cstddef>
//     #include <cstdint>
// #endif

#if defined(UMBA_TOKENIZER_TYPES_COMPACT)

    #if !defined(UMBA_CHAR_CLASS_UNDERLYING_COMPACT)
        #define UMBA_CHAR_CLASS_UNDERLYING_COMPACT
    #endif

#endif

#if defined(UMBA_CHAR_CLASS_UNDERLYING_COMPACT)
    #if !defined(UMBA_TOKENIZER_TYPES_COMPACT)
        #define UMBA_TOKENIZER_TYPES_COMPACT
    #endif
#endif


#if defined(UMBA_TOKENIZER_TYPES_COMPACT)

    #if !defined(UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE)
        #define UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE
    #endif

    #if !defined(UMBA_TOKENIZER_TRIE_INDEX_TYPE_COMPACT)
        #define  UMBA_TOKENIZER_TRIE_INDEX_TYPE_COMPACT
    #endif

    #if !defined(UMBA_TOKENIZER_TOKEN_TYPE_COMPACT)
        #define  UMBA_TOKENIZER_TOKEN_TYPE_COMPACT
    #endif

    #if !defined(UMBA_TOKENIZER_PAYLOAD_TYPE_COMPACT)
        #define  UMBA_TOKENIZER_PAYLOAD_TYPE_COMPACT
    #endif

#endif


#if defined(UMBA_TOKENIZER_TRIE_NODE_EXTRA_FIELDS_DISABLE)

    #if !defined(UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_DISABLE)
        #define  UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_DISABLE
    #endif

    #if !defined(UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE)
        #define  UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE
    #endif

#endif


// must be anually included before
// #include "c_char_class.h"


// std::size_t https://stackoverflow.com/questions/36594569/which-header-should-i-include-for-size-t



#if !defined(UMBA_TOKENIZER_TRIE_INDEX_TYPE)
    #if !defined(__cplusplus)

        #if defined(UMBA_TOKENIZER_TRIE_INDEX_TYPE_COMPACT)
            #define UMBA_TOKENIZER_TRIE_INDEX_TYPE  uint_least16_t
        #else
            #define UMBA_TOKENIZER_TRIE_INDEX_TYPE  size_t
        #endif

    #else

        #if defined(UMBA_TOKENIZER_TRIE_INDEX_TYPE_COMPACT)
            #define UMBA_TOKENIZER_TRIE_INDEX_TYPE  ::std::uint_least16_t
        #else
            #define UMBA_TOKENIZER_TRIE_INDEX_TYPE  ::std::size_t
        #endif

    #endif
#endif

#if !defined(UMBA_TOKENIZER_TRIE_INDEX_INVALID)
    #define UMBA_TOKENIZER_TRIE_INDEX_INVALID ((UMBA_TOKENIZER_TRIE_INDEX_TYPE)-1)
#endif

// #if !defined(UMBA_TOKENIZER_TRIE_INDEX_INITIAL)
//     #define UMBA_TOKENIZER_TRIE_INDEX_INITIAL ((UMBA_TOKENIZER_TRIE_INDEX_TYPE)0)
// #endif



#if !defined(UMBA_TOKENIZER_TOKEN_TYPE)
    #if !defined(__cplusplus)

        #if defined(UMBA_TOKENIZER_TOKEN_TYPE_SUPER_COMPACT)
            #define UMBA_TOKENIZER_TOKEN_TYPE  uint_least8_t
        #elif defined(UMBA_TOKENIZER_TOKEN_TYPE_COMPACT)
            #define UMBA_TOKENIZER_TOKEN_TYPE  uint_least16_t
        #else
            #define UMBA_TOKENIZER_TOKEN_TYPE  size_t
        #endif

    #else

        #if defined(UMBA_TOKENIZER_TOKEN_TYPE_SUPER_COMPACT)
            #define UMBA_TOKENIZER_TOKEN_TYPE  ::std::uint_least8_t
        #elif defined(UMBA_TOKENIZER_TOKEN_TYPE_COMPACT)
            #define UMBA_TOKENIZER_TOKEN_TYPE  ::std::uint_least16_t
        #else
            #define UMBA_TOKENIZER_TOKEN_TYPE  ::std::size_t
        #endif

    #endif
#endif

#if !defined(UMBA_TOKENIZER_TOKEN_INVALID)
    #define UMBA_TOKENIZER_TOKEN_INVALID ((UMBA_TOKENIZER_TOKEN_TYPE)-1)
#endif



#if !defined(UMBA_TOKENIZER_PAYLOAD_TYPE)
    #if !defined(__cplusplus)

        #if defined(UMBA_TOKENIZER_PAYLOAD_TYPE_COMPACT)
            #define UMBA_TOKENIZER_PAYLOAD_TYPE  uint_least16_t
        #else
            #define UMBA_TOKENIZER_PAYLOAD_TYPE  size_t
        #endif

    #else

        #if defined(UMBA_TOKENIZER_PAYLOAD_TYPE_COMPACT)
            #define UMBA_TOKENIZER_PAYLOAD_TYPE  ::std::uint_least16_t
        #else
            #define UMBA_TOKENIZER_PAYLOAD_TYPE  ::std::size_t
        #endif

    #endif
#endif

#if !defined(UMBA_TOKENIZER_PAYLOAD_INVALID)
    #define UMBA_TOKENIZER_PAYLOAD_INVALID ((UMBA_TOKENIZER_PAYLOAD_TYPE)-1)
#endif


#if !defined(UMBA_TOKENIZER_PAYLOAD_FLAGS_TYPE)
    #if !defined(__cplusplus) || defined(__GNUC__) /* there is a problem in GCC with std::uintptr_t */
        #define UMBA_TOKENIZER_PAYLOAD_FLAGS_TYPE  uintptr_t
    #else
        #define UMBA_TOKENIZER_PAYLOAD_FLAGS_TYPE  ::std::uintptr_t
    #endif
#endif



#if defined(UMBA_TOKENIZER_TYPES_COMPACT)
    #include "pushpack1.h"
#endif
typedef struct tag_umba_tokenizer_trie_node
{
    UMBA_TOKENIZER_TRIE_INDEX_TYPE       parentNodeIndex      ;
    UMBA_TOKENIZER_TRIE_INDEX_TYPE       lookupChunkStartIndex; /* Одно и то же значение для всех элементов lookupChunk'а */
    UMBA_TOKENIZER_TRIE_INDEX_TYPE       lookupChunkSize      ; /* Одно и то же значение для всех элементов lookupChunk'а */
    UMBA_TOKENIZER_TRIE_INDEX_TYPE       childsIndex          ;
    UMBA_TOKENIZER_PAYLOAD_TYPE          payload              ; // Полезная нагрузка
#if !defined(UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_DISABLE)
    UMBA_TOKENIZER_PAYLOAD_FLAGS_TYPE    payloadExtra         ; // Пользовательские флаги или данные, влезает указатель
#endif
    UMBA_TOKENIZER_TOKEN_TYPE            token                ; // Токен или символ

#if !defined(UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE)
    UMBA_TOKENIZER_TRIE_INDEX_TYPE       level                ; // Нужно, чтобы делать красивый граф таблицы trie
#endif

} umba_tokenizer_trie_node;
#if defined(UMBA_TOKENIZER_TYPES_COMPACT)
    #include "packpop.h"
#endif


// Standard mode   : Trie size : 32 items, 1024 bytes
// Compact mode    : Trie size : 32 items, 448 bytes
// Compact no flags: Trie size : 32 items, 384 bytes


#if defined(UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_DISABLE)
    #define UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_INITIALIZER_LIST_INIT(p)
#else
    #define UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_INITIALIZER_LIST_INIT(p)  , (p)
#endif

#if defined(UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE)
    #define UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_INITIALIZER_LIST_INIT(l)
#else
    #define UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_INITIALIZER_LIST_INIT(l)  , (l)
#endif

static inline
void umba_tokenizer_trie_node_init_make_uninitialized(umba_tokenizer_trie_node *pNode)
{
    *pNode = umba_tokenizer_trie_node{ UMBA_TOKENIZER_TRIE_INDEX_INVALID
                                     , UMBA_TOKENIZER_TRIE_INDEX_INVALID
                                     , 0
                                     , UMBA_TOKENIZER_TRIE_INDEX_INVALID
                                     , UMBA_TOKENIZER_PAYLOAD_INVALID
                                     /*,*/ UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_INITIALIZER_LIST_INIT(0)
                                     , UMBA_TOKENIZER_TOKEN_INVALID
                                     /*,*/ UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_INITIALIZER_LIST_INIT(0)
                                     };

#if 0
    pNode->parentNodeIndex       = UMBA_TOKENIZER_TRIE_INDEX_INVALID;
    pNode->lookupChunkStartIndex = UMBA_TOKENIZER_TRIE_INDEX_INVALID;
    pNode->lookupChunkSize       = 0;
    pNode->childsIndex           = UMBA_TOKENIZER_TRIE_INDEX_INVALID;
    pNode->payload               = UMBA_TOKENIZER_PAYLOAD_INVALID;
#if !defined(UMBA_TOKENIZER_TRIE_NODE_PAYLOAD_EXTRA_FIELD_DISABLE)
    pNode->payloadExtra          = 0;
#endif
    pNode->token                 = UMBA_TOKENIZER_TOKEN_INVALID;
#if !defined(UMBA_TOKENIZER_TRIE_NODE_LEVEL_FIELD_DISABLE)
    pNode->level                 = 0;
#endif

#endif
}


#if !defined(UMBA_TOKEN_TRIE_FIND_NEXT_BINARY_SEARCH_CHUNK_SIZE_LIMIT)
    #define UMBA_TOKEN_TRIE_FIND_NEXT_BINARY_SEARCH_CHUNK_SIZE_LIMIT  4u
#endif


#if defined(__cplusplus)

// umba::tokenizer::
namespace umba {
namespace tokenizer {


//----------------------------------------------------------------------------
using  trie_index_type                                     = UMBA_TOKENIZER_TRIE_INDEX_TYPE;
inline constexpr const trie_index_type trie_index_invalid  = UMBA_TOKENIZER_TRIE_INDEX_INVALID;
//inline constexpr const trie_index_type trie_index_initial  = UMBA_TOKENIZER_TRIE_INDEX_INITIAL;

//----------------------------------------------------------------------------
using  token_type                                          = UMBA_TOKENIZER_TOKEN_TYPE;
inline constexpr const token_type token_id_invalid         = UMBA_TOKENIZER_TOKEN_INVALID;

//----------------------------------------------------------------------------
using  payload_type                                        = UMBA_TOKENIZER_PAYLOAD_TYPE;
inline constexpr const payload_type payload_invalid        = UMBA_TOKENIZER_PAYLOAD_INVALID;

//----------------------------------------------------------------------------
using payload_flags_type                                   = UMBA_TOKENIZER_PAYLOAD_FLAGS_TYPE;

//----------------------------------------------------------------------------
using TrieNode = umba_tokenizer_trie_node;

//----------------------------------------------------------------------------


template<typename ContainerType>
trie_index_type tokenTrieFindNext(const ContainerType &tokenTrie, trie_index_type curIndex, token_type tk)
{
    // Если на входе инвалид, то начинать надо со старта

    trie_index_type lookupChunkStartIdx  = 0;
    trie_index_type lookupChunkSize      = 0;

    if (curIndex==trie_index_invalid)
    {
        lookupChunkStartIdx  = tokenTrie[0].lookupChunkStartIndex;
        lookupChunkSize      = tokenTrie[0].lookupChunkSize;
    }
    else
    {
        if (curIndex>=tokenTrie.size())
        {
            return trie_index_invalid;
        }

        if (tokenTrie[curIndex].childsIndex==trie_index_invalid)
        {
            // Детей нет, дальше искать нечего
            return trie_index_invalid;
        }

        lookupChunkStartIdx = tokenTrie[curIndex].childsIndex;
        #ifdef UMBA_ASSERT
            UMBA_ASSERT(lookupChunkStartIdx<tokenTrie.size());
        #endif
        lookupChunkSize = tokenTrie[lookupChunkStartIdx].lookupChunkSize;
    }

    #ifdef UMBA_ASSERT
        UMBA_ASSERT((lookupChunkStartIdx+lookupChunkSize)<=tokenTrie.size());
    #endif

    // Двоичный поиск
    // https://codelessons.dev/ru/binarnyj-poisk-po-massivu-c/
    // https://brestprog.by/topics/binsearch/
    // Интересная статья, может списюганить там поиск? https://habr.com/ru/companies/ruvds/articles/756422/
    // На самом деле надо будет просто проверить сначала обычный lower_bound
    // И ещё вопрос для исследования - оставлять ли для мелких чанков линейный поиск или нет?

    // С двоичным поиском что-то не так идёт, добавил возможность его запретить
    #if !defined(UMBA_TOKEN_TRIE_FIND_NEXT_BINARY_SEARCH_DISABLED)
    if (lookupChunkSize>=UMBA_TOKEN_TRIE_FIND_NEXT_BINARY_SEARCH_CHUNK_SIZE_LIMIT)
    {
        TrieNode cmpNode;
        cmpNode.token = tk;
        auto resIt = ::std::lower_bound( &tokenTrie[lookupChunkStartIdx]
                                     , &tokenTrie[lookupChunkStartIdx+lookupChunkSize]
                                     , cmpNode
                                     , [](const TrieNode &tn1, const TrieNode &tn2)
                                       {
                                           return tn1.token < tn2.token;
                                       }
                                     );
        if (resIt==&tokenTrie[lookupChunkStartIdx+lookupChunkSize] || resIt->token!=tk)
            return trie_index_invalid; // Не нашли, обломс

        return resIt-&tokenTrie[lookupChunkStartIdx];
    }
    #endif

    // Чанк небольшой, фигачим линейным поиском
    // Или, возможно, двоичный поиск запрещён настройками
    // Линейный поиск
    for(trie_index_type i=0; i!=lookupChunkSize; ++i)
    {
        const auto idx = lookupChunkStartIdx + i;

        if (tokenTrie[idx].token==tk)
            return idx;

        if (tokenTrie[idx].token>tk)
            return trie_index_invalid; // у нас символы отсортированы по возрастанию, и если код искомого символа больше того, что мы обнаружили в очередной entry, то дальше искать нет смысла
    }

    return trie_index_invalid; // Не нашли, обломс
}

//----------------------------------------------------------------------------
template<typename ContainerType>
trie_index_type tokenTrieFindFirst(const ContainerType &tokenTrie, token_type tk)
{
    return tokenTrieFindNext(tokenTrie, trie_index_invalid, tk);
}

//----------------------------------------------------------------------------
template<typename ContainerType, typename TokenSequenceIteratorType>
trie_index_type tokenTrieTraverse(const ContainerType &tokenTrie, TokenSequenceIteratorType b, TokenSequenceIteratorType e)
{
    if (b==e)
        return trie_index_invalid;

    trie_index_type idx = tokenTrieFindFirst(tokenTrie, *b);

    for(++b; idx!=trie_index_invalid && b!=e; ++b)
    {
        idx = tokenTrieFindNext(tokenTrie, idx, *b);
    }

    return idx;
}

//----------------------------------------------------------------------------
// // Надо прошагать по последовательности от seqB, seqE,
// template<typename ContainerType, typename TokenSequenceIteratorType>
// trie_index_type tokenTrieTraverse(const ContainerType &tokenTrie, TokenSequenceIteratorType seqB, TokenSequenceIteratorType seqE, TokenSequenceIteratorType globalE)
// {
//     if (b==e)
//         return trie_index_invalid;
//
//     trie_index_type idx = tokenTrieFindFirst(tokenTrie, *b);
//
//     for(++b; idx!=trie_index_invalid && b!=e; ++b)
//     {
//         idx = tokenTrieFindNext(tokenTrie, idx, *b);
//     }
//
//     return idx;
// }

//----------------------------------------------------------------------------
template<typename ContainerType, typename BackTraceHandlerType>
void tokenTrieBackTrace(const ContainerType &tokenTrie, trie_index_type curIndex, BackTraceHandlerType handler)
{
    while(curIndex!=trie_index_invalid)
    {
        #ifdef UMBA_ASSERT
            UMBA_ASSERT(curIndex<tokenTrie.size());
        #endif
        handler(tokenTrie[curIndex].token, tokenTrie[curIndex]);
        curIndex = tokenTrie[curIndex].parentNodeIndex;
    }
}


} // namespace tokenizer
} // namespace umba


#endif // __cplusplus




