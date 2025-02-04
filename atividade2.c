#include <stdio.h> //biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include "pico/stdlib.h" //biblioteca para controle de GPIO, UART e temporização
#include "pico/time.h" //biblioteca para uso de temporizadores (add_alarm_in_ms)

//define os pinos GPIOs para os LEDs
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define LED_PIN_GREEN 11

//define o pino GPIO para o botão
#define BUTTON_0 5

//variável de controle
bool sequence_active = false; //indica se a sequência está ativa
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data);

//rotina de callback para desligar o LED azul
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) { 
    gpio_put(LED_PIN_BLUE, false); // Desliga o LED azul
    sequence_active = false; // Permite nova ativação pelo botão
    return 0;
}

//rotina de callback para desligar o LED vermelho e ligar o LED azul
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) { 
    gpio_put(LED_PIN_RED, false); // Desliga o LED vermelho
    gpio_put(LED_PIN_BLUE, true); // Liga o LED azul
    add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false); // Agenda o desligamento do LED azul
    return 0;
}

//rotina de callback para desligar o LED verde e ligar o LED vermelho
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_GREEN, false); // Desliga o LED verde
    gpio_put(LED_PIN_RED, true); // Liga o LED vermelho
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false); // Agenda o desligamento do LED vermelho
    return 0;
}

//função principal
int main() {
    //inicializa a comunicação serial
    stdio_init_all();

    //configuração dos LEDs
    //inicializa os LEDs
    gpio_init(LED_PIN_BLUE); 
    gpio_init(LED_PIN_RED); 
    gpio_init(LED_PIN_GREEN); 

    //configura como saída
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT); 
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    //configuração do botão 
    gpio_init(BUTTON_0); //inicializa o botão
    gpio_set_dir(BUTTON_0, GPIO_IN); //configura como entrada
    gpio_pull_up(BUTTON_0); //configura pull-up interno

    //loop principal
    while (true) {
        //verifica se o botão foi pressionado e se a sequência não está ativa
        if (gpio_get(BUTTON_0) == 0 && !sequence_active) {
            sleep_ms(50); //atraso para debounce

            //confirma o pressionamento do botão
            if (gpio_get(BUTTON_0) == 0) {
                sequence_active = true; //bloqueia novas ativações

                //liga todos os LEDs
                gpio_put(LED_PIN_BLUE, true);
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_GREEN, true);

                //inicia a sequência de desligamento com temporizador
                add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);
            }
        }
        sleep_ms(10); //pequena pausa para reduzir consumo de CPU
    }

    return 0;
}
