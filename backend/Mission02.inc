
Mission02 PROC
    CALL Clrscr

    ; INITIALIZE MISSION
    MOV CURRENT_MISSION, 2
    MOV MISSION_STATUS, 0
    MOV ATTEMPTS_REMAINING, 3

    CALL DisplayHeading

    MOV EDX, OFFSET m2Intro
    CALL DisplayMsg

    MOV EDX, OFFSET m2Story
    CALL DisplayMsg

    CALL Crlf

; ==========================================
; STAGE 01 - SIGNAL INTEGRITY
; ==========================================

M2Stage1:
    MOV CURRENT_STAGE, 1

    MOV EDX, OFFSET m2Stage1Title
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Info1
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Info2
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Info3
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Info4
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Info5
    CALL DisplayMsg

    CALL Crlf

    MOV EDX, OFFSET m2Stage1Question
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Options
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Option2
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Option3
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage1Option4
    CALL DisplayMsg

M2Stage1InputLoop:
    MOV EDX, OFFSET m2Stage1Prompt
    CALL WriteString
    CALL GetAnswer

    MOV EAX, playerAnswer
    CMP EAX, 3
    JE M2Stage1Correct
    JMP M2WrongAnswer

M2Stage1Correct:
    MOV EDX, OFFSET m2Stage1Success
    CALL DisplayMsg
    CALL Crlf

; ==========================================
; STAGE 02 - DATA RECONSTRUCTION
; ==========================================

M2Stage2:
    MOV CURRENT_STAGE, 2

    MOV EDX, OFFSET m2Stage2Title
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage2Info1
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage2Info2
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage2Question
    CALL DisplayMsg

    MOV EDX, OFFSET m2Stage2Option1
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage2Option2
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage2Option3
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage2Option4
    CALL DisplayMsg

M2Stage2InputLoop:
    MOV EDX, OFFSET m2Stage2Prompt
    CALL WriteString
    CALL GetAnswer

    MOV EAX, playerAnswer
    CMP EAX, 3
    JE M2Stage2Correct
    JMP M2WrongAnswer

M2Stage2Correct:
    MOV EDX, OFFSET m2Stage2Success
    CALL DisplayMsg
    CALL Crlf

; ==========================================
; STAGE 03 - SOURCE AUTHENTICATION
; ==========================================

M2Stage3:
    MOV CURRENT_STAGE, 3

    MOV EDX, OFFSET m2Stage3Title
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Info1
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Original
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Record1
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Record2
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Record3
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3SourceA
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3SourceB
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3SourceC
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Question
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Option1
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Option2
    CALL DisplayMsg
    MOV EDX, OFFSET m2Stage3Option3
    CALL DisplayMsg

M2Stage3InputLoop:
    MOV EDX, OFFSET m2Stage3Prompt
    CALL WriteString
    CALL GetAnswer

    MOV EAX, playerAnswer
    CMP EAX, 1
    JE M2Stage3Correct
    JMP M2WrongAnswer

M2Stage3Correct:
    MOV EDX, OFFSET m2Stage3Success
    CALL DisplayMsg

    MOV MISSION_STATUS, 1

    MOV EDX, OFFSET m2CorrectMsg
    CALL DisplayMsg
    MOV EDX, OFFSET m2MissionSuccess
    CALL DisplayMsg

    RET

; ==========================================
; WRONG ANSWER HANDLER
; ==========================================

M2WrongAnswer:
    MOV EDX, OFFSET m2WrongMsg
    CALL DisplayMsg

    DEC ATTEMPTS_REMAINING

    MOV EDX, OFFSET attemptMsg
    CALL WriteString
    MOV EAX, ATTEMPTS_REMAINING
    CALL WriteDec
    CALL Crlf

    CMP ATTEMPTS_REMAINING, 0
    JE M2Failed

    CALL Crlf

    CMP CURRENT_STAGE, 1
    JE M2Stage1InputLoop

    CMP CURRENT_STAGE, 2
    JE M2Stage2InputLoop

    JMP M2Stage3InputLoop

M2Failed:
    MOV MISSION_STATUS, 0

    MOV EDX, OFFSET m2MissionFail
    CALL DisplayMsg

    RET

Mission02 ENDP
