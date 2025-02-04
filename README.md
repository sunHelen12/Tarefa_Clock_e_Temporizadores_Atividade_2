<h1 align="center">Tarefa - Temporizador One Shot - Embarcatech 🔵 🔴 🟢  </h1>
<p>Este projeto utiliza o Raspberry Pi Pico W para controlar uma sequência de LEDs (azul, vermelho e verde) com base no pressionamento de um botão. A sequência de LEDs é ativada ao pressionar o botão e, em seguida, os LEDs são apagados em uma ordem predefinida de 3 segundos de intervalo.</p>   

<h2>Descrição</h2>
<p>Foram empregadas a função <code>add_alarm_in_ms()</code> e a função de call-back do temporizador <code>turn_off_callback()</code> para desenvolver um sistema de temporização.</p>
<ul>
    <li>O Projeto irá iniciar com as  funções de Teste de LEDs e Testte de Botão;</li>
    <li>Em seguida, quando o botão é pressionado, os LEDs azul, vermelho e verde são acesos;</li>
    <li>Após 3 segundos, o LED verde se apaga e o LED vermelho e azul permanecem acesos;</li>
    <li>Depois de mais 3 segundos, o LED vermelho se apaga e o LED azul permanece aceso;</li>
    <li>Após mais 3 segundos todos os LEDs estarão apagados e será necessário pressionar o botão novamente para reinciar a sequência;</li>
    <li>O processo é gerido por alarmes que temporizam o desligamento dos LEDs.</li>   
</ul>

<h2>Importante⚠️</h2>
<p>Esse código foi produzido em um Sistema Operacional Linux. Certifique-se de importar o projeto adequadamente e verificar as configurações do <code>c_cpp_properties.json</code>.</p>

<h2>Demonstração</h2>
    <img src="assets/semaforo.gif" width="500" height="300">

<h2>Componentes Necessários</h2>
    <ul>
        <li>1 x Raspberry Pi Pico W;</li>
        <li>1 x LED Azul;</li>
        <li>1 x LED Vermelho;</li>
        <li>1 x LED Verde;</li>
        <li>3 x Resistores (330Ω): para limitar a corrente nos LEDs.</li>
    </ul>
    
<h2>Tecnologias Utilizadas</h2>
  <ul>
    <li>Linguagem C;</li>
    <li>IDE Visual Studio Code;</li>
    <li>Extensão Wokwi Simulator no Visual Studio Code;</li>
    <li>Wokwi Web;</li>
    <li>Pico SDK;</li>
    <li>Placa BitDogLab.</li>  
  </ul>

<h2>Clone o Repositório</h2>
  <ol>
     <li>Abra o <strong>Prompt de Comando</strong> ou o terminal de sua preferência.</li>
     <li>Clone o repositório usando o Git:
       <pre><code>git clone https://github.com/seu-usuario/seu-repositorio.git</code></pre>
     </li>
      <li>Entre no diretório do projeto:
          <pre><code>cd seu-repositorio</code></pre>
      </li>
  </ol>
  
<h2>Como Compilar e Executar</h2>
    <pre>
    mkdir build
    cd build
    cmake ..
    make
    </pre>
    <p>Depois, utilize o Wokwi Simulator para executar o projeto no Visual Studio Code ou a placa BitDogLab!</p>
    
<h2>Simulando o projeto no Wokwi Web</h2>
  <p>Para simular o projeto no Wokwi Web acesse: <a href="https://wokwi.com/projects/421833577874139137" target="_blank">Tarefa Temporizador One Shot</a>.</p>
