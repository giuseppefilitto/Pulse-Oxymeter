from matplotlib import pyplot as plt
import pandas as pd
from scipy import signal
import numpy as np

df = pd.read_csv('test.out', delimiter='\t', index_col=0)

df.head()

df[30:].plot()
