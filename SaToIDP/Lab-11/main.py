import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mglearn

from sklearn.datasets import load_breast_cancer
from sklearn.preprocessing import StandardScaler

cancer = load_breast_cancer()
X = cancer.data
y = cancer.target
X_scaled = StandardScaler().fit_transform(X, y)

print(f"Dataset shape: {X.shape}\n"
      f"Target shape: {y.shape}")

from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)

tree_clf = DecisionTreeClassifier(max_depth=5,
                                  max_leaf_nodes=5,
                                  random_state=42).fit(X_train, y_train)

print(f"Tree train score: {tree_clf.score(X_train, y_train)}\n"
      f"Tree test score: {tree_clf.score(X_test, y_test)}")

import sklearn.decomposition as decomposition

pca = decomposition.PCA().fit(X_scaled)
plt.figure(figsize=(10, 7))

plt.plot(np.cumsum(pca.explained_variance_ratio_), color='b', lw=2)
plt.xlabel('Number of components')
plt.ylabel('Total explained variance')
plt.xlim(0, 30)
plt.yticks(np.arange(0, 1.1, 0.1))
plt.axhline(0.95, c='r')
plt.show()

pca = decomposition.PCA(n_components=9)
X_centered = X - X.mean(axis=0)
pca.fit(X_centered)
X_pca = pca.transform(X_centered)

X_train, X_test, y_train, y_test = train_test_split(X_pca,
                                                    y,
                                                    test_size=0.3,
                                                    stratify=y,
                                                    random_state=42)

tree_clf = DecisionTreeClassifier(max_depth=5,
                                  max_leaf_nodes=5,
                                  random_state=42).fit(X_train, y_train)

print(f"Tree train score: {tree_clf.score(X_train, y_train)}\n"
      f"Tree test score: {tree_clf.score(X_test, y_test)}")

from sklearn.feature_selection import VarianceThreshold

cancer = load_breast_cancer()
X = cancer.data
y = cancer.target
cancer1 = VarianceThreshold(threshold=0.1).fit_transform(X, y)

print(f"Dataset shape: {X.shape}\n"
      f"New dataset shape: {cancer1.shape}\n"
      f"Target shape: {y.shape}")

X_train, X_test, y_train, y_test = train_test_split(cancer1,
                                                    y,
                                                    random_state=42)

tree_clf = DecisionTreeClassifier(max_depth=5,
                                  max_leaf_nodes=5,
                                  random_state=42).fit(X_train, y_train)

print(f"Tree train score: {tree_clf.score(X_train, y_train)}\n"
      f"Tree test score: {tree_clf.score(X_test, y_test)}")