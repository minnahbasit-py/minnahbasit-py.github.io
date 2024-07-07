import tensorflow as tf
from tensorflow.keras import datasets, layers, models
import matplotlib.pyplot as plt

# Load and preprocess the dataset
# CIFAR-10 is a dataset with 60,000 32x32 color images in 10 classes, with 6,000 images per class
(train_images, train_labels), (test_images, test_labels) = datasets.cifar10.load_data()
train_images, test_images = train_images / 255.0, test_images / 255.0  # Normalize the images to [0, 1] range

# Define class names for the CIFAR-10 dataset
class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']

# Build the model using a Sequential API
model = models.Sequential()

# Add layers to the model
model.add(layers.Input(shape=(32, 32, 3)))  # Input layer, expects 32x32 color images
model.add(layers.Conv2D(32, (3, 3), activation='relu'))  # Convolutional layer with 32 filters and 3x3 kernel
model.add(layers.MaxPooling2D((2, 2)))  # Max pooling layer to reduce the spatial dimensions
model.add(layers.Flatten())  # Flatten the 3D output to 1D for the dense layer
model.add(layers.Dense(64, activation='relu'))  # Fully connected layer with 64 units and ReLU activation
model.add(layers.Dense(10))  # Output layer with 10 units (one for each class)

# Compile the model
model.compile(optimizer='adam',  # Adam optimizer
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),  # Loss function for classification
              metrics=['accuracy'])  # Metrics to evaluate during training and testing

# Data augmentation to improve model generalization
from tensorflow.keras.preprocessing.image import ImageDataGenerator

datagen = ImageDataGenerator(
    rotation_range=10,  # Randomly rotate images by 10 degrees
    width_shift_range=0.1,  # Randomly shift images horizontally by 10%
    height_shift_range=0.1,  # Randomly shift images vertically by 10%
    horizontal_flip=True  # Randomly flip images horizontally
)
datagen.fit(train_images)  # Fit the generator to our training data

# Train the model
history = model.fit(datagen.flow(train_images, train_labels, batch_size=64),  # Use augmented data
                    steps_per_epoch=len(train_images) // 64,  # Number of batches per epoch
                    epochs=10,  # Number of epochs
                    validation_data=(test_images, test_labels))  # Validation data

# Evaluate the model on test data
test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=2)
print(f"Test accuracy: {test_acc}")  # Print the test accuracy

# Plot training & validation accuracy and loss values
plt.figure(figsize=(12, 4))

# Plot accuracy
plt.subplot(1, 2, 1)
plt.plot(history.history['accuracy'], label='accuracy')
plt.plot(history.history['val_accuracy'], label='val_accuracy')
plt.xlabel('Epoch')  # X-axis label
plt.ylabel('Accuracy')  # Y-axis label
plt.ylim([0, 1])  # Set y-axis range
plt.legend(loc='lower right')  # Add legend in the lower right corner

# Plot loss
plt.subplot(1, 2, 2)
plt.plot(history.history['loss'], label='loss')
plt.plot(history.history['val_loss'], label='val_loss')
plt.xlabel('Epoch')  # X-axis label
plt.ylabel('Loss')  # Y-axis label
plt.ylim([0, 1])  # Set y-axis range
plt.legend(loc='upper right')  # Add legend in the upper right corner

# Show the plots
plt.show()
