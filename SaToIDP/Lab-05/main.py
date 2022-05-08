import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

titanic = pd.read_csv('Lab-05/titanic_clear.csv')
Y = titanic['Survived'].map({0: 'Died', 1: 'Survived'}).astype('string')
X = titanic.drop(['Survived', 'Unnamed: 0'], axis=1)

print(X.head())

from sklearn.model_selection import train_test_split, cross_val_score

X_train, X_test, y_train, y_test = train_test_split(X,
                                                    Y,
                                                    test_size=0.3,
                                                    random_state=17)
print(f"Inputs X (train/test): {X_train.shape}, {X_test.shape}\n"
      f"Inputs Y (train/test): {y_train.shape}, {y_test.shape}")

from sklearn.tree import DecisionTreeClassifier, plot_tree

clf = DecisionTreeClassifier(max_depth=4, random_state=17)

cv_score = cross_val_score(clf, X_train, y_train, cv=5)
print(f"DTC score: {cv_score}\n"
      f"DTC mean score: {np.mean(cv_score)}")

import time as t
from sklearn.model_selection import GridSearchCV

tree_params = {
    'max_depth': np.arange(1, 11),
    'max_features': [0.5, 0.6, 0.7, 0.8, 0.9, 1]
}
tree_grid = GridSearchCV(clf, tree_params, cv=5, n_jobs=-1)
tgf = tree_grid.fit(X_train, y_train)

print(f"TGF: {tgf}\n"
      f"-----Best decision tree parameters-----\n"
      f"{tree_grid.best_params_}\n"
      f"-----Best decision tree score-----\n"
      f"{tree_grid.best_score_}")

tree_test_pred = tree_grid.predict(X_test)
print(f"-------------Prediction------------\n"
      f"{X_test.head(10)}\n"
      f"{tree_test_pred[0:10]}")

from sklearn.metrics import accuracy_score, confusion_matrix

ac_score = accuracy_score(y_test, tree_test_pred)
print(f"Accuracy score: {ac_score}")

confusion_mat = confusion_matrix(y_test, tree_test_pred)
print(f"Confusion matrix:\n"
      f"{confusion_mat}")

from sklearn import tree

ftf = clf.fit(X_train, y_train)
fig, axes = plt.subplots(nrows=1, ncols=1, figsize=(30, 6), dpi=300)
cn = ['Died', 'Survived']
plot_tree = tree.plot_tree(clf, class_names=cn, filled=True)

fig.savefig('Lab-05/fig.png')