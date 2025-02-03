#include <stdio.h> //biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include "pico/stdlib.h" //biblioteca padrão para alocação de memória, controle de processos, etc.
#include "hardware/timer.h" //biblioteca da Raspberry Pi Pico para funções básicas (GPIO, UART, delays, etc.)

//define os pinos GPIOs para os LEDs
#define LED_PIN_BLUE 10
#define LED_PIN_RED 11
#define LED_PIN_GREEN 12

//define o pino GPIO para o botão
#define BUTTON_0 5

// variavel de controle
bool sequence_active = false; //indica se a sequência está ativa

//rotina de callback para desligar o LED verde
int16_t turn_off_green_callback(alarm_id_t id, void *user_data){
    gpio_put(LED_PIN_GREEN, false); //desliga o LED verde
    sequence_active = false; //permite nova ativação pelo botão
    return 0;
}

//rotina de callback para desligar o LED vermelho e ligar o LED verde
int64_t turn_off_red_callback(alarm_id_t id, void *user_data){
    gpio_put(LED_PIN_RED, false); //desliga o LED vermelho
    gpio_put(LED_PIN_GREEN, true); //liga o LED verde
    add_alarm_in_ms(3000, turn_off_green_callback, NULL, false); //alarme que agenda o desligamento do LED verde
    return 0;
}

//rotina de callback para desligar o LED azul e ligar o LED vermelho 
int16_t turn_off_blue_callback(alarm_id_t id, void *user_data){
    gpio_put(LED_PIN_BLUE, false); //desliga o LED azul
    gpio_put(LED_PIN_RED, true); // liga o LED vermelho
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false); //alarme que agenda o desligamento do LED vermelho
    return 0;
}