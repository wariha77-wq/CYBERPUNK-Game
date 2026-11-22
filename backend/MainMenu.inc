
MainMenu PROC

MenuLoop:

    CALL Crlf

    MOV EDX, OFFSET gameTitle
    CALL DisplayMsg

    MOV EDX, OFFSET menu1
    CALL DisplayMsg

    MOV EDX, OFFSET menu2
    CALL DisplayMsg

    MOV EDX, OFFSET menu3
    CALL DisplayMsg

    MOV EDX, OFFSET prompt
    CALL WriteString

    CALL ReadInt

    CMP EAX, 1
    JE StartGame

    CMP EAX, 2
    JE Instructions

    CMP EAX, 3
    JE ExitMenu

    MOV EDX, OFFSET invalidChoiceMsg
    CALL DisplayMsg
    JMP MenuLoop

StartGame:

    CALL InitializeGame
    CALL GameController
    JMP MenuLoop

Instructions:

    CALL Crlf

    MOV EDX, OFFSET instruction1
    CALL DisplayMsg

    MOV EDX, OFFSET instruction2
    CALL DisplayMsg

    MOV EDX, OFFSET instruction3
    CALL DisplayMsg

    MOV EDX, OFFSET instruction4
    CALL DisplayMsg

    MOV EDX, OFFSET instruction5
    CALL DisplayMsg

    CALL WaitMsg
    JMP MenuLoop

ExitMenu:
    RET

MainMenu ENDP