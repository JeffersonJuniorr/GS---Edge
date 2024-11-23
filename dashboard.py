# Integrantes:

# Jefferson Junior Alvarez Urbina RM 558497

import tkinter as tk
from tkinter import ttk
import paho.mqtt.client as mqtt
import json

# Configurações do broker MQTT
MQTT_SERVER = "56251ee2211347a29811165c3047af9b.s1.eu.hivemq.cloud"
MQTT_PORT = 8883
MQTT_USER = "edgegs"
MQTT_PASSWORD = "GlobalSolution2024"
MQTT_TOPICS = ["renovavel/temperatura", "renovavel/umidade", "renovavel/luminosidade", "alertas/energia"]

# Função de callback quando o cliente se conecta ao broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conectado ao broker MQTT!")
        for topic in MQTT_TOPICS:
            client.subscribe(topic)
    else:
        print(f"Falha na conexão. Código de retorno: {rc}")

# Função de callback quando uma mensagem é recebida
def on_message(client, userdata, msg):
    if msg.topic == "renovavel/temperatura":
        temperatura.set(msg.payload.decode())
    elif msg.topic == "renovavel/umidade":
        umidade.set(msg.payload.decode())
    elif msg.topic == "renovavel/luminosidade":
        luminosidade.set(msg.payload.decode())
    elif msg.topic == "alertas/energia":
        alerta.set(msg.payload.decode())

# Configuração do cliente MQTT
client = mqtt.Client()
client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
client.tls_set()  # Usa o TLS padrão
client.on_connect = on_connect
client.on_message = on_message

# Função para iniciar o cliente MQTT em segundo plano
def start_mqtt():
    client.connect(MQTT_SERVER, MQTT_PORT)
    client.loop_start()

# Criação do dashboard com Tkinter
def create_dashboard():
    root = tk.Tk()
    root.title("Dashboard de Monitoramento")
    root.geometry("400x300")

    # Variáveis globais associadas ao Tkinter
    global temperatura, umidade, luminosidade, alerta
    temperatura = tk.StringVar(value="---")
    umidade = tk.StringVar(value="---")
    luminosidade = tk.StringVar(value="---")
    alerta = tk.StringVar(value="Nenhum alerta")

    # Título
    ttk.Label(root, text="Monitoramento de Sensores", font=("Helvetica", 16, "bold")).pack(pady=10)

    # Exibição dos valores
    ttk.Label(root, text="Temperatura:").pack()
    ttk.Label(root, textvariable=temperatura, font=("Helvetica", 14)).pack()

    ttk.Label(root, text="Umidade:").pack()
    ttk.Label(root, textvariable=umidade, font=("Helvetica", 14)).pack()

    ttk.Label(root, text="Luminosidade:").pack()
    ttk.Label(root, textvariable=luminosidade, font=("Helvetica", 14)).pack()

    ttk.Label(root, text="Alertas de Energia:").pack()
    ttk.Label(root, textvariable=alerta, font=("Helvetica", 14, "bold"), foreground="red").pack(pady=10)

    # Botão para sair
    ttk.Button(root, text="Sair", command=lambda: (client.loop_stop(), client.disconnect(), root.destroy())).pack(pady=10)

    root.mainloop()

# Iniciar o MQTT e abrir o dashboard
if __name__ == "__main__":
    start_mqtt()
    create_dashboard()
