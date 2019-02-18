/*
2019/2/18
任务记录：
确认所有文件状态，是否已完成、是否需要修改

S_ByteAnalysis.cpp .h 更改了帧确认函数的名字
S_ByteAnalysis.cpp .h 部分未完成   工作优先级高

S_ServiceSender.cpp .h 未完成  工作优先级高

S_TimerUs.cpp 更改书写方式 逻辑不变
S_TimerUs.h 删除不必要的变量成员

S_Vector.cpp .h 增加一个互斥量

S_ThreadWatchDog.cpp .h
S_ThreadWatchDogWork.cpp .h     暂时使用一个Vector存储运行中线程编号    使用一个看门狗队列   看门狗线程只需要检查队列喂狗情况即可
								更改为 喂狗为TRUE    FALSE为喂狗失败

未来版本：
可直接修改各种表以增加模块或者其他号
增加判断总表长度进而轮询以达到上个功能


























*/