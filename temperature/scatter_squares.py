# -*- coding: utf-8 -*-
"""
Created on Mon Apr 13 20:58:59 2020

@author: w
"""

import matplotlib.pyplot as plt 

x_values = list(range(1, 1001))
y_values = [x**2 for x in x_values]
plt.scatter(x_values, y_values, c = y_values, cmap = plt.cm.Blues, edgecolor = 'none', s = 1)

# 设置图标标题并给坐标轴加上标签
plt.title("Square Numbers", fontsize = 24)
plt.xlabel("Value", fontsize = 14)
plt.ylabel("Square of Value", fontsize = 14)

# 设置刻度标记的大小
plt.axis([0, 1100, 0, 1100000])

plt.savefig('squares_plt.png', bbox_inches='tight')