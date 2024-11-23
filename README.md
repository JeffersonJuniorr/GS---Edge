# Jefferson Junior Alvarez Urbina RM 558497

Dashboard de Monitoramento com MQTT e Tkinter
Descrição do Projeto
Este projeto é uma aplicação em Python que monitora dados provenientes de sensores conectados a um broker MQTT. Utilizando a biblioteca Tkinter, os dados são exibidos em um dashboard gráfico de forma simples e intuitiva, permitindo o acompanhamento em tempo real de variáveis como temperatura, umidade, luminosidade e alertas de energia.

Problema Abordado
A falta de ferramentas acessíveis e em tempo real para visualizar dados provenientes de sensores IoT dificulta o monitoramento e a tomada de decisões rápidas. Este projeto busca resolver essa lacuna ao criar uma interface amigável e eficiente que centraliza essas informações.

Arquitetura do Projeto
Cliente MQTT:

Utiliza a biblioteca paho-mqtt para conectar-se ao broker, assinar tópicos e processar mensagens.
Tópicos monitorados:
renovavel/temperatura
renovavel/umidade
renovavel/luminosidade
alertas/energia
Interface Gráfica (Tkinter):

Exibe os dados recebidos em tempo real.
Atualiza automaticamente as variáveis conforme as mensagens chegam.
Fornece um botão para encerrar o programa e desconectar do broker.
Requisitos
Softwares Necessários
Python 3.8 ou superior.
Dependências do Projeto
As dependências podem ser instaladas com o comando:

pip install -r requirements.txt
Lista de Dependências:

paho-mqtt
tkinter (nativo no Python)

Instruções de Uso

Clone este repositório:
git clone https://github.com/seu-usuario/seu-repositorio.git
Entre no diretório do projeto:


cd dashboard-mqtt
Instale as dependências:


pip install -r requirements.txt
Execute o programa:


python main.py
Interação com o Dashboard:

O dashboard exibirá dados em tempo real provenientes dos sensores.
Para encerrar, clique no botão "Sair".
Resultados Esperados
Monitoramento em tempo real de dados de sensores.
Interface gráfica intuitiva para exibir variáveis e alertas.
Possibilidade de rápida tomada de decisão com base nos dados apresentados.
Impacto
Este projeto oferece uma solução prática e acessível para monitorar sistemas IoT, promovendo maior eficiência na gestão de sensores e reações rápidas a eventos críticos. Sua aplicação pode ser estendida para diversos cenários, como automação residencial, monitoramento industrial e sustentabilidade energética.

Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests para melhorias e correções.
