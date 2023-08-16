# LLanguage

包含L脚本语言解释引擎的核心代码
和两个扩展对象OS,Socket的实现

### build on linux

```shell
apt install make g++

git clone https://github.com/zhaoliangcn/llanguage.git --recursive

cd llanguage

make clean && make

make bin && make test 

cd bin

scriptengine ../script/hello.scp
```


