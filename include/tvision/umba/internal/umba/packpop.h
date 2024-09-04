/*! \file
    \brief Восстановление значения по умолчанию для упаковки структур
*/
#if defined(_WIN32)
    #include <poppack.h>
#else
    #pragma pack(pop)
#endif

