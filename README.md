# Description
    Basic projects about STM32 uC, apply STM32 uC to interact to peripherals

# Software
    - STM32CubeIDE
    - Proteus
    - Virtual Serial Port Driver
    - Hercules

# Projects
    - Led_HAL: blink led by periodically using interrupt timer
    - Led_reg: blink led by periodically using counter timer
    - UART_HAL: interaction between uC and Hercules by UART protocol, request user enter command and respond correspond code
    - UART_Reg: transmit data to virtual terminal by UART protocol
    - ADC_HAL: based on reference voltage, read ADC value and transmit to terminal by UART
    - ADC_Reg: based on reference voltage, read ADC value and transmit to terminal by UART
    - WWDG_HAL: test reset feature of Window Watchdog via blinking led

# Common source
    Projects using HAL library:
        - Core: includes source code (main.c, ...) 
        - Debug: includes hex file to upload to board
        - Drivers: includes libraries
        - Simulation: includes proteus file and schematic
        - *.ioc: setting

    Projects using register:
        - Debug: includes hex file to upload to board
        - Simulation: includes proteus file
        - Src: includes source code (main.c, ...)
        *** Right-click project in workspace and choose Properties -> C/C++ Build -> Settings -> MCU GCC Compiler -> Include paths -> Modify paths based on project using HAL in current workspace 

# Reference
    https://deviot.vn/tutorials/stm32f4.62153513/lap-trinh-timer-che-do-counter-de-tao-delay.58829201
    https://khuenguyencreator.com/lap-trinh-stm32-wwdg-window-watchdog-timer/ 