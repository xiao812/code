# -*- coding: utf-8 -*-
"""
Created on Mon Apr 13 21:20:42 2020

@author: w
"""

import matplotlib.pyplot as plt 
from RandomWalk import RandomWalk 

# 只要程序处于活动状态，就不断地模拟随机漫步 
while True: 
    # 创建一个RandowWalk实例, 并将其包含的点都绘制出来
    rw = RandomWalk(200000)
    rw.fill_walk()
    
    # 设置绘图窗口的尺寸 
    plt.figure(figsize=(25, 15))
    point_numbers = list(range(rw.num_points))
    plt.scatter(rw.x_values, rw.y_values, c = point_numbers, cmap = plt.cm.Blues, edgecolor = 'none', s = 3)
    # 突出起点和终点 
    plt.scatter(0, 0, c = 'green', edgecolors='none', s = 10)
    plt.scatter(rw.x_values[-1], rw.y_values[-1], c = 'red', edgecolors = 'none', s = 10)
    
    plt.axes().get_xaxis().set_visible(False)
    plt.axes().get_yaxis().set_visible(False)
    plt.show()
    
    keep_running = input("Make another walk? (y/n): ")
    if keep_running == 'n':
        break