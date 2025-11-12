<img width="1024" height="1024" alt="Gemini_Generated_Image_e2syope2syope2sy" src="https://github.com/user-attachments/assets/82dd2dcc-5cb0-4e6a-9a8c-951ae75c4fc1" />
# 🌾 SmartAgro - Système de Surveillance Agricole Intelligent

## 📋 Description

**SmartAgro** est un système embarqué de surveillance et d'automatisation agricole intelligente basé sur deux cartes **STM32H7**. Le système collecte des données environnementales en temps réel, détecte les maladies des plantes grâce à l'intelligence artificielle embarquée, et contrôle automatiquement l'irrigation, la ventilation et l'éclairage pour optimiser les conditions de croissance.

Les données sont transmises au cloud **Adafruit IO** via MQTT sécurisé (TLS) grâce à un module **ESP32** pour une supervision à distance en temps réel.

> 🎯 **Objectif** : Automatiser la gestion agricole pour maximiser les rendements tout en réduisant la consommation d'eau et d'énergie.

## 🎥 Vidéo de démonstration

[![Voir la démo sur Google Drive](https://drive.google.com/uc?export=view&id=1bJFTI6KcqEKpHZDCCuNOP9v2ajTUpQTe)](https://drive.google.com/file/d/1bJFTI6KcqEKpHZDCCuNOP9v2ajTUpQTe/view?usp=sharing)


## ✨ Fonctionnalités Principales

### 🔍 Surveillance Environnementale
- **Température et humidité de l'air** : Capteur AM2320 (I²C)
- **Humidité du sol** : Capteur analogique capacitif
- **Luminosité** : Module LDR + LM393 (sortie digitale)

### 🤖 Intelligence Artificielle
- Détection des maladies des plantes (pomme de terre, tomate, poivron)
- Analyse embarquée en temps réel
- Alertes préventives

### ⚙️ Automatisation
- **Irrigation automatique** : Pompe contrôlée selon l'humidité du sol
- **Régulation thermique** : Ventilateur activé selon la température
- **Éclairage intelligent** : LEDs pour conditions optimales de croissance

### 🌐 Connectivité IoT
- Communication inter-cartes via **CAN Bus** (MCP2515 - SPI)
- Publication cloud via **ESP32** et **MQTT/TLS**
- Dashboard temps réel sur **Adafruit IO**

---

## 🔧 Architecture Système
```
<img width="1024" height="1024" alt="Gemini_Generated_Image_e2syope2syope2sy" src="https://github.com/user-attachments/assets/2ae45d90-0f7f-4d93-baf4-e367d0248a5d" />

```
## ⚙️ Protocoles de communication utilisés

| Protocole | Vitesse     | Usage                        |
|------------|-------------|------------------------------|
| I²C        | 400 kHz     | AM2320 → STM32               |
| CAN        | 500 kbps    | STM32 ↔ STM32                |
| UART       | 115200 bps  | STM32 → ESP32                |
| SPI        | 2 MHz       | STM32 → MCP2515              |
| MQTT/TLS   | Variable    | ESP32 → Cloud (Adafruit IO)  |

---


## 👥 Auteurs

**Votre Nom** - *chaima ghouili*

---

## 📞 Contact

- Email : chaimaghouili691@gmail.com
- LinkedIn : [Votre Profil](https://www.linkedin.com/in/chaima-ghouili-98b54527a/)


---

⭐ **Si ce projet vous est utile, n'hésitez pas à lui donner une étoile !**
```
