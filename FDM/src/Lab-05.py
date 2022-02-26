import mglearn
import matplotlib.pyplot as plt

from sklearn.linear_model import LogisticRegression
from sklearn.svm import LinearSVC
from utils.datasets import make_forge

X, y = make_forge()
fig, axes = plt.subplots(1, 2, figsize=(10, 3))

for model, ax in zip([LinearSVC(max_iter=10000), LogisticRegression()], axes):
    clf = model.fit(X, y)
    mglearn.plots.plot_2d_separator(clf, X, eps=0.5, ax=ax, alpha=0.7)
    mglearn.discrete_scatter(X[:, 0], X[:, 1], y, ax=ax)
    ax.set_title(f"{clf.__class__.__name__}")
    ax.set_xlabel("Признак 0")
    ax.set_xlabel("Признак 1")

axes[0].legend()
plt.show()

from utils.plots import plot_linear_svc_regularization

plot_linear_svc_regularization()
plt.show()

from sklearn.datasets import load_breast_cancer

cancer = load_breast_cancer()
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(cancer.data,
                                                    cancer.target,
                                                    stratify=cancer.target,
                                                    random_state=42)

for C, marker in zip([1, 100, 0.001], ["o", "^", "v"]):
    lr = LogisticRegression(
        C=C,
        max_iter=10000,
        solver="liblinear",
    ).fit(X_train, y_train)
    print(
        f"""Правильность на обучении логрегрессии с C={C:.3f}: {lr.score(X_train, y_train):.3f}
        Правильность на обучении логрегрессии с C={C:.3f}: {lr.score(X_test, y_test):.3f}"""
    )
    plt.plot(lr.coef_.T, marker, label=f"C={C:.3f}")

plt.xticks(range(cancer.data.shape[1]),
           cancer.feature_names,
           rotation=90,
           fontsize="xx-small")
plt.hlines(0, 0, cancer.data.shape[1])
plt.ylim(-5, 5)
plt.xlabel("Индекс коэффициента")
plt.xlabel("Оценка коэффициента")
plt.legend()
plt.show()

for C, marker in zip([1, 100, 0.001], ["o", "^", "v"]):
    lr_l1 = LogisticRegression(C=C,
                               penalty="l1",
                               solver="liblinear",
                               max_iter=10000).fit(X_train, y_train)
    print(
        f"""Правильность на обучении логрегрессии l1 с C={C:.3f}: {lr_l1.score(X_train, y_train):.3f}
        Правильность на обучении логрегрессии l1 с C={C:.3f}: {lr_l1.score(X_test, y_test):.3f}"""
    )
    plt.plot(lr_l1.coef_.T, marker, label=f"C={C:.3f}")

plt.xticks(range(cancer.data.shape[1]),
           cancer.feature_names,
           rotation=90,
           fontsize="xx-small")
plt.hlines(0, 0, cancer.data.shape[1])
plt.ylim(-5, 5)
plt.xlabel("Индекс коэффициента")
plt.xlabel("Оценка коэффициента")
plt.legend(loc=3)
plt.show()
