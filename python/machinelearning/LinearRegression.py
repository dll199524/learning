import numpy as np
import matplotlib.pyplot as plt

class LinearRegression(object):
    def __init__(self):
        self.w = 0
        self.b = 0
        self.sqrloss = 0
        self.trainSet = 0
        self.label = 0
        self.learning_rate = None
        self.n_iters = None
        self.lossList = []
    
    def train(self, x, y, method, learning_rate = 0.1, n_iters = 1000):
        if x.ndim < 2:  ##维度
            raise ValueError("x must be 2d array like")
        self.trainSet = x
        self.label = y
        if method.lower() == "formula":
            self.train_formula()
        elif method.lower() == "matrix":
            self.train_matrix()
        elif method.lower() == "gradient":
            self.train_gradient()
        else:
            raise ValueError("method value not found")
        return
    
    def train_formula(self):
        n_samples, n_featrues = self.trainSet.shape()
        x = self.trainSet.flatten()
        y = self.label
        xmean = np.mean(x)
        ymean = np.mean(y)

        self.w = (np.dot(x, y) - n_samples * xmean * ymean) / (np.power(x, 2).sum() - n_samples * xmean **2)
        self.b = ymean - self.w * xmean

        self.sqrloss = np.power((y - np.dot(x, self.w) - self.b), 2).sum()
        return
    
    def train_matrix(self):
        pass

    def train_gradient(self):
        pass