
file = open('ScoreCalculator.cpp', 'r', encoding="utf-8")
lines = file.read().splitlines()
file.close()

file = open('ScoreCalculator.cpp', 'w', encoding="utf-8")

print('[INFO] 调参说明:输入浮点数即可调参，输入非浮点数(比如空格)则保持原样')

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
	else:
		file.write(line + '\n')

file.close()