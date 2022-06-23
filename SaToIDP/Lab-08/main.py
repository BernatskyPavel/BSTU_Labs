import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score

data = pd.read_csv('Lab-08/reklama.csv')
print(data.head())

data = data.drop(['Unnamed: 0'], axis=1)
hm = sns.heatmap(data.corr(), cbar=True, annot=True)
plt.show()

g = sns.PairGrid(data)
g.map_diag(sns.histplot)
g.map_offdiag(sns.scatterplot)
plt.show()

sns.scatterplot(data=data, x="TV", y="sales")
plt.show()

X = data['TV'].values.reshape(-1, 1)
y = data['sales'].values.reshape(-1, 1)

reg = LinearRegression().fit(X, y)

print(
    f"Coefficients: {reg.coef_}\n"
    f"Intercept: {reg.intercept_}\n"
    f"The linear model is: Y = {reg.intercept_[0]:.5} + {reg.coef_[0][0]:.5}X")

predictions = reg.predict(X)

plt.figure(figsize=(16, 8))
plt.scatter(
    data['TV'],
    data['sales'],
)
plt.plot(data['TV'], predictions, c='red', linewidth=2)
plt.xlabel("Money spent on TV ads ($)")
plt.ylabel("Sales ($)")
plt.show()

print(f"Regression score: {reg.score(X, y, sample_weight=None)}")

Xs = data.drop('sales', axis=1)
ys = data['sales'].values.reshape(-1, 1)

reg = LinearRegression().fit(Xs, ys)
print(
    f"Coefficients: {reg.coef_}\n"
    f"Intercept: {reg.intercept_}\n"
    f"The linear model is: Y = {reg.intercept_[0]:.5} + {reg.coef_[0][0]:.5}*TV + {reg.coef_[0][1]:.5}*radio + {reg.coef_[0][2]:.5}*newspaper\n"
    f"Coefficient of determination: {reg.score(Xs, ys)}")
