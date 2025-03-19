import numpy as np
from concrete.ml.sklearn import KMeans

# Encrypted threat scores
threat_scores = np.array([[0.3], [0.6], [0.9], [0.1], [0.8]])

# Define secure K-Means
kmeans = KMeans(n_clusters=3, n_bits=5)
kmeans.fit(threat_scores)

# Encrypted cluster assignments
print("Secure Cluster Assignments:", kmeans.labels_)
