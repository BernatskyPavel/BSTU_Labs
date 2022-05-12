import pandas as pd
import matplotlib.pyplot as plt

dataset = pd.read_csv('Lab-10/Mall_Customers.csv')
X = dataset.iloc[:, [3, 4]].values

from scipy.cluster.hierarchy import linkage, dendrogram

mergings = linkage(X, method='ward')
dendrogram(mergings)

plt.title('Dendrogram')
plt.xlabel('Customers')
plt.ylabel('Euclidian distances')
plt.show()

from sklearn.cluster import AgglomerativeClustering

hc = AgglomerativeClustering(n_clusters=5,
                             affinity='euclidean',
                             linkage='ward')
y_hc = hc.fit_predict(X)

labels = ['Cluster 1', 'Cluster 2', 'Cluster 3', 'Cluster 4', 'Cluster 5']
colors = ['red', 'blue', 'green', 'cyan', 'magenta']

for i in range(5):
    plt.scatter(X[y_hc == i, 0],
                X[y_hc == i, 1],
                s=100,
                c=colors[i],
                label=labels[i])

plt.title('Clusters of customers')
plt.xlabel('Annual Income (k$)')
plt.ylabel('Spending Score (1-100)')
plt.legend()
plt.show()

from sklearn.cluster import KMeans

wcss = []
for i in range(1, 11):
    kmeans = KMeans(n_clusters=i, init='k-means++', random_state=42)
    kmeans.fit(X)
    wcss.append(kmeans.inertia_)
plt.plot(range(1, 11), wcss)
plt.title('The Elbow Method')
plt.xlabel('Number of clusters')
plt.ylabel('WCSS')
plt.show()

kmeans = KMeans(n_clusters=5, init='k-means++', random_state=42)
y_kmeans = kmeans.fit_predict(X)

for i in range(5):
    plt.scatter(X[y_hc == i, 0],
                X[y_hc == i, 1],
                s=100,
                c=colors[i],
                label=labels[i])
plt.scatter(kmeans.cluster_centers_[:, 0],
            kmeans.cluster_centers_[:, 1],
            s=300,
            c='yellow',
            label='Centroids')
plt.title('Clusters of customers')
plt.xlabel('Annual Income (k$)')
plt.ylabel('Spending Score (1-100)')
plt.legend()
plt.show()