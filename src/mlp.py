import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import cross_val_score
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler
import sys

if len(sys.argv) < 3:
	print(sys.argv)
	print('usage: python3 mlp.py [hidden_layer_sizes] [solver]')
	exit(1)

iris = load_iris()
X, y = iris['data'], iris['target']
scaler = StandardScaler()
X = scaler.fit_transform(X)

parsed = sys.argv[1].split(',')
hls = tuple([int(s) for s in parsed])

mlp = MLPClassifier(hidden_layer_sizes=hls,solver=sys.argv[2],random_state=1)

import warnings
warnings.filterwarnings("ignore")
with open('scores.csv','a') as result_file:
	score = np.mean(cross_val_score(mlp, X, y, cv=3))
	print('\t',sys.argv[1],sys.argv[2],score)
	result_file.write(str(score)+'\n')