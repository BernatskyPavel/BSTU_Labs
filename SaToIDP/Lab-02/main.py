import numpy as np

rng = np.random.default_rng(seed=42)
a = np.array([1, 6, 3, 4, 5, 6, 7, 8, 6, 10])
b = rng.integers(low=1, high=20, size=10)

print(f"a:        {a}\n"
      f"b:        {b}\n"
      f"a+b:      {a+b}\n"
      f"a-b:      {a-b}\n"
      f"a*b:      {a*b}")

d = np.arange(16)
_d = d.reshape(4, 4)
k, p = np.hsplit(_d, 2)
print(f"d:        {d}\n"
      f"2D array: \n{_d}\n"
      f"k:        \n{k}\n"
      f"p:        \n{p}\n"
      f"k length: {k.size}\n"
      f"p min:    {p.min()}\n"
      f"p max:    {p.max()}\n"
      f"p mean:   {p.mean()}\n"
      f"6es in a: {np.where(a==6)[0]}")

import pandas as pd

s = pd.Series(a[:3], ['a', 'b', 'c'])
img1 = pd.Series([4.485, 10.020, 6.150], ['Feb', 'Mar', 'Apr'])
img2_data = {
    'Key1': [1, 2, 3],
    'Key2': ['Hank', 'Steve', 'Lisa'],
    'Key3': [1.2, 3.1, 3.1]
}
img2 = pd.DataFrame(img2_data)
img3_data = {
    'state': ['NY', 'TX', 'FL'],
    'color': ['blue', 'green', 'red'],
    'food': ['Steak', 'Lamb', 'Mango']
}
img3 = pd.DataFrame(img3_data, ['Jane', 'Niko', 'Aaron'])

print(f"s:      \n{s}\n"
      f"s+b:    \n{s+b[:3]}\n"
      f"s-b:    \n{s-b[:3]}\n"
      f"s/b:    \n{s/b[:3]}\n"
      f"s*b:    \n{s*b[:3]}\n"
      f"log(s): \n{np.log(s)}\n"
      f"img1:   \n{img1}\n"
      f"img2:   \n{img2}\n"
      f"img2*:  \n{img2.drop(columns='Key1')}\n"
      f"img3:   \n{img3}\n"
      f"img3*:  \n{img3.get('food')}\n")
