import numpy as np
from sklearn.datasets import load_wine
from sklearn.model_selection import cross_val_score
from sklearn.neural_network import MLPClassifier
import sys

if len(sys.argv) < 3:
	print('usage: python3 mlp.py [hidden_layer_sizes] [solver]')
	exit(1)
else:
	print(sys.argv)

wine = load_wine()
X, y = wine['data'], wine['target']

parsed = sys.argv[1].split(',')
hls = tuple([int(s) for s in parsed])

mlp = MLPClassifier(hidden_layer_sizes=hls,solver=sys.argv[2],random_state=1)

import warnings
warnings.filterwarnings("ignore")
with open('scores.csv','a') as result_file:
	result_file.write(str(np.mean(cross_val_score(mlp, X, y, cv=3)))+'\n')