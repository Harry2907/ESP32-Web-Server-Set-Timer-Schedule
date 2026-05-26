# 🚀 ESP32 Web-Based GPIO Timer Scheduler

A powerful Wi-Fi controlled GPIO automation system built using ESP32, Embedded C, FreeRTOS, and asynchronous web server architecture.

Control GPIOs instantly from your browser, schedule timed ON/OFF operations, monitor live countdown status, and run everything directly on the ESP32 without blocking execution.

---

## ✨ Features

- Real-time GPIO control from browser
- Timer scheduling in Seconds / Minutes / Hours
- FreeRTOS Software Timer based architecture
- Asynchronous non-blocking web server
- Live countdown timer updates
- Responsive web dashboard
- REST-style API endpoints
- Lightweight embedded IoT design
- Flash memory optimized using PROGMEM

---

# 🧠 Technologies Used

| Technology | Purpose |
|---|---|
| Embedded C | Firmware Development |
| ESP32 | Main Controller |
| FreeRTOS | Real-Time Scheduling |
| ESPAsyncWebServer | Async HTTP Server |
| AsyncTCP | Non-blocking TCP Stack |
| HTML/CSS/JS | Frontend Dashboard |
| Wi-Fi | Wireless Communication |

---

# 📡 System Architecture

```text
        +-------------------+
        |   Web Browser     |
        | HTML / CSS / JS   |
        +---------+---------+
                  |
             HTTP Requests
                  |
        +---------v---------+
        |   ESP32 WebServer |
        | Async Architecture|
        +---------+---------+
                  |
          FreeRTOS Timers
                  |
        +---------v---------+
        | GPIO Control Logic|
        +---------+---------+
                  |
               GPIO 2
                  |
               LED/Relay
```

---

# ⚡ Working Flow

1. ESP32 connects to Wi-Fi  
2. Hosts a local web dashboard  
3. User opens ESP32 IP in browser  
4. User can:
   - Turn GPIO ON/OFF instantly
   - Schedule future GPIO actions
   - Monitor active timer
   - Cancel running timer
5. FreeRTOS timer executes GPIO action automatically after timeout

---

# 🌐 Web Dashboard

## Manual GPIO Control

- TURN ON
- TURN OFF

## Timer Scheduler

- Select GPIO action
- Select time unit
- Enter duration
- Start timer

## Live Status

- Remaining countdown
- Current GPIO state
- Active timer status

---

# 🔥 FreeRTOS Timer Logic

The project uses FreeRTOS software timers instead of blocking delays.

```c
xTimerCreate();
xTimerStart();
xTimerChangePeriod();
```

This enables:

- Non-blocking execution
- Accurate scheduling
- Better CPU efficiency
- Real-time embedded behavior

---

# 📂 API Endpoints

| Endpoint | Method | Description |
|---|---|---|
| `/` | GET | Load Web Dashboard |
| `/control` | GET | Instant GPIO Control |
| `/led-state` | GET | Current GPIO State |
| `/set-timer` | POST | Schedule GPIO Action |
| `/timer-status` | GET | Remaining Timer Status |
| `/cancel-timer` | POST | Stop Active Timer |

---

# 🛠️ Hardware Used

- ESP32 Development Board
- LED / Relay Module
- Wi-Fi Network

---

# 🚀 Getting Started

## 1️⃣ Install Required Libraries

Install the following libraries in Arduino IDE:

- ESPAsyncWebServer
- AsyncTCP

---

## 2️⃣ Configure Wi-Fi Credentials

```c
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

---

## 3️⃣ Upload Firmware

- Select ESP32 board
- Choose correct COM port
- Upload the code

---

## 4️⃣ Open Serial Monitor

After successful connection:

```text
Wi-Fi Connected!
Access ESP32 IP Address: http://192.168.x.x
```

Open the IP address in your browser.

---

# 📸 Project Highlights

- Embedded Web Server
- Event-Driven IoT Architecture
- Real-Time Scheduling
- Browser Controlled GPIO
- Async Embedded Networking
- FreeRTOS Integration

---

# 🔮 Future Improvements

- Authentication System
- WebSocket Real-Time Updates
- RTC Clock Scheduling
- Multiple GPIO Support
- MQTT Cloud Integration
- Mobile App Interface

---

# 💡 Applications

- Smart Home Automation
- Industrial Control Systems
- IoT Relay Automation
- Remote Device Scheduling
- Wi-Fi Based Embedded Controllers

---

# 👨‍💻 Author

**Harshal**  
Embedded Systems & Firmware Developer

---

# ⭐ Support

If you like this project, give it a star ⭐ and feel free to contribute.
