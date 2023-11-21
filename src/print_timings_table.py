import pandas as pd
import sys

format = "{n:.2f}"

timings = []

for arg in sys.argv[1:]:
    timings.append(arg)


pd.set_option("display.max_colwidth",5)
pd.set_option('display.width', 1000)
df = pd.read_csv('results.csv')

new= pd.DataFrame({'Order':timings[0], 'Compress':timings[1], 'CandidatesA':timings[2], 'CandidatesB':timings[3], 'Pairs':timings[4], 'Candidates':str(timings[5]) + "s", 'UncompressedPairs':timings[6], 'Uncompression':str(timings[7]) + "s", 'Total':str(timings[8]) + "s"}, index=[0])
df2 = pd.concat([new,df.loc[:]]).reset_index(drop=True)

print(df2.to_string(index=False))

df2.to_csv('results.csv', index=False)

