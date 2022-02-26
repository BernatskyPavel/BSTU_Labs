from matplotlib import pyplot as plt
from mglearn import discrete_scatter
import numpy as np
from sklearn.datasets import make_blobs
from sklearn.decomposition import NMF
from sklearn.exceptions import ConvergenceWarning
from sklearn.linear_model import LinearRegression, Ridge
from sklearn.metrics import euclidean_distances
from sklearn.model_selection import KFold, learning_curve
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import LinearSVC
from sklearn.utils._testing import ignore_warnings
from utils.datasets import make_forge, load_extended_california


def plot_knn_classification(n_neighbors=1):
    X, y = make_forge()

    X_test = np.array([[8.2, 3.66214339], [9.9, 3.2], [11.2, .5]])
    dist = euclidean_distances(X, X_test)
    closest = np.argsort(dist, axis=0)

    for x, neighbors in zip(X_test, closest.T):
        for neighbor in neighbors[:n_neighbors]:
            plt.arrow(x[0],
                      x[1],
                      X[neighbor, 0] - x[0],
                      X[neighbor, 1] - x[1],
                      head_width=0,
                      fc='k',
                      ec='k')

    clf = KNeighborsClassifier(n_neighbors=n_neighbors).fit(X, y)
    test_points = discrete_scatter(X_test[:, 0],
                                   X_test[:, 1],
                                   clf.predict(X_test),
                                   markers="*")
    training_points = discrete_scatter(X[:, 0], X[:, 1], y)
    plt.legend(
        training_points + test_points,
        ["training class 0", "training class 1", "test pred 0", "test pred 1"])


def plot_learning_curve(est, X, y):
    training_set_size, train_scores, test_scores = learning_curve(
        est,
        X,
        y,
        train_sizes=np.linspace(.1, 1, 20),
        cv=KFold(20, shuffle=True, random_state=1))
    estimator_name = est.__class__.__name__
    line = plt.plot(training_set_size,
                    train_scores.mean(axis=1),
                    '--',
                    label="training " + estimator_name)
    plt.plot(training_set_size,
             test_scores.mean(axis=1),
             '-',
             label="test " + estimator_name,
             c=line[0].get_color())
    plt.xlabel('Training set size')
    plt.ylabel('Score (R^2)')
    plt.ylim(0, 1.1)


def plot_ridge_n_samples():
    X, y = load_extended_california()

    plot_learning_curve(Ridge(alpha=1), X, y)
    plot_learning_curve(LinearRegression(), X, y)
    plt.legend(loc=(0, 1.05), ncol=2, fontsize=11)


def plot_linear_svc_regularization():
    X, y = make_blobs(centers=2, random_state=4, n_samples=30)
    fig, axes = plt.subplots(1, 3, figsize=(12, 4))

    # a carefully hand-designed dataset lol
    y[7] = 0
    y[27] = 0
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5

    for ax, C in zip(axes, [1e-2, 10, 1e3]):
        discrete_scatter(X[:, 0], X[:, 1], y, ax=ax)

        svm = LinearSVC(C=C, tol=0.00001, dual=False).fit(X, y)
        w = svm.coef_[0]
        a = -w[0] / w[1]
        xx = np.linspace(6, 13)
        yy = a * xx - (svm.intercept_[0]) / w[1]
        ax.plot(xx, yy, c='k')
        ax.set_xlim(x_min, x_max)
        ax.set_ylim(y_min, y_max)
        ax.set_xticks(())
        ax.set_yticks(())
        ax.set_title("C = %f" % C)
    axes[0].legend(loc="best")


@ignore_warnings(category=ConvergenceWarning)
def plot_nmf_illustration():
    rnd = np.random.RandomState(5)
    X_ = rnd.normal(size=(300, 2))
    # Add 8 to make sure every point lies in the positive part of the space
    X_blob = np.dot(X_, rnd.normal(size=(2, 2))) + rnd.normal(size=2) + 8

    with ignore_warnings(category=ConvergenceWarning):
        nmf = NMF(random_state=0, init=None)
    nmf.fit(X_blob)
    X_nmf = nmf.transform(X_blob)

    fig, axes = plt.subplots(1, 2, figsize=(15, 5))

    axes[0].scatter(X_blob[:, 0],
                    X_blob[:, 1],
                    c=X_nmf[:, 0],
                    linewidths=0,
                    s=60,
                    cmap='viridis')
    axes[0].set_xlabel("feature 1")
    axes[0].set_ylabel("feature 2")
    axes[0].set_xlim(0, 12)
    axes[0].set_ylim(0, 12)
    axes[0].arrow(0,
                  0,
                  nmf.components_[0, 0],
                  nmf.components_[0, 1],
                  width=.1,
                  head_width=.3,
                  color='k')
    axes[0].arrow(0,
                  0,
                  nmf.components_[1, 0],
                  nmf.components_[1, 1],
                  width=.1,
                  head_width=.3,
                  color='k')
    axes[0].set_aspect('equal')
    axes[0].set_title("NMF with two components")

    # second plot
    nmf = NMF(random_state=0, n_components=1, init="nndsvdar", max_iter=100000)
    nmf.fit(X_blob)

    axes[1].scatter(X_blob[:, 0],
                    X_blob[:, 1],
                    c=X_nmf[:, 0],
                    linewidths=0,
                    s=60,
                    cmap='viridis')
    axes[1].set_xlabel("feature 1")
    axes[1].set_ylabel("feature 2")
    axes[1].set_xlim(0, 12)
    axes[1].set_ylim(0, 12)
    axes[1].arrow(0,
                  0,
                  nmf.components_[0, 0],
                  nmf.components_[0, 1],
                  width=.1,
                  head_width=.3,
                  color='k')

    axes[1].set_aspect('equal')
    axes[1].set_title("NMF with one component")