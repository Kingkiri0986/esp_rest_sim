# ESP REST SIM

A lightweight REST API simulator for ESP8266/ESP32 microcontrollers. Perfect for prototyping IoT applications, testing REST clients, or learning embedded systems development without requiring complex backend infrastructure.

## 🚀 Features

- **RESTful API Server** - Full HTTP REST API implementation
- **Simulated Sensors** - Generate realistic temperature, humidity, and pressure data
- **Device Control** - Toggle GPIOs, LEDs, and relays via API calls
- **WiFi Management** - Easy network configuration
- **JSON Responses** - Standard JSON format for all endpoints
- **CORS Enabled** - Works with web applications and AJAX requests
- **Low Memory** - Optimized for resource-constrained devices
- **Real-time Monitoring** - Device health and status endpoints

## 📋 Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Configuration](#configuration)
- [API Documentation](#api-documentation)
- [Usage Examples](#usage-examples)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## 🔧 Hardware Requirements

- **ESP8266** (NodeMCU, Wemos D1 Mini, ESP-01, etc.) or **ESP32**
- USB cable (Micro-USB or USB-C depending on board)
- WiFi router/access point

## 💾 Software Requirements

- **Arduino IDE** (1.8.19 or later) or **PlatformIO**
- **Board Support Packages:**
  - ESP8266: https://arduino.esp8266.com/stable/package_esp8266com_index.json
  - ESP32: https://espressif.github.io/arduino-esp32/package_esp32_index.json
- **Libraries:**
  - ArduinoJson (6.21.0 or later)
  - ESP8266WiFi / WiFi (included with board package)
  - ESP8266WebServer / WebServer (included with board package)

## 📦 Installation

### Method 1: Arduino IDE

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/esp_rest_sim.git
   cd esp_rest_sim
   ```

2. **Install ESP board support:**
   - Open Arduino IDE
   - Go to File → Preferences
   - Add board manager URL (see Software Requirements)
   - Go to Tools → Board → Boards Manager
   - Search and install "ESP8266" or "ESP32"

3. **Install ArduinoJson library:**
   - Go to Sketch → Include Library → Manage Libraries
   - Search "ArduinoJson"
   - Install version 6.21.0 or later

4. **Open the project:**
   - Open `esp_rest_sim.ino` in Arduino IDE

5. **Upload to device:**
   - Select board: Tools → Board → (your ESP board)
   - Select port: Tools → Port → (your COM/USB port)
   - Click Upload button

### Method 2: PlatformIO

1. **Clone and open project:**
   ```bash
   git clone https://github.com/yourusername/esp_rest_sim.git
   cd esp_rest_sim
   code .
   ```

2. **Build and upload:**
   ```bash
   pio run --target upload
   pio device monitor
   ```

## ⚙️ Configuration

### WiFi Settings

Edit the configuration in `esp_rest_sim.ino`:

```cpp
// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Server port (default: 80)
const int serverPort = 80;

// Device name
const char* deviceName = "ESP-REST-SIM";
```

### Pin Configuration

```cpp
// GPIO pins
const int LED_PIN = 2;        // Built-in LED (GPIO2 on most boards)
const int RELAY_PIN = 5;      // External relay
```

## 📚 API Documentation

Base URL: `http://<ESP_IP_ADDRESS>`

### Endpoints

#### 1. Get Device Status

**GET** `/api/status`

Returns device information and health metrics.

**Response:**
```json
{
  "device": "ESP-REST-SIM",
  "status": "online",
  "uptime": 3600,
  "freeHeap": 45120,
  "chipId": "A4CF12F1",
  "wifiRssi": -65,
  "ipAddress": "192.168.1.100"
}
```

#### 2. Get Sensor Data

**GET** `/api/sensors`

Returns simulated sensor readings.

**Response:**
```json
{
  "temperature": 23.5,
  "humidity": 55.2,
  "pressure": 1013.25,
  "timestamp": 1609459200
}
```

#### 3. Control Device

**POST** `/api/control`

Control GPIO outputs (LED, relays, etc.).

**Request Body:**
```json
{
  "device": "led",
  "state": "on"
}
```

**Valid devices:** `led`, `relay`, `gpio`  
**Valid states:** `on`, `off`, `toggle`

**Response:**
```json
{
  "success": true,
  "device": "led",
  "state": "on",
  "message": "Device controlled successfully"
}
```

#### 4. Get Configuration

**GET** `/api/config`

Retrieve current device configuration.

**Response:**
```json
{
  "deviceName": "ESP-REST-SIM",
  "sensorInterval": 5000,
  "ledEnabled": true,
  "version": "1.0.0"
}
```

#### 5. Update Configuration

**POST** `/api/config`

Update device configuration.

**Request Body:**
```json
{
  "sensorInterval": 10000,
  "ledEnabled": false
}
```

**Response:**
```json
{
  "success": true,
  "message": "Configuration updated",
  "config": {
    "sensorInterval": 10000,
    "ledEnabled": false
  }
}
```

#### 6. Reboot Device

**POST** `/api/reboot`

Restart the ESP device.

**Response:**
```json
{
  "success": true,
  "message": "Device rebooting..."
}
```

## 💡 Usage Examples

### curl

```bash
# Get device status
curl http://192.168.1.100/api/status

# Get sensor data
curl http://192.168.1.100/api/sensors

# Turn LED on
curl -X POST http://192.168.1.100/api/control \
  -H "Content-Type: application/json" \
  -d '{"device":"led","state":"on"}'

# Update configuration
curl -X POST http://192.168.1.100/api/config \
  -H "Content-Type: application/json" \
  -d '{"sensorInterval":15000}'
```

### Python

```python
import requests
import json

ESP_IP = "192.168.1.100"
BASE_URL = f"http://{ESP_IP}/api"

# Get status
response = requests.get(f"{BASE_URL}/status")
print(json.dumps(response.json(), indent=2))

# Get sensor data
sensors = requests.get(f"{BASE_URL}/sensors")
print(f"Temperature: {sensors.json()['temperature']}°C")

# Control LED
control_data = {
    "device": "led",
    "state": "on"
}
response = requests.post(f"{BASE_URL}/control", json=control_data)
print(response.json())
```

### JavaScript (Fetch API)

```javascript
const ESP_IP = "192.168.1.100";
const BASE_URL = `http://${ESP_IP}/api`;

// Get status
async function getStatus() {
  const response = await fetch(`${BASE_URL}/status`);
  const data = await response.json();
  console.log(data);
}

// Control device
async function controlLED(state) {
  const response = await fetch(`${BASE_URL}/control`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({
      device: 'led',
      state: state
    })
  });
  const data = await response.json();
  console.log(data);
}

// Get sensors with auto-refresh
async function monitorSensors() {
  setInterval(async () => {
    const response = await fetch(`${BASE_URL}/sensors`);
    const data = await response.json();
    console.log(`Temp: ${data.temperature}°C, Humidity: ${data.humidity}%`);
  }, 5000);
}

getStatus();
controlLED('on');
monitorSensors();
```

### Node.js

```javascript
const axios = require('axios');

const ESP_IP = '192.168.1.100';
const BASE_URL = `http://${ESP_IP}/api`;

// Get all sensor data
axios.get(`${BASE_URL}/sensors`)
  .then(response => {
    console.log('Sensor Data:', response.data);
  })
  .catch(error => {
    console.error('Error:', error.message);
  });

// Control relay
axios.post(`${BASE_URL}/control`, {
  device: 'relay',
  state: 'toggle'
})
  .then(response => {
    console.log('Control Response:', response.data);
  });
```

## 🔍 Troubleshooting

### Device not connecting to WiFi

- Verify SSID and password are correct
- Check if WiFi network is 2.4GHz (ESP8266 doesn't support 5GHz)
- Ensure router is not using MAC filtering
- Check serial monitor for connection status

### Cannot access API endpoints

- Verify ESP IP address in serial monitor
- Check if firewall is blocking port 80
- Try pinging the device: `ping <ESP_IP>`
- Ensure device and client are on same network

### Upload errors

- Select correct board and port
- Press FLASH/BOOT button during upload (some boards)
- Reduce upload speed: Tools → Upload Speed → 115200
- Try different USB cable or port

### Memory issues

- Reduce JSON buffer sizes in code
- Disable serial debugging in production
- Use `F()` macro for string literals

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Commit your changes: `git commit -m 'Add amazing feature'`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- ESP8266/ESP32 Community
- Arduino Community
- ArduinoJson library by Benoit Blanchon

## 📞 Support

- **Issues:** [GitHub Issues](https://github.com/Kingkiri0986/esp_rest_sim/issues)
- **Discussions:** [GitHub Discussions](https://github.com/Kingkiri0986/esp_rest_sim/discussions)
- **Email:** paramtap0809@gmail.com

---

**Made with ❤️ for the IoT community**