﻿
函数 整型 入口函数_窗口()   //窗口程序入口

	整型  数组1[5] = {1, 2, 3, 4, 5}
	数组1[2] = 20

	列表循环 整型 i = 0; 数组1  //循环数组成员
		调试输出("测试_数组: ", 数组1[i])
		延时(10)

	整型  数组2[10][10]
	数组2[1][2] = 10
	调试输出(数组2[1][2])


	调试输出("------动态数组------------")
	动态数组<整型>  数组A
	数组A.添加(1)
	数组A.添加(2)
	数组A.添加(3)

	列表循环 整型 i = 0; 数组A
		调试输出(数组A[i])

	整型   size = 数组A.取大小()
	计次循环  整型  i = 0; size
		调试输出(数组A[i])
	

	返回 0
