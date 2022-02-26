import mglearn
import matplotlib.pyplot as plt
import numpy as np

from sklearn.datasets import make_blobs

X, y = make_blobs(random_state=42)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.legend(["Класс 0", "Класс 1", "Класс 2"])
plt.show()

from sklearn.svm import LinearSVC

linear_svm = LinearSVC().fit(X, y)
print(f"""Форма коэффициента: {linear_svm.coef_.shape}
Форма константы: {linear_svm.intercept_.shape}""")

mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
line = np.linspace(-15, 15)

for coef, intercept, color in zip(linear_svm.coef_, linear_svm.intercept_,
                                  ["b", "r", "g"]):
    plt.plot(line, -(line * coef[0] + intercept) / coef[1], c=color)

plt.ylim(-10, 15)
plt.xlim(-10, 8)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")

plt.legend(
    [
        "Класс 0",
        "Класс 1",
        "Класс 2",
        "Линия класса 0",
        "Линия класса 1",
        "Линия класса 2",
    ],
    loc="best",
)
plt.show()

mglearn.plots.plot_2d_classification(linear_svm, X, fill=True, alpha=0.7)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
line = np.linspace(-15, 15)

for coef, intercept, color in zip(linear_svm.coef_, linear_svm.intercept_,
                                  ["b", "r", "g"]):
    plt.plot(line, -(line * coef[0] + intercept) / coef[1], c=color)

plt.xlabel("Признак 0")
plt.ylabel("Признак 1")

plt.legend(
    [
        "Класс 0",
        "Класс 1",
        "Класс 2",
        "Линия класса 0",
        "Линия класса 1",
        "Линия класса 2",
    ],
    loc="best",
)
plt.show()
