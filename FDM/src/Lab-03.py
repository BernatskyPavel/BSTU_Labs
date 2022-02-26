import mglearn
import matplotlib.pyplot as plt
import numpy as np
from utils.datasets import make_forge, make_wave

X, y = make_forge()
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.legend(["Класс 0", "Класс 1"], loc=4)
plt.xlabel("Первый признак")
plt.ylabel("Второй признак")
print(f"Форма массива X: {X.shape}")
plt.show()

X, y = make_wave(n_samples=40)
plt.plot(X, y, "o")
plt.ylim(-3, 3)
plt.xlabel("Признак")
plt.ylabel("Целевая переменная")
plt.show()

from sklearn.datasets import load_breast_cancer

cancer = load_breast_cancer()
print(f"""Ключи cancer():\n{cancer.keys()}
Форма массива data для набора cancer: {cancer.data.shape}
Форма массива data для каждого класса:\n{ {n: v for n, v in zip(cancer.target_names, np.bincount(cancer.target))}}"""
      )

from sklearn.datasets._base import get_data_home
from sklearn.datasets import fetch_california_housing

california = fetch_california_housing(data_home=get_data_home())
print(f"Форма массива data для набора california: {california.data.shape}")

from utils.datasets import load_extended_california

X, y = load_extended_california()

print(f"Форма массива data для набора extended california: {X.shape}")

from utils.plots import plot_knn_classification

plot_knn_classification(n_neighbors=1)
plt.show()

plot_knn_classification(n_neighbors=3)
plt.show()

from sklearn.model_selection import train_test_split

X, y = make_forge()
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

from sklearn.neighbors import KNeighborsClassifier

clf = KNeighborsClassifier(n_neighbors=3).fit(X_train, y_train)

print(f"""Прогноз на тестовом наборе: {clf.predict(X_test)}
Правильность на тестовом наборе: {clf.score(X_test, y_test):.2f}""")

fig, axes = plt.subplots(1, 3, figsize=(10, 3))
for n_neighbors, ax in zip([1, 3, 9], axes):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors).fit(X, y)
    mglearn.plots.plot_2d_separator(clf,
                                    X,
                                    fill=True,
                                    eps=0.5,
                                    ax=ax,
                                    alpha=0.4)
    mglearn.discrete_scatter(X[:, 0], X[:, 1], y, ax=ax)
    ax.set_title(f"Количество соседей:{n_neighbors}")
    ax.set_xlabel("Признак 0")
    ax.set_xlabel("Признак 1")

axes[0].legend(loc=3)
plt.show()

from sklearn.datasets import load_breast_cancer

cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(cancer.data,
                                                    cancer.target,
                                                    stratify=cancer.target,
                                                    random_state=66)

training_accuracy = []
test_accuracy = []

neighbors_settings = range(1, 11)

for n_neighbors in neighbors_settings:
    clf = KNeighborsClassifier(n_neighbors=n_neighbors)
    clf.fit(X_train, y_train)
    training_accuracy.append(clf.score(X_train, y_train))
    test_accuracy.append(clf.score(X_test, y_test))

plt.plot(neighbors_settings,
         training_accuracy,
         label="Правильность на обучающем наборе")
plt.plot(neighbors_settings,
         test_accuracy,
         label="Правильность на тестовом наборе")
plt.ylabel("Правильность")
plt.xlabel("Количество соседей")
plt.legend()
plt.show()

from mglearn.plots import plot_knn_regression

plot_knn_regression(n_neighbors=1)
plt.show()

plot_knn_regression(n_neighbors=3)
plt.show()

from sklearn.neighbors import KNeighborsRegressor

X, y = make_wave(n_samples=40)
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

reg = KNeighborsRegressor(n_neighbors=3).fit(X_train, y_train)

print(f"""Прогнозы для тестового набора:\n{reg.predict(X_test)}
"R^2 на тестовом наборе: {reg.score(X_test, y_test):.2f}""")

_, axes = plt.subplots(1, 3, figsize=(15, 4))
line = np.linspace(-3, 3, 1000).reshape(-1, 1)

for n_neighbors, ax in zip([1, 3, 9], axes):
    reg = KNeighborsRegressor(n_neighbors=n_neighbors)
    reg.fit(X_train, y_train)
    ax.plot(line, reg.predict(line))
    ax.plot(X_train, y_train, "^", c=mglearn.cm2(0), markersize=8)
    ax.plot(X_test, y_test, "v", c=mglearn.cm2(1), markersize=8)
    ax.set_title(
        f"{n_neighbors} neighbor(s)\n train score: {reg.score(X_train, y_train):.2f} test score: {reg.score(X_test, y_test):.2f}"
    )
    ax.set_xlabel("Признак")
    ax.set_ylabel("Целевая переменная")

axes[0].legend(
    ["Прогноз модели", "Обучающие данные/ответы", "Тестовые данные/ответы"],
    loc="best")
plt.show()
