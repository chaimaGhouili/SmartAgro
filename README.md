## 🎥 Vidéo de démonstration

[![Voir la démo sur Google Drive](https://drive.google.com/uc?export=view&id=1bJFTI6KcqEKpHZDCCuNOP9v2ajTUpQTe)](https://drive.google.com/file/d/1bJFTI6KcqEKpHZDCCuNOP9v2ajTUpQTe/view?usp=sharing)

# 🌾 SmartAgro - Système de Surveillance Agricole Intelligent

<div align="center">

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![STM32](https://img.shields.io/badge/STM32-H7-brightgreen.svg)
![Platform](https://img.shields.io/badge/Platform-Embedded-orange.svg)
![CAN](https://img.shields.io/badge/CAN-MCP2515-red.svg)
![IoT](https://img.shields.io/badge/IoT-MQTT-purple.svg)

</div>

## 📋 Description

**SmartAgro** est un système embarqué de surveillance et d'automatisation agricole intelligente basé sur deux cartes **STM32H7**. Le système collecte des données environnementales en temps réel, détecte les maladies des plantes grâce à l'intelligence artificielle embarquée, et contrôle automatiquement l'irrigation, la ventilation et l'éclairage pour optimiser les conditions de croissance.

Les données sont transmises au cloud **Adafruit IO** via MQTT sécurisé (TLS) grâce à un module **ESP32** pour une supervision à distance en temps réel.

> 🎯 **Objectif** : Automatiser la gestion agricole pour maximiser les rendements tout en réduisant la consommation d'eau et d'énergie.

---

## 🎥 Démonstration

[![SmartAgro Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=YOUR_VIDEO_ID)

> Cliquez sur l'image pour voir la démonstration complète du système

---

## 📸 Captures d'Écran

<div align="center">

| Dashboard Temps Réel | Monitoring Capteurs | Contrôle Actionneurs |
|:-------------------:|:------------------:|:-------------------:|
| ![Dashboard](docs/images/dashboard.png) | ![Sensors](docs/images/sensors.png) | ![Actuators](docs/images/actuators.png) |

</div>

---

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
┌─────────────────────────────────────────────────────────────┐
│                    SmartAgro System                          │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  ┌──────────────┐         CAN Bus        ┌──────────────┐   │
│  │   STM32 #1   │◄──────────────────────►│   STM32 #2   │   │
│  │  (Capteurs)  │      MCP2515 (SPI)     │ (Actionneurs)│   │
│  └──────┬───────┘                         └──────┬───────┘   │
│         │                                        │            │
│    ┌────▼────┐                             ┌────▼────┐       │
│    │ AM2320  │                             │  Pompe  │       │
│    │ (I²C)   │                             │Irrigation│      │
│    └─────────┘                             └─────────┘       │
│    ┌─────────┐                             ┌─────────┐       │
│    │ Humidité│                             │Ventila- │       │
│    │   Sol   │                             │  teur   │       │
│    │ (ADC)   │                             └─────────┘       │
│    └─────────┘                             ┌─────────┐       │
│    ┌─────────┐                             │  LEDs   │       │
│    │   LDR   │                             │Éclairage│       │
│    │(Digital)│                             └─────────┘       │
│    └─────────┘                                                │
│         │                                                     │
│         └──────────────┐                                      │
│                        │                                      │
│                   ┌────▼────┐                                 │
│                   │  ESP32  │                                 │
│                   │  MQTT   │                                 │
│                   └────┬────┘                                 │
│                        │                                      │
│                        ▼                                      │
│                 ┌─────────────┐                               │
│                 │ Adafruit IO │                               │
│                 │   (Cloud)   │                               │
│                 └─────────────┘                               │
└─────────────────────────────────────────────────────────────┘
```

---

## 📁 Structure du Projet
```
SmartAgro/
│
├── Core/
│   ├── Inc/
│   │   ├── CAN_SPI.h          # Interface SPI pour MCP2515
│   │   ├── MCP2515.h          # Driver MCP2515
│   │   ├── main.h             # Configurations principales
│   │   ├── stm32h7xx_hal_conf.h
│   │   └── stm32h7xx_it.h     # Handlers d'interruptions
│   │
│   └── Src/
│       ├── CAN_SPI.c          # Implémentation SPI CAN
│       ├── MCP2515.c          # Implémentation MCP2515
│       ├── main.c             # Programme principal
│       ├── stm32h7xx_hal_msp.c
│       ├── stm32h7xx_it.c
│       └── syscalls.c
│
├── Drivers/               # HAL STM32
├── docs/                  # Documentation et images
├── README.md
└── LICENSE
```

---

## 🛠️ Matériel Requis

### Microcontrôleurs
- 2x **STM32H743ZIT6** (Nucleo-H743ZI2)

### Capteurs
| Capteur | Interface | Fonction |
|---------|-----------|----------|
| AM2320 | I²C (0x5C) | Température et humidité |
| Capteur d'humidité du sol | ADC (CH15) | Mesure humidité sol |
| LDR + LM393 | GPIO (PA6) | Détection luminosité |

### Actionneurs
- Pompe d'irrigation (contrôle GPIO)
- Ventilateur (contrôle GPIO)
- LEDs d'éclairage (contrôle GPIO)

### Communication
- 2x **MCP2515** (Contrôleur CAN via SPI)
- 1x **ESP32** (WiFi + MQTT)

### Périphériques
- 2x Transceivers CAN (TJA1050/MCP2551)
- Alimentation 5V/12V

---

## 🚀 Installation et Configuration

### Prérequis
- **STM32CubeIDE** (version 1.14+)
- **STM32CubeMX** (configuration HAL)
- **Arduino IDE** (pour ESP32)
- Compte **Adafruit IO**

### 1. Configuration STM32
```bash
# Cloner le repository
git clone https://github.com/votre-username/smartagro.git
cd smartagro

# Ouvrir le projet dans STM32CubeIDE
# File > Open Projects from File System > Sélectionner le dossier
```

#### Configuration des périphériques (CubeMX)
- **I2C1** : PB8 (SCL), PB9 (SDA) - AM2320
- **ADC1** : PC4 (CH15) - Humidité sol
- **SPI3** : PC10 (SCK), PC11 (MISO), PC12 (MOSI) - MCP2515
- **GPIO** : PA6 (LDR input), PD10 (CS SPI)
- **UART2** : PA2 (TX), PA3 (RX) - ESP32
- **UART3** : PD8 (TX), PD9 (RX) - Debug

### 2. Calibration Capteurs

Dans `main.c`, ajuster les valeurs de calibration :
```c
// Calibration humidité du sol
#define VALEUR_SECHE 60000   // ADC en air sec
#define VALEUR_HUMIDE 20000  // ADC dans l'eau
```

### 3. Configuration CAN

- **Vitesse** : 500 kbps
- **ID Message** : 0x36
- **Format** : Standard (11 bits)

#### Format du message CAN (6 octets)
```
Byte 0-1 : Température × 10 (int16_t)
Byte 2-3 : Humidité air × 10 (int16_t)
Byte 4   : Humidité sol (0-100%)
Byte 5   : État lumière (0=jour, 1=nuit)
```

---

## 📊 Protocole de Communication

### STM32 → ESP32 (UART)
Format CSV : `temperature,humidity,soil_moisture,light_state\r\n`

Exemple :
```
23.50,65.20,45,0
```

### ESP32 → Adafruit IO (MQTT)
Topics :
- `smartagro/temperature`
- `smartagro/humidity`
- `smartagro/soil`
- `smartagro/light`

---

## 📖 Utilisation

### 1. Compilation et Flash
```bash
# Dans STM32CubeIDE
# Build > Build Project (Ctrl+B)
# Run > Debug (F11)
```

### 2. Monitoring Série
Connectez un terminal série (115200 baud) sur UART3 :
```
Test de communication avec MCP2515...
Valeur lue de CANSTAT: 0x80
CAN initialisé avec succès
Temp: 23.50°C, Humidité: 65.20%
humidite de sol 45
lumiere
Message CAN transmis
```

### 3. Dashboard Adafruit IO
- Connectez-vous sur [io.adafruit.com](https://io.adafruit.com)
- Créez un nouveau dashboard
- Ajoutez des blocks pour chaque feed

---

## 🔬 Fonctionnalités Avancées

### Optimisation de la Transmission
Le système envoie les données uniquement si :
- Δ Température > 1°C
- Δ Humidité > 1%
- Changement d'état du sol ou luminosité

Ceci réduit la consommation de bande passante et prolonge la durée de vie du système.

### Détection d'Erreurs
- Vérification CRC sur I²C (AM2320)
- Timeout sur SPI (MCP2515)
- Retry automatique en cas d'échec CAN

---

## 🐛 Dépannage

### Problème I²C (AM2320)
```c
// Le capteur nécessite un "wake-up" avant lecture
HAL_I2C_Master_Transmit(&hi2c1, 0x5C << 1, &wake, 0, 5);
HAL_Delay(2);
```

### CAN ne démarre pas
- Vérifier les résistances de terminaison (120Ω)
- Contrôler les connexions CANH/CANL
- Tester la continuité SPI vers MCP2515

### ADC retourne des valeurs erronées
```c
// Activer la calibration ADC
HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
```

---

## 🤝 Contribution

Les contributions sont les bienvenues ! Pour contribuer :

1. Fork le projet
2. Créez une branche (`git checkout -b feature/amelioration`)
3. Commit vos changements (`git commit -m 'Ajout fonctionnalité X'`)
4. Push vers la branche (`git push origin feature/amelioration`)
5. Ouvrez une Pull Request

---

## 📄 Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

---

## 👥 Auteurs

**Votre Nom** - *Développement initial*

---

## 📞 Contact

- Email : votre.email@example.com
- LinkedIn : [Votre Profil](https://linkedin.com/in/votre-profil)
- GitHub : [@votre-username](https://github.com/votre-username)

---

## 🙏 Remerciements

- STMicroelectronics pour la HAL STM32
- Microchip pour le MCP2515
- Communauté Adafruit pour l'IoT Platform
- Tous les contributeurs open-source

---

## 📚 Documentation Additionnelle

- [Datasheet AM2320](https://akizukidenshi.com/download/ds/aosong/AM2320.pdf)
- [MCP2515 CAN Controller](https://ww1.microchip.com/downloads/en/DeviceDoc/MCP2515-Stand-Alone-CAN-Controller-with-SPI-20001801J.pdf)
- [STM32H7 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0433-stm32h742-stm32h743753-and-stm32h750-value-line-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

---

⭐ **Si ce projet vous est utile, n'hésitez pas à lui donner une étoile !**
```

**Instructions pour l'utiliser :**

1. Créez un fichier `README.md` à la racine de votre projet
2. Copiez-collez tout le code ci-dessus
3. Personnalisez les sections suivantes :
   - Remplacez `votre-username` par votre nom d'utilisateur GitHub
   - Ajoutez votre nom dans la section Auteurs
   - Mettez à jour les informations de contact
   - Ajoutez l'ID de votre vidéo YouTube si vous en avez une
   - Créez un dossier `docs/images/` et ajoutez vos captures d'écran

4. Créez également un fichier `LICENSE` avec la licence MIT :
```
MIT License

Copyright (c) 2025 Votre Nom

Permission is hereby granted, free of charge, to any person obtaining a copy...
