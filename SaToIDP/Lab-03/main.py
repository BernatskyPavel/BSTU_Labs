import pandas as pd

titanic = pd.read_csv('Lab-03/titanic.csv')
print(
    f"{titanic.head()}\n"
    f"Average age: {titanic['Age'].mean()}\n"
    f"Average age and fare: {titanic[['Age', 'Fare']].mean()}\n"
    f"Age and Fare description: {titanic[['Age', 'Fare']].describe()}\n"
    f"Age custom description: {titanic['Age'].describe(percentiles=[0.05, 0.2, 0.6, 0.95])}"
)

import seaborn as sns
import matplotlib.pyplot as plt

ax = sns.histplot(data=titanic['Age'], bins=10)
x_mean = titanic["Age"].mean()

ax.axvline(x_mean, color='red')
plt.show()

print(f"Mean age by sex: {titanic[['Age', 'Sex']].groupby('Sex').mean()}\n"
      f"Mean by sex: {titanic.groupby('Sex').mean()}\n"
      f"Passangers in every class: {titanic['Pclass'].value_counts()}\n"
      f"Survivors count: {titanic['Survived'].count()}\n"
      f"Survivors sum: {titanic['Survived'].sum()}")

ay = sns.boxplot(x=titanic["Age"])
plt.show()

at = sns.boxplot(x=titanic['Fare'])
plt.show()