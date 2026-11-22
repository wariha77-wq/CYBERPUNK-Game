INCLUDE Irvine32.inc

.data
INCLUDE GameData.inc

.code
INCLUDE Display.inc
INCLUDE InitializeGame.inc
INCLUDE SharedProcedures.inc
INCLUDE Mission01.inc
INCLUDE Mission02.inc
INCLUDE Mission03.inc
INCLUDE Mission04.inc
INCLUDE Mission05.inc
INCLUDE GameController.inc
INCLUDE MainMenu.inc

main PROC
    CALL InitializeGame
    CALL GameController
    EXIT
main ENDP

END main