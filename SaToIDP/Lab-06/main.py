import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

titanic = pd.read_csv('Lab-06/titanic_clear.csv')
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

from sklearn.neighbors import KNeighborsClassifier

clf = KNeighborsClassifier()

knn_model = clf.fit(X_train, y_train)
print(f"First KNN model train score: {knn_model.score(X_train, y_train)}\n"
      f"First KNN model test score: {knn_model.score(X_test, y_test)}")

cv_score = cross_val_score(clf, X_train, y_train, cv=5)
print(f"KNN score: {cv_score}\n"
      f"KNN mean score: {np.mean(cv_score)}")

from sklearn.model_selection import GridSearchCV

knn_params = {'n_neighbors': range(5, 30, 1)}
knn_grid = GridSearchCV(clf, knn_params, cv=5, n_jobs=-1)
knf = knn_grid.fit(X_train, y_train)

print(f"TGF: {knf}\n"
      f"-----Best K-neighbors parameters-----\n"
      f"{knn_grid.best_params_}\n"
      f"-----Best K-neighbors score-----\n"
      f"{knn_grid.best_score_}")

knn_test_pred = knn_grid.predict(X_test)
print(f"-------------Prediction------------\n"
      f"{X_test.head(10)}\n"
      f"{knn_test_pred[0:10]}")

from sklearn.metrics import accuracy_score, confusion_matrix

ac_score = accuracy_score(y_test, knn_test_pred)
print(f"Accuracy score: {ac_score}")

confusion_mat = confusion_matrix(y_test, knn_test_pred)
print(f"Confusion matrix:\n"
      f"{confusion_mat}")

from sklearn.svm import SVC

clf = SVC(kernel='rbf', C=1)

svc_model = clf.fit(X_train, y_train)
print(f"First SVC model train score: {svc_model.score(X_train, y_train)}\n"
      f"First SVC model test score: {svc_model.score(X_test, y_test)}")

cv_score = cross_val_score(clf, X_train, y_train, cv=5)
print(f"SVC score: {cv_score}\n"
      f"SVC mean score: {np.mean(cv_score)}")

from sklearn.model_selection import GridSearchCV

svc_params = {'C': [0.5, 1], 'gamma': [0.2, 0.6, 1]}
svc_grid = GridSearchCV(clf, svc_params, cv=5, n_jobs=-1)
svf = svc_grid.fit(X_train, y_train)

print(f"SVF: {svf}\n"
      f"-----Best support vector machine parameters-----\n"
      f"{svc_grid.best_params_}\n"
      f"-----Best support vector machine score-----\n"
      f"{svc_grid.best_score_}")

svc_test_pred = svc_grid.predict(X_test)
print(f"-------------Prediction------------\n"
      f"{X_test.head(10)}\n"
      f"{svc_test_pred[0:10]}")

from sklearn.metrics import accuracy_score, confusion_matrix

ac_score = accuracy_score(y_test, svc_test_pred)
print(f"Accuracy score: {ac_score}")

confusion_mat = confusion_matrix(y_test, svc_test_pred)
print(f"Confusion matrix:\n"
      f"{confusion_mat}")