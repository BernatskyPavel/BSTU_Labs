import numpy as np
from sklearn.datasets import make_blobs
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import MinMaxScaler, PolynomialFeatures


def make_forge():
    X, y = make_blobs(centers=2, random_state=4, n_samples=30)
    y[np.array([7, 27])] = 0
    mask = np.ones(len(X), dtype=np.bool)
    mask[np.array([0, 1, 5, 26])] = 0
    X, y = X[mask], y[mask]
    return X, y


def make_wave(n_samples=100):
    rnd = np.random.RandomState(42)
    x = rnd.uniform(-3, 3, size=n_samples)
    y_no_noise = np.sin(4 * x) + x
    y = (y_no_noise + rnd.normal(size=len(x))) / 2
    return x.reshape(-1, 1), y


def load_extended_california():
    california = fetch_california_housing()
    X = california.data

    X = MinMaxScaler().fit_transform(california.data)
    X = PolynomialFeatures(degree=2, include_bias=False).fit_transform(X)
    return X, california.target