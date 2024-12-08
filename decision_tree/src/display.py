import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('../dataset/accuracies.csv')

print(data.head())

plt.plot(data['depth'], data['train_accuracy'], label='Train Accuracy', marker='o')
plt.plot(data['depth'], data['test_accuracy'], label='Test Accuracy', marker='x')

plt.xlabel('Depth')
plt.ylabel('Accuracy')
plt.title('Accuracy vs Depth')
plt.legend()

plt.show()
