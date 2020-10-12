此部分代码主要是为了演示在 Windows 下，C++ 程序读取 UTF8 数据文件，并输出到终端上发生乱码的问题。
这个问题其实 Python 也有，在 Windows 上不指定编码，Python 直接 `open` UTF8 编码的数据文件时会直接报错。

```python
# data.txt 为 UTF8 编码的数据文件
data = open('data.txt', 'r').read()

# 错误提示：
#
# UnicodeDecodeError: 'gbk' codec can't decode byte 0xab in position 28: illegal multibyte sequence
```