#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// define os pinos dos LEDs e o pino do botão
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define LED_PIN_GREEN 11
#define BUTTON_0 5

// variável que controla se a sequência de LEDs está ativa ou não
bool sequence_active = false;

// declarações das funções de callback que serão chamadas para desligar os LEDs após determinado tempo
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data);
int64_t turn_off_red_callback(alarm_id_t id, void *user_data);
int64_t turn_off_green_callback(alarm_id_t id, void *user_data);

// função de teste inicial dos LEDs
void test_leds() {
    printf("Testando LEDs...\n");
    gpio_put(LED_PIN_BLUE, true);  // acende o LED azul
    sleep_ms(500);                  // espera por 500 milissegundos
    gpio_put(LED_PIN_BLUE, false);  // apaga o LED azul
    
    gpio_put(LED_PIN_RED, true);    // acende o LED vermelho
    sleep_ms(500);                  // espera por 500 milissegundos
    gpio_put(LED_PIN_RED, false);   // apaga o LED vermelho
    
    gpio_put(LED_PIN_GREEN, true);  // acende o LED verde
    sleep_ms(500);                  // espera por 500 milissegundos
    gpio_put(LED_PIN_GREEN, false); // apaga o LED verde
    printf("Teste de LEDs concluído.\n");
}

// função de teste inicial do botão
void test_button() {
    printf("Pressione o botão para testar...\n");
    while (gpio_get(BUTTON_0) != 0) {  // espera o botão ser pressionado
        sleep_ms(10);                   // espera 10 milissegundos antes de verificar novamente
    }
    printf("Botão detectado!\n");
}

// função de callback para desligar o LED azul após 3 segundos
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) { 
    gpio_put(LED_PIN_BLUE, false);   // desliga o LED azul
    sequence_active = false;         // a sequência não está mais ativa
    printf("LED azul desligado.\n");
    return 0;
}

// função de callback para desligar o LED vermelho
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) { 
    gpio_put(LED_PIN_RED, false);    // desliga o LED vermelho
    gpio_put(LED_PIN_BLUE, true);    // acende o LED azul
    printf("LED vermelho desligado.\n");
    add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);  // chama a função para desligar o LED azul após 3 segundos
    return 0;
}

// função de callback para desligar o LED verde 
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_GREEN, false);  // desliga o LED verde
    gpio_put(LED_PIN_RED, true);     // acende o LED vermelho
    printf("LED verde desligado.\n");
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);  // chama a função para desligar o LED vermelho após 3 segundos
    return 0;
}

int main() {
    stdio_init_all();  // inicializa o sistema de entrada e saída padrão

    // inicializa os pinos dos LEDs
    gpio_init(LED_PIN_BLUE);
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);  // define o pino do LED azul como saída
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);   // define o pino do LED vermelho como saída
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT); // define o pino do LED verde como saída

    // inicializa o pino do botão
    gpio_init(BUTTON_0);
    gpio_set_dir(BUTTON_0, GPIO_IN);   // define o pino do botão como entrada
    gpio_pull_up(BUTTON_0);            // ativa o resistor de pull-up para o botão

    // chama as funções de teste de LEDs e do botão
    test_leds();
    test_button();
    
    while (true) {
        // verifica se o botão foi pressionado e se a sequência ainda não está ativa
        if (gpio_get(BUTTON_0) == 0 && !sequence_active) {
            sleep_ms(50);  // aguarda 50 milissegundos para evitar múltiplos registros do botão
            if (gpio_get(BUTTON_0) == 0) {  // confirma se o botão está pressionado
                sequence_active = true;  // define que a sequência está ativa
                printf("Botão pressionado, iniciando sequência.\n");
                gpio_put(LED_PIN_BLUE, true);  // acende o LED azul
                gpio_put(LED_PIN_RED, true);   // acende o LED vermelho
                gpio_put(LED_PIN_GREEN, true); // acende o LED verde
                add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);  // chama a função para desligar o LED verde após 3 segundos
            }
        }
        sleep_ms(10);  // espera 10 milissegundos antes de verificar novamente
    }
    return 0;
}
