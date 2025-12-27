"""
AI Image Classifier
A deep learning image classification system using Convolutional Neural Networks
"""

import numpy as np
from typing import List, Tuple, Dict
from dataclasses import dataclass
from datetime import datetime
import json

@dataclass
class Prediction:
    """Prediction result"""
    class_name: str
    confidence: float
    timestamp: str

class ImagePreprocessor:
    """Image preprocessing for neural network input"""
    
    @staticmethod
    def normalize(image: np.ndarray) -> np.ndarray:
        """Normalize image to [0, 1] range"""
        return image.astype(np.float32) / 255.0
    
    @staticmethod
    def resize(image: np.ndarray, size: Tuple[int, int]) -> np.ndarray:
        """Resize image to target size"""
        # Simplified resize (in production, use proper interpolation)
        return np.resize(image, (*size, image.shape[2] if len(image.shape) > 2 else 1))
    
    @staticmethod
    def preprocess(image: np.ndarray, target_size: Tuple[int, int] = (224, 224)) -> np.ndarray:
        """Full preprocessing pipeline"""
        processed = ImagePreprocessor.resize(image, target_size)
        processed = ImagePreprocessor.normalize(processed)
        return processed

class CNNLayer:
    """Convolutional Neural Network Layer"""
    
    def __init__(self, filters: int, kernel_size: int, activation: str = 'relu'):
        self.filters = filters
        self.kernel_size = kernel_size
        self.activation = activation
        self.weights = None
        self.bias = None
        
    def forward(self, x: np.ndarray) -> np.ndarray:
        """Forward pass through layer"""
        # Simplified convolution (in production, use proper conv2d)
        if self.weights is None:
            self.weights = np.random.randn(self.filters, x.shape[-1], 
                                         self.kernel_size, self.kernel_size) * 0.1
            self.bias = np.zeros(self.filters)
        
        # Simplified convolution operation
        output = np.zeros((*x.shape[:-1], self.filters))
        for i in range(self.filters):
            output[..., i] = np.sum(x, axis=-1) * 0.1 + self.bias[i]
        
        if self.activation == 'relu':
            output = np.maximum(0, output)
        elif self.activation == 'softmax':
            exp = np.exp(output - np.max(output, axis=-1, keepdims=True))
            output = exp / np.sum(exp, axis=-1, keepdims=True)
        
        return output

class AIImageClassifier:
    """AI Image Classifier using CNN"""
    
    def __init__(self, num_classes: int = 10):
        self.num_classes = num_classes
        self.classes = [
            'Airplane', 'Automobile', 'Bird', 'Cat', 'Deer',
            'Dog', 'Frog', 'Horse', 'Ship', 'Truck'
        ]
        self.preprocessor = ImagePreprocessor()
        self.model = self._build_model()
        self.training_history = []
        
    def _build_model(self) -> List[CNNLayer]:
        """Build CNN model architecture"""
        return [
            CNNLayer(filters=32, kernel_size=3, activation='relu'),
            CNNLayer(filters=64, kernel_size=3, activation='relu'),
            CNNLayer(filters=128, kernel_size=3, activation='relu'),
            CNNLayer(filters=self.num_classes, kernel_size=1, activation='softmax')
        ]
    
    def predict(self, image: np.ndarray) -> Prediction:
        """Predict class for an image"""
        # Preprocess image
        processed = self.preprocessor.preprocess(image)
        
        # Forward pass through model
        x = processed
        for layer in self.model:
            x = layer.forward(x)
        
        # Get predictions
        predictions = x.flatten() if x.ndim > 1 else x
        predictions = predictions[:self.num_classes]
        
        # Get top prediction
        class_idx = np.argmax(predictions)
        confidence = float(predictions[class_idx])
        
        return Prediction(
            class_name=self.classes[class_idx] if class_idx < len(self.classes) else 'Unknown',
            confidence=confidence,
            timestamp=datetime.now().isoformat()
        )
    
    def predict_batch(self, images: List[np.ndarray]) -> List[Prediction]:
        """Predict classes for multiple images"""
        return [self.predict(img) for img in images]
    
    def get_top_predictions(self, image: np.ndarray, top_k: int = 5) -> List[Prediction]:
        """Get top K predictions"""
        processed = self.preprocessor.preprocess(image)
        
        x = processed
        for layer in self.model:
            x = layer.forward(x)
        
        predictions = x.flatten() if x.ndim > 1 else x
        predictions = predictions[:self.num_classes]
        
        # Get top K indices
        top_indices = np.argsort(predictions)[-top_k:][::-1]
        
        results = []
        for idx in top_indices:
            if idx < len(self.classes):
                results.append(Prediction(
                    class_name=self.classes[idx],
                    confidence=float(predictions[idx]),
                    timestamp=datetime.now().isoformat()
                ))
        
        return results
    
    def analyze_image(self, image: np.ndarray) -> Dict:
        """Complete image analysis"""
        top_predictions = self.get_top_predictions(image, top_k=3)
        
        return {
            'primary_prediction': {
                'class': top_predictions[0].class_name,
                'confidence': top_predictions[0].confidence
            },
            'all_predictions': [
                {'class': p.class_name, 'confidence': p.confidence}
                for p in top_predictions
            ],
            'model_info': {
                'num_classes': self.num_classes,
                'architecture': 'CNN',
                'layers': len(self.model)
            },
            'timestamp': datetime.now().isoformat()
        }

def generate_sample_image(shape: Tuple[int, int, int] = (224, 224, 3)) -> np.ndarray:
    """Generate a sample image for testing"""
    return np.random.randint(0, 255, shape, dtype=np.uint8)

def main():
    """Main function to demonstrate the AI Image Classifier"""
    print("AI Image Classifier")
    print("=" * 50)
    
    # Initialize classifier
    classifier = AIImageClassifier(num_classes=10)
    print(f"Initialized classifier with {classifier.num_classes} classes")
    print(f"Classes: {', '.join(classifier.classes)}\n")
    
    # Generate sample images
    print("Generating sample images...")
    sample_images = [generate_sample_image() for _ in range(3)]
    
    # Make predictions
    print("\nMaking predictions...")
    for i, image in enumerate(sample_images, 1):
        print(f"\nImage {i}:")
        analysis = classifier.analyze_image(image)
        
        print(f"  Primary Prediction: {analysis['primary_prediction']['class']}")
        print(f"  Confidence: {analysis['primary_prediction']['confidence']:.2%}")
        print(f"  Top 3 Predictions:")
        for pred in analysis['all_predictions']:
            print(f"    - {pred['class']}: {pred['confidence']:.2%}")
    
    print("\n" + "=" * 50)
    print("AI Image Classifier Demo Complete!")
    print("\nFeatures:")
    print("  - Convolutional Neural Network (CNN)")
    print("  - Image preprocessing pipeline")
    print("  - Multi-class classification")
    print("  - Confidence scoring")
    print("  - Batch prediction support")

if __name__ == "__main__":
    main()

