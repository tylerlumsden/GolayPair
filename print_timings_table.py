import pandas as pd
import sys

format = "{n:.2f}"

timings = []

for arg in sys.argv[1:]:
    timings.append(arg)


pd.set_option("display.max_colwidth",5)
pd.set_option('display.width', 1000)
df = pd.read_csv('results.csv')

new= pd.DataFrame({'Order':timings[0], 'CandidatesA':timings[1], 'CandidatesB':timings[2], 'Pairs':timings[3], 'Classes':str(timings[4]) + "s", 'Matching':str(timings[5]) + "s", 'Total':str(timings[6]) + "s"}, index=[0])
df2 = pd.concat([new,df.loc[:]]).reset_index(drop=True)

print(df2.to_string(index=False))

df2.to_csv('results.csv', index=False)

