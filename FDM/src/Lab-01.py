import pandas as pds
import mglearn
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris

iris_dataset = load_iris()

print(f"""Ключи iris_dataset: \n{iris_dataset.keys()}
iris_dataset["DESCR"][:193]\n...
Название ответов: {iris_dataset['target_names']}
Название признаков: {iris_dataset['feature_names']}
Тип массива data: {type(iris_dataset['data'])}
Форма массива data: {iris_dataset['data'].shape}
Первые пять строк массива data:\n{iris_dataset['data'][:5]}
Тип массива target: {type(iris_dataset['target'])}
Форма массива target: {iris_dataset['target'].shape}
Ответы:\n{iris_dataset['target']}""")

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
