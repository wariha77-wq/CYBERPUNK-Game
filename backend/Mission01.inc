Mission01 PROC

    CALL Clrscr

    ; INITIALIZE MISSION
    MOV CURRENT_MISSION, 1
    MOV MISSION_STATUS, 0
    MOV ATTEMPTS_REMAINING, 2

    CALL DisplayHeading

    ; INTRODUCTION
    MOV EDX, OFFSET m1Intro
    CALL DisplayMsg

    MOV EDX, OFFSET m1Story
    CALL DisplayMsg

    CALL Crlf

    ; DISPLAY SECURITY LOGS
    MOV EDX, OFFSET m1LogHeading
    CALL DisplayMsg

    CALL Crlf

    ; RECORD 01
    MOV EDX, OFFSET m1Record1
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record1Time
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record1Location
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record1Status
    CALL DisplayMsg

    CALL Crlf

    ; RECORD 02
    MOV EDX, OFFSET m1Record2
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record2Time
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record2Location
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record2Status
    CALL DisplayMsg

    CALL Crlf

    ; RECORD 03
    MOV EDX, OFFSET m1Record3
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record3Time
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record3Location
    CALL DisplayMsg

    MOV EDX, OFFSET m1Record3Status
    CALL DisplayMsg

    CALL Crlf

    ; INVESTIGATION QUESTION
    MOV EDX, OFFSET m1Question
    CALL DisplayMsg

    MOV EDX, OFFSET m1Options
    CALL DisplayMsg

    MOV EDX, OFFSET m1Option2
    CALL DisplayMsg

    MOV EDX, OFFSET m1Option3
    CALL DisplayMsg


M1AttemptLoop:

    CALL Crlf

    MOV EDX, OFFSET m1Prompt
    CALL WriteString

    CALL GetAnswer

    ; CHECK ANSWER
    MOV EAX, playerAnswer
    CMP EAX, m1ExpectedAnswer
    JE M1Success

    ; WRONG ANSWER
    MOV EDX, OFFSET m1WrongMsg
    CALL DisplayMsg

    DEC ATTEMPTS_REMAINING

    MOV EDX, OFFSET attemptMsg
    CALL WriteString

    MOV EAX, ATTEMPTS_REMAINING
    CALL WriteDec

    CALL Crlf

    CMP ATTEMPTS_REMAINING, 0
    JE M1Failed

    JMP M1AttemptLoop


M1Success:

    MOV MISSION_STATUS, 1

    MOV EDX, OFFSET m1CorrectMsg
    CALL DisplayMsg

    MOV EDX, OFFSET m1SuccessMsg
    CALL DisplayMsg

    RET


M1Failed:

    MOV MISSION_STATUS, 0

    MOV EDX, OFFSET m1FailMsg
    CALL DisplayMsg

    RET

Mission01 ENDP

