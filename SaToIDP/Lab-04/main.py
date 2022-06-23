import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

titanic = pd.read_csv('Lab-04/titanic.csv')
print(titanic.head())

cols = titanic.columns[:]
colours = ['#eeeeee', '#ff0000']
sns.heatmap(titanic[cols].isnull(), cmap=sns.color_palette(colours))
plt.show()

print(titanic.isnull().any())

for col in titanic.columns:
    pct_missing = titanic[col].isnull().sum()
    pct_missing_mean = np.mean(titanic[col].isnull())
    print(f'{col} - {round(pct_missing)} - {round(pct_missing_mean*100)}%')

titanic = titanic.drop('Cabin', axis=1)
titanic['Age'] = titanic['Age'].fillna(titanic['Age'].mean())
titanic['Embarked'] = titanic['Embarked'].fillna(titanic['Embarked'].mode()[0])

print(titanic.dtypes)

titanic['Sex'] = titanic['Sex'].map({'male': 1, 'female': 0})
titanic['Embarked'] = titanic['Embarked'].map({'S': 2, 'C': 1, 'Q': 0})
titanic = titanic.drop(['Name', 'Ticket'], axis=1)

print(titanic.dtypes)
print(titanic['Survived'].value_counts())

titanic.to_csv('Lab-05/titanic_clear.csv')

indians = pd.read_csv('Lab-04/indians-diabetes.csv')
print(indians.head())

cols = indians.columns[:]
colours = ['#eeeeee', '#ff0000']
sns.heatmap(indians[cols].isnull(), cmap=sns.color_palette(colours))
plt.show()

print(indians.isnull().any())

for col in indians.columns:
    pct_missing = indians[col].isnull().sum()
    pct_missing_mean = np.mean(indians[col].isnull())
    print(f'{col} - {round(pct_missing)} - {round(pct_missing_mean*100)}%')

print(indians.dtypes)