import pandas as pd
import sys

file1 = input('x軸に入れるデータのファイル名(基本CH1のデータ。〇〇.txt)>> ')
file2 = input('y軸に入れるデータのファイル名(基本CH2のデータ。〇〇.txt)>> ')

df_ch1 = pd.read_csv(file1, header=None)
df_ch2 = pd.read_csv(file2, header=None)

f = pd.concat([df_ch1, df_ch2], axis=1)

file3 = input('書き込みたいファイル名(〇〇.txt)>> ')
f.to_csv(file3, index=False, header=None, sep=' ')

print('Writing Completed')
