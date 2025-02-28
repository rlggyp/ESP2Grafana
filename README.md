# ESP2Grafana  
A lightweight and efficient data monitoring system using **ESP32** as a sensor endpoint, designed for **Prometheus** and **Grafana** integration.  

## Features  
- **ESP32 as a REST API Server** – Exposes sensor data via `/metrics` endpoints.
- **Prometheus-Compatible Metrics** – Provides structured metrics for easy scraping.
- **Grafana Integration** – Visualize sensor data with custom dashboards.
- **Static IP Support** – Ensures a stable network connection.
- **Docker-Ready** – Includes `docker-compose.yml` for Prometheus and Grafana.

---

## Getting Started  

### **ESP32 Setup**  
#### **Requirements:**  
- **ESP32** (with WiFi support)  
- **PlatformIO**  

#### **Install Dependencies (PlatformIO)**  
1. Clone this repository:  
   ```sh
   git clone https://github.com/rlggyp/ESP2Grafana.git
   cd ESP2Grafana 
   ```  
2. Install PlatformIO dependencies:  
   ```sh
   pio lib install
   ```  
3. Flash the firmware to your ESP32.  

#### **ESP32 API Endpoints**  
| Endpoint       | Method | Description |
|--------------- |--------|-------------|
| `/set`         | `GET` | Set the value of humidity and temperature sensors. `/set?humidity=48` or `/set?temperature=24`|
| `/metrics`     | `GET` | Returns Prometheus-compatible data |

---

### **Setting Up Prometheus & Grafana (Docker)**  
#### **Install Docker & Docker Compose**  
Make sure you have **Docker** installed:  
```sh
docker --version
docker-compose --version
```  

#### **Start Services**  
1. Navigate to the project directory:  
   ```sh
   cd ESP2Grafana/docker
   ```  
2. Run Prometheus & Grafana using Docker Compose:  
   ```sh
   docker-compose up -d
   ```  

#### **Configuration Files**  
- **Prometheus config:** `prometheus/prometheus.yml`  
- **Grafana dashboards:** Configured manually via Grafana UI  

#### **Access Services:**  
| Service     | URL |
|------------|----------------------------|
| Prometheus | [http://localhost:9090](http://localhost:9090) |
| Grafana    | [http://localhost:3000](http://localhost:3000) |

---

## Visualizing Data in Grafana  
1. Open **Grafana** at `http://localhost:3000` (default user: `admin`, password: `admin`).  
2. Add a **new Prometheus data source** with URL:  
   ```
   http://<your_ip_address>:9090
   ```  
3. Create a dashboard and add **PromQL queries** like:  
   ```promql
   temperature
   humidity
   ```  
4. Customize panels and save your dashboard!

