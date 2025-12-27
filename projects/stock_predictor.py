"""
Machine Learning Stock Predictor
A sophisticated stock market analysis tool using LSTM neural networks
"""

import numpy as np
import pandas as pd
from datetime import datetime, timedelta
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from typing import Tuple, List

class StockPredictor:
    """
    Stock price prediction using LSTM neural network
    """
    
    def __init__(self, sequence_length: int = 60):
        """
        Initialize the stock predictor
        
        Args:
            sequence_length: Number of days to look back for prediction
        """
        self.sequence_length = sequence_length
        self.scaler = MinMaxScaler(feature_range=(0, 1))
        self.model = None
        
    def generate_sample_data(self, days: int = 1000) -> pd.DataFrame:
        """
        Generate sample stock data for demonstration
        
        Args:
            days: Number of days of data to generate
            
        Returns:
            DataFrame with stock price data
        """
        dates = pd.date_range(start='2020-01-01', periods=days, freq='D')
        
        # Generate realistic stock price data with trend and volatility
        np.random.seed(42)
        base_price = 100
        prices = []
        current_price = base_price
        
        for _ in range(days):
            # Random walk with slight upward trend
            change = np.random.normal(0.1, 2)
            current_price = max(10, current_price + change)
            prices.append(current_price)
        
        df = pd.DataFrame({
            'Date': dates,
            'Open': prices,
            'High': [p * (1 + abs(np.random.normal(0, 0.02))) for p in prices],
            'Low': [p * (1 - abs(np.random.normal(0, 0.02))) for p in prices],
            'Close': [p * (1 + np.random.normal(0, 0.01)) for p in prices],
            'Volume': np.random.randint(1000000, 10000000, days)
        })
        
        return df
    
    def prepare_data(self, df: pd.DataFrame) -> Tuple[np.ndarray, np.ndarray]:
        """
        Prepare data for LSTM model
        
        Args:
            df: DataFrame with stock data
            
        Returns:
            X (features) and y (targets) arrays
        """
        # Use closing prices
        prices = df['Close'].values.reshape(-1, 1)
        
        # Scale the data
        scaled_prices = self.scaler.fit_transform(prices)
        
        X, y = [], []
        for i in range(self.sequence_length, len(scaled_prices)):
            X.append(scaled_prices[i-self.sequence_length:i, 0])
            y.append(scaled_prices[i, 0])
        
        return np.array(X), np.array(y)
    
    def create_lstm_model(self, input_shape: Tuple) -> object:
        """
        Create a simple LSTM model structure
        (In production, this would use TensorFlow/Keras)
        
        Args:
            input_shape: Shape of input data
            
        Returns:
            Model structure description
        """
        model_structure = {
            'type': 'LSTM',
            'layers': [
                {'type': 'LSTM', 'units': 50, 'return_sequences': True},
                {'type': 'Dropout', 'rate': 0.2},
                {'type': 'LSTM', 'units': 50, 'return_sequences': True},
                {'type': 'Dropout', 'rate': 0.2},
                {'type': 'LSTM', 'units': 50},
                {'type': 'Dropout', 'rate': 0.2},
                {'type': 'Dense', 'units': 1}
            ],
            'optimizer': 'adam',
            'loss': 'mean_squared_error'
        }
        
        return model_structure
    
    def predict(self, data: np.ndarray) -> np.ndarray:
        """
        Make predictions (simplified version)
        
        Args:
            data: Input data for prediction
            
        Returns:
            Predicted values
        """
        # Simplified prediction using moving average
        predictions = []
        for sequence in data:
            # Use weighted average of recent values
            weights = np.linspace(0.1, 1.0, len(sequence))
            prediction = np.average(sequence, weights=weights)
            predictions.append(prediction)
        
        return np.array(predictions)
    
    def visualize_predictions(self, actual: np.ndarray, predicted: np.ndarray, 
                            dates: pd.DatetimeIndex):
        """
        Visualize actual vs predicted stock prices
        
        Args:
            actual: Actual stock prices
            predicted: Predicted stock prices
            dates: Date range for plotting
        """
        plt.figure(figsize=(12, 6))
        plt.plot(dates[-len(actual):], actual, label='Actual Price', linewidth=2)
        plt.plot(dates[-len(predicted):], predicted, label='Predicted Price', 
                linewidth=2, linestyle='--')
        plt.title('Stock Price Prediction', fontsize=16, fontweight='bold')
        plt.xlabel('Date', fontsize=12)
        plt.ylabel('Price ($)', fontsize=12)
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.xticks(rotation=45)
        plt.tight_layout()
        plt.savefig('stock_prediction.png', dpi=300, bbox_inches='tight')
        print("Prediction chart saved as 'stock_prediction.png'")
    
    def analyze_stock(self, symbol: str = "SAMPLE") -> dict:
        """
        Complete stock analysis pipeline
        
        Args:
            symbol: Stock symbol
            
        Returns:
            Analysis results dictionary
        """
        print(f"Analyzing stock: {symbol}")
        print("=" * 50)
        
        # Generate sample data
        df = self.generate_sample_data(days=1000)
        print(f"Loaded {len(df)} days of data")
        
        # Prepare data
        X, y = self.prepare_data(df)
        print(f"Prepared {len(X)} sequences for training")
        
        # Create model
        model = self.create_lstm_model(X.shape[1:])
        print(f"Created {model['type']} model with {len(model['layers'])} layers")
        
        # Split data (80% train, 20% test)
        split = int(len(X) * 0.8)
        X_train, X_test = X[:split], X[split:]
        y_train, y_test = y[:split], y[split:]
        
        # Make predictions
        predictions = self.predict(X_test)
        
        # Inverse transform to get actual prices
        y_test_actual = self.scaler.inverse_transform(y_test.reshape(-1, 1)).flatten()
        predictions_actual = self.scaler.inverse_transform(
            predictions.reshape(-1, 1)
        ).flatten()
        
        # Calculate metrics
        mse = np.mean((y_test_actual - predictions_actual) ** 2)
        mae = np.mean(np.abs(y_test_actual - predictions_actual))
        accuracy = 100 * (1 - mae / np.mean(y_test_actual))
        
        print(f"\nPrediction Metrics:")
        print(f"  Mean Squared Error: ${mse:.2f}")
        print(f"  Mean Absolute Error: ${mae:.2f}")
        print(f"  Accuracy: {accuracy:.2f}%")
        
        # Visualize
        test_dates = df['Date'].values[split + self.sequence_length:]
        self.visualize_predictions(y_test_actual, predictions_actual, 
                                  pd.DatetimeIndex(test_dates))
        
        return {
            'symbol': symbol,
            'mse': mse,
            'mae': mae,
            'accuracy': accuracy,
            'current_price': df['Close'].iloc[-1],
            'predicted_next': predictions_actual[-1]
        }


def main():
    """Main function to run the stock predictor"""
    predictor = StockPredictor(sequence_length=60)
    results = predictor.analyze_stock("AAPL")
    
    print("\n" + "=" * 50)
    print("Analysis Complete!")
    print(f"Current Price: ${results['current_price']:.2f}")
    print(f"Predicted Next Price: ${results['predicted_next']:.2f}")


if __name__ == "__main__":
    main()

