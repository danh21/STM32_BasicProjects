# Description
    Basic projects about STM32 uC, apply STM32 uC to interact to peripherals

# Software
    - STM32CubeIDE
    - Proteus

# Projects
    - Led_HAL: toggle led by button (polling) using HAL lib
    - Led_reg: blink led by periodically using register

# Common source
    Projects using HAL library:
        - Core: includes source code (main.c, ...) 
        - Debug: includes hex file to upload to board
        - Drivers: includes libraries
        - Simulation: includes proteus file
        - *.ioc: setting

    Projects using register:
        - Debug: includes hex file to upload to board
        - Simulation: includes proteus file
        - Src: includes source code (main.c, ...)
        *** Right-click project in workspace and choose Properties -> C/C++ Build -> Settings -> MCU GCC Compiler -> Include paths -> Modify paths based on project using HAL in current workspace 
