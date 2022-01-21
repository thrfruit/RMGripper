芯片型号：stm32f407zgt

电脑与stm32：通过ch340
ch340 tx--------stm32 USART3 RX PB11
      rx-------- stm32 USART TX PB10
      gnd--------gnd
      3v3---------不接

舵机调试板：tx —————— 32 USART2的tx:PA2
            rx——————— 32 PA3
            GND—————— 32 GND
            5v————————32 5v
             
直线电机 ： 蓝线 ———————— pwm输出TIM4——CH1 PD12

压力传感器：
           
