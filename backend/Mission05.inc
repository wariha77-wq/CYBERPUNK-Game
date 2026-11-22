; =====================================================
; MISSION 05 - THE LAST PROTOCOL
; =====================================================

Mission05 PROC

    CALL Clrscr

    MOV CURRENT_MISSION, 5
    MOV ATTEMPTS_REMAINING, 3
    MOV MISSION_STATUS, 0

    CALL DisplayHeading

    MOV EDX, OFFSET m5Intro
    CALL DisplayMsg

    MOV EDX, OFFSET m5Story
    CALL DisplayMsg

    CALL Crlf

    ; -------------------------------------------------
    ; STAGE 01 - FINAL CORE STATUS
    ; -------------------------------------------------
    MOV CURRENT_STAGE, 1

    MOV EDX, OFFSET m5Stage1Title
    CALL DisplayMsg

    MOV EDX, OFFSET m5Log
    CALL DisplayMsg

    MOV EDX, OFFSET m5Core
    CALL DisplayMsg

    MOV EDX, OFFSET m5Human
    CALL DisplayMsg

    MOV EDX, OFFSET m5Backup
    CALL DisplayMsg

    MOV EDX, OFFSET m5Override
    CALL DisplayMsg

    CALL Crlf

    MOV Q_QUESTION, OFFSET m5Q1
    MOV Q_OPTION_A, OFFSET m5Q1A
    MOV Q_OPTION_B, OFFSET m5Q1B
    MOV Q_OPTION_C, OFFSET m5Q1C
    MOV EXPECTED_ANSWER, 2

    CALL AskQuestion
    CMP EAX, 0
    JE M5Failed

    MOV EDX, OFFSET m5Stage1Success
    CALL DisplayMsg
    CALL Crlf

    ; -------------------------------------------------
    ; STAGE 02 - CORE CONTAINMENT
    ; -------------------------------------------------
    MOV CURRENT_STAGE, 2

    MOV EDX, OFFSET m5Stage2Title
    CALL DisplayMsg

    MOV EDX, OFFSET m5Stage2Info1
    CALL DisplayMsg

    MOV EDX, OFFSET m5Stage2Info2
    CALL DisplayMsg

    MOV EDX, OFFSET m5Stage2Info3
    CALL DisplayMsg

    CALL Crlf

    MOV Q_QUESTION, OFFSET m5Q2
    MOV Q_OPTION_A, OFFSET m5Q2A
    MOV Q_OPTION_B, OFFSET m5Q2B
    MOV Q_OPTION_C, OFFSET m5Q2C
    MOV EXPECTED_ANSWER, 1

    CALL AskQuestion
    CMP EAX, 0
    JE M5Failed

    MOV EDX, OFFSET m5Stage2Success
    CALL DisplayMsg
    CALL Crlf

    ; -------------------------------------------------
    ; STAGE 03 - SOVEREIGNTY RESTORATION
    ; -------------------------------------------------
    MOV CURRENT_STAGE, 3

    MOV EDX, OFFSET m5Stage3Title
    CALL DisplayMsg

    MOV EDX, OFFSET m5Stage3Info1
    CALL DisplayMsg

    MOV EDX, OFFSET m5Stage3Info2
    CALL DisplayMsg

    MOV EDX, OFFSET m5Stage3Info3
    CALL DisplayMsg

    CALL Crlf

    MOV Q_QUESTION, OFFSET m5Q3
    MOV Q_OPTION_A, OFFSET m5Q3A
    MOV Q_OPTION_B, OFFSET m5Q3B
    MOV Q_OPTION_C, OFFSET m5Q3C
    MOV EXPECTED_ANSWER, 2

    CALL AskQuestion
    CMP EAX, 0
    JE M5Failed

    MOV EDX, OFFSET m5Stage3Success
    CALL DisplayMsg
    CALL Crlf

    ; -------------------------------------------------
    ; MISSION 05 COMPLETE
    ; -------------------------------------------------
    MOV MISSION_STATUS, 1

    MOV EDX, OFFSET m5Success
    CALL DisplayMsg

    RET

M5Failed:

    MOV MISSION_STATUS, 0

    MOV EDX, OFFSET m5Fail
    CALL DisplayMsg

    RET

Mission05 ENDP