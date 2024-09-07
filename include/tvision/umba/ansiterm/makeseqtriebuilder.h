#pragma once

inline
umba::tokenizer::TrieBuilder makeSeqTrieBuilder()
{
    using umba::tokenizer::payload_type;

    umba::tokenizer::TrieBuilder  trieBuilder;

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

    return trieBuilder;

}

