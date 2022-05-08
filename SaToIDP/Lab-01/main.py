#List
list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print(f"Initial list: {list}, length: {len(list)}\n"
      "Specify element to append:")
list.append(int(input()))
print(f"After append: {list}, length: {len(list)}\n"
      "Specify value to insert:")
value = int(input())
print("Specify where to insert:")
index = int(input())
list.insert(index, value)
print(f"After insert: {list}, length: {len(list)}")
list.extend([13, 15, 14])
print(f"After extend: {list}, length: {len(list)}\n"
      f"list[6]: {list[6]}\nlist[-3]: {list[-3]}\nlist[2:4]: {list[2:4]}")
list.remove(9)
print(f"After remove: {list}, length: {len(list)}\n"
      f"Pop last: {list.pop()}\n"
      f"After pop: {list}, length: {len(list)}\n"
      f"Index of 5: {list.index(5)}")
#Tuple
stuple = tuple("TUPLE")
ntuple = (1, 2, 3)
mtuple = stuple + ntuple
print(f"String tuple:          {stuple}\n"
      f"Numeric tuple:         {ntuple}\n"
      f"Mixed tuple:           {mtuple}\n"
      f"String tuple (sorted): {sorted(stuple)}\n"
      f"Min of numeric tuple:  {min(ntuple)}\n"
      f"Max of numeric tuple:  {max(ntuple)}\n"
      f"Sum of numeric tuple:  {sum(ntuple)}\n"
      f"Len of mixed tuple:    {len(mtuple)}")
a, b, c = ntuple
print(f"Unpacked values of numeric tuple (a,b,c = ntuple):\n"
      f"a:                                 {a}\n"
      f"b:                                 {b}\n"
      f"c:                                 {c}\n"
      f"Slices of tuple:\n"
      f"Skip 3 first elements:             {mtuple[3:]}\n"
      f"Reverse tuple elements:            {mtuple[::-1]}\n"
      f"Range of elements:                 {mtuple[3:6]}\n"
      f"Elements of tuple with even index: {mtuple[::2]}")
#Dictionary
pdict = {1: 'H', 2: 'He', 3: 'Li', 4: 'Na'}
mdict = {"Key": "Value", 1: 2, 'c': ['a', 'b', 'c']}
tdata = [(1, "Hello"), (2, ','), (3, "World")]
tdict = dict(tdata)
ndict = {'name': 'Periodic Table', 'table': pdict}
print(f"Dictionary with int indexes:     {pdict}\n"
      f"Keys:                            {pdict.keys()}\n"
      f"Values:                          {pdict.values()}\n"
      f"Items:                           {pdict.items()}\n"
      f"Dictionary with mixed indexes:   {mdict}\n"
      f"Array of tuples:                 {tdata}\n"
      f"Dictionary from array of tuples: {tdict}\n"
      f"Nested dict:                     {ndict}")
ndict['table'][5] = 'B'
ndict['error'] = 'Error'
ndict['popthis'] = 'OK'
ndict['popitem'] = 'OK2'
print(f"Nested dict after adding element:{ndict}\n"
      f"Added element:                   {ndict['table'][5]}")
del ndict['error']
print(f"Nested dict after removing error:{ndict}\n"
      f"Poped value:                     {ndict.pop('popthis')}\n"
      f"Popped item:                     {ndict.popitem()}")
ndict.clear()
print(f"Nested dict after clear:         {ndict}")
#Set
words = ["hello", "daddy", "hello", "mum"]
wset = set(words)
aset = {1, 2, 4, 5, 8, 16, 1735, 8567, 3145, 223}
bset = {10, 21, 4, 51, 8, 16, 35, 857, 315, 223}
cset = {1, 2, 4, 16}
print(f"Set of words:                      {wset}\n"
      f"Set A:                             {aset}\n"
      f"Set B:                             {bset}\n"
      f"Set C:                             {cset}\n"
      f"Is A and B have no common elements:{aset.isdisjoint(bset)}\n"
      f"Is C a subset of A:                {cset.issubset(aset)}\n"
      f"Is C a subset of B:                {cset.issubset(bset)}\n"
      f"Is A a superset of C:              {aset.issuperset(cset)}\n"
      f"Is A a superset of B:              {aset.issuperset(bset)}\n"
      f"Union of A and B:                  {aset.union(bset)}\n"
      f"Intersection of A and B:           {aset.intersection(bset)}\n"
      f"Unique elements of A from B:       {aset.difference(bset)}\n"
      f"Unique elements of A and B:        {aset.symmetric_difference(bset)}")
