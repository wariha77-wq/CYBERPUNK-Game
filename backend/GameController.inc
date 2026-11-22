
GameController PROC

    MOV PLAYER_SCORE, 0
    MOV MISSION_STATUS, 0
    CALL Randomize

    ; MISSION 01
    CALL Mission01
    CMP MISSION_STATUS, 1
    JNE ControllerFailed

    CALL UpdateScore
    CALL WaitMsg

    ; MISSION 02
    CALL Mission02
    CMP MISSION_STATUS, 1
    JNE ControllerFailed

    CALL UpdateScore
    CALL WaitMsg

    ; MISSION 03
    CALL Mission03
    CMP MISSION_STATUS, 1
    JNE ControllerFailed

    CALL UpdateScore
    CALL WaitMsg

    ; MISSION 04
    CALL Mission04
    CMP MISSION_STATUS, 1
    JNE ControllerFailed

    CALL UpdateScore
    CALL WaitMsg

    ; MISSION 05
    CALL Mission05
    CMP MISSION_STATUS, 1
    JNE ControllerFailed

    CALL UpdateScore
    CALL WaitMsg

    CALL Crlf
    CALL VictoryScreen
    CALL WaitMsg
    RET

ControllerFailed:

    CALL GameOver
    CALL WaitMsg
    RET

GameController ENDP
