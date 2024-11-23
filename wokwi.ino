#include <WiFi.h>
#include <WiFiClientSecure.h> // Para suporte a TLS
#include <PubSubClient.h>
#include <DHT.h>

//Monitoramento de sistema renovavel

// Configurações da rede WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configuração do broker MQTT
const char* mqtt_server = "56251ee2211347a29811165c3047af9b.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "edgegs";
const char* mqtt_password = "GlobalSolution2024";

// Certificado raiz da Let's Encrypt (ISRG Root X1)
const char* root_ca =
"-----BEGIN CERTIFICATE-----\n"
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n"
"WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n"
"ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n"
"MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n"
"h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n"
"0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n"
"A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n"
"T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n"
"B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n"
"B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n"
"KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n"
"OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n"
"jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n"
"qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n"
"rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n"
"HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n"
"hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n"
"ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n"
"3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n"
"NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n"
"ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n"
"TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n"
"jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n"
"oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n"
"4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n"
"mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n"
"emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n"
"-----END CERTIFICATE-----";

// Configuração do cliente MQTT com TLS
WiFiClientSecure espClient;
PubSubClient client(espClient);

// Configuração do DHT22
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configuração do sensor LDR
#define LDRPIN 36

// LED de alerta
#define LEDPIN 2

// Variáveis dos sensores
float temperatura;
float umidade;
int luminosidade;

// Função para reconectar ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    if (client.connect("ESP32_Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha. Código: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  dht.begin();

  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Configure o certificado raiz para TLS
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Ler dados do DHT22
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  // Ler dados do sensor LDR
  int valorLDR = analogRead(LDRPIN);
  luminosidade = map(valorLDR, 0, 4095, 0, 100);

  if (!isnan(temperatura) && !isnan(umidade)) {
    // Publicar temperatura
    char tempString[8];
    dtostrf(temperatura, 1, 2, tempString);
    client.publish("renovavel/temperatura", tempString);
    Serial.print("Temperatura: ");
    Serial.println(tempString);

    // Publicar umidade
    char humString[8];
    dtostrf(umidade, 1, 2, humString);
    client.publish("renovavel/umidade", humString);
    Serial.print("Umidade: ");
    Serial.println(humString);

    // Publicar luminosidade
    char lumString[8];
    sprintf(lumString, "%d", luminosidade);
    client.publish("renovavel/luminosidade", lumString);
    Serial.print("Luminosidade: ");
    Serial.println(lumString);

    // Verificar alertas
    bool alerta = false;

    if (temperatura > 45.0) {
      client.publish("alertas/energia", "ALERTA: Temperatura alta crítica!");
      alerta = true;
    } else if (temperatura < 0.0) {
      client.publish("alertas/energia", "ALERTA: Temperatura baixa crítica!");
      alerta = true;
    }

    if (umidade > 85.0) {
      client.publish("alertas/energia", "ALERTA: Umidade alta crítica!");
      alerta = true;
    } else if (umidade < 20.0) {
      client.publish("alertas/energia", "ALERTA: Umidade baixa crítica!");
      alerta = true;
    }

    if (luminosidade > 90) {
      client.publish("alertas/energia", "ALERTA: Luminosidade excessiva!");
      alerta = true;
    } else if (luminosidade < 20) {
      client.publish("alertas/energia", "ALERTA: Luminosidade extremamente baixa!");
      alerta = true;
    }

    digitalWrite(LEDPIN, alerta ? HIGH : LOW);
  } else {
    Serial.println("Erro ao ler os dados do DHT22.");
  }

  delay(5000);
}
