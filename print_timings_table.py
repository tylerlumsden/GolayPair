import pandas as pd

class0 = open("timings/classgeneration-0", "r")
class1 = open("timings/classgeneration-1", "r")
matching = open("timings/matching", "r")
order = open("timings/order", "r")
total = open("timings/total", "r")
pairs = open("timings/pairs", "r")

class0 = class0.read()
class1 = class1.read()
matching = matching.read()
order = order.read()
total = total.read()
pairs = pairs.read()

if class0 == '':  
  class0 = "N/A"
else: 
  class0 = float(class0)
  
if class1 == '':
  class1 = "N/A"
else:
  class1 = float(class1)

if matching == '':
  matching = "N/A"
else:
  matching = float(matching)

if order == '':
  order = "N/A"
else:
  order = int(order)
if total == "":
  total = "N/A"
else:
  total = float(total)
if pairs == "":
  pairs = "N/A"
else:
  pairs = int(pairs)



pd.set_option("display.max_colwidth",5)
pd.set_option('display.width', 1000)
df = pd.read_csv('results.csv')

new= pd.DataFrame({'Order':order, 'Pairs':pairs, 'Classes-0':str(class0) + "s", 'Classes-1':str(class1) + "s", 'Matching':str(matching) + "s", 'Total':str(total) + "s"}, index=[0])
df2 = pd.concat([new,df.loc[:]]).reset_index(drop=True)

print(df2.to_string(index=False))

df2.to_csv('results.csv', index=False)

