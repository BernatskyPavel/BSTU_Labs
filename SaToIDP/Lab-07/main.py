import pandas as pd
import numpy as np

indians = pd.read_csv('Lab-07/indians-diabetes.csv')

print(indians.head())

feature_cols = [
    'Pregnancies', 'Glucose', 'BloodPressure', 'Insulin', 'BMI',
    'DiabetesPedigreeFunction', 'Age'
]

X = indians[feature_cols]
y = indians['Outcome']

from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(X,
                                                    y,
                                                    test_size=0.25,
                                                    random_state=0)
print(f"Inputs X (train/test): {X_train.shape}, {X_test.shape}\n"
      f"Inputs Y (train/test): {y_train.shape}, {y_test.shape}")

from sklearn.linear_model import LogisticRegression

logreg = LogisticRegression(max_iter=150).fit(X_train, y_train)

print(f"Logreg score: {logreg.score(X, y)}")

y_pred = logreg.predict(X_test)

from sklearn import metrics

cnf_matrix = metrics.confusion_matrix(y_test, y_pred)
print(f"Confusion matrix:\n"
      f"{cnf_matrix}")

import matplotlib.pyplot as plt
import seaborn as sns

class_names = [0, 1]
fig, ax = plt.subplots()
tick_marks = np.arange(len(class_names))
plt.xticks(tick_marks, class_names)
plt.yticks(tick_marks, class_names)

sns.heatmap(pd.DataFrame(cnf_matrix), annot=True, cmap="YlGnBu", fmt="g")
ax.xaxis.set_label_position("top")
plt.tight_layout()
plt.title("Confusion matrix", y=1.1)
plt.ylabel("Actual label")
plt.xlabel("Predicted label")
plt.show()

print(f"Accuracy: {metrics.accuracy_score(y_test, y_pred)}\n"
      f"Precision: {metrics.precision_score(y_test, y_pred)}\n"
      f"Recall: {metrics.recall_score(y_test, y_pred)}")

y_pred_proba = logreg.predict_proba(X_test)[::, 1]
fpr, tpr, _ = metrics.roc_curve(y_test, y_pred_proba)
auc = metrics.roc_auc_score(y_test, y_pred_proba)
plt.plot(fpr, tpr, label=f"data 1, auc={auc}")
plt.legend(loc=4)
plt.show()

model = LogisticRegression(C=10.0, max_iter=150,
                           random_state=0).fit(X_train, y_train)
print(f"Model score: {model.score(X, y)}")

y_pred = model.predict(X_test)
print(f"Accuracy: {metrics.accuracy_score(y_test, y_pred)}\n"
      f"Precision: {metrics.precision_score(y_test, y_pred)}\n"
      f"Recall: {metrics.recall_score(y_test, y_pred)}\n"
      f"Intercept: {model.intercept_}\n"
      f"Recall: {model.coef_}")

from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier(n_neighbors=8).fit(X_train, y_train)
svc = SVC(C=1, probability=True).fit(X_train, y_train)
tree = DecisionTreeClassifier(max_depth=5).fit(X_train, y_train)

for model, name in zip([logreg, knn, svc, tree],
                       ['LogReg', 'KNN', 'SVC', 'DTC']):
    y_pred_proba = model.predict_proba(X_test)[::, 1]
    fpr, tpr, _ = metrics.roc_curve(y_test, y_pred_proba)
    auc = metrics.roc_auc_score(y_test, y_pred_proba)
    plt.plot(fpr, tpr, label=f"{name}, auc={auc}")

plt.legend(loc=4)
plt.show()
