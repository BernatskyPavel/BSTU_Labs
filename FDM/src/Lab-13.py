import mglearn
import matplotlib.pyplot as plt

mglearn.plots.plot_scaling()
plt.show()

from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split

cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(cancer.data,
                                                    cancer.target,
                                                    random_state=1)
print(f"""Форма обучающего набора: {X_train.shape}
Форма тестирующего набора: {X_test.shape}""")

from sklearn.preprocessing import MinMaxScaler

scaler = MinMaxScaler().fit(X_train)

min_on_training = X_train.min(axis=0)
range_on_training = (X_train - min_on_training).max(axis=0)
X_train_scaled = (X_train - min_on_training) / range_on_training
print(f"""Форма преобразованного массива: {X_train_scaled.shape}
min значение признака до масштабирования:\n{X_train.min(axis=0)}
max значение признака до масштабирования:\n{X_train.max(axis=0)}
min значение признака после масштабирования:\n{X_train_scaled.min(axis=0)}
max значение признака после масштабирования:\n{X_train_scaled.max(axis=0)}""")

X_test_scaled = (X_test - min_on_training) / range_on_training
print(
    f"""min значение признака после масштабирования:\n{X_test_scaled.min(axis=0)}
max значение признака после масштабирования:\n{X_test_scaled.max(axis=0)}""")

from sklearn.datasets import make_blobs

X, _ = make_blobs(n_samples=50, centers=5, random_state=4, cluster_std=2)
X_train, X_test = train_test_split(X, random_state=5, test_size=0.1)
fig, axes = plt.subplots(1, 3, figsize=(13, 4))
axes[0].scatter(X_train[:, 0],
                X_train[:, 1],
                color=mglearn.cm2(0),
                label="Обучающий набор",
                s=60)
axes[0].scatter(
    X_test[:, 0],
    X_test[:, 1],
    marker="^",
    color=mglearn.cm2(1),
    label="Тестовый набор",
    s=60,
)
axes[0].legend(loc="upper left")
axes[0].set_title("Исходные данные")

scaler = MinMaxScaler().fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)

axes[1].scatter(
    X_train_scaled[:, 0],
    X_train_scaled[:, 1],
    color=mglearn.cm2(0),
    label="Обучающий набор",
    s=60,
)
axes[1].scatter(
    X_test_scaled[:, 0],
    X_test_scaled[:, 1],
    marker="^",
    color=mglearn.cm2(1),
    label="Тестовый набор",
    s=60,
)
axes[1].set_title("Масштабированные данные")

scaler = MinMaxScaler().fit(X_test)
X_test_scaled_badly = scaler.transform(X_test)

axes[2].scatter(
    X_train_scaled[:, 0],
    X_train_scaled[:, 1],
    color=mglearn.cm2(0),
    label="Обучающий набор",
    s=60,
)
axes[2].scatter(
    X_test_scaled_badly[:, 0],
    X_test_scaled_badly[:, 1],
    marker="^",
    color=mglearn.cm2(1),
    label="Тестовый набор",
    s=60,
)
axes[2].set_title("Неправильно масштабированные данные")

for ax in axes:
    ax.set_xlabel("Признак 0")
    ax.set_ylabel("Признак 1")

plt.show()

from sklearn.preprocessing import StandardScaler

scaler = StandardScaler()
X_scaled = scaler.fit(X).transform(X)
X_scaled_d = scaler.fit_transform(X)

from sklearn.svm import SVC

X_train, X_test, y_train, y_test = train_test_split(cancer.data,
                                                    cancer.target,
                                                    random_state=0)
svm = SVC(C=100).fit(X_train, y_train)
print(f"Правильность на тестовом наборе: {svm.score(X_test, y_test):.2f}")

scaler = MinMaxScaler().fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm.fit(X_train_scaled, y_train)
print(
    f"Правильность на масштабированном тестовом наборе: {svm.score(X_test_scaled, y_test):.2f}"
)

from sklearn.preprocessing import StandardScaler

scaler = StandardScaler().fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm.fit(X_train_scaled, y_train)
print(
    f"Правильность SVC на тестовом наборе: {svm.score(X_test_scaled, y_test):.2f}"
)
