# Portfolio Projects

This directory contains working project implementations demonstrating proficiency in C++, Python, and JavaScript.

## C++ Projects

### 1. High-Performance Game Engine
- **Files**: `game_engine.h`, `game_engine.cpp`, `game_engine_demo.html`
- **Description**: Entity-Component-System architecture game engine
- **Features**:
  - Component-based architecture
  - Transform and Render components
  - Scene management
  - Memory-efficient design
  - Interactive web demo

**To compile and run:**
```bash
g++ -std=c++17 game_engine.cpp -o game_engine
./game_engine
```

**To view the interactive demo:**
Open `game_engine_demo.html` in a web browser.

### 2. Ray Tracing Engine
- **Files**: `ray_tracing_engine.h`, `ray_tracing_engine.cpp`, `ray_tracing_demo.html`
- **Description**: Physically-based ray tracing engine with real-time 3D rendering
- **Features**:
  - Sphere intersection algorithms
  - Material systems
  - Advanced lighting calculations
  - Real-time camera controls
  - Interactive web demo

**To compile and run:**
```bash
g++ -std=c++20 ray_tracing_engine.cpp -o ray_tracing
./ray_tracing
```

**To view the interactive demo:**
Open `ray_tracing_demo.html` in a web browser.

## Python Projects

### 1. Machine Learning Stock Predictor
- **Files**: `stock_predictor.py`, `stock_predictor_demo.html`, `requirements.txt`
- **Description**: LSTM-based stock price prediction tool with real-time data
- **Features**:
  - Real-time stock data from Yahoo Finance API
  - Data preprocessing
  - LSTM neural network architecture
  - Interactive visualization with Chart.js
  - Performance metrics
  - 6 months of historical data

**To run:**
```bash
pip install -r requirements.txt
python stock_predictor.py
```

**To view the interactive demo:**
Open `stock_predictor_demo.html` in a web browser.

### 2. AI Image Classifier
- **Files**: `ai_image_classifier.py`, `ai_image_classifier_demo.html`
- **Description**: Deep learning image classification system using CNN
- **Features**:
  - Convolutional Neural Network architecture
  - 10 category classification (CIFAR-10 classes)
  - Pixel-based image analysis
  - Confidence scoring
  - Interactive web demo with drag-and-drop

**To run:**
```bash
pip install -r requirements.txt
python ai_image_classifier.py
```

**To view the interactive demo:**
Open `ai_image_classifier_demo.html` in a web browser.

## JavaScript Projects

### 1. Real-Time Collaborative Platform
- **Files**: `collaborative_platform.html`
- **Description**: Real-time collaborative editor with live sync
- **Features**:
  - Real-time text editing
  - User presence indicators
  - Live chat functionality
  - LocalStorage persistence
  - Auto-save functionality
  - Modern responsive UI

**To view:**
Simply open `collaborative_platform.html` in a web browser.

### 2. E-Commerce Dashboard
- **Files**: `ecommerce_dashboard.html`
- **Description**: Fully functional admin dashboard for e-commerce management
- **Features**:
  - Sales analytics with Chart.js
  - Real-time statistics
  - Full CRUD operations (Create, Read, Update, Delete)
  - Data import/export (CSV/JSON)
  - Multi-section navigation (Dashboard, Products, Orders, Customers, Analytics, Settings)
  - LocalStorage persistence
  - Dynamic charts and statistics
  - Responsive design

**To view:**
Simply open `ecommerce_dashboard.html` in a web browser.

## Project Structure

```
projects/
├── game_engine.h
├── game_engine.cpp
├── game_engine_demo.html
├── ray_tracing_engine.h
├── ray_tracing_engine.cpp
├── ray_tracing_demo.html
├── stock_predictor.py
├── stock_predictor_demo.html
├── ai_image_classifier.py
├── ai_image_classifier_demo.html
├── collaborative_platform.html
├── ecommerce_dashboard.html
├── requirements.txt
└── README.md
```

## Notes

- All projects are fully functional and demonstrate real-world programming concepts
- C++ projects use modern C++17/C++20 features
- Python projects include proper error handling and documentation
- JavaScript projects are self-contained and work in modern browsers
- All code follows best practices and includes comments

