import pandas as pd
import matplotlib.pyplot as plt

bankruptcy = pd.read_csv('Lab-09/bankruptcy.csv')

print(bankruptcy.head())

X = bankruptcy.drop('Bankrupt?', axis=1)
y = bankruptcy['Bankrupt?']

from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

print(f"Inputs X (train/test): {X_train.shape}, {X_test.shape}\n"
      f"Inputs Y (train/test): {y_train.shape}, {y_test.shape}")

from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier

tree_clf = DecisionTreeClassifier(max_depth=4,
                                  random_state=42).fit(X_train, y_train)
svc_clf = SVC(C=0.001, probability=True, random_state=42).fit(X_train, y_train)
rf_clf = RandomForestClassifier(random_state=42).fit(X_train, y_train)

from sklearn import metrics

for model, name in zip([tree_clf, svc_clf, rf_clf], ['DTC', 'SVC', 'RF']):
    y_pred_proba = model.predict_proba(X_test)[::, 1]
    fpr, tpr, _ = metrics.roc_curve(y_test, y_pred_proba)
    auc = metrics.roc_auc_score(y_test, y_pred_proba)
    plt.plot(fpr, tpr, label=f"{name}, auc={auc}")

plt.legend()
plt.show()