; =====================================================
; MISSION 04 - THE BROKEN PROTOCOL
; =====================================================

Mission04 PROC

    CALL Clrscr

    MOV CURRENT_MISSION, 4
    MOV ATTEMPTS_REMAINING, 3
    MOV MISSION_STATUS, 0

    CALL DisplayHeading

    MOV EDX, OFFSET m4Intro
    CALL DisplayMsg

    MOV EDX, OFFSET m4Story
    CALL DisplayMsg

    CALL Crlf

    ; -------------------------------------------------
    ; STAGE 01 - SYSTEM DEPENDENCY AUDIT
    ; -------------------------------------------------
    MOV CURRENT_STAGE, 1

    MOV EDX, OFFSET m4Stage1Title
    CALL DisplayMsg

    MOV EDX, OFFSET m4Log
    CALL DisplayMsg

    MOV EDX, OFFSET m4Power
    CALL DisplayMsg

    MOV EDX, OFFSET m4Kernel
    CALL DisplayMsg

    MOV EDX, OFFSET m4Drivers
    CALL DisplayMsg

    MOV EDX, OFFSET m4Database
    CALL DisplayMsg

    MOV EDX, OFFSET m4Network
    CALL DisplayMsg

    CALL Crlf

    MOV Q_QUESTION, OFFSET m4Q1
    MOV Q_OPTION_A, OFFSET m4Q1A
    MOV Q_OPTION_B, OFFSET m4Q1B
    MOV Q_OPTION_C, OFFSET m4Q1C
    MOV EXPECTED_ANSWER, 2

    CALL AskQuestion
    CMP EAX, 0
    JE M4Failed

    MOV EDX, OFFSET m4Stage1Success
    CALL DisplayMsg
    CALL Crlf

    ; -------------------------------------------------
    ; STAGE 02 - BOOT SEQUENCE RECOVERY
    ; -------------------------------------------------
    MOV CURRENT_STAGE, 2

    MOV EDX, OFFSET m4Stage2Title
    CALL DisplayMsg

    MOV EDX, OFFSET m4Stage2Info1
    CALL DisplayMsg

    MOV EDX, OFFSET m4Stage2Info2
    CALL DisplayMsg

    MOV EDX, OFFSET m4Stage2Info3
    CALL DisplayMsg

    CALL Crlf

    MOV Q_QUESTION, OFFSET m4Q2
    MOV Q_OPTION_A, OFFSET m4Q2A
    MOV Q_OPTION_B, OFFSET m4Q2B
    MOV Q_OPTION_C, OFFSET m4Q2C
    MOV EXPECTED_ANSWER, 2

    CALL AskQuestion
    CMP EAX, 0
    JE M4Failed

    MOV EDX, OFFSET m4Stage2Success
    CALL DisplayMsg
    CALL Crlf

    ; -------------------------------------------------
    ; STAGE 03 - NETWORK RESTORATION
    ; -------------------------------------------------
    MOV CURRENT_STAGE, 3

    MOV EDX, OFFSET m4Stage3Title
    CALL DisplayMsg

    MOV EDX, OFFSET m4Stage3Info1
    CALL DisplayMsg

    MOV EDX, OFFSET m4Stage3Info2
    CALL DisplayMsg

    MOV EDX, OFFSET m4Stage3Info3
    CALL DisplayMsg

    CALL Crlf

    MOV Q_QUESTION, OFFSET m4Q3
    MOV Q_OPTION_A, OFFSET m4Q3A
    MOV Q_OPTION_B, OFFSET m4Q3B
    MOV Q_OPTION_C, OFFSET m4Q3C
    MOV EXPECTED_ANSWER, 1

    CALL AskQuestion
    CMP EAX, 0
    JE M4Failed

    MOV EDX, OFFSET m4Stage3Success
    CALL DisplayMsg
    CALL Crlf

    ; -------------------------------------------------
    ; MISSION 04 COMPLETE
    ; -------------------------------------------------
    MOV MISSION_STATUS, 1

    MOV EDX, OFFSET m4Success
    CALL DisplayMsg

    RET

M4Failed:

    MOV MISSION_STATUS, 0

    MOV EDX, OFFSET m4Fail
    CALL DisplayMsg

    RET

Mission04 ENDP