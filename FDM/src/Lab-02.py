from operator import imod
import pandas as pds
import mglearn
import matplotlib.pyplot as plt
import numpy as np

from sklearn.datasets import load_iris

iris_dataset = load_iris()

from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(iris_dataset["data"],
                                                    iris_dataset["target"],
                                                    random_state=0)
print(f"""Форма массива X_train: {X_train.shape}
Форма массива y_train: {y_train.shape}
Форма массива X_test: {X_test.shape}
Форма массива y_test: {y_test.shape}""")
iris_dataframe = pds.DataFrame(X_train, columns=iris_dataset.feature_names)

from pandas.plotting import scatter_matrix

grr = scatter_matrix(
    iris_dataframe,
    c=y_train,
    figsize=(15, 15),
    marker="o",
    hist_kwds={"bins": 20},
    s=60,
    alpha=0.8,
    cmap=mglearn.cm3,
)

plt.show()

from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier(n_neighbors=1).fit(X_train, y_train)

X_new = np.array([[5, 2.9, 1, 0.2]])
print(f"Форма массива X_new: {X_new.shape}")

prediction = knn.predict(X_new)
print(f"""Прогноз: {prediction}
Спрогнозированная метка: {iris_dataset['target_names'][prediction]}""")

y_pred = knn.predict(X_test)
print(f"""Прогноз для тестового набора: {y_pred}
Правильность на тестовом наборе: {np.mean(y_pred==y_test):.2f}
Правильность на тестовом наборе: {knn.score(X_test, y_test):.2f}""")
