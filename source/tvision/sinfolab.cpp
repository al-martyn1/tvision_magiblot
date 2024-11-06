/*------------------------------------------------------------*/
/* filename -       sinfolab.cpp                              */
/*                                                            */
/* Registeration object for the class TInfoLabel              */
/*------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(NO_STREAMABLE)
#define Uses_TInfoLabel
#define Uses_TStreamableClass
#include <tvision/tv.h>
__link( RStaticText )

TStreamableClass RInfoLabel( TInfoLabel::name,
                             TInfoLabel::build,
                             __DELTA(TInfoLabel)
                           );
#endif

