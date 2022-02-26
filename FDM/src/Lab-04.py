import mglearn
import matplotlib.pyplot as plt
import numpy as np
from utils.datasets import make_wave, load_extended_california

mglearn.plots.plot_linear_regression_wave()
plt.show()

from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

X, y = make_wave(n_samples=60)
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)
lr = LinearRegression().fit(X_train, y_train)

print(f"""lr.coef_: {lr.coef_}
lr.intercept_: {lr.intercept_}
Правильность на обучающем наборе: {lr.score(X_train, y_train):.2f}
Правильность на тестовом наборе: {lr.score(X_test, y_test):.2f}""")

X, y = load_extended_california()
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
lr = LinearRegression().fit(X_train, y_train)

print(f"""Правильность на обучающем наборе: {lr.score(X_train, y_train):.2f}
Правильность на тестовом наборе: {lr.score(X_test, y_test):.2f}""")

from sklearn.linear_model import Ridge

coefs_ = {}
alphas = [1, 10, 0.1]
symbols = ["s", "^", "v"]
for alpha in alphas:
    ridge = Ridge(alpha=alpha).fit(X_train, y_train)
    coefs_[alpha] = ridge.coef_
    print(f"""Значение параметра alpha: {alpha}
    Правильность на обучающем наборе: {ridge.score(X_train, y_train):.2f}
    Правильность на тестовом наборе: {ridge.score(X_test, y_test):.2f}""")

for alpha, symbol in zip(alphas, symbols):
    plt.plot(coefs_[alpha], symbol, label=f"Гребневая регрессия alpha={alpha}")

plt.plot(lr.coef_, "o", label="Линейная регрессия")
plt.xlabel("Индекс коэффициента")
plt.ylabel("Оценка коэффициента")
plt.hlines(0, 0, len(lr.coef_))
plt.ylim(-25, 25)
plt.legend()
plt.show()

from utils.plots import plot_ridge_n_samples

plot_ridge_n_samples()
plt.show()

from sklearn.linear_model import Lasso

lasso_coefs_ = {}
lasso_alphas = [1, 0.01, 0.0001]
lasso_iters = [100000, 100000, 100000]
lasso_symbols = ["s", "^", "v"]
for alpha, iter in zip(lasso_alphas, lasso_iters):
    lasso = Lasso(alpha=alpha, max_iter=iter).fit(X_train, y_train)
    lasso_coefs_[alpha] = lasso.coef_
    print(
        f"""Правильность на обучающем наборе: {lasso.score(X_train, y_train):.2f}
        Правильность на тестовом наборе: {lasso.score(X_test, y_test):.2f}
        Количество использованных признаков: {np.sum(lasso.coef_ != 0)}""")

for alpha, symbol in zip(lasso_alphas, lasso_symbols):
    plt.plot(lasso_coefs_[alpha], symbol, label=f"Лассо alpha={alpha}")

plt.plot(coefs_[0.1], "o", label="Гребневая регрессия alpha=0.1")
plt.legend(ncol=2, loc=(0, 1.05))
plt.xlabel("Индекс коэффициента")
plt.ylabel("Оценка коэффициента")
plt.ylim(-25, 25)
plt.legend()
plt.show()
