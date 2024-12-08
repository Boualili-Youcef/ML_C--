import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('../dataset/accuracies.csv')

print(data.head())
plt.figure(figsize=(10, 6))

plt.plot(data['depth'], data['train_accuracy'], label='Train Accuracy', color="blue", marker='o')
plt.plot(data['depth'], data['test_accuracy'], label='Test Accuracy', color="red", marker='x')

plt.xlabel('Depth')
plt.ylabel('Accuracy')
plt.xticks(ticks=[x for x in range(1, len(data['train_accuracy']) + 1, 1)]) 
plt.title('Accuracy vs Depth')
plt.legend()
plt.grid()

plt.show()


