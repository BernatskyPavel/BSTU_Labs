import numpy as np
from sklearn.naive_bayes import BernoulliNB, MultinomialNB, GaussianNB

X = np.array([[0, 1, 0, 1], [1, 0, 1, 1], [0, 0, 0, 1], [1, 0, 1, 0]])
y = np.array([0, 1, 0, 1])

counts = {}
for label in np.unique(y):
    counts[label] = X[y == label].sum(axis=0)

print(f"Частоты признаков:\n{counts}")

clf = BernoulliNB()
clf.fit(X, y)
print(f"BernoulliNB predict:{clf.predict(X[2:3])}")

rng = np.random.RandomState(1)
X = rng.randint(5, size=(6, 100))
y = np.array([1, 2, 3, 4, 5, 6])

clf = MultinomialNB()
clf.fit(X, y)
print(f"MultinomialNB predict:{clf.predict(X[2:3])}")

X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])
Y = np.array([1, 1, 1, 2, 2, 2])

clf = GaussianNB()
clf.fit(X, y)
print(f"GaussianNB predict:{clf.predict([[-0.8, -1]])}")

clf_pf = GaussianNB()
clf_pf.partial_fit(X, Y, np.unique(Y))
print(f"GaussianNB partial predict:{clf.predict([[-0.8, -1]])}")