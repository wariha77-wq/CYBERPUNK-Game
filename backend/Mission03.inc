; =====================================================
; MISSION 03 - DEADLOCK PROTOCOL (1-OF-3 ROTATION)
; =====================================================

Mission03 PROC

    CALL Clrscr

    ; INITIALIZE MISSION
    MOV CURRENT_MISSION, 3
    MOV MISSION_STATUS, 0
    MOV ATTEMPTS_REMAINING, 3
    MOV m3QuestionIndex, 0

    CALL DisplayHeading

    ; DISPLAY INTRODUCTION
    MOV EDX, OFFSET m3Intro
    CALL DisplayMsg

    MOV EDX, OFFSET m3Story
    CALL DisplayMsg

    CALL Crlf

; ==========================================
; DISPLAY CURRENT VECTOR QUESTION
; ==========================================
m3DisplayQuestion:

    ; PRINT STAGE HEADER (Updates left-panel telemetry card in UI)
    MOV ESI, OFFSET m3StageTitles
    MOV EAX, m3QuestionIndex
    MOV EDX, [ESI + EAX * 4]
    CALL DisplayMsg

    ; PRINT ASSEMBLY SNIPPET & QUESTION FROM ARRAY
    MOV ESI, OFFSET m3QuestionBank
    MOV EAX, m3QuestionIndex
    MOV EDX, [ESI + EAX * 4]
    CALL DisplayMsg
    CALL Crlf

; ==========================================
; PLAYER INPUT
; ==========================================
m3AskAgain:

    MOV EDX, OFFSET m3InputPrompt
    CALL WriteString

    CALL GetAnswer
    MOV EAX, playerAnswer
    MOV m3PlayerAnswer, EAX

    ; REJECT NEGATIVE INPUT
    CMP EAX, 0
    JL m3Invalid

    ; CHECK ANSWER ARRAY
    MOV ESI, OFFSET m3Answers
    MOV ECX, m3QuestionIndex
    CMP EAX, [ESI + ECX * 4]
    JE m3Success

; ==========================================
; WRONG ANSWER -> ROTATE TO NEXT QUESTION
; ==========================================
    DEC ATTEMPTS_REMAINING
    INC THREAT_LEVEL

    MOV EDX, OFFSET m3WrongMsg
    CALL DisplayMsg

    MOV EDX, OFFSET attemptMsg
    CALL WriteString
    MOV EAX, ATTEMPTS_REMAINING
    CALL WriteDec
    CALL Crlf

    CMP ATTEMPTS_REMAINING, 0
    JE m3Failure

    ; ROTATE QUESTION INDEX (0 -> 1 -> 2 -> 0)
    INC m3QuestionIndex
    CMP m3QuestionIndex, 3
    JL m3RotateNext
    MOV m3QuestionIndex, 0

m3RotateNext:
    CALL Crlf
    JMP m3DisplayQuestion

; ==========================================
; INVALID INPUT
; ==========================================
m3Invalid:

    MOV EDX, OFFSET m3InvalidMsg
    CALL DisplayMsg
    JMP m3AskAgain

; ==========================================
; MISSION SUCCESS (ANY 1 QUESTION SOLVED)
; ==========================================
m3Success:

    MOV MISSION_STATUS, 1
    INC ACCESS_LEVEL

    MOV EDX, OFFSET m3CorrectMsg
    CALL DisplayMsg

    MOV EDX, OFFSET m3SuccessMsg
    CALL DisplayMsg

    RET

; ==========================================
; MISSION FAILURE
; ==========================================
m3Failure:

    MOV MISSION_STATUS, 0

    MOV EDX, OFFSET m3FailMsg
    CALL DisplayMsg

    RET

Mission03 ENDP