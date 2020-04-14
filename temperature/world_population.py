# -*- coding: utf-8 -*-
"""
Created on Tue Apr 14 22:25:21 2020

@author: w
"""

import json 
from test import get_country_code 

# 将数据加载到一个列表中
filename = 'population_data.json'
with open(filename) as f: 
    pop_data = json.load(f)
    
# 打印每个国家2010年的人口 
for pop_dict in pop_data: 
    if pop_dict['Year'] == '2010': 
        country_name = pop_dict['Country Name']
        population = int(float(pop_dict['Value']))
        code = get_country_code(country_name)
        if code: 
            print(code + ": " +str(population))
        else: 
            print('ERROR - ' + country_name)
