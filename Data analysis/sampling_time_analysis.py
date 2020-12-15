from matplotlib import pyplot as plt
import pandas as pd
from scipy import signal
import numpy as np


df = pd.read_csv('test.out', delimiter='\t', index_col=0)

df_ts = pd.DataFrame(df.index)

# diff() is used to find the first discrete difference of objects over the given axis
df_ts_diffs = df_ts.diff()

df_ts_diffs[10:40].plot()

df_ts_diffs.hist()
