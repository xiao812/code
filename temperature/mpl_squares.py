# -*- coding: utf-8 -*-
"""
Created on Mon Apr 13 20:52:41 2020

@author: w
"""

import matplotlib.pyplot as plt 

input_values = [1, 2, 3, 4, 5]
squares =  [1, 3, 9, 16, 25]
plt.plot(input_values, squares, linewidth = 3)

# 设置图表标题，并给坐标轴加上标签
plt.title("Square Numbers", fontsize = 24)
plt.xlabel("Value", fontsize = 14)
plt.ylabel("Square of Value", fontsize = 14)

# 设置刻度标记的大小 
plt.tick_params(axis = 'both', labelsize = 14)

plt.show()