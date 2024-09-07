#pragma once

inline
umba::tokenizer::TrieBuilder makeSeqTrieBuilder()
{
    using umba::tokenizer::payload_type;

    umba::tokenizer::TrieBuilder  trieBuilder;

    // ESC - 0x1B "\x1B"

    trieBuilder.addTokenSequence("\x1B"    , (payload_type)kbEsc   );
    trieBuilder.addTokenSequence("\x1B\x1B", (payload_type)kbAltEsc);

    // *** ESC [ N ~

    trieBuilder.addTokenSequence("\x1B[11~"    , (payload_type)kbF1 );
    trieBuilder.addTokenSequence("\x1B[12~"    , (payload_type)kbF2 );
    trieBuilder.addTokenSequence("\x1B[13~"    , (payload_type)kbF3 );
    trieBuilder.addTokenSequence("\x1B[14~"    , (payload_type)kbF4 );
    trieBuilder.addTokenSequence("\x1B[15~"    , (payload_type)kbF5 );
    trieBuilder.addTokenSequence("\x1B[17~"    , (payload_type)kbF6 );
    trieBuilder.addTokenSequence("\x1B[18~"    , (payload_type)kbF7 );
    trieBuilder.addTokenSequence("\x1B[19~"    , (payload_type)kbF8 );
    trieBuilder.addTokenSequence("\x1B[20~"    , (payload_type)kbF9 );
    trieBuilder.addTokenSequence("\x1B[21~"    , (payload_type)kbF10);
    trieBuilder.addTokenSequence("\x1B[23~"    , (payload_type)kbF11);
    trieBuilder.addTokenSequence("\x1B[24~"    , (payload_type)kbF12);

    trieBuilder.addTokenSequence("\x1B[23~"    , (payload_type)kbShiftF1 );
    trieBuilder.addTokenSequence("\x1B[24~"    , (payload_type)kbShiftF2 );
    trieBuilder.addTokenSequence("\x1B[25~"    , (payload_type)kbShiftF3 );
    trieBuilder.addTokenSequence("\x1B[26~"    , (payload_type)kbShiftF4 );
    trieBuilder.addTokenSequence("\x1B[28~"    , (payload_type)kbShiftF5 );
    trieBuilder.addTokenSequence("\x1B[29~"    , (payload_type)kbShiftF6 );
    trieBuilder.addTokenSequence("\x1B[31~"    , (payload_type)kbShiftF7 );
    trieBuilder.addTokenSequence("\x1B[32~"    , (payload_type)kbShiftF8 );
    trieBuilder.addTokenSequence("\x1B[33~"    , (payload_type)kbShiftF9 );
    trieBuilder.addTokenSequence("\x1B[34~"    , (payload_type)kbShiftF10);
    trieBuilder.addTokenSequence("\x1B[23~"    , (payload_type)kbShiftF11);
    trieBuilder.addTokenSequence("\x1B[24~"    , (payload_type)kbShiftF12);

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

    // Ctrl - no change for Fn

    // Up/Down/Right/Left
    trieBuilder.addTokenSequence("\x1B[A"      , (payload_type)kbUp   );
    trieBuilder.addTokenSequence("\x1B[B"      , (payload_type)kbDown );
    trieBuilder.addTokenSequence("\x1B[C"      , (payload_type)kbRight);
    trieBuilder.addTokenSequence("\x1B[D"      , (payload_type)kbLeft );

    // Shift - no change

    // Alt
    trieBuilder.addTokenSequence("\x1B\x1B[A"  , (payload_type)kbAltUp   );
    trieBuilder.addTokenSequence("\x1B\x1B[B"  , (payload_type)kbAltDown );
    trieBuilder.addTokenSequence("\x1B\x1B[C"  , (payload_type)kbAltRight);
    trieBuilder.addTokenSequence("\x1B\x1B[D"  , (payload_type)kbAltLeft );

    // Ctrl
    trieBuilder.addTokenSequence("\x1BOA"      , (payload_type)kbCtrlUp   );
    trieBuilder.addTokenSequence("\x1BOB"      , (payload_type)kbCtrlDown );
    trieBuilder.addTokenSequence("\x1BOC"      , (payload_type)kbCtrlRight);
    trieBuilder.addTokenSequence("\x1BOD"      , (payload_type)kbCtrlLeft );

    // Home/Ins/Del/End
    trieBuilder.addTokenSequence("\x1B[1~"     , (payload_type)kbHome);
    trieBuilder.addTokenSequence("\x1B[2~"     , (payload_type)kbIns );
    trieBuilder.addTokenSequence("\x1B[3~"     , (payload_type)kbDel );
    trieBuilder.addTokenSequence("\x1B[4~"     , (payload_type)kbEnd );

    // Alt
    trieBuilder.addTokenSequence("\x1B\x1B[1~" , (payload_type)kbAltHome);
    trieBuilder.addTokenSequence("\x1B\x1B[2~" , (payload_type)kbAltIns );
    trieBuilder.addTokenSequence("\x1B\x1B[3~" , (payload_type)kbAltDel );
    trieBuilder.addTokenSequence("\x1B\x1B[4~" , (payload_type)kbAltEnd );

    // Ctrl  - nothing
    // Shift - no change


    // *** VT-100

    // F1-12
    trieBuilder.addTokenSequence("\x1BOP" , (payload_type)kbF1  );
    trieBuilder.addTokenSequence("\x1BOQ" , (payload_type)kbF2  );
    trieBuilder.addTokenSequence("\x1BOR" , (payload_type)kbF3  );
    trieBuilder.addTokenSequence("\x1BOS" , (payload_type)kbF4  );
    trieBuilder.addTokenSequence("\x1BOT" , (payload_type)kbF5  );
    trieBuilder.addTokenSequence("\x1BOU" , (payload_type)kbF6  );
    trieBuilder.addTokenSequence("\x1BOV" , (payload_type)kbF7  );
    trieBuilder.addTokenSequence("\x1BOW" , (payload_type)kbF8  );
    trieBuilder.addTokenSequence("\x1BOX" , (payload_type)kbF9  );
    trieBuilder.addTokenSequence("\x1BOY" , (payload_type)kbF10 );
    trieBuilder.addTokenSequence("\x1BOZ" , (payload_type)kbF11 );
    trieBuilder.addTokenSequence("\x1BO[" , (payload_type)kbF12 );

    // Alt+Fn - extra ESC
    trieBuilder.addTokenSequence("\x1B\x1BOP" , (payload_type)kbAltF1  );
    trieBuilder.addTokenSequence("\x1B\x1BOQ" , (payload_type)kbAltF2  );
    trieBuilder.addTokenSequence("\x1B\x1BOR" , (payload_type)kbAltF3  );
    trieBuilder.addTokenSequence("\x1B\x1BOS" , (payload_type)kbAltF4  );
    trieBuilder.addTokenSequence("\x1B\x1BOT" , (payload_type)kbAltF5  );
    trieBuilder.addTokenSequence("\x1B\x1BOU" , (payload_type)kbAltF6  );
    trieBuilder.addTokenSequence("\x1B\x1BOV" , (payload_type)kbAltF7  );
    trieBuilder.addTokenSequence("\x1B\x1BOW" , (payload_type)kbAltF8  );
    trieBuilder.addTokenSequence("\x1B\x1BOX" , (payload_type)kbAltF9  );
    trieBuilder.addTokenSequence("\x1B\x1BOY" , (payload_type)kbAltF10 );
    trieBuilder.addTokenSequence("\x1B\x1BOZ" , (payload_type)kbAltF11 );
    trieBuilder.addTokenSequence("\x1B\x1BO[" , (payload_type)kbAltF12 );

    // Ctrl - same as nothing

    // Shift
    // F1/F2 - looks like F11/F12
    // F11/F12 - looks like F11/F12 with no Shift
    // F3-F10 - same as ~ sequence above

    // Up/Down/Right/Left - as above

    // Home/Ins/Del/End - as above

    // trieBuilder.addTokenSequence("\x1B" , (payload_type) );


    return trieBuilder;

}

