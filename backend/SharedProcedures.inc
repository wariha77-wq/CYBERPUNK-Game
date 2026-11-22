
; =====================================================
; SHARED PROCEDURES
; CYBERPUNK 2086
; =====================================================

; -----------------------------------------------------
; GET ANSWER
; Reads an integer and stores it in playerAnswer.
; -----------------------------------------------------

GetAnswer PROC

    CALL ReadInt
    MOV playerAnswer, EAX

    RET

GetAnswer ENDP


; -----------------------------------------------------
; ASK QUESTION
; Used by Mission 04 and Mission 05.
; Returns EAX = 1 for correct answer.
; Returns EAX = 0 when attempts are exhausted.
; -----------------------------------------------------

AskQuestion PROC

AQInputLoop:

    MOV EDX, Q_QUESTION
    CALL DisplayMsg

    MOV EDX, Q_OPTION_A
    CALL DisplayMsg

    MOV EDX, Q_OPTION_B
    CALL DisplayMsg

    MOV EDX, Q_OPTION_C
    CALL DisplayMsg

    MOV EDX, OFFSET questionPrompt
    CALL WriteString

    CALL GetAnswer

    MOV EAX, playerAnswer
    CMP EAX, EXPECTED_ANSWER
    JE AQCorrect

    DEC ATTEMPTS_REMAINING

    MOV EDX, OFFSET wrongMsg
    CALL DisplayMsg

    MOV EDX, OFFSET attemptMsg
    CALL WriteString

    MOV EAX, ATTEMPTS_REMAINING
    CALL WriteDec
    CALL Crlf

    CMP ATTEMPTS_REMAINING, 0
    JE AQFailed

    CALL Crlf
    JMP AQInputLoop

AQCorrect:

    MOV EAX, 1
    RET

AQFailed:

    MOV EAX, 0
    RET

AskQuestion ENDP


; -----------------------------------------------------
; UPDATE SCORE
; Awards 20 points for each completed mission.
; Maximum score = 100.
; -----------------------------------------------------

UpdateScore PROC

    ADD PLAYER_SCORE, 20

    MOV EDX, OFFSET scoreMsg
    CALL WriteString

    MOV EAX, PLAYER_SCORE
    CALL WriteDec

    CALL Crlf

    RET

UpdateScore ENDP
