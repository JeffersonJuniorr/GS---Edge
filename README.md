 Jefferson Junior Alvarez Urbina RM 558497


# Dashboard de Monitoramento com MQTT e Tkinter
Descrição do Projeto
Este projeto é uma aplicação desenvolvida em Python que se conecta a um broker MQTT para monitorar dados de sensores em tempo real. Ele utiliza o protocolo MQTT para comunicação e Tkinter para exibição de um dashboard gráfico simples e intuitivo. Os dados monitorados incluem temperatura, umidade, luminosidade e alertas de energia, apresentados de maneira dinâmica e acessível ao usuário.

# Motivação
Com o crescimento de aplicações IoT, há uma necessidade crescente de ferramentas para monitorar sensores em tempo real. Muitas soluções existentes são complexas ou pouco acessíveis. Este projeto busca resolver esse problema criando um dashboard funcional e intuitivo que centraliza informações críticas e facilita a tomada de decisões.

# Tecnologias Utilizadas
Python
O Python foi escolhido devido à sua simplicidade, vasta comunidade de suporte e bibliotecas específicas para as necessidades do projeto. Ele permite integrar de forma eficiente o protocolo MQTT e a interface gráfica Tkinter.

Paho MQTT
Biblioteca que implementa o protocolo MQTT, facilitando a comunicação com o broker HiveMQ. É utilizada para conectar-se, assinar tópicos e processar mensagens.

Tkinter
Biblioteca nativa do Python para construção de interfaces gráficas. Foi utilizada para criar o dashboard, permitindo uma exibição visual dos dados recebidos pelo MQTT.

HiveMQ
Broker MQTT utilizado no projeto. Ele oferece uma solução confiável e segura para transmissão de dados entre dispositivos IoT e a aplicação.

Wokwi
Simulador de hardware usado para emular sensores IoT no projeto. Ele possibilita a geração de dados em tempo real, como temperatura, umidade e luminosidade, para validação do sistema.

# Arquitetura do Projeto
Simulação de Sensores (Wokwi):

Sensores simulados no Wokwi enviam dados de temperatura, umidade e luminosidade para o broker MQTT.
Comunicação com o Broker (HiveMQ):

O broker HiveMQ recebe os dados dos sensores e os disponibiliza para assinantes (neste caso, o dashboard).
Cliente MQTT:

A aplicação Python utiliza a biblioteca Paho MQTT para se conectar ao HiveMQ e receber os dados em tempo real.
Interface Gráfica:

O dashboard, desenvolvido com Tkinter, exibe as informações recebidas em tempo real e alerta o usuário em caso de mensagens críticas.

# Requisitos
Softwares Necessários
Python 3.8 ou superior.
Dependências
As dependências do projeto estão listadas no arquivo requirements.txt.

python

paho-mqtt

# Instruções de Uso
Clone o Repositório

git clone https://github.com/JeffersonJuniorr/GS---Edge.git
Entre no Diretório do Projeto

cd dashboard-mqtt
Instale as Dependências

pip install -r requirements.txt
Inicie a Aplicação

python main.py
Interação com o Dashboard
O dashboard exibirá os dados em tempo real recebidos do broker.
Para encerrar, clique no botão "Sair".

# Resultados Esperados
Monitoramento eficiente e em tempo real dos dados enviados pelos sensores.
Interface gráfica amigável que facilita a visualização e a interpretação dos dados.
Capacidade de emitir alertas ao usuário em situações críticas, como problemas relacionados ao consumo de energia.

# Impacto Esperado
Este projeto visa facilitar a gestão de dados IoT em sistemas de monitoramento, promovendo maior controle e eficiência. Ele é aplicável em diversas áreas, como automação residencial, monitoramento industrial e gestão sustentável de energia. Ao simplificar o acesso a informações críticas, a solução melhora a tomada de decisões e otimiza recursos.

# Contribuições
Contribuições para melhorias ou novas funcionalidades são sempre bem-vindas. Para isso, envie suas sugestões através de issues ou pull requests.

