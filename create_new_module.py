
### 使用python3 运行

module_name = input('name :')
print(module_name)

module_name = module_name.replace(' ','')

### h
def creat_head():
  f = open("./include/"+module_name+'.h','w+',1024,'utf-8')
  f.write(' \n\
#pragma once \n\
\n\
')
  f.close()
  return

### cc
def creat_cc():
  f = open("./src/"+module_name+'.cc','w+',1024,'utf-8')
  f.write('\n\
#include \"include/'+module_name+'.h\" \n'
)
  f.close()
  return

### test
def creat_test():
  f = open("./test/"+module_name+'_test.cc','w+',1024,'utf-8')
  f.write('\n\
#include \"include/'+module_name+'.h\" \n'
+'#include <gtest/gtest.h> \n')
  f.close()
  return

creat_head()
creat_cc()
creat_test()

