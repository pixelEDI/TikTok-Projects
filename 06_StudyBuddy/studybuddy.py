#         _          _ ______ _____ _____ 
#        (_)        | |  ____|  __ \_   _|
#   _ __  ___  _____| | |__  | |  | || |  
#  | '_ \| \ \/ / _ \ |  __| | |  | || |  
#  | |_) | |>  <  __/ | |____| |__| || |_ 
#  | .__/|_/_/\_\___|_|______|_____/_____|
#  | |                                    
#  |_|                                    
                             
# www.pixeledi.eu | twitter.com/pixeledi
# CLI Study Buddy | V 1.0 | 09.2022

# 0) Install all Librarys with "pip install -r requirements.txt"
# 1) You need a *.docx File
# 2) A table with 2 columns are needed (see example file)
# 3) Start python program
# 4) Follow the program instruction 
# 5) LEARN!

import docx #use for this library -> pip install python-docx
import random
import pandas as pd
import numpy as np
import os
from colorama import Fore, Back, Style

startASCII = '''  

███████ ████████ ██    ██ ██████  ██    ██     ██████  ██    ██ ██████  ██████  ██    ██ 
██         ██    ██    ██ ██   ██  ██  ██      ██   ██ ██    ██ ██   ██ ██   ██  ██  ██  
███████    ██    ██    ██ ██   ██   ████       ██████  ██    ██ ██   ██ ██   ██   ████   
     ██    ██    ██    ██ ██   ██    ██        ██   ██ ██    ██ ██   ██ ██   ██    ██    
███████    ██     ██████  ██████     ██        ██████   ██████  ██████  ██████     ██ v.1   
                                                                                                                                 
  '''


antwortASCII = '''                                               
    _    _   _  ______        _______  ____ 
   / \  | | / ||___ \ \      / |____ |/ _  |
  / _ \ | |/  |/ ___/\ \ /\ / /  |_  | (_| |
 / ___ \|  /| | (___  \ V  V /  ___| |> _  |
/_/   \_|_/ |_|\____|  \_/\_/  |_____/_/ |_|


'''
os.system('cls||clear')
print(Style.RESET_ALL+ Fore.CYAN)
print(startASCII)
print(Style.RESET_ALL)
inputfile = input("Dataname without extension: ")
firstRow = input("Question (column name): ")
secondRow = input("Answer (column name): ")

filepath = os.getcwd()+"\\"+inputfile+".docx"
document = docx.Document(filepath)
table = document.tables[0]

# Data will be a list of rows represented as dictionaries
# containing each row's data.
data = []
docxList = [] 
keys = None
for i, row in enumerate(table.rows):
    text = (cell.text for cell in row.cells)

    # Establish the mapping based on the first row
    # headers; these will become the keys of our dictionary
    if i == 0:
        keys = tuple(text)
        continue

    # Construct a dictionary for this row, mapping
    # keys to values for this row
    row_data = dict(zip(keys, text))
    #dict
    data.append(row_data)
    #adding each row to a dict and than to a list
    docxList.append(row_data) 
    #print((row_data).values())


random.shuffle(docxList)

for i in docxList:  
    os.system('cls||clear')
    print("-----------------------------------------------------------")
    print(i[firstRow]) 
    print("-----------------------------------------------------------")
    input("")
    print(Style.RESET_ALL+ Fore.GREEN)
    print(antwortASCII)
    if(i[secondRow]!=""):
        print(i[secondRow]) 
    else:   
        print("")

    print()
    print(Style.RESET_ALL+ Fore.YELLOW)
    answerRight = input("(Y)es / (n)o: ").lower()  

    # if answer = n than append to dict and the question comes once again
    # if answer = y go futher on
    if(answerRight=="n"):
        docxList.append(i) 


    print(Style.RESET_ALL)        
    print("------------------------")