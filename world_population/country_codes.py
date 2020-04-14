# -*- coding: utf-8 -*-
"""
Created on Tue Apr 14 22:38:30 2020

@author: w
"""

from pygal_maps_world.i18n import COUNTRIES 

def get_country_code(country_name): 
    for code, name in COUNTRIES.items():
        if name == country_name:
            return code 
    return None 

print(get_country_code('Andorra'))