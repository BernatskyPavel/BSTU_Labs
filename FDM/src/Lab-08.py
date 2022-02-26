from distutils.util import change_root
import mglearn
import matplotlib.pyplot as plt
import numpy as np
import os

os.chdir("./src/Lab-08")

X = np.array([[0, 1, 0, 1], [1, 0, 1, 1], [0, 0, 0, 1], [1, 0, 1, 0]])
y = np.array([0, 1, 0, 1])

counts = {}
for label in np.unique(y):
    counts[label] = X[y == label].sum(axis=0)

print(f"Частоты признаков:\n{counts}")

mglearn.plots.plot_animal_tree()
plt.show()

mglearn.plots.plot_tree_progressive()
plt.show()

from sklearn.tree import DecisionTreeClassifier
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split

cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(cancer.data,
                                                    cancer.target,
                                                    stratify=cancer.target,
                                                    random_state=42)

tree = DecisionTreeClassifier(random_state=0).fit(X_train, y_train)
print(f"""Правильность на обучающем наборе: {tree.score(X_train, y_train):.3f}
Правильность на тестовом наборе: {tree.score(X_test, y_test):.3f}""")

tree = DecisionTreeClassifier(max_depth=4,
                              random_state=0).fit(X_train, y_train)
print(f"""Правильность на обучающем наборе: {tree.score(X_train, y_train):.3f}
Правильность на тестовом наборе: {tree.score(X_test, y_test):.3f}""")

from sklearn.tree import export_graphviz

export_graphviz(
    tree,
    out_file="tree.dot",
    class_names=["malignant", "benign"],
    feature_names=cancer.feature_names,
    impurity=False,
    filled=True,
)

import graphviz

with open("tree.dot") as f:
    dot_graph = f.read()
graphviz.Source(dot_graph)

clf = DecisionTreeClassifier(max_depth=4, random_state=0).fit(X_train, y_train)

import pydotplus

dot_data = export_graphviz(clf, out_file=None)
pydotplus.graph_from_dot_data(dot_data).write_pdf("cancer.pdf")

from IPython.display import Image

dot_data = export_graphviz(
    clf,
    out_file=None,
    feature_names=cancer.feature_names,
    class_names=cancer.target_names,
    filled=True,
    rounded=True,
    special_characters=True,
)
graph = pydotplus.graph_from_dot_data(dot_data)
Image(graph.create_png())

tree = DecisionTreeClassifier().fit(X_train, y_train)
print(f"Важности признаков:\n{tree.feature_importances_}")


def plot_feature_cancer(model):
    n_features = cancer.data.shape[1]
    plt.barh(range(n_features), model.feature_importances_, align="center")
    plt.yticks(np.arange(n_features), cancer.feature_names)
    plt.xlabel("Важность признака")
    plt.ylabel("Признак")
    plt.show()


plot_feature_cancer(tree)

tree = mglearn.plots.plot_tree_not_monotone()
plt.show()

from IPython.display import display

display(tree)

import pandas as pd

ram_prices = pd.read_csv("ram_price.csv")

plt.semilogy(ram_prices.date, ram_prices.price)
plt.xlabel("Год")
plt.ylabel("Цена $/Мбайт")
plt.show()

from sklearn.tree import DecisionTreeRegressor

data_train = ram_prices[ram_prices.date < 2000]
data_test = ram_prices[ram_prices.date >= 2000]
y_train = np.log(data_train.price)
X_train = np.array(data_train.date)[:, np.newaxis]

print(f"X:\n{X_train}\ny:\n{y_train}")

tree = DecisionTreeRegressor().fit(X_train, y_train)
from sklearn.linear_model import LinearRegression

linear_reg = LinearRegression().fit(X_train, y_train)

X_all = np.array(ram_prices.date)[:, np.newaxis]

pred_tree = tree.predict(X_all)
pred_lr = linear_reg.predict(X_all)

price_tree = np.exp(pred_tree)
price_lr = np.exp(pred_lr)

plt.semilogy(data_train.date, data_train.price, label="Обучающие данные")
plt.semilogy(data_test.date, data_test.price, label="Тестовые данные")
plt.semilogy(ram_prices.date, price_tree, label="Прогнозы дерева")
plt.semilogy(ram_prices.date, price_lr, label="Прогнозы линейной регрессии")
plt.legend()
plt.show()
