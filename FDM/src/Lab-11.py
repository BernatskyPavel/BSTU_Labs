import mglearn
import matplotlib.pyplot as plt
import numpy as np

from IPython.display import display

display(mglearn.plots.plot_single_hidden_layer_graph())

line = np.linspace(-3, 3, 100)
plt.plot(line, np.tanh(line), label="tanh")
plt.plot(line, np.maximum(line, 0), label="relu")
plt.legend(loc="best")
plt.xlabel("x")
plt.ylabel("relu(x), tanh(x)")
plt.show()

mglearn.plots.plot_two_hidden_layer_graph()
plt.show()

from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.datasets import make_moons

X, y = make_moons(n_samples=100, noise=0.25, random_state=3)
X_train, X_test, y_train, y_test = train_test_split(X,
                                                    y,
                                                    stratify=y,
                                                    random_state=42)

layers = [(100, ), (10, ), (10, 10), (10, 10)]
activations = ["relu", "relu", "relu", "tanh"]

for layer, activation in zip(layers, activations):
    mlp = MLPClassifier(solver="lbfgs",
                        random_state=0,
                        max_iter=100000,
                        activation=activation,
                        hidden_layer_sizes=layer).fit(X_train, y_train)
    mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3)
    mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train)
    plt.xlabel("Признак 0")
    plt.ylabel("Признак 1")
    plt.title(f"MLPClassifier(activation: {activation}, layers: {layer})")
    plt.show()

fig, axes = plt.subplots(2, 4, figsize=(20, 8))
for axx, n_hidden_nodes in zip(axes, [10, 100]):
    for ax, alpha in zip(axx, [0.0001, 0.01, 0.1, 1]):
        mlp = MLPClassifier(
            solver="lbfgs",
            random_state=0,
            hidden_layer_sizes=[n_hidden_nodes, n_hidden_nodes],
            alpha=alpha,
            max_iter=100000).fit(X_train, y_train)
        mglearn.plots.plot_2d_separator(mlp,
                                        X_train,
                                        fill=True,
                                        alpha=0.3,
                                        ax=ax)
        mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train, ax=ax)
        ax.set_title(
            f"n_hidden=[{n_hidden_nodes}, {n_hidden_nodes}]\nalpha={alpha:.4f}"
        )
plt.show()

fig, axes = plt.subplots(2, 4, figsize=(20, 8))
for i, ax in enumerate(axes.ravel()):
    mlp = MLPClassifier(solver="lbfgs",
                        random_state=i,
                        hidden_layer_sizes=[100, 100],
                        max_iter=100000).fit(X_train, y_train)
    mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3, ax=ax)
    mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train, ax=ax)
plt.show()

from sklearn.datasets import load_breast_cancer

cancer = load_breast_cancer()
print(f"Максимальное значение характеристик:\n{cancer.data.max(axis=0)}")
X_train, X_test, y_train, y_test = train_test_split(cancer.data,
                                                    cancer.target,
                                                    random_state=0)
mlp = MLPClassifier(random_state=42, max_iter=100000).fit(X_train, y_train)
print(f"""Правильность на обучающем наборе: {mlp.score(X_train, y_train):.2f}
Правильность на тестовом наборе: {mlp.score(X_test, y_test):.2f}""")

min_on_training = X_train.min(axis=0)
range_on_training = (X_train - min_on_training).max(axis=0)
X_train_scaled = (X_train - min_on_training) / range_on_training
mean_on_training = X_train.mean(axis=0)
std_on_training = X_train.std(axis=0)
X_test_scaled = (X_test - mean_on_training) / std_on_training

mlp.fit(X_train_scaled, y_train)
print(
    f"""Правильность на масштабированном обучающем наборе: {mlp.score(X_train_scaled, y_train):.3f}
    Правильность на масштабированном тестовом наборе: {mlp.score(X_test_scaled, y_test):.3f}"""
)

mlp = MLPClassifier(max_iter=1000, random_state=0).fit(X_train_scaled, y_train)
print(
    f"""Правильность на масштабированном обучающем наборе: {mlp.score(X_train_scaled, y_train):.3f}
    Правильность на масштабированном тестовом наборе: {mlp.score(X_test_scaled, y_test):.3f}"""
)

mlp = MLPClassifier(max_iter=1000, alpha=1,
                    random_state=0).fit(X_train_scaled, y_train)
print(
    f"""Правильность на масштабированном обучающем наборе: {mlp.score(X_train_scaled, y_train):.3f}
    Правильность на масштабированном тестовом наборе: {mlp.score(X_test_scaled, y_test):.3f}"""
)

plt.figure(figsize=(20, 5))
plt.imshow(mlp.coefs_[0], interpolation="none", cmap="viridis")
plt.yticks(range(30), cancer.feature_names)
plt.xlabel("Столбцы матрицы весов")
plt.ylabel("Входная характеристика")
plt.colorbar()
plt.show()
