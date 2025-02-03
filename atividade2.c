#include <stdio.h> //biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include "pico/stdlib.h" //biblioteca padrão para alocação de memória, controle de processos, etc.
#include "hardware/timer.h" //biblioteca da Raspberry Pi Pico para funções básicas (GPIO, UART, delays, etc.)

//define os pinos GPIOs para os LEDs
#define LED_PIN_BLUE 10
#define LED_PIN_RED 11
#define LED_PIN_GREEN 12

//define o pino GPIO para o botão
#define BUTTON_0 5



