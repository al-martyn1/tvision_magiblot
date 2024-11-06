/*------------------------------------------------------------*/
/* filename -           tinfolab.cpp                          */
/*                                                            */
/* function(s)                                                */
/*                      TInfoLabel member functions           */
/*------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#define Uses_TInfoLabel
#define Uses_TEvent
#define Uses_TDrawBuffer
#define Uses_TGroup
#define Uses_TView
#define Uses_opstream
#define Uses_ipstream
#include <tvision/tv.h>

#if !defined( __CTYPE_H )
#include <ctype.h>
#endif  // __CTYPE_H


// 1 02 ("\x70") black on lgray - normal
// 2 88 ("\x30") black on light blue   - info
// 2 8C ("\x3F") white on light blue - info
// 3 89 ("\x34") red on light blue - warning
// 3 8D ("\x3C") lred on light blue - warning
// 3 8E ("\x35") dmagenta on light blue - warning
// 4 8A ("\x4F") white on red - error
// 5 8B ("\x38") gray on light blue - disable


// #define cpLabel "\x02\x88\x89\x8A\x8B"
// #define cpLabel "\x02\x8C\x89\x8A\x8B"
// #define cpLabel "\x02\x8C\x8D\x8A\x8B"
#define cpLabel "\x02\x8C\x8E\x8A\x8B"

TInfoLabel::TInfoLabel( const TRect& bounds, TStringView aText) noexcept :
    TStaticText( bounds, aText )
{
    options |= ofPreProcess | ofPostProcess;
    eventMask |= evBroadcast;
}

TView* TInfoLabel::getTopOwner()
{
    TView* resOwner = owner;
    while(resOwner)
    {
        if (resOwner->owner==0)
            return resOwner;
        resOwner = resOwner->owner;
    }

    return resOwner;
}

void TInfoLabel::shutDown()
{
    TStaticText::shutDown();
}

void TInfoLabel::setText( TStringView aText )
{
    delete[] (char *)text;
    text = newStr( aText );
    draw();
}

unsigned TInfoLabel::getInfoKind()
{
    return infoKind;
}

void TInfoLabel::setInfoKind(unsigned aInfoKind)
{
    infoKind = aInfoKind;
    draw();
}

uchar TInfoLabel::getForceColor()
{
    return forceColor;
}

void TInfoLabel::setForceColor(uchar aColor)
{
    forceColor = aColor;
    draw();
}

TColorAttr TInfoLabel::mapColor( uchar index ) noexcept
{
    TPalette& p = getPalette();
    TColorAttr color;
    if( p[0] != 0 )
    {
        if( 0 < index && index <= p[0] )
            color = p[index];
        else
            return errorAttr;
    }
    else
        color = index;


    if( color == 0 )
        return errorAttr;

    auto topOwner = getTopOwner();

    if( topOwner )
        return topOwner->mapColor(color);
    
    return color;
}

void TInfoLabel::draw()
{
    TAttrPair color;
    TDrawBuffer b;

    if (forceColor!=0)
    {
        auto colorMapper = getTopOwner();
        if (colorMapper)
        {
            color = colorMapper->mapColor(forceColor);
        }
        else
        {
            ushort colorIndex = 0;
            if (state&sfDisabled) // sfDisabled sfVisible
                colorIndex = 4;
            else
                colorIndex = (ushort)(infoKind&0x03)+1;
            color = getColor(colorIndex);
        }
    }
    else
    {
        ushort colorIndex = 0;
        if (state&sfDisabled) // sfDisabled sfVisible
            colorIndex = 4;
        else
            colorIndex = (ushort)(infoKind&0x03)+1;
        color = getColor(colorIndex);
    }

    b.moveChar( 0, ' ', color, size.x );
    if( text != 0 )
        b.moveCStr( 0 /* 1 */ , text, color );
    // if( showMarkers )
    //     b.putChar( 0, specialChars[scOff] );
    writeLine( 0, 0, size.x, 1, b );
}

TPalette& TInfoLabel::getPalette() const
{
    static TPalette palette( cpLabel, sizeof( cpLabel )-1 );
    return palette;
}

#if !defined(NO_STREAMABLE)

void TInfoLabel::write( opstream& os )
{
    TStaticText::write( os );
}

void *TInfoLabel::read( ipstream& is )
{
    TStaticText::read( is );
    return this;
}

TStreamable *TInfoLabel::build()
{
    return new TInfoLabel( streamableInit );
}

TInfoLabel::TInfoLabel( StreamableInit ) noexcept : TStaticText( streamableInit )
{
}


#endif
