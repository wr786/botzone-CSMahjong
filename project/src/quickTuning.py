import os

file = open('ScoreCalculator.cpp', 'r', encoding="utf-8")
lines = file.read().splitlines()
file.close()

file = open('ScoreCalculator_tmp.cpp', 'w', encoding="utf-8")

print('[INFO] 调参说明:输入浮点数即可调参，输入非浮点数(比如空格)则保持原样')
print('[INFO] 切换是否使用shanten计算手牌分时，输入r代表用原本的计算方式，输入s代表使用shanten，输入其它则保持原样')

for line in lines:
	if line.find("double k") != -1:
		startPos = line.find('=') + 1
		endPos = line.find(';')
		print(f'[INFO] double k{line[startPos-2:endPos]}')
		inputStr = input('>>> ')
		try:	# 如果输入非数字，则保持原样
			aug = float(inputStr)
			file.write(line[:startPos] + str(aug) + line[endPos:] + '\n')
		except ValueError:
			file.write(line + '\n')
	# elif line.find("return result") != -1:
	# 	startPos = line.find('return result')
	# 	endPos = line.find('* c;')
	# 	print(f'[INFO] Using {line[startPos+7:endPos]}')
	# 	inputStr = input('>>> ')
	# 	if inputStr.strip() == 'r':
	# 		file.write(line[:startPos+13] + " * c;\n")
	# 	elif inputStr.strip() == 's':
	# 		file.write(line[:startPos+13] + "Shanten * c;\n")
	# 	else:
	# 		file.write(line + '\n')
	else:
		file.write(line + '\n')

file.close()

os.remove('ScoreCalculator.cpp')
os.rename('ScoreCalculator_tmp.cpp', 'ScoreCalculator.cpp')