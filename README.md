# botzone-CSMahjong
A bot of Chinese Standard Mahjong in botzone

#### 关于几个地方的说明:

1. `./project/src`中存放着我们的源码。
2. 想要在本地进行测试的话，请修改`./project/main_local.cpp`，然后就可以编译并进行测试了。
3. 想要上传到botzone的话，请先使用`./project/src/generateAM.bat`，然后将同目录下的`./main.am.cpp`上传即可。需要注意的一点是，仅修改`main_local.cpp`**不会**使bot有所改变，需要修改的是`main.cpp`！
4. Visual Studio的项目文件已经被移动到`project/VS_projectfile_tmp`下。

---

改为陈列`material`文件夹中的内容及其相关说明

```cpp
- Botzone2020_Mahjong.pptx		// 官方PPT
- Building a Computer Mahjong Player Based on Monte Carlo Simulation and Opponent Models.pdf
- 资料导航.md					 // 一些关于国标麻将及botzone的资料
- 国标麻将规则笔记_wr786.md
```