
; =====================================================
; CYBERPUNK 2086
; DISPLAY MODULE
; =====================================================


; =====================================================
; DISPLAY MESSAGE
; =====================================================

DisplayMsg PROC

    CALL WriteString
    CALL Crlf

    RET

DisplayMsg ENDP


; =====================================================
; BOOT SEQUENCE
; =====================================================

BootSequence PROC

    CALL Clrscr
    CALL Crlf

    MOV EAX, lightcyan + (black * 16)
    CALL SetTextColor

    MOV EDX, OFFSET boot1
    CALL DisplayMsg

    MOV EDX, OFFSET boot2
    CALL DisplayMsg

    MOV EDX, OFFSET boot3
    CALL DisplayMsg

    MOV EDX, OFFSET boot4
    CALL DisplayMsg

    MOV EAX, red + (black * 16)
    CALL SetTextColor

    MOV EDX, OFFSET boot5
    CALL DisplayMsg

    MOV EDX, OFFSET boot6
    CALL DisplayMsg

    MOV EDX, OFFSET boot7
    CALL DisplayMsg

    MOV EAX, yellow + (black * 16)
    CALL SetTextColor

    MOV EDX, OFFSET boot8
    CALL DisplayMsg

    MOV EDX, OFFSET boot9
    CALL DisplayMsg

    MOV EDX, OFFSET boot10
    CALL DisplayMsg

    MOV EAX, lightgray + (black * 16)
    CALL SetTextColor

    CALL Crlf
    CALL WaitMsg
    CALL Clrscr

    RET

BootSequence ENDP


; =====================================================
; DISPLAY MISSION HEADING
; =====================================================

DisplayHeading PROC

    MOV EAX, yellow + (black * 16)
    CALL SetTextColor

    CMP CURRENT_MISSION, 1
    JE DH1

    CMP CURRENT_MISSION, 2
    JE DH2

    CMP CURRENT_MISSION, 3
    JE DH3

    CMP CURRENT_MISSION, 4
    JE DH4

    CMP CURRENT_MISSION, 5
    JE DH5

    JMP DHDone

DH1:
    MOV EDX, OFFSET m1Heading
    JMP DHPrint

DH2:
    MOV EDX, OFFSET m2Heading
    JMP DHPrint

DH3:
    MOV EDX, OFFSET m3Heading
    JMP DHPrint

DH4:
    MOV EDX, OFFSET m4Heading
    JMP DHPrint

DH5:
    MOV EDX, OFFSET m5Heading

DHPrint:

    CALL DisplayMsg

DHDone:

    MOV EAX, lightgray + (black * 16)
    CALL SetTextColor

    RET

DisplayHeading ENDP


; =====================================================
; GAME OVER SCREEN
; =====================================================

GameOver PROC

    CALL Clrscr
    CALL Crlf

    MOV EAX, red + (black * 16)
    CALL SetTextColor

    MOV EDX, OFFSET gameOverTitle
    CALL DisplayMsg

    CALL Crlf

    MOV EDX, OFFSET gameOverMsg
    CALL DisplayMsg

    MOV EDX, OFFSET operatorMsg
    CALL DisplayMsg

    CALL Crlf

    MOV EDX, OFFSET finalScoreMsg
    CALL WriteString

    MOV EAX, PLAYER_SCORE
    CALL WriteDec

    CALL Crlf
    CALL Crlf

    MOV EDX, OFFSET gameOverFooter
    CALL DisplayMsg

    MOV EAX, lightgray + (black * 16)
    CALL SetTextColor

    RET

GameOver ENDP


; =====================================================
; VICTORY SCREEN
; =====================================================

VictoryScreen PROC

    CALL Crlf

    MOV EDX, OFFSET victoryTitle
    CALL DisplayMsg

    MOV EDX, OFFSET finalVictoryMsg
    CALL DisplayMsg

    MOV EDX, OFFSET finalScoreMsg
    CALL WriteString

    MOV EAX, PLAYER_SCORE
    CALL WriteDec
    CALL Crlf

   MOV EDX, OFFSET victoryCliff
CALL DisplayMsg

MOV EDX, OFFSET Cliff
CALL DisplayMsg

    RET

VictoryScreen ENDP
