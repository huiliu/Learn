�˲��ִ�����Ҫ��Ϊ����ʾ�� Windows �£�C++ �����ȡ UTF8 �����ļ�����������ն��Ϸ�����������⡣
���������ʵ Python Ҳ�У��� Windows �ϲ�ָ�����룬Python ֱ�� `open` UTF8 ����������ļ�ʱ��ֱ�ӱ���

```python
# data.txt Ϊ UTF8 ����������ļ�
data = open('data.txt', 'r').read()

# ������ʾ��
#
# UnicodeDecodeError: 'gbk' codec can't decode byte 0xab in position 28: illegal multibyte sequence
```