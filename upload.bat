@echo off


SET command=%1
SHIFT


IF %command% == master (
    echo Uploading to Master 
    cd Master

) ELSE (
    IF %command% == slave (
        echo Uploading to Slave
        cd Slave
    )
)

:loop
IF NOT "%1" == "" (

    IF "%1" == "-b" (
        echo -Build-
        pio run
        SHIFT
    )

    IF "%1" == "-u" (
        echo -Upload-
        pio run -t upload
        SHIFT
    )

    IF "%1" == "-m" (
        echo -Monitor-
        pio run -t monitor
        SHIFT
    )

    IF "%1" == "-c" (
        echo -Clean-
        pio run -t clean
        SHIFT
    )

    GOTO :loop

)




cd ..


