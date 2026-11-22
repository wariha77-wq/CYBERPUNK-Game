
InitializeGame PROC

    mov eax, 0
    mov PLAYER_SCORE, eax

    mov ATTEMPTS_REMAINING, 3
    mov CURRENT_MISSION, 1
    mov THREAT_LEVEL, 0
    mov ACCESS_LEVEL, 0
    mov MISSION_STATUS, 0

    ret

InitializeGame ENDP